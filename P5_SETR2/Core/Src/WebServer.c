/*
 * Wifi.c
 *
 *  Created on: Nov 29, 2020
 *      Author: rpaz
 */
#include "WebServer.h"

extern float temperature;

/* Update SSID and PASSWORD with own Access point settings */
#define SSID     "Pixelito"
#define PASSWORD "bombardeenlaus"
#define PORT           80

#define TERMINAL_USE

#define WIFI_WRITE_TIMEOUT 10000
#define WIFI_READ_TIMEOUT  10000
#define SOCKET                 0

#ifdef  TERMINAL_USE
#define LOG(a) printf a
#else
#define LOG(a)
#endif
/* Private defines -----------------------------------------------------------*/

static uint8_t http[1024];
static uint8_t IP_Addr[4];

static int WifiStart(void) {
	uint8_t MAC_Addr[6];

	/*Initialize and use WIFI module */
	if (WIFI_Init() == WIFI_STATUS_OK) {
		LOG(("ES-WIFI Initialized.\n"));
		if (WIFI_GetMAC_Address(MAC_Addr) == WIFI_STATUS_OK) {
			LOG(
					("> es-wifi module MAC Address : %X:%X:%X:%X:%X:%X\n", MAC_Addr[0], MAC_Addr[1], MAC_Addr[2], MAC_Addr[3], MAC_Addr[4], MAC_Addr[5]));
		} else {
			LOG(("> ERROR : CANNOT get MAC address\n"));
			return -1;
		}
	} else {
		return -1;
	}
	return 0;
}

int WifiConnect(void) {

	WifiStart();

	LOG(("\nConnecting to %s , %s\n",SSID,PASSWORD));
	if (WIFI_Connect(SSID, PASSWORD, WIFI_ECN_WPA2_PSK) == WIFI_STATUS_OK) {
		if (WIFI_GetIP_Address(IP_Addr) == WIFI_STATUS_OK) {
			LOG(
				("> es-wifi module connected: got IP Address : %d.%d.%d.%d\n", IP_Addr[0], IP_Addr[1], IP_Addr[2], IP_Addr[3]));
		} else {
			LOG((" ERROR : es-wifi module CANNOT get IP address\n"));
			return -1;
		}
	} else {
		LOG(("ERROR : es-wifi module NOT connected\n"));
		return -1;
	}
	return 0;
}

int WifiServer(void) {
	bool stop_server = false;

	LOG(("\nRunning HTTP Server test\n"));
	if (WifiConnect() != 0)
		return -1;

	if (WIFI_STATUS_OK
			!= WIFI_StartServer(SOCKET, WIFI_TCP_PROTOCOL, 1, "", PORT)) {
		LOG(("ERROR: Cannot start server.\n"));
	}

	LOG(("Server is running and waiting for an HTTP  Client connection to %d.%d.%d.%d\n",IP_Addr[0],IP_Addr[1],IP_Addr[2],IP_Addr[3]));

	do {
		uint8_t remote_ip[4];
		uint16_t remote_port;

		while (WIFI_STATUS_OK
				!= WIFI_WaitServerConnection(SOCKET, 1000, remote_ip,
						&remote_port)) {
			LOG(
					("Waiting connection to  %d.%d.%d.%d\n",IP_Addr[0],IP_Addr[1],IP_Addr[2],IP_Addr[3]));

		}

		LOG(
				("Client connected %d.%d.%d.%d:%d\n",remote_ip[0],remote_ip[1],remote_ip[2],remote_ip[3],remote_port));

		stop_server = WebServerProcess();

		if (WIFI_CloseServerConnection(SOCKET) != WIFI_STATUS_OK) {
			LOG(("ERROR: failed to close current Server connection\n"));
			return -1;
		}
	} while (stop_server == false);

	if (WIFI_STATUS_OK != WIFI_StopServer(SOCKET)) {
		LOG(("ERROR: Cannot stop server.\n"));
	}

	LOG(("Server stopped\n"));
	return 0;
}

