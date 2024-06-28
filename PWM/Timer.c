#include "stm32f10x.h"                  // Device header

void Timer_Init(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_Structure;
	TIM_Structure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_Structure.TIM_CounterMode = TIM_CounterMode_Down;
	TIM_Structure.TIM_Period = 7200 - 1;
	TIM_Structure.TIM_Prescaler = 0;
	TIM_Structure.TIM_RepetitionCounter = ;
}