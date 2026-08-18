#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "gptim.h"
#include "driver/timer.h"
#include "esp_log.h"

void app_main(void)
{
	//1. 动态分配定时器配置结构体内存；malloc函数（从堆区动态分配指定大小的内存）；
	timg_config_t *timgr_config = malloc(sizeof(timg_config_t));
	//2. 初始化 LED 硬件 
	led_init();
	//3. 配置定时器参数
	timgr_config->timer_count_value = 0;                  //定时器计数器初始值
	timgr_config->clk_src = TIMER_SRC_CLK_DEFAULT;        //时钟源，默认时钟源
	timgr_config->timer_group = TIMER_GROUP_0;            //定时器组，默认定时器组0
	timgr_config->timer_idx = TIMER_0;                    //定时器索引
	timgr_config->timing_time = 1 * 1000000;              //定时时间，单位为微秒
	timgr_config->alarm_value = timgr_config->timing_time;//定时器中断时间，单位为微秒
	timgr_config->auto_reload = TIMER_AUTORELOAD_DIS;     //是否自动重载，默认不自动重载，若开启自动重载，定时器计数器值会自动重置为0
	//4. 调用 timg_init() 初始化定时器
	timg_init(timgr_config);
	//5. 进入主循环：检测中断标志并记录日志
	while (1)
	{
		if(timgr_config->timer_count_value!=0)//计数器值不为零
		{
			//ESP_LOGI在终端打印日志，打印timgr_config->timer_count_value计数器值
			ESP_LOGI("Timer", "Timer auto reloaded, count value in ISR:%llu", timgr_config->timer_count_value);
			timgr_config->timer_count_value = 0;//清零定时器计数器值
		}
		vTaskDelay(10);
	}
	
}
