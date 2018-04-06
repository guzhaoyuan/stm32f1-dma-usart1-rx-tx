#include "stm32f10x.h"
#include "usart.h"

#ifndef NVIC_H
#define NVIC_H

void Init_NVIC(void);
void USART1_IRQHandler(void);
void DMA1_Channel4_IRQHandler(void);
#endif
