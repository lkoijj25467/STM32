#include "stm32f10x.h"                  // Device header
#include "LED.h"

void LED_init(){
	RCC->APB2ENR |= (1 << 2);
	int MODn = 4*LED_PIN;
	int CNFn = MODn + 2;
	GPIO_LED->CRL |= (3 << MODn);
	GPIO_LED->CRL |= (0 << CNFn);
}

void LED_on(){
	int ODRn = LED_PIN;
	GPIO_LED->ODR |= (1 << ODRn);
}

void LED_off(){
	int ODRn = LED_PIN;
	GPIO_LED->ODR |= (0 << ODRn);
}