#ifndef __USART_H
#define __USART_H

//头文件包含
#include "stdio.h"	 
#include <string.h>
#include "stm32f10x.h"

#define  DMASIZE 8

extern u8 sendbuf[DMASIZE];
extern u8 receivebuf[DMASIZE];

//函数声明
void USART1_Send_Byte(u16 dat);
uint8_t USART1_Receive_Byte(void);
void uart1_gpio_init(void);
void uart_setbaudrate(USART_TypeDef* USARTx,u32 value);
void uart1_dma_configuration(void);
u16 Uart_Send_Data(void* buffer, u16 size);
void Uart_Dma_Clr(void);
#endif
