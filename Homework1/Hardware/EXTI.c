#include "stm32f10x.h"                  // Device header

void EXTI_init(){
	// PA0 WK_UP
	EXTI_InitTypeDef EXTI_Structure;
	EXTI_Structure.EXTI_Line = EXTI_Line0;
	EXTI_Structure.EXTI_LineCmd = ENABLE;
	EXTI_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Structure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Structure);
	// PC5 KEY0
	EXTI_Structure.EXTI_Line = EXTI_Line5;
	EXTI_Structure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Structure);
	// PA15 KEY1
	EXTI_Structure.EXTI_Line = EXTI_Line15;
	EXTI_Init(&EXTI_Structure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource5);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
}