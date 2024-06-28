#ifndef __MOTORENCODER_H 
#define __MOTORENCODER_H 
#include "stm32f10x_gpio.h" 

void MotorEncoder_Init(void); 
int Read_Encoder(void);
void Encoder_TIM2(u16 arr, u16 psc);
#endif
