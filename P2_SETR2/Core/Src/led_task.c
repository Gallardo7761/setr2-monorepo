/*
 * led_task.c
 *
 *  Created on: Oct 6, 2025
 *      Author: jomaa
 */

#include "led_task.h"

void CreateLedTask()
{
	LED_Config* cfg = pvPortMalloc(sizeof(LED_Config));

	if (cfg != NULL)
	{
		cfg->led = 0;
		cfg->delay = 200;
	}

	xTaskCreate(
		LedToggleTask,
		"LedToggleTask_1",
		128,
		(void*) cfg,
		1,
		NULL
	);
}

void LedToggleTask(void* pArgs)
{
	LED_Config* cfg = (LED_Config*) pArgs;
	uint8_t counter = 5;
	for(;;)
	{
		if(cfg->led > 2)
		{
			cfg->led = 0;
		}

		while (counter > 0)
		{
			LED_Toggle(cfg->led);
			vTaskDelay(cfg->delay);
			counter--;
		}

		cfg->led++;

		xTaskCreate(
			LedToggleTask,
			"LedToggleTask_New",
			128,
			(void*) cfg,
			1,
			NULL
		);

		vTaskDelete(NULL);
	}
}
