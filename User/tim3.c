#include "stm32f10x.h"
#ifndef __TIMER_H
#define __TIMER_H
void TIM4_Config(void);
#endif

u16 CCR1_Val ;   //PWM ռ�ձȵ���������  0xffff 100%    0x0 0%
u16 CCR2_Val ;
u16 CCR3_Val ;

//GPIO,TIM4-pwm���ó�ʼ��
void TIM4_Config(void)
{ 
  TIM_TimeBaseInitTypeDef  TIM4_TimeBaseStructure; //��ʱ����ʼ���ṹ
  TIM_OCInitTypeDef  TIM4_OCInitStructure;		   //ͨ�������ʼ���ṹ

  GPIO_InitTypeDef GPIO_InitStructure;
   
  //PB6 7 8 9��TIM4_CH1 2 3 4�����PWM
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);/* TIM3 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);/* GPIOB clock enable */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  TIM_DeInit(TIM4);
 
  TIM4_TimeBaseStructure.TIM_Prescaler = 35;//(36-1)Ԥ��Ƶ 72M/36=2M
  TIM4_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
  TIM4_TimeBaseStructure.TIM_Period = 40000;//����
  TIM4_TimeBaseStructure.TIM_ClockDivision = 0x0;// ʱ�ӷָ�
  TIM_TimeBaseInit(TIM4,&TIM4_TimeBaseStructure);

  TIM_OCStructInit(& TIM4_OCInitStructure);          //Ĭ�ϲ���
  /* PWM1 Mode configuration: Channel1 */
  TIM4_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //������Ʒ�ʽ2
  /*��һ·PWM���Ʋ�ɫLED_RED*/
	TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�                 
  TIM4_OCInitStructure.TIM_Pulse = CCR1_Val;  //����Ƚ�ֵ ����ռ�ձ�
  TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//����Ƚϼ��Ե�
  TIM_OC1Init(TIM4,&TIM4_OCInitStructure);	  //��ʼ��TIM4 ͨ��1
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
/*�ڶ�·PWM���Ʋ�ɫLED_BLUE*/
TIM4_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ������Ƚ�                 
  TIM4_OCInitStructure.TIM_Pulse = CCR1_Val;  //����Ƚ�ֵ ����ռ�ձ�
  TIM4_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//����Ƚϼ��Ե�
  TIM_OC2Init(TIM4,&TIM4_OCInitStructure);	  //��ʼ��TIM4 ͨ��1
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}
