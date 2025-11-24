/*
 * Tasks.h
 *
 *  Created on: Nov 17, 2025
 *      Author: jomaa
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include "main.h"
#include "global.h"
#include "Sensors.h"

int WifiServer(void);

void CreateTasks();
void CreateSerialObjects();

void TaskSensors(void* pArg);
void TaskWebServer(void* pArg);
void TaskLed(void* pArg);

void QueueLed(char ch);
SensorData_t GetSensors();

#endif /* INC_TASKS_H_ */
