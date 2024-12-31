/**
 * @file ui.c
 * @author Nicholas Loehrke (nicholasnloehrke@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2024-12-31
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

#include "ui.h"
#include "../lvgl/lv_port_display.h"

static lv_obj_t *dvd_logo;
static int x_velocity = 5;
static int y_velocity = 3;

// Screen dimensions (adjust as per your display resolution)
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

// Logo dimensions (adjust as per the object size)
#define LOGO_WIDTH 50
#define LOGO_HEIGHT 30

static void move_dvd_logo(lv_timer_t *timer)
{
    // Get current position
    lv_coord_t x = lv_obj_get_x(dvd_logo);
    lv_coord_t y = lv_obj_get_y(dvd_logo);

    // Update position
    x += x_velocity;
    y += y_velocity;

    // Check for collisions with screen edges
    if (x <= 0 || x + LOGO_WIDTH >= SCREEN_WIDTH)
        x_velocity = -x_velocity;

    if (y <= 0 || y + LOGO_HEIGHT >= SCREEN_HEIGHT)
        y_velocity = -y_velocity;

    // Set new position
    lv_obj_set_pos(dvd_logo, x, y);
}

void ui_init()
{
    lv_port_display_init();

    // Create a rectangle to simulate the DVD logo
    dvd_logo = lv_obj_create(lv_scr_act());
    lv_obj_set_size(dvd_logo, LOGO_WIDTH, LOGO_HEIGHT);
    lv_obj_set_style_bg_color(dvd_logo, lv_color_hex(0xFF0000), 0); // Red color
    lv_obj_set_pos(dvd_logo, (SCREEN_WIDTH - LOGO_WIDTH) / 2, (SCREEN_HEIGHT - LOGO_HEIGHT) / 2);

    // Create a timer to move the DVD logo
    lv_timer_create(move_dvd_logo, 20, NULL); // 20 ms interval for smooth animation
}