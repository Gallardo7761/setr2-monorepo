/*
 * Sensores.c
 *
 *  Created on: Nov 29, 2020
 *      Author: rpaz
 */
#include "Sensors.h"

TickType_t sensor_period = 100;
SensorData_t sensor_data;
extern QueueHandle_t xQueueSensors;

void InitSensors()
{
	BSP_HSENSOR_Init();
	BSP_PSENSOR_Init();
	BSP_TSENSOR_Init();

	BSP_ACCELERO_Init();
	BSP_GYRO_Init();
	BSP_MAGNETO_Init();
}

void ReadSensors()
{
	sensor_data.humidity = BSP_HSENSOR_ReadHumidity();
	sensor_data.pressure = BSP_PSENSOR_ReadPressure();
	sensor_data.temperature = BSP_TSENSOR_ReadTemp();

	BSP_ACCELERO_AccGetXYZ(sensor_data.accelerometer);
	BSP_GYRO_GetXYZ(sensor_data.gyroscope);
	BSP_MAGNETO_GetXYZ(sensor_data.magnetometer);
}
