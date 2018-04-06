#include "gpio.h"

GPIO_InitTypeDef GPIO_InitStructure;

void IO_Config(void)
{  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	  //AFIO时钟,管脚重映射时需开启  	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
		
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE); // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: Init_LED
** 功能描述: LED IO引脚配置
** 参数描述：无
** 作  　者: Dream
** 日　  期: 2011年6月20日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void Init_LED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;					//定义一个GPIO结构体变量

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB ,ENABLE);	//使能各个端口时钟，重要！！！
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;	//配置LED端口挂接到6、12、13端口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	   	//通用输出推挽
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	   	//配置端口速度为50M
  GPIO_Init(GPIOB, &GPIO_InitStructure);				   	//根据参数初始化GPIOB寄存器
}