static bool WebServerProcess(void)
{
    uint8_t led_state = 1;
    SensorData_t tmp; // struct temporal
    uint16_t response_length;
    static uint8_t response[1024];
    bool stop_server = false;

    if (WIFI_STATUS_OK == WIFI_ReceiveData(SOCKET, response, sizeof(response) - 1, &response_length, WIFI_READ_TIMEOUT))
    {
        LOG(("get %d byte from server\n", response_length));

        if (response_length > 0)
        {
            if (response_length < sizeof(response))
                response[response_length] = '\0';
            else
                response[sizeof(response) - 1] = '\0';

            char method[8] = {0};
            char path[64] = {0};

            sscanf((char*)response, "%7s %63s", method, path);

            LOG(("Request: method=%s path=%s\n", method, path));

            // --- GET ----------------------------------------
            if (strcmp(method, "GET") == 0)
            {
                tmp = GetSensors();
                if (SendJsonResponse(&tmp) != WIFI_STATUS_OK) {
                    LOG(("> ERROR : Cannot send JSON\n"));
                } else {
                    LOG(("Send JSON after GET\n"));
                }
            }

            // --- POST ----------------------------------------
            else if (strcmp(method, "POST") == 0)
            {
                if (strstr((char*)response, "radio")) {
                    if (strstr((char*)response, "radio=0")) {
                        led_state = 0;
                        QueueLed(led_state);
                    } else if (strstr((char*)response, "radio=1")) {
                        led_state = 1;
                        QueueLed(led_state);
                    }
                }

                if (strstr((char*)response, "stop_server")) {
                    if (strstr((char*)response, "stop_server=0"))
                        stop_server = false;
                    else if (strstr((char*)response, "stop_server=1"))
                        stop_server = true;
                }

                tmp = GetSensors();

                if (SendJsonResponse(&tmp) != WIFI_STATUS_OK) {
                    LOG(("> ERROR : Cannot send JSON after POST\n"));
                } else {
                    LOG(("Send JSON after POST\n"));
                }
            }

            // --- INVALID METHOD ----------------------------------------
            else {
                LOG(("Unsupported method: %s\n", method));
            }
        }
    } else {
        LOG(("Client close connection or receive timeout\n"));
    }

    return stop_server;
}

/**
 * @brief  Send HTML page
 * @param  None
 * @retval None
 */
static WIFI_Status_t SendJsonResponse(SensorData_t* payload)
{
    uint16_t sent_data_length = 0;
    WIFI_Status_t return_status;

    char body[512];
    int body_length = snprintf(body, sizeof(body),
        "{"
        "\"humidity\": %.2f,"
        "\"temperature\": %.2f,"
        "\"pressure\": %.2f,"
        "\"accelerometer\": [%d, %d, %d],"
        "\"gyroscope\": [%.2f, %.2f, %.2f],"
        "\"magnetometer\": [%d, %d, %d]"
        "}",
        payload->humidity,
        payload->temperature,
        payload->pressure,
        payload->accelerometer[0], payload->accelerometer[1], payload->accelerometer[2],
        payload->gyroscope[0], payload->gyroscope[1], payload->gyroscope[2],
        payload->magnetometer[0], payload->magnetometer[1], payload->magnetometer[2]
    );

    if (body_length < 0) body_length = 0;
    if (body_length >= (int)sizeof(body)) body_length = (int)sizeof(body) - 1;

    int header_length = snprintf((char*)http, sizeof(http),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "Pragma: no-cache\r\n"
        "\r\n",
		body_length
    );

    if (header_length <= 0 || header_length >= (int)sizeof(http))
        return WIFI_STATUS_ERROR;

    if ((size_t)header_length + (size_t)body_length >= sizeof(http))
        return WIFI_STATUS_ERROR;

    memcpy(http + header_length, body, body_length);

    size_t total_length = header_length + body_length + 2;

    return_status = WIFI_SendData(
		SOCKET,
		(uint8_t*)http,
		total_length,
		&sent_data_length,
		WIFI_WRITE_TIMEOUT
	);

    if (return_status != WIFI_STATUS_OK) {
        LOG(("WIFI_SendData return_status != OK (%d)\n", (int)return_status));
        return return_status;
    }

    if (sent_data_length != (uint16_t)total_length) {
        LOG(("WIFI_SendData sent %u of %u\n", sent_data_length, (unsigned)total_length));
        return WIFI_STATUS_ERROR;
    }

    return WIFI_STATUS_OK;
}


//*************************************************************************//

extern SPI_HandleTypeDef hspi3;

/******************************************************************************/
/*                 STM32L4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file.                                                                     */
/************************************************************
 *															*
 *		Rutinas de servicio de interrupciones				*
 *															*
 ************************************************************/

/**
 * @brief  This function handles external lines 1interrupt request.
 * @param  None
 * @retval None
 */
void EXTI1_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
	portYIELD_FROM_ISR(pdFALSE);
}

/**
 * @brief  EXTI line detection callback.
 * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
	case (GPIO_PIN_1): {
		SPI_WIFI_ISR();
		break;
	}
	default: {
		break;
	}
	}
	portYIELD_FROM_ISR(pdFALSE);
}

/**
 * @brief  SPI3 line detection callback.
 * @param  None
 * @retval None
 */
extern SPI_HandleTypeDef hspi;
void SPI3_IRQHandler(void) {
	HAL_SPI_IRQHandler(&hspi);
	portYIELD_FROM_ISR(pdFALSE);
}
