#include "stm32f10x.h"
#include "stdio.h"
#include "LED.h"
#include "stdlib.h"
#include "delay.h"

int main(){
	LED_init();
	unsigned int t;
	while(1){
		t = rand() % 6000 + 1000;
		Delay_ms(t);
		LED_on();
		Delay_ms(1500);
		LED_off();
		
	}
}