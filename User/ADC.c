#include "ADC.h"

void ADC_config(void)
{	 
	ADC_InitTypeDef  ADC_InitStructure;	//¶¨ÒåADC³õÊ¼»¯½á¹¹Ìå±äÁ¿
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		 //PA4 ADC Í¨ÓÃÍÆÍìÊä³ö  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1ºÍADC2¹¤×÷ÔÚ¶ÀÁ¢Ä£Ê½
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //Ê¹ÄÜÉ¨ÃDIè
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADC×ª»»¹¤×÷ÔÚÁ¬ĞøÄ£Ê½
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ÓĞÈí¼ş¿ØÖÆ×ª»»
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//×ª»»Êı¾İÓÒ¶ÔÆë
	ADC_InitStructure.ADC_NbrOfChannel = 1;//×ª»»Í¨µÀ1¸ö
	ADC_Init(ADC1, &ADC_InitStructure); //³õÊ¼»¯ADC
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6,1, ADC_SampleTime_239Cycles5);//Ñ¡ÔñADC1 Í¨µÀ4(ÒòÎªÊÇADC_4),´ÎĞò1,²ÉÑù239.5ÖÜÆÚ 
		
	ADC_Cmd(ADC1, ENABLE);//Ê¹ÄÜADC1
	
	ADC_ResetCalibration(ADC1); //ÖØÖÃADC1Ğ£×¼¼Ä´æÆ÷
	while(ADC_GetResetCalibrationStatus(ADC1));//µÈ´ıADC1Ğ£×¼ÖØÖÃÍê³É
	ADC_StartCalibration(ADC1);//¿ªÊ¼ADC1Ğ£×¼
	while(ADC_GetCalibrationStatus(ADC1));//µÈ´ıADC1Ğ£×¼Íê³É
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //Ê¹ÄÜADC1Èí¼ş¿ªÊ¼×ª»»
}

u16 TestAdc(void)
{
	u16 adc;
	if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==SET)
	{
		adc=ADC_GetConversionValue(ADC1);
	}
	return adc;
}
