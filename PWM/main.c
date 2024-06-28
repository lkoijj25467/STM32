#include "stm32f10x.h"   // Device header
#include "ServoDriver.h"
#include "Delay.h"
#include "Key.h"
int main(){
	Servo_Init();
	Key_Init();
	while(1){
		if(getFlag())
			Servo_SetAngle(0);
		else
			Servo_SetAngle(180);
	}
	return 0;
}
