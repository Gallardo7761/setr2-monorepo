/*
 * serial_task.c
 *
 *  Created on: Nov 3, 2025
 *      Author: jomaa
 */

#include "serial_task.h"

char c;
QueueHandle_t xQueue;

SemaphoreHandle_t xSemaphore;

TaskHandle_t hRxTask;
TaskHandle_t hTxTask;

extern UART_HandleTypeDef huart1;

void CreateSerialObjects(void)
{
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphore);
	xQueue = xQueueCreate(16, sizeof(char));
}

void CreateSerialTask(void)
{
	xTaskCreate(
		SerialTxTask,
		"SerialTxTask",
		128,
		NULL,
		1,
		&hTxTask
	);

	xTaskCreate(
		SerialRxTask,
		"SerialRxTask",
		128,
		NULL,
		1,
		&hRxTask
	);
}

void SerialTxTask(void* pArgs)
{
	for(;;) {
		SerialSendByte('h');
		vTaskDelay(200);
		SerialSendByte('o');
		vTaskDelay(200);
		SerialSendByte('l');
		vTaskDelay(200);
		SerialSendByte('a');
		vTaskDelay(200);
	}
}

void SerialRxTask(void* pArgs)
{
	for(;;) {
		HAL_UART_Receive_IT(&huart1, &c, 1);

		char data;
		while(1)
		{
			xQueueReceive(xQueue, &data, portMAX_DELAY);
			SerialSendByte(data);
		}
	}
}

void SerialSendByte(char data)
{
	BaseType_t status = xSemaphoreTake(xSemaphore, -1);
	if(status == pdTRUE)
		HAL_UART_Transmit_IT(&huart1, &data, 1);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	static BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(xSemaphore, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	xQueueSendFromISR(xQueue, &c, &xHigherPriorityTaskWoken);
	HAL_UART_Receive_IT(&huart1, &c, 1);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}
