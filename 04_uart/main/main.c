#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led.h"
#include "uart.h"

void app_main(void)
{
	uint8_t len = 0;						// 接收数据长度
    uint16_t times = 0;						//计数变量
    unsigned char data[RX_BUF_SIZE] = {0};  //接收缓存区
	
	usart_init(115200);
    led_init();

    while(1)
    {	
		uart_get_buffered_data_len(USART_UX, (size_t*) &len);                           /* 获取环形缓冲区数据长度 */
		//串口回显功能
        if (len > 0)                                                                    /* 判断数据长度 */
        {
            memset(data, 0, RX_BUF_SIZE);                                               /* 对缓冲区清零 */
            printf("\n您发送的消息为:\n");
            uart_read_bytes(USART_UX, data, len, 100);                                  /* 读数据 */
            uart_write_bytes(USART_UX, (const char*)data, strlen((const char*)data));   /* 写数据 */
        }
        else//没有接收到数据，time计数，实现周期性任务
        {
            times++;

            if (times % 5000 == 0)
            {
                printf("\n正点原子 ATK-DNESP32-S3 开发板 串口实验\n");
                printf("正点原子@ALIENTEK\n\n\n");
            }

            if (times % 200 == 0)
            {
                printf("请输入数据，以回车键结束\n");
            }

            if (times % 30 == 0)
            {
                LED_TOGGLE();
            }

            vTaskDelay(10);//短暂延时，避免任务占满CPU
        }
	}

}
