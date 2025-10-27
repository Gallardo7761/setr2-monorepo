/*
 * pressure.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jomaa
 */

#include "pressure.h"

void Pressure_Test(void)
{
	float press_value = 0;
	BSP_PSENSOR_Init();
	press_value = BSP_PSENSOR_ReadPressure();
	printf("PRESSURE is = %.2f mBar \n", press_value);
}
