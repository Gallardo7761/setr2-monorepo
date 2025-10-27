/*
 * temperature.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jomaa
 */

#include "temperature.h"

void Temperature_Test(void)
{
	float temp_value = 0;
	BSP_TSENSOR_Init();
	temp_value = BSP_TSENSOR_ReadTemp();
	printf("TEMPERATURE is = %.2f ºC\n", temp_value);
}
