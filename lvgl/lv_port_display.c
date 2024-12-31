/**
 * @file main.c
 * @author Nicholas Loehrke (nicholasnloehrke@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2024-12-29
 *
 * MIT License
 *
 * Copyright (c) 2024 Nicholas Loehrke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "ili9486_driver.h"
#include "ili9486_hal_pico.h"
#include "lvgl.h"
#include "pico/stdlib.h"
#include "time.h"

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320

lv_display_t *lv_display;

ili9486_t ili9486_display = {
    .width = DISPLAY_WIDTH,
    .height = DISPLAY_HEIGHT,
    .hal = &ili9486_hal_pico,
};

static void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map);
static uint32_t elapsed_ms(void);

void lv_port_display_init()
{
    lv_init();

    ili9486_hal_pico_init();
    ili9486_init(&ili9486_display);

    lv_tick_set_cb(elapsed_ms);

    lv_display = lv_display_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);

    lv_display_set_flush_cb(lv_display, flush_cb);

    static uint16_t buf[DISPLAY_WIDTH * DISPLAY_HEIGHT / 10];
    lv_display_set_buffers(lv_display, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
}

static void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map)
{
    uint16_t *buf16 = (uint16_t *)px_map; // RGB565

    uint32_t width = area->x2 - area->x1 + 1;
    uint32_t height = area->y2 - area->y1 + 1;

    ili9486_set_area(&ili9486_display, area->x1, area->y1, width, height, buf16);

    lv_display_flush_ready(display);
}

static uint32_t elapsed_ms(void)
{
    return time_us_32() / 1000;
}