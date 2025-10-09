/*
 * led_driver.h
 *
 *  Created on: Oct 6, 2025
 *      Author: jomaa
 */

#ifndef INC_LED_DRIVER_H_
#define INC_LED_DRIVER_H_

#include "stm32l4xx_hal.h"

#ifdef INC_FREERTOS_H
#include "task.h"
#endif

void LED_On(uint8_t led);
void LED_Off(uint8_t led);
void LED_Toggle(uint8_t led);
void animation1(void);
void animation2(void);
void animation3(void);

#endif /* INC_LED_DRIVER_H_ */
