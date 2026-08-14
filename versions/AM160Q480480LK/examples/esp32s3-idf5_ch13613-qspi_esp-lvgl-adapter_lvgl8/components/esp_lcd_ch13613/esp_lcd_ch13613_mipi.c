/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "soc/soc_caps.h"

#if SOC_MIPI_DSI_SUPPORTED
#include "esp_check.h"
#include "esp_log.h"
#include "esp_lcd_panel_commands.h"
#include "esp_lcd_panel_interface.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_mipi_dsi.h"
#include "esp_lcd_panel_vendor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_lcd_ch13613.h"
#include "esp_lcd_ch13613_interface.h"

typedef struct {
    esp_lcd_panel_io_handle_t io;
    int reset_gpio_num;
    uint8_t madctl_val; // save current value of LCD_CMD_MADCTL register
    uint8_t colmod_val; // save surrent value of LCD_CMD_COLMOD register
    ch13613_panel_context_t panel_ctx; // runtime context shared with public API
    const ch13613_lcd_init_cmd_t *init_cmds;
    uint16_t init_cmds_size;
    struct {
        unsigned int reset_level: 1;
    } flags;
    // To save the original functions of MIPI DPI panel
    esp_err_t (*del)(esp_lcd_panel_t *panel);
    esp_err_t (*init)(esp_lcd_panel_t *panel);
} ch13613_panel_t;

static const char *TAG = "ch13613_mipi";

static esp_err_t panel_ch13613_del(esp_lcd_panel_t *panel);
static esp_err_t panel_ch13613_init(esp_lcd_panel_t *panel);
static esp_err_t panel_ch13613_reset(esp_lcd_panel_t *panel);
static esp_err_t ch13613_mipi_apply_brightness(void *driver_data, uint8_t brightness_percent);

esp_err_t esp_lcd_new_panel_ch13613_mipi(const esp_lcd_panel_io_handle_t io, const esp_lcd_panel_dev_config_t *panel_dev_config,
                                        esp_lcd_panel_handle_t *ret_panel)
{
    ESP_LOGI(TAG, "version: %d.%d.%d", ESP_LCD_CH13613_VER_MAJOR, ESP_LCD_CH13613_VER_MINOR,
             ESP_LCD_CH13613_VER_PATCH);
    ESP_RETURN_ON_FALSE(io && panel_dev_config && ret_panel, ESP_ERR_INVALID_ARG, TAG, "invalid arguments");
    ch13613_vendor_config_t *vendor_config = (ch13613_vendor_config_t *)panel_dev_config->vendor_config;
    ESP_RETURN_ON_FALSE(vendor_config && vendor_config->mipi_config.dpi_config && vendor_config->mipi_config.dsi_bus, ESP_ERR_INVALID_ARG, TAG,
                        "invalid vendor config");

    esp_err_t ret = ESP_OK;
    ch13613_panel_t *ch13613 = (ch13613_panel_t *)calloc(1, sizeof(ch13613_panel_t));
    ESP_RETURN_ON_FALSE(ch13613, ESP_ERR_NO_MEM, TAG, "no mem for ch13613 panel");

    if (panel_dev_config->reset_gpio_num >= 0) {
        gpio_config_t io_conf = {
            .mode = GPIO_MODE_OUTPUT,
            .pin_bit_mask = 1ULL << panel_dev_config->reset_gpio_num,
        };
        ESP_GOTO_ON_ERROR(gpio_config(&io_conf), err, TAG, "configure GPIO for RST line failed");
    }

    switch (panel_dev_config->rgb_ele_order) {
    case LCD_RGB_ELEMENT_ORDER_RGB:
        ch13613->madctl_val = 0;
        break;
    case LCD_RGB_ELEMENT_ORDER_BGR:
        ch13613->madctl_val |= LCD_CMD_BGR_BIT;
        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported color space");
        break;
    }

    switch (panel_dev_config->bits_per_pixel) {
    case 16: // RGB565
        ch13613->colmod_val = 0x55;
        break;
    case 18: // RGB666
        ch13613->colmod_val = 0x66;
        break;
    case 24: // RGB888
        ch13613->colmod_val = 0x77;

        if (vendor_config->mipi_config.dpi_config->video_timing.h_size * vendor_config->mipi_config.dpi_config->video_timing.v_size % 8 != 0) {
            ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported resolution");
        }

        break;
    default:
        ESP_GOTO_ON_FALSE(false, ESP_ERR_NOT_SUPPORTED, err, TAG, "unsupported pixel width");
        break;
    }

    ch13613->io = io;
    ch13613->init_cmds = vendor_config->init_cmds;
    ch13613->init_cmds_size = vendor_config->init_cmds_size;
    ch13613->reset_gpio_num = panel_dev_config->reset_gpio_num;
    ch13613->flags.reset_level = panel_dev_config->flags.reset_active_high;

    // Create MIPI DPI panel
    esp_lcd_panel_handle_t panel_handle = NULL;
    ESP_GOTO_ON_ERROR(esp_lcd_new_panel_dpi(vendor_config->mipi_config.dsi_bus, vendor_config->mipi_config.dpi_config, &panel_handle), err, TAG,
                      "create MIPI DPI panel failed");
    ESP_LOGD(TAG, "new MIPI DPI panel @%p", panel_handle);

    // Save the original functions of MIPI DPI panel
    ch13613->del = panel_handle->del;
    ch13613->init = panel_handle->init;
    // Overwrite the functions of MIPI DPI panel
    panel_handle->del = panel_ch13613_del;
    panel_handle->init = panel_ch13613_init;
    panel_handle->reset = panel_ch13613_reset;
    ch13613->panel_ctx.driver_data = ch13613;
    ch13613->panel_ctx.apply_brightness = ch13613_mipi_apply_brightness;
    panel_handle->user_data = &ch13613->panel_ctx;
    *ret_panel = panel_handle;
    ESP_LOGD(TAG, "new ch13613 panel @%p", ch13613);

    return ESP_OK;

err:
    if (ch13613) {
        if (panel_dev_config->reset_gpio_num >= 0) {
            gpio_reset_pin(panel_dev_config->reset_gpio_num);
        }
        free(ch13613);
    }
    return ret;
}

