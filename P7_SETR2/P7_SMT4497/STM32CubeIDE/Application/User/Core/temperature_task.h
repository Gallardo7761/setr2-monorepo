/*
 * temperature_task.h
 *
 *  Created on: Dec 15, 2025
 *      Author: practicas
 */

#ifndef APPLICATION_USER_CORE_TEMPERATURE_TASK_H_
#define APPLICATION_USER_CORE_TEMPERATURE_TASK_H_

#include "stm32f7xx_hal.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

void create_temperature_task();
void temperature_callback(void* pArgs);

#endif /* APPLICATION_USER_CORE_TEMPERATURE_TASK_H_ */
