#include "gptim.h"

//timer_group_isr_callback定时器中断处理函数（用户数据）
static bool IRAM_ATTR timer_group_isr_callback(void *arg)
{
	timg_config_t *user_data = (timg_config_t *)arg; //获取用户数据
	user_data->timer_count_value = 0;//清零定时器计数器值
	user_data->timer_count_value = timer_group_get_counter_value_in_isr(user_data->timer_group, user_data->timer_idx);//获取定时器计数器值
	LED_TOGGLE();
	if (!user_data->auto_reload)//是否自动重载，开启跳过
	{
		user_data->alarm_value += user_data->timing_time;
		timer_group_set_alarm_value_in_isr(user_data->timer_group, user_data->timer_idx, user_data->alarm_value);
	}

	return 1;//返回1，表示中断处理函数执行完成
	
}
//ESP_ERROR_CHECK错误检查工具
void timg_init(timg_config_t *timg_config)
{
	uint32_t clk_src_hz = 0;//存放时钟源真实频率
	timer_config_t timer_config = {0};//定时器配置结构体清零

	//esp_clk_tree_src_get_freq_hz（时钟源（main函数配置），时钟源精度（选择已缓存精度），时钟源真实频率通过指针写入变量）获取时钟源真实频率
	ESP_ERROR_CHECK(esp_clk_tree_src_get_freq_hz(timg_config->clk_src, ESP_CLK_TREE_SRC_FREQ_PRECISION_CACHED, &clk_src_hz));
	
	timer_config.alarm_en = TIMER_ALARM_EN;              //使能报警
	timer_config.auto_reload = timg_config->auto_reload; //是否自动重载
	timer_config.clk_src = timg_config->clk_src;         //时钟源
	timer_config.counter_dir = TIMER_COUNT_UP;           //向上计数
	timer_config.counter_en = TIMER_PAUSE;               //使能计数器（停止）
	timer_config.divider = clk_src_hz / 1000000;         //分频器

	//timer_init初始化定时器（定时器组，定时器索引，定时器配置结构体）
	ESP_ERROR_CHECK(timer_init(timg_config->timer_group, timg_config->timer_idx, &timer_config));

	//timer_set_counter_value设置定时器计数器初始值（定时器组，定时器索引，初始值）
	ESP_ERROR_CHECK(timer_set_counter_value(timg_config->timer_group, timg_config->timer_idx, 0));

	//timer_set_alarm_value设置定时器报警值（定时器组，定时器索引，报警值）
	ESP_ERROR_CHECK(timer_set_alarm_value(timg_config->timer_group, timg_config->timer_idx, timg_config->alarm_value));

	//timer_enable_intr使能定时器中断（定时器组，定时器索引）
	ESP_ERROR_CHECK(timer_enable_intr(timg_config->timer_group, timg_config->timer_idx));

	//timer_isr_callback_add添加定时器中断处理函数（定时器组，定时器索引，中断处理函数，用户数据，中断处理函数优先级）
	ESP_ERROR_CHECK(timer_isr_callback_add(timg_config->timer_group, timg_config->timer_idx, timer_group_isr_callback, timg_config, 0));

	//timer_start启动定时器（定时器组，定时器索引）
	ESP_ERROR_CHECK(timer_start(timg_config->timer_group, timg_config->timer_idx));
}