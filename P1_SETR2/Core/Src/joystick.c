/*
 * joystick.c
 *
 *  Created on: Oct 6, 2025
 *      Author: jomaa
 */

#include "joystick_driver.h"

static uint8_t previous_state = GPIO_PIN_SET;
static uint8_t virtual_button = 0;

uint8_t ReadJoy(void)
{
	GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

	if (previous_state == GPIO_PIN_SET && current_state == GPIO_PIN_RESET)
	{
		virtual_button++;
		if (virtual_button > 4)	virtual_button = 1;
	}

	previous_state = current_state;

	if (current_state == GPIO_PIN_RESET) return virtual_button;
	else return 0;
}
