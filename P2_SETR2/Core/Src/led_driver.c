/*
 * led_driver.c
 *
 *  Created on: Oct 6, 2025
 *      Author: jomaa
 */

#include "led_driver.h"

void LED_On(uint8_t led)
{
	switch(led)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		break;
	}
}

void LED_Off(uint8_t led)
{
	switch(led)
	{
	case 0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		break;
	}
}

void LED_Toggle(uint8_t led)
{
	switch(led)
	{
	case 0:
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		break;
	case 1:
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		break;
	case 2:
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
		break;
	}
}