static const ch13613_lcd_init_cmd_t vendor_specific_init_code_default[] = {
    //  {cmd, { data }, data_size, delay_ms}
    {0xFE, (uint8_t []){0x20}, 1, 0},
    {0xF4, (uint8_t []){0x5A}, 1, 0},
    {0xF5, (uint8_t []){0x59}, 1, 0},
    {0xFE, (uint8_t []){0x80}, 1, 0},
    {0x03, (uint8_t []){0x00}, 1, 0},

    {0xFE, (uint8_t []){0x00}, 1, 0},

    {0x35, (uint8_t []){0x00}, 1, 0},
    {0x53, (uint8_t []){0x20}, 1, 0},
    {0x51, (uint8_t []){0xFF}, 1, 0},
    {0x63, (uint8_t []){0xAB}, 1, 0},
    {0x2A, (uint8_t []){0x00, 0x06, 0x01, 0xD7}, 4, 0},
    {0x2B, (uint8_t []){0x00, 0x00, 0x01, 0xD1}, 4, 0},
    {0x11, NULL, 0, 400},
    {0x29, NULL, 0, 0},
};

static esp_err_t panel_ch13613_del(esp_lcd_panel_t *panel)
{
    ch13613_panel_context_t *panel_ctx = (ch13613_panel_context_t *)panel->user_data;
    ESP_RETURN_ON_FALSE(panel_ctx, ESP_ERR_INVALID_STATE, TAG, "panel context not initialized");
    ch13613_panel_t *ch13613 = (ch13613_panel_t *)panel_ctx->driver_data;
    ESP_RETURN_ON_FALSE(ch13613, ESP_ERR_INVALID_STATE, TAG, "invalid panel data");

    // Delete MIPI DPI panel
    ESP_RETURN_ON_ERROR(ch13613->del(panel), TAG, "del ch13613 panel failed");
    if (ch13613->reset_gpio_num >= 0) {
        gpio_reset_pin(ch13613->reset_gpio_num);
    }

    if (ch13613->del) {
        ESP_RETURN_ON_ERROR(ch13613->del(panel), TAG, "delete MIPI DPI panel failed");
    }
    ESP_LOGD(TAG, "del ch13613 panel @%p", ch13613);
    free(ch13613);

    return ESP_OK;
}

