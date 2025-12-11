/*
 * WebServer.h
 *
 *  Created on: Nov 17, 2025
 *      Author: jomaa
 */

#ifndef INC_WEBSERVER_H_
#define INC_WEBSERVER_H_

#include <unistd.h>
#include "main.h"
#include "es_wifi.h"
#include "wifi.h"
#include "cmsis_os.h"
#include "semphr.h"
#include "Sensors.h"
#include "Tasks.h"

int WifiServer(void);
static WIFI_Status_t SendJsonResponse(SensorData_t* payload);
static int WifiStart(void);
static int WifiConnect(void);
static bool WebServerProcess(void);

SensorData_t GetSensors();

#endif /* INC_WEBSERVER_H_ */
