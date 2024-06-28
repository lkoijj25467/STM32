#include "stm32f10x.h"                  // Device header
#include "ADC.h"
#include "delay.h"


void ADC_Config(){
	ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);    // 72/6 = 12MHz
	

	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	// 设置指定ADC的规则组通道，设置它们的转换顺序和采样相同
	//ADC1_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	// 使能ADC1
	ADC_Cmd(ADC1, ENABLE);
	// 重置指定ADC的校准寄存器
	ADC_ResetCalibration(ADC1);
	// check
	while(ADC_GetResetCalibrationStatus(ADC1));
	// 开始校准状态
	ADC_StartCalibration(ADC1);
	// 
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	//while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));				// 等待转换结束
}

uint16_t Get_ADC(uint8_t ch){
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1);
}

uint16_t Get_ADC_Average(uint8_t ch, uint8_t times){
	uint32_t temp_val = 0;
	uint8_t t;
	for(t = 0; t < times; t++){
		temp_val += Get_ADC(ch);
		delay_ms(5);
	}
	return temp_val/times;
}
