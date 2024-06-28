#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "inv_mpu.h"
#include "mpu6050.h"
#include "delay.h"
#include <stdio.h>

int main(){
	OLED_Init();
	delay_init();
	MPU_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	float pitch, roll, yaw;
	char* strpitch = "PI: xxxxxxx";
	char* strroll = "RO: xxxxxxx";
	char* stryaw = "YW: xxxxxxx";
	while(mpu_dmp_init()){
		delay_ms(20);
	}
	while(1){
		mpu_dmp_get_data(&pitch, &roll, &yaw);
		sprintf(strpitch, "PI: %f", pitch);
		sprintf(strroll, "RO: %f", roll);
		sprintf(stryaw, "YW: %f", yaw);
		OLED_ShowString(1, 1, strpitch);
		OLED_ShowString(2, 1, strroll);
		OLED_ShowString(3, 1, stryaw);
	}
	return 0;
}
