#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "esptim.h"

void app_main(void)
{
	led_init();
	esptim_int_init(1000000);	//初始化定时器1s.翻转一次
    
    // while(1)
    // {	
	// 	vTaskDelay(10);//延时10ms
	// }

}
