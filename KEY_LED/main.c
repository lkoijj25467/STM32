#include "stm32f10x.h"                  // Device header
#include "KEY.h"
#include "LED.h"
#include "OLED.h"
#include "COUNT_SENSOR.h"


int main(){
	
	OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(2, 1, "114514");
	CountSensor_Init();
	OLED_Clear();
	while(1){
		OLED_ShowNum(2, 1, GetCount(), 3);
	}
}
