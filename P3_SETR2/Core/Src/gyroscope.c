/*
 * gyroscope.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jomaa
 */

#include "gyroscope.h"

void Gyro_Test(void)
{
	float pGyroDataXYZ[3] = {0};
	BSP_GYRO_Init();

	BSP_GYRO_GetXYZ(pGyroDataXYZ);
	printf("GYRO_X = %.2f \n", pGyroDataXYZ[0]);
	printf("GYRO_Y = %.2f \n", pGyroDataXYZ[1]);
	printf("GYRO_Z = %.2f \n", pGyroDataXYZ[2]);

	BSP_GYRO_DeInit();
	printf("\n*** End of Gyro Test ***\n\n");
	return;
}

