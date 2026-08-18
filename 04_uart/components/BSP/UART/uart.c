#include "uart.h"
#include "driver/gpio.h"
void usart_init(uint32_t baudrate)
{
	uart_config_t uart_config = {0};//1.配置结构体

	uart_config.baud_rate = baudrate;        //波特率
	uart_config.data_bits = UART_DATA_8_BITS;//数据8位
	uart_config.stop_bits = UART_STOP_BITS_1; //停止1位
	uart_config.parity = UART_PARITY_DISABLE;//奇偶无校验位
	uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;//无流控
	uart_config.rx_flow_ctrl_thresh = 122; //接收流控控阈值
	uart_config.source_clk = UART_SCLK_APB; //使用APB时钟

	uart_param_config(USART_UX, &uart_config);

    //设置串口引脚,串口号,发送引脚,接收引脚,控制引脚（默认）,RTS引脚（默认）
	uart_set_pin(USART_UX, USART_TX_GPIO_PIN, USART_RX_GPIO_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
	//安装串口驱动,串口号,接收缓冲区大小,发送缓冲区大小,中断优先级，队列，标志位相关
	uart_driver_install(USART_UX, RX_BUF_SIZE * 2, RX_BUF_SIZE * 2, 20, NULL, 0);//2.安装驱动
}