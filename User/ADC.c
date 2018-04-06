#include "ADC.h"

void ADC_config(void)
{	 
	ADC_InitTypeDef  ADC_InitStructure;	//����ADC��ʼ���ṹ�����
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		 //PA4 ADC ͨ���������  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //ʹ��ɨ�DI�
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADCת������������ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���������ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת�������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;//ת��ͨ��1��
	ADC_Init(ADC1, &ADC_InitStructure); //��ʼ��ADC
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6,1, ADC_SampleTime_239Cycles5);//ѡ��ADC1 ͨ��4(��Ϊ��ADC_4),����1,����239.5���� 
		
	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1
	
	ADC_ResetCalibration(ADC1); //����ADC1У׼�Ĵ���
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�ADC1У׼�������
	ADC_StartCalibration(ADC1);//��ʼADC1У׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�ADC1У׼���
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //ʹ��ADC1�����ʼת��
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
