/*
 * Sensores.h
 *
 *  Created on: Nov 29, 2020
 *      Author: jomaa
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "main.h"
#include "global.h"

void InitSensors();
void ReadSensors();

typedef struct SensorData_t {
	float humidity;
	float temperature;
	float pressure;
	int16_t accelerometer[3];
	float gyroscope[3];
	int16_t magnetometer[3];
} SensorData_t;

#endif /* INC_SENSORS_H_ */
