#ifndef ADC_H__
#define ADC_H__
#include "stdint.h"
#include "stm32f10x_adc.h"

void ADC_Config();
uint16_t Get_ADC(uint8_t ch);
uint16_t Get_ADC_Average(uint8_t ch, uint8_t times);

#endif
