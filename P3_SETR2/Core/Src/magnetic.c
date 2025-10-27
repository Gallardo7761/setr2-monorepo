/*
 * magnetic.c
 *
 *  Created on: Oct 27, 2025
 *      Author: jomaa
 */

#include "magnetic.h"

void Magneto_Test(void)
{
	int16_t pDataXYZ[3] = {0};
	BSP_MAGNETO_Init();

	BSP_MAGNETO_GetXYZ(pDataXYZ);
	printf("MAGNETO_X = %d \n", pDataXYZ[0]);
	printf("MAGNETO_Y = %d \n", pDataXYZ[1]);
	printf("MAGNETO_Z = %d \n", pDataXYZ[2]);

	BSP_MAGNETO_DeInit();
	printf("\n*** End of Magneto Test ***\n\n");
	return;
}
