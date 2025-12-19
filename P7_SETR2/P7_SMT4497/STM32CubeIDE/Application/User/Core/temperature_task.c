/*
 * temperature_task.c
 *
 *  Created on: Dec 15, 2025
 *      Author: practicas
 */

#include "temperature_task.h"

QueueHandle_t temperature_queue;
TaskHandle_t temperature_task;
extern ADC_HandleTypeDef hadc1;

void create_temperature_task()
{
	xTaskCreate(
		temperature_callback,
		"TemperatureTask",
		128,
		NULL,
		1,
		&temperature_task
	);

	temperature_queue = xQueueCreate(
		16, sizeof(uint16_t)
	);
}

void temperature_callback(void* pArgs)
{
	// leer del ADC y encolar el valor en mV
	// Temperature = ((Vsense - 0.76)/2.5) + 25.0
	uint32_t adc_raw;
	float vsense_mV;
	float temperature;

	HAL_ADC_Start(&hadc1);

	if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
	{
		adc_raw = HAL_ADC_GetValue(&hadc1);
		vsense_mV = (adc_raw * 3300.0f) / 4095.0f;
		temperature = ((vsense_mV - 760.0f) / 2.5f) + 25.0f;
		xQueueSend(temperature_queue, &temperature, 10);
	}

	HAL_ADC_Stop(&hadc1);
}
