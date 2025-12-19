/*
 * button_task.c
 *
 *  Created on: Dec 15, 2025
 *      Author: practicas
 */

#include "button_task.h"

QueueHandle_t button_queue;
TaskHandle_t button_task;

void create_button_task()
{
	xTaskCreate(
		button_callback,
		"ButtonTask",
		128,
		NULL,
		1,
		&button_task
	);

	button_queue = xQueueCreate(
		10, sizeof(uint8_t)
	);
}

void button_callback(void* pArgs)
{
	uint8_t button_state;
	for(;;)
	{
		button_state = HAL_GPIO_ReadPin(GPIOI, GPIO_PIN_11);
		xQueueSend(button_queue, &button_state, 10);
		vTaskDelay(100); // en ticks
	}
}
