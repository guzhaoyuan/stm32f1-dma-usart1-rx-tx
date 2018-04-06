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
** ��������: USART1_IRQHandler
** ����������
** Ԥ�ڹ���: �����жϺ��������ս�����rx idle������dma��usart->dr��ȡ��buffer
** ��������: �� 
** ��  ����: zion
** �ա�  ��: 2018��4��6��
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
void USART1_IRQHandler(void)
{
	uint8_t ReceiveData;								//����һ��������Ž��յ�����
	if((USART_GetITStatus(USART1,USART_IT_RXNE))) 
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);	//����жϱ�־λ
		ReceiveData = USART_ReceiveData(USART1);			//�����ַ���������
		USART1_Send_Byte(ReceiveData);
		//printf("%d",(char*)ReceiveData);				//��ʮ������������ֵ,���������ǿ��Կ������������еļ�ֵ��Ӧ��ʮ������
	}  
}

//���ͽ����󣬹ر�dma���ͣ��ȴ��´�ϵͳ�������ݺ��ٴ�ʹ��dma����
//Ŀǰ���֣������������û�н��룬û���κ��ô�
void DMA1_Channel4_IRQHandler(void){
	//USART1_Send_Byte('x');//for debug
	if(DMA_GetFlagStatus(DMA1_FLAG_TC4)){
		DMA_ClearFlag(DMA1_FLAG_TC4);
//		DMA_ClearITPendingBit(DMA1_IT_TC4);//�ƺ����flag�����IT��־λ��һ����Ч������̫ȷ��

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
