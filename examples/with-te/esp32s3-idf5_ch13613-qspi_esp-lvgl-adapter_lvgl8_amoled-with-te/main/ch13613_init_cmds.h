#ifndef CH13613_INIT_CMDS_H
#define CH13613_INIT_CMDS_H

#include "esp_lcd_ch13613.h"

#ifdef __cplusplus
extern "C" {
#endif

// ==================== CH13613 初始化命令数组 ====================
static const ch13613_lcd_init_cmd_t lcd_init_cmds[] = {
    {0xFE, (uint8_t []){0x00}, 1, 0},
    {0xF0, (uint8_t []){0x50}, 1, 0},
    {0xB1, (uint8_t []){0x78,0x70}, 2, 0},
    {0xC4, (uint8_t []){0x80}, 1, 0},
    {0x35, (uint8_t []){0x00}, 1, 0},
    {0x36, (uint8_t []){0x00}, 1, 0},
    {0x3A, (uint8_t []){0x55}, 1, 0},
    {0x53, (uint8_t []){0x20}, 1, 0},
    {0x51, (uint8_t []){0xFF}, 1, 0},
    {0x63, (uint8_t []){0xFF}, 1, 0},
    {0x64, (uint8_t []){0x10}, 1, 0},
    {0x67, (uint8_t []){0x01}, 1, 0},
    {0x68, (uint8_t []){0x31}, 1, 0},
    {0x2A, (uint8_t []){0x00,0x00,0x01,0xdf}, 4, 0},
    {0x2B, (uint8_t []){0x00,0x00,0x01,0xdf}, 4, 0},
    {0x11, (uint8_t []){0x00}, 0, 120},
    {0x29, (uint8_t []){0x00}, 0, 120},
};

static const size_t lcd_init_cmds_size = sizeof(lcd_init_cmds) / sizeof(ch13613_lcd_init_cmd_t);

#ifdef __cplusplus
}
#endif

#endif // CH13613_INIT_CMDS_H