#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "FreeRTOS.h"
#include "queue.h"

extern "C" {
extern QueueHandle_t button_queue;
extern QueueHandle_t temperature_queue;
}

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if(xQueueReceive(button_queue, &button_state, 10) == pdPASS)
	{
		modelListener->set_button(button_state); // lo envia al presenter
	}

	if(xQueueReceive(temperature_queue, &temp, 10) == pdPASS)
	{
		modelListener->set_temperature(temp); // lo envia al presenter
	}
}
