idf_component_register(SRCS "esp_lcd_ch13613.c" "esp_lcd_ch13613_spi.c" "esp_lcd_ch13613_mipi.c"
                       INCLUDE_DIRS "include"
                       PRIV_INCLUDE_DIRS "priv_include"
                       REQUIRES "esp_lcd" "driver")
