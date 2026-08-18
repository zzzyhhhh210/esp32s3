#include "exit.h"
/*
 * @brief 处理退出引脚中断
 * @param arg 引脚编号
 * IRAM_ATTR表示该函数在IRAM中运行，因为中断处理函数需要快速响应
*/
void IRAM_ATTR exit_gpio_isr_handler(void* arg)
{
	uint32_t gpio_num = (uint32_t)arg;

	if (gpio_num == BOOT_INT_GPIO_PIN)
	{
	    LED_TOGGLE();
	}
}
void exit_init(void)
{
	gpio_config_t gpio_init_struct = {0};//1.配置结构体
	gpio_init_struct.intr_type = GPIO_INTR_NEGEDGE;//2.设置引脚为下降沿触发
	gpio_init_struct.mode = GPIO_MODE_INPUT;//3.设置引脚为输入模式
	gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;//4.上拉使能
	gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;//5.下拉失能
	gpio_init_struct.pin_bit_mask = (1ULL << BOOT_INT_GPIO_PIN);//5.设置引脚为输出模式-输入输出

	gpio_config(&gpio_init_struct);

	gpio_install_isr_service(0);//6.注册中断服务，优先级为0，仅开启中断
	gpio_isr_handler_add(BOOT_INT_GPIO_PIN, exit_gpio_isr_handler, BOOT_INT_GPIO_PIN);
	//7.添加回调函数,参数为引脚编号
}


