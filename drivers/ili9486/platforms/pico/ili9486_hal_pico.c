/**
 * @file ili9486_hal_pico.c
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

#include "ili9486_hal_pico.h"

#include "hardware/gpio.h"
#include "pico/stdlib.h"

static const uint gpio_DB[16] = {
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
};

static const uint gpio_RS = 21;   // register select (D/CX in datasheet) low->command, high->parameter/data
static const uint gpio_WR = 20;   // write data at rising edge
static const uint gpio_CSn = 19;  // chip select (active low)
static const uint gpio_RSTn = 18; // reset (active low)

int ili9486_hal_pico_init()
{
    // init gpio
    for (int i = 0; i < 16; ++i)
    {
        gpio_init(gpio_DB[i]);
        gpio_set_dir(gpio_DB[i], GPIO_OUT);
    }
    gpio_init(gpio_RS);
    gpio_init(gpio_WR);
    gpio_init(gpio_CSn);
    gpio_init(gpio_RSTn);

    gpio_set_dir(gpio_RS, GPIO_OUT);
    gpio_set_dir(gpio_WR, GPIO_OUT);
    gpio_set_dir(gpio_CSn, GPIO_OUT);
    gpio_set_dir(gpio_RSTn, GPIO_OUT);

    gpio_put(gpio_RS, 0);
    gpio_put(gpio_WR, 1);
    gpio_put(gpio_CSn, 1);
    gpio_put(gpio_RSTn, 0);

    return 0;
}

void cs_active()
{
    gpio_put(gpio_CSn, 0);
}

void cs_idle()
{
    gpio_put(gpio_CSn, 1);
}

void hard_reset()
{
    gpio_put(gpio_RSTn, 0);
    delay_ms(10);
    gpio_put(gpio_RSTn, 1);
    delay_ms(120);
}

void write_command(uint8_t cmd)
{
    gpio_put_masked(0xFFFF << gpio_DB[0], cmd << gpio_DB[0]); // set data pins
    gpio_put(gpio_RS, 0);                                     // RS low for command
    gpio_put(gpio_WR, 0);                                     // pulse WR
    gpio_put(gpio_WR, 1);
}

void write_data(uint16_t data)
{
    gpio_put_masked(0xFFFF << gpio_DB[0], data << gpio_DB[0]); // set data pins
    gpio_put(gpio_RS, 1);                                      // RS high for data
    gpio_put(gpio_WR, 0);                                      // pulse WR
    gpio_put(gpio_WR, 1);
}

void write_data_buffer(uint16_t *buffer, size_t length)
{
    gpio_put(gpio_RS, 1); // RS high for data
    for (size_t i = 0; i < length; ++i)
    {
        gpio_put_masked(0xFFFF << gpio_DB[0], buffer[i] << gpio_DB[0]); // set data pins
        gpio_put(gpio_WR, 0);                                           // pulse WR
        gpio_put(gpio_WR, 1);
    }
}

void delay_ms(uint32_t ms)
{
    sleep_ms(ms);
}

ili9486_hal_t ili9486_hal_pico = {
    .cs_active = cs_active,
    .cs_idle = cs_idle,
    .hard_reset = hard_reset,
    .write_command = write_command,
    .write_data = write_data,
    .write_data_buffer = write_data_buffer,
    .delay_ms = delay_ms,
};