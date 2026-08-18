#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
void app_main(void)
{
    led_init();
    while(1)
    {	
		LED(0);//亮
		vTaskDelay(1000 / portTICK_PERIOD_MS);//延时1s
		LED(1);//灭
		vTaskDelay(1000 / portTICK_PERIOD_MS);//延时1s
	}

}
