/**
 * @file ili9486_hal_pico.h
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

#ifndef ILI9486_HAL_PICO_F86CEDF3_8771_4A90_9083_13D0EED9AF13
#define ILI9486_HAL_PICO_F86CEDF3_8771_4A90_9083_13D0EED9AF13

#include "ili9486_driver.h"

extern ili9486_hal_t ili9486_hal_pico;

int ili9486_hal_pico_init();
void cs_active();
void cs_idle();
void hard_reset();
void write_command(uint8_t cmd);
void write_data(uint16_t data);
void write_data_buffer(uint16_t *buffer, size_t length);
void delay_ms(uint32_t ms);

#endif // ILI9486_HAL_PICO_F86CEDF3_8771_4A90_9083_13D0EED9AF13
