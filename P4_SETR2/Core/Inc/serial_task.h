/*
 * serial_task.h
 *
 *  Created on: Nov 3, 2025
 *      Author: jomaa
 */

#ifndef INC_SERIAL_TASK_H_
#define INC_SERIAL_TASK_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_uart.h"
#include "FreeRTOS.h"
#include "semphr.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void CreateSerialTask(void);
void CreateSerialObjects(void);

void SerialTxTask(void* pArgs);
void SerialRxTask(void* pArgs);

void SerialSendByte(char data);

#endif /* INC_SERIAL_TASK_H_ */
