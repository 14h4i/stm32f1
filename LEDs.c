/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void
gpio_setup(void) {

	/* Enable GPIOA clock. */

	rcc_periph_clock_enable(RCC_GPIOA);


	gpio_set_mode(GPIOA,GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL,GPIO8);
	gpio_set_mode(GPIOA,GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL,GPIO9);
	gpio_set_mode(GPIOA,GPIO_MODE_OUTPUT_2_MHZ,
		      GPIO_CNF_OUTPUT_PUSHPULL,GPIO10);

}

int
main(void) {
	int i;

	gpio_setup();

	for (;;) {
		gpio_clear(GPIOA,GPIO10);
		for (i = 0; i < 1500000; i++)	/* Wait a bit. */
			__asm__("nop");
		gpio_clear(GPIOA,GPIO9);
		for (i = 0; i < 1500000; i++)	/* Wait a bit. */
			__asm__("nop");
		gpio_clear(GPIOA,GPIO8);
		for (i = 0; i < 1500000; i++)	/* Wait a bit. */
			__asm__("nop");



		gpio_set(GPIOA,GPIO10);
		for (i = 0; i < 1500000; i++)	/* Wait a bit. */
			__asm__("nop");
		gpio_set(GPIOA,GPIO9);
		for (i = 0; i < 1500000; i++)	/* Wait a bit. */
			__asm__("nop");
		gpio_set(GPIOA,GPIO8);
		for (i = 0; i < 1500000; i++)	/* Wait a bit. */
			__asm__("nop");
	}

	return 0;
}
