//ͷ�ļ�����
//#include "usually.h"
#include "stm32f10x.h"
#include "usart.h"

u8 sendbuf[DMASIZE];
u8 receivebuf[DMASIZE];

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  

#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int Data, FILE *f)
{   
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus���õ�����״̬λ
														  //USART_FLAG_TXE:���ͼĴ���Ϊ�� 1��Ϊ�գ�0��æ״̬
	USART_SendData(USART1,Data);						  //����һ���ַ�
	   
	return Data;										  //����һ��ֵ
}



void USART1_Send_Byte(uint16_t Data)
{ 
	while(!USART_GetFlagStatus(USART1,USART_FLAG_TXE));	  //USART_GetFlagStatus���õ�����״̬λ
														  //USART_FLAG_TXE:���ͼĴ���Ϊ�� 1��Ϊ�գ�0��æ״̬
	USART_SendData(USART1,Data);						  //����һ���ַ�
}

uint8_t USART1_Receive_Byte(void)
{ 
   	while(!(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))); //USART_GetFlagStatus���õ�����״̬λ
														   //USART_FLAG_RXNE:�������ݼĴ����ǿձ�־λ 
														   //1��æ״̬  0������(û�յ����ݣ��ȴ�������)
	return USART_ReceiveData(USART1);					   //����һ���ַ�
}


void uart1_gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA   |
                     RCC_APB2Periph_USART1  |
                         RCC_APB2Periph_AFIO, ENABLE) ;

	//0x3 output, 0x4 adc, 0x8 input, 0xB af output
//  GPIOA->CRH&=0XFFFFF00F; 
//  GPIOA->CRH|=0X000008B0;

  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  /* Configure USART1 Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  //USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
  //USART_ITConfig(USART1, USART_IT_TC, ENABLE);
  //USART_ITConfig(USART1, USART_IT_FE, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //ʹ�ܽ����ж�
}

void uart_setbaudrate(USART_TypeDef* USARTx,u32 value)
{
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = value;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTx, &USART_InitStructure);
  USART_Cmd(USARTx, ENABLE);
}

void uart1_dma_configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,
                        ENABLE);

  /* DMA1 Channel5 (triggered by USART1 Rx event) Config */
  DMA_DeInit(DMA1_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr =(u32)receivebuf;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = DMASIZE;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
  DMA_Init(DMA1_Channel5, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel5, DMA_CCR1_TCIE, ENABLE); //ʹ�ܽ�������ж� = DMA1_Channel4->CCR |= 1<<1;
	//DMA_ITConfig(DMA1_Channel4, DMA1_IT_TC5, ENABLE);////���Ǵ�ģ�DMA1_IT_TC4���жϱ�־λ�ĵ�ַ������ʹ��λ�ĵ�ַ
  DMA_Cmd(DMA1_Channel5, ENABLE);

  /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
  DMA_DeInit(DMA1_Channel4);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
  DMA_InitStructure.DMA_MemoryBaseAddr =(u32)sendbuf;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = DMASIZE;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	DMA_SetCurrDataCounter(DMA1_Channel4, 0);//ʣ���ַ����ͼ���������
	
	
	//DMA_ITConfig(DMA1_Channel4, DMA1_IT_TC4, ENABLE);//���Ǵ�ģ�DMA1_IT_TC4���жϱ�־λ�ĵ�ַ������ʹ��λ�ĵ�ַ
	DMA_ITConfig(DMA1_Channel4, DMA_CCR1_TCIE, ENABLE); //ʹ�ܷ�������ж� = DMA1_Channel4->CCR |= 1<<1;
	
	//DMA_Cmd(DMA1_Channel4, ENABLE); //������ɣ����Խ���ENABLE����

  USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);//ʹ��DMA�Ĵ����շ�
}

u16 Uart_Send_Data(void* buffer, u16 size)
{
  if(!size) return 0;
  while (DMA_GetCurrDataCounter(DMA1_Channel4));
  if(buffer) memcpy(sendbuf, buffer,(size > 1024?1024:size));

  DMA_Cmd(DMA1_Channel4, DISABLE);
  DMA1_Channel4->CNDTR = size;
  DMA_Cmd(DMA1_Channel4, ENABLE);
  return size;
}

void Uart_Dma_Clr(void)
{
    DMA_Cmd(DMA1_Channel4, DISABLE);
    DMA1_Channel4->CNDTR=0;
    DMA_Cmd(DMA1_Channel5, DISABLE);
    DMA1_Channel5->CNDTR=DMASIZE ;
    DMA_Cmd(DMA1_Channel5, ENABLE);
}

