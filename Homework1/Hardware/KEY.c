#include "stm32f10x.h"                  // Device header
#include "EXTI.h"

void Key_init(){
	EXTI_init();
	GPIO_InitTypeDef GPIO_Structure;
	// PA0 VCC3.3
	GPIO_Structure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Structure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz;
	// PC5 GND
	GPIO_Structure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Structure.GPIO_Pin = GPIO_Pin5;
}