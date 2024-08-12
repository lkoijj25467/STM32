#include "../Drivers/SYSTEM/delay/delay.h"
#include "../Drivers/SYSTEM/sys/sys.h"
#include "../Drivers/SYSTEM/usart/usart.h"
#include "../Drivers/BSP/LED/led.h"
#include "../Drivers/BSP/KEY/key.h"

int main(){
	delay_init(400);
	HAL_Init();
	led_init();
	KEY_EXTI_Init();
//	key_init();
//	while(1){
//		if(WK_UP)
//			LED0(0);
//		else
//			LED0(1);
//	}
	while(1){}
}

