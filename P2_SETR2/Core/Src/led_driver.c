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

void animation1(void)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        LED_On(i);
#ifdef INC_FREERTOS_H
        vTaskDelay(150);
#else
        HAL_Delay(150);
#endif
        LED_Off(i);
    }
    for(i = 1; i > 0; i--)
    {
        LED_On(i);
#ifdef INC_FREERTOS_H
        vTaskDelay(150);
#else
        HAL_Delay(150);
#endif
        LED_Off(i);
    }
}

void animation2(void)
{
    int i, j;
    for(j = 0; j < 5; j++)
    {
        for(i = 0; i < 3; i++)
            LED_On(i);

#ifdef INC_FREERTOS_H
        vTaskDelay(100);
#else
        HAL_Delay(100);
#endif

        for(i = 0; i < 3; i++)
            LED_Off(i);

#ifdef INC_FREERTOS_H
        vTaskDelay(100);
#else
        HAL_Delay(100);
#endif
    }
}

void animation3(void)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        LED_On(i);
#ifdef INC_FREERTOS_H
        vTaskDelay(150);
#else
        HAL_Delay(150);
#endif
    }
    for(i = 2; i >= 0; i--)
    {
        LED_Off(i);
#ifdef INC_FREERTOS_H
        vTaskDelay(150);
#else
        HAL_Delay(150);
#endif
    }
}
