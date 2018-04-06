#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"
//#include "ADC.h"
#include "usart.h"
#include "tim3.h"
#include "util.h"
#include "gpio.h"
#include "nvic.h"

u8 a[] = "program start";

int main()
{
	SystemInit();					//系统时钟配置到72MHz
  IO_Config();					//释放jtag io

	Init_LED();
	Init_NVIC();					//中断向量表注册函数
	uart1_gpio_init();
	uart_setbaudrate(USART1, 115200);
	uart1_dma_configuration();

	Uart_Send_Data(a, 13);
	
	while (1)
	{
	}
}
