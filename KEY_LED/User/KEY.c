#include "stm32f10x.h"
#include "Delay.h"
#define KEY GPIO_Pin_9

void KEY_INIT(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = KEY;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
uint8_t KEY_GET(void){
    uint8_t KeyNum = 0;
	if(GPIO_ReadInputDataBit(GPIOA, KEY) == 0){
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA, KEY) == 0);
		Delay_ms(20);
		KeyNum = 1;
	}
	
    return KeyNum;
}