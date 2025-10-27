/*
 * humidity.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jomaa
 */

#include "humidity.h"

void Humidity_Test(void)
{
	float humidity_value;
	BSP_HSENSOR_Init();
	humidity_value = BSP_HSENSOR_ReadHumidity();
	printf("HUMIDITY is = %.2f %%\n", humidity_value);
}
