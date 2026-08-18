#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "key.h"

void app_main(void)
{
	uint8_t key = 0;
    led_init();
    key_init();

    while(1)
    {	
		key = key_scan(0);
		switch(key) {
			case BOOT_PRES:
			{
				LED_TOGGLE();//切换状态
				break;
			}
			default:
				break;
		}
		vTaskDelay(10);
	}

}
