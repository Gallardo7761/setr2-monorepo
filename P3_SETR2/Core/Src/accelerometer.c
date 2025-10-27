/*
 * accelerometer.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jomaa
 */

#include "accelerometer.h"

void Accelero_Test(void)
{
	int16_t pDataXYZ[3] = {0};
	BSP_ACCELERO_Init();
	BSP_ACCELERO_AccGetXYZ(pDataXYZ);
	printf("X= %d, Y = %d, Z = %d \n\r", pDataXYZ[0],
			pDataXYZ[1], pDataXYZ[2]);

	BSP_ACCELERO_DeInit();
	printf("\n*** End of Accelerometer Test ***\n\n");
	return;
}