static esp_err_t panel_ch13613_init(esp_lcd_panel_t *panel)
{
    ch13613_panel_context_t *panel_ctx = (ch13613_panel_context_t *)panel->user_data;
    ESP_RETURN_ON_FALSE(panel_ctx, ESP_ERR_INVALID_STATE, TAG, "panel context not initialized");
    ch13613_panel_t *ch13613 = (ch13613_panel_t *)panel_ctx->driver_data;
    ESP_RETURN_ON_FALSE(ch13613, ESP_ERR_INVALID_STATE, TAG, "invalid panel data");
    esp_lcd_panel_io_handle_t io = ch13613->io;
    const ch13613_lcd_init_cmd_t *init_cmds = NULL;
    uint16_t init_cmds_size = 0;
    bool is_cmd_overwritten = false;

    uint8_t ID[3];
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_rx_param(io, 0x04, ID, 3), TAG, "read ID failed");
    ESP_LOGI(TAG, "LCD ID: %02X %02X %02X", ID[0], ID[1], ID[2]);

    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, LCD_CMD_MADCTL, (uint8_t[]) {
        ch13613->madctl_val,
    }, 1), TAG, "send command failed");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, LCD_CMD_COLMOD, (uint8_t[]) {
        ch13613->colmod_val,
    }, 1), TAG, "send command failed");

    // vendor specific initialization, it can be different between manufacturers
    // should consult the LCD supplier for initialization sequence code
    if (ch13613->init_cmds) {
        init_cmds = ch13613->init_cmds;
        init_cmds_size = ch13613->init_cmds_size;
    } else {
        init_cmds = vendor_specific_init_code_default;
        init_cmds_size = sizeof(vendor_specific_init_code_default) / sizeof(ch13613_lcd_init_cmd_t);
    }

    for (int i = 0; i < init_cmds_size; i++) {
        // Check if the command has been used or conflicts with the internal
        if (init_cmds[i].data_bytes > 0) {
            switch (init_cmds[i].cmd) {
            case LCD_CMD_MADCTL:
                is_cmd_overwritten = true;
                ch13613->madctl_val = ((uint8_t *)init_cmds[i].data)[0];
                break;
            case LCD_CMD_COLMOD:
                is_cmd_overwritten = true;
                ch13613->colmod_val = ((uint8_t *)init_cmds[i].data)[0];
                break;
            default:
                is_cmd_overwritten = false;
                break;
            }

            if (is_cmd_overwritten) {
                is_cmd_overwritten = false;
                ESP_LOGW(TAG, "The %02Xh command has been used and will be overwritten by external initialization sequence",
                         init_cmds[i].cmd);
            }
        }

        // Send command
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, init_cmds[i].cmd, init_cmds[i].data, init_cmds[i].data_bytes), TAG, "send command failed");
        vTaskDelay(pdMS_TO_TICKS(init_cmds[i].delay_ms));
    }

    ESP_LOGD(TAG, "send init commands success");

    if (ch13613->init) {
        ESP_RETURN_ON_ERROR(ch13613->init(panel), TAG, "init MIPI DPI panel failed");
    }

    return ESP_OK;
}

static esp_err_t panel_ch13613_reset(esp_lcd_panel_t *panel)
{
    ch13613_panel_context_t *panel_ctx = (ch13613_panel_context_t *)panel->user_data;
    ESP_RETURN_ON_FALSE(panel_ctx, ESP_ERR_INVALID_STATE, TAG, "panel context not initialized");
    ch13613_panel_t *ch13613 = (ch13613_panel_t *)panel_ctx->driver_data;
    ESP_RETURN_ON_FALSE(ch13613, ESP_ERR_INVALID_STATE, TAG, "invalid panel data");
    esp_lcd_panel_io_handle_t io = ch13613->io;

    // Perform hardware reset
    if (ch13613->reset_gpio_num >= 0) {
        gpio_set_level(ch13613->reset_gpio_num, !ch13613->flags.reset_level);
        vTaskDelay(pdMS_TO_TICKS(5));
        gpio_set_level(ch13613->reset_gpio_num, ch13613->flags.reset_level);
        vTaskDelay(pdMS_TO_TICKS(10));
        gpio_set_level(ch13613->reset_gpio_num, !ch13613->flags.reset_level);
        vTaskDelay(pdMS_TO_TICKS(120));
    } else if (io) { // Perform software reset
        ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, LCD_CMD_SWRESET, NULL, 0), TAG, "send command failed");
        vTaskDelay(pdMS_TO_TICKS(120));
    }

    return ESP_OK;
}

static esp_err_t ch13613_mipi_apply_brightness(void *driver_data, uint8_t brightness_percent)
{
    ch13613_panel_t *ch13613 = (ch13613_panel_t *)driver_data;
    ESP_RETURN_ON_FALSE(ch13613, ESP_ERR_INVALID_ARG, TAG, "invalid panel data");

    esp_lcd_panel_io_handle_t io = ch13613->io;
    ESP_RETURN_ON_FALSE(io, ESP_ERR_INVALID_STATE, TAG, "panel IO not initialized");

    uint8_t hw_brightness = (brightness_percent * 255) / 100;

    ESP_RETURN_ON_ERROR(esp_lcd_panel_io_tx_param(io, 0x51, (uint8_t[]) {
        hw_brightness
    }, 1), TAG, "send brightness command failed");

    ESP_LOGI(TAG, "set brightness to %d%% (hardware value: %d)", brightness_percent, hw_brightness);

    return ESP_OK;
}
#endif
