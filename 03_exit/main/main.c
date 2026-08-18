#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "exit.h"
void app_main(void)
{
	exit_init();
    led_init();
    while(1)
    {		
		vTaskDelay(10);//延时10ms
	}

}
