#include "stm32f10x.h"

#ifndef GPIO_H
#define GPIO_H

#define LED1_OFF GPIO_SetBits(GPIOB, GPIO_Pin_8);  
#define LED1_ON GPIO_ResetBits(GPIOB, GPIO_Pin_8);

#define LED2_OFF GPIO_SetBits(GPIOB, GPIO_Pin_9);  
#define LED2_ON GPIO_ResetBits(GPIOB, GPIO_Pin_9);

void IO_Config(void);
void Init_LED(void);
#endif
