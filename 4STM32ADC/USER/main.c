#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"

//ALIENTEK Mini STM32开发板范例代码15  ADC实验  

 int main(void)
 { 
	u16 adcx;
	float temp;
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
 	LCD_Init();
 	Adc_Init();		  		//ADC初始化	    
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,60,200,16,16,(uint8_t*)"STM32 ADC TEST");	
	
	//显示提示信息
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,(uint8_t*)"ADC_CH1_VAL:");	      
	LCD_ShowString(60,150,200,16,16,(uint8_t*)"ADC_CH1_VOL:0.000V");	 
   
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(156,150,adcx,1,16,0);//显示电压值
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(172,150,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(250);	
	}											    
}	











社会存在
{
  自然地理环境（影响因素）
  人口因素（影响因素）
  物质生产方式（决定性力量）{
生产力{
	劳动资料（生产工具是区分社会经济时代的客观根据）
	劳动对象（现实生产的必要前提）
	劳动者（生产力中最活跃的因素）
}
生产关系{
	生产资料所有制关系（最基本、决定性的内容）
	生产中人与人的关系
	产品分配关系
}
  }
}
