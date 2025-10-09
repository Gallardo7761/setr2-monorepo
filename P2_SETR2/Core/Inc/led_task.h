/*
 * led_task.h
 *
 *  Created on: Oct 6, 2025
 *      Author: jomaa
 */

#ifndef INC_LED_TASK_H_
#define INC_LED_TASK_H_

#include "stm32l4xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led_driver.h"
#include "joystick_driver.h"

typedef struct
{
	uint8_t led;
	uint32_t delay;
} LED_Config;

void CreateLedTask();
void LedToggleTask(void* pArgs);

void LedAnimationTask(void* pArgs);
void LedAnimationTask1(void* pArgs);
void LedAnimationTask2(void* pArgs);
void LedAnimationTask3(void* pArgs);

#endif /* INC_LED_TASK_H_ */
