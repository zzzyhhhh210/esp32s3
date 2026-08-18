#include "key.h"

void key_init(void)
{
	gpio_config_t gpio_init_struct = {0};//1.配置结构体
	gpio_init_struct.intr_type = GPIO_INTR_DISABLE;//2.失能引脚中断
	gpio_init_struct.mode = GPIO_MODE_INPUT;//3.设置引脚为输入模式
	gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;//4.上拉使能 
	gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;//5.下拉失能
	gpio_init_struct.pin_bit_mask = (1ULL << BOOT_GPIO_PIN);//6.设置引脚位掩码

	gpio_config(&gpio_init_struct);

}
/**
 * @brief 按键扫描函数
 * 
 * @param mode 模式参数，1表示支持长按模式，0表示不支持长按模式
 * @return uint8_t 按键值，0表示无按键按下，BOOT_PRES表示按键按下
 */
uint8_t key_scan(uint8_t mode)		//mode==1支持长按模式
{
	uint8_t keyval = 0; //按键值
	static uint8_t key_boot = 1;	//按键按下标志,1:松开,0:按下

	if(mode)						//支持长按模式
	{
		key_boot = 1; 				//按键松开
	}

	if((BOOT == 0) && key_boot)		//按键被按下
	{
		vTaskDelay(10);				//延时10ms，消抖
		key_boot = 0;  				//按键按下
		if(BOOT == 0)  				//按键持续按下
		{
			keyval = BOOT_PRES;		//按键值，按下
		} 
	}
	else if(BOOT == 1)				//按键松开
	{
		key_boot = 1;  				//按键松开
	}

	return keyval;					//返回按键值

}