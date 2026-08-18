#ifndef __USART_H_
#define __USART_H_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/uart_select.h"
#include "driver/gpio.h"

#define USART_UX UART_NUM_0//串口编号
#define USART_TX_GPIO_PIN GPIO_NUM_43//串口发送引脚
#define USART_RX_GPIO_PIN GPIO_NUM_44//串口接收引脚

#define RX_BUF_SIZE          1024   	//接收缓冲区大小

void usart_init(uint32_t baudrate);

#endif