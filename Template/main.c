#include "stm32f10x.h"                  // Device header

int main(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef* GPIO_struct;
	GPIO_struct->GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_struct->GPIO_Pin = GPIO_Pin_4;
	GPIO_struct->GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, GPIO_struct);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_4);
	return 0;
}
