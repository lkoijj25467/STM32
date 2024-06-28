#include "stm32f10x.h"                  // Device header
#include "LED.h"

void LED_init(){
	RCC->APB2ENR |= (1 << 2);
	int MODn = 4*3;
	int CNFn = MODn + 2;
	GPIOA->CRL |= (1 << MODn);
	GPIOA->CRL &= ~(11 << CNFn);
}

void LED_on(){
	int ODRn = 3;
	GPIOA->ODR |= (1 << ODRn);
}

void LED_off(){
	int ODRn = 3;
	GPIOA->ODR &= ~(1 << ODRn);
}