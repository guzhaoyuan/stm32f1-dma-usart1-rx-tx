#include "ADC.h"

void ADC_config(void)
{	 
	ADC_InitTypeDef  ADC_InitStructure;	//定义ADC初始化结构体变量
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		 //PA4 ADC 通用推挽输出  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; //使能扫肈I�
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ADC转换工作在连续模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//有软件控制转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//转换数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;//转换通道1个
	ADC_Init(ADC1, &ADC_InitStructure); //初始化ADC
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6,1, ADC_SampleTime_239Cycles5);//选择ADC1 通道4(因为是ADC_4),次序1,采样239.5周期 
		
	ADC_Cmd(ADC1, ENABLE);//使能ADC1
	
	ADC_ResetCalibration(ADC1); //重置ADC1校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));//等待ADC1校准重置完成
	ADC_StartCalibration(ADC1);//开始ADC1校准
	while(ADC_GetCalibrationStatus(ADC1));//等待ADC1校准完成
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //使能ADC1软件开始转换
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
