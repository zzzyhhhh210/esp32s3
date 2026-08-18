#include "led.h"

void led_init(void)
{
	gpio_config_t gpio_init_struct = {0};//1.配置结构体
	gpio_init_struct.intr_type = GPIO_INTR_DISABLE;//2.失能引脚中断
	gpio_init_struct.mode = GPIO_MODE_INPUT_OUTPUT;//3.设置引脚为输出模式-输入输出
	gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;//4.上拉使能
	gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;//5.下拉失能
	gpio_init_struct.pin_bit_mask = (1ULL << LED_GPIO_PIN);//5.设置引脚为输出模式-输入输出

	gpio_config(&gpio_init_struct);

	LED(1);//6.设置引脚为高电平
}


