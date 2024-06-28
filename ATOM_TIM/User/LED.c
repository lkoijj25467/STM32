#include "stm32f10x.h"
#define LED_0 GPIO_Pin_1
#define LED_1 GPIO_Pin_2

void LED_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = LED_0 | LED_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void LED0_ON(){
    GPIO_ResetBits(GPIOA, LED_0);
}
void LED0_OFF(){
    GPIO_SetBits(GPIOA, LED_0);
}
void LED1_ON(){
    GPIO_ResetBits(GPIOA, LED_1);
}
void LED1_OFF(){
    GPIO_SetBits(GPIOA, LED_1);
}