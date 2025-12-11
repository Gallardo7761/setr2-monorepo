/*
 * Tareas.c
 *
 *  Created on: 29 nov. 2020
 *      Author: rpaz
 */

#include "Tasks.h"

extern UART_HandleTypeDef huart1;

TaskHandle_t sensorTaskHandle;
SemaphoreHandle_t xSemaphore;
QueueHandle_t xQueue;
QueueHandle_t xQueueLED;
QueueHandle_t xQueueSensors;

void CreateSerialObjects()
{
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive (xSemaphore);

	xQueue = xQueueCreate(5, sizeof (char*));
	xQueueLED = xQueueCreate(1, sizeof (char*));
	xQueueSensors = xQueueCreate(1, sizeof (SensorData_t));
}

void QueueLed(char ch)
{
	xQueueSend(xQueueLED,&ch, portMAX_DELAY);
}

SensorData_t GetSensors()
{
	SensorData_t aux;
	xTaskNotifyGive(sensorTaskHandle);
	xQueueReceive(xQueueSensors, &aux, portMAX_DELAY);
	return aux;
}

void CreateTasks()
{
	xTaskCreate(
		TaskSensors,
		"TaskSensors",
		256,
		NULL,
		1,
		&sensorTaskHandle
	);

	xTaskCreate(
		TaskWebServer,
		"TaskWebServer",
		512,
		NULL,
		1,
		NULL
	);

	xTaskCreate(
		TaskLed,
		"TaskLed",
		128,
		NULL,
		1,
		NULL
	);
}

void TaskSensors(void* pArg)
{
	SensorData_t data;
	InitSensors();

	while(1)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		ReadSensors(&data);
		xQueueSend(xQueueSensors, &data, portMAX_DELAY);
	}
}

void TaskWebServer(void* pArg)
{
	WifiServer();
}

void TaskLed(void* pArg)
{
	char ch;
	while(1)
	{
		xQueueReceive(xQueueLED, &ch, portMAX_DELAY);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, ch);
	}
}
