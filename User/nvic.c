#include "nvic.h"

void Init_NVIC(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	
	#ifdef  VECT_TAB_RAM  							//向量表基地址选择
	  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);  	//将0x20000000地址作为向量表基地址(RAM)
	#else  
	  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); //将0x08000000地址作为向量表基地址(FLASH)  
	#endif
	
	/* Enable the USART1 Interrupt */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断组 为2 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//配置串口1为中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 	//设置占先优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//设置副优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//使能串口1中断
	NVIC_Init(&NVIC_InitStructure);							  	//根据参数初始化中断寄存器

  USART_ClearFlag(USART1, USART_FLAG_TC); 

	/* Enable the DMA1 channel4 tx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;			//配置DMA TX为中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 	//设置占先优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//设置副优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//使能中断
	NVIC_Init(&NVIC_InitStructure);							  	//根据参数初始化中断寄存器
	
	DMA_ClearFlag(DMA1_FLAG_TC4); 

	/* Enable the DMA1 channel5 rx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;			//配置DMA RX为中断源
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//设置占先优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  	//设置副优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  	//使能中断
	NVIC_Init(&NVIC_InitStructure);							  	//根据参数初始化中断寄存器
	
	DMA_ClearFlag(DMA1_FLAG_TC5); 
}
