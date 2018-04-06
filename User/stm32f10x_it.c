/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.4.0
  * @date    10/15/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
** 函数名称: USART1_IRQHandler
** 功能描述：
** 预期功能: 串口中断函数，接收结束后，rx idle，调用dma从usart->dr读取到buffer
** 参数描述: 无 
** 作  　者: zion
** 日　  期: 2018年4月6日
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler(void)
{
	uint8_t ReceiveData;								//定义一个变量存放接收的数据
	if((USART_GetITStatus(USART1,USART_IT_RXNE))) 
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//清楚中断标志位
		ReceiveData = USART_ReceiveData(USART1);			//接收字符存入数组
		USART1_Send_Byte(ReceiveData);
		//printf("%d",(char*)ReceiveData);				//以十进制输出输入的值,从这里我们可以看到键盘上所有的键值对应的十进制数
	}  
}

//发送结束后，关闭dma发送，等待下次系统更改数据后再次使能dma发送
//目前发现，这个函数根本没有进入，没有任何用处
void DMA1_Channel4_IRQHandler(void){
	//USART1_Send_Byte('x');//for debug
	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)){
		DMA_ClearFlag(DMA1_FLAG_TC4);
//		DMA_ClearITPendingBit(DMA1_IT_TC4);//似乎清除flag和清除IT标志位是一样的效果，不太确定

		DMA_Cmd(DMA1_Channel4, DISABLE);
	}
}

void DMA1_Channel5_IRQHandler(void)
{
	//USART1_Send_Byte('y');//for debug
	if(DMA_GetFlagStatus(DMA1_FLAG_TC5))
	{
		//DMA_ClearITPendingBit(DMA1_IT_TC5);
		DMA_ClearFlag(DMA1_FLAG_TC5);
		
		DMA_Cmd (DMA1_Channel5,DISABLE);
		DMA_SetCurrDataCounter(DMA1_Channel5, DMASIZE);
		DMA_Cmd (DMA1_Channel5,ENABLE);
		Uart_Send_Data(receivebuf, DMASIZE);
	}
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
