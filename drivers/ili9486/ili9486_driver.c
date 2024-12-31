/**
 * @file ili9486_driver.c
 * @author Nicholas Loehrke (nicholasnloehrke@gmail.com)
 * @brief
 * @version 1.0.0
 * @date 2024-12-28
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

int ili9486_init(ili9486_t *display)
{
    display->hal->cs_active();

    display->hal->hard_reset();

    display->hal->write_command(ILI9486_CMD_MEMORY_ACCESS_CONTROL);
    display->hal->write_data(0x28);
    display->hal->write_command(ILI9486_CMD_INTERFACE_PIXEL_FORMAT);
    display->hal->write_data(0x55); // RGB565
    display->hal->write_command(ILI9486_CMD_SLEEP_OUT);
    display->hal->delay_ms(120);
    display->hal->write_command(ILI9486_CMD_DISPLAY_ON);

    display->hal->cs_idle();

    return 0;
}

int ili9486_set_pixel(ili9486_t *display, uint32_t x, uint32_t y, uint16_t color)
{
    if (x >= display->width || y >= display->height)
    {
        return -1;
    }

    display->hal->cs_active();

    // column set
    display->hal->write_command(ILI9486_CMD_COLUMN_ADDRESS_SET);
    display->hal->write_data(x >> 8);
    display->hal->write_data(x & 0xFF);
    display->hal->write_data(x >> 8);
    display->hal->write_data(x & 0xFF);

    // row set
    display->hal->write_command(ILI9486_CMD_PAGE_ADDRESS_SET);
    display->hal->write_data(y >> 8);
    display->hal->write_data(y & 0xFF);
    display->hal->write_data(y >> 8);
    display->hal->write_data(y & 0xFF);

    // write memory
    display->hal->write_command(ILI9486_CMD_MEMORY_WRITE);
    display->hal->write_data(color);

    display->hal->cs_idle();

    return 0;
}

int ili9486_set_area(ili9486_t *display, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint16_t *color_buffer)
{
    if (x + width > display->width || y + height > display->height)
    {
        return -1;
    }

    display->hal->cs_active();

    // column set
    display->hal->write_command(ILI9486_CMD_COLUMN_ADDRESS_SET);
    display->hal->write_data(x >> 8);
    display->hal->write_data(x & 0xFF);
    display->hal->write_data((x + width - 1) >> 8);
    display->hal->write_data((x + width - 1) & 0xFF);

    // row set
    display->hal->write_command(ILI9486_CMD_PAGE_ADDRESS_SET);
    display->hal->write_data(y >> 8);
    display->hal->write_data(y & 0xFF);
    display->hal->write_data((y + height - 1) >> 8);
    display->hal->write_data((y + height - 1) & 0xFF);

    // write memory
    display->hal->write_command(ILI9486_CMD_MEMORY_WRITE);
    display->hal->write_data_buffer(color_buffer, width * height);

    display->hal->cs_idle();

    return 0;
}
