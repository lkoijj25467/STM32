#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "adc.h"

//ALIENTEK Mini STM32�����巶������15  ADCʵ��  

 int main(void)
 { 
	u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 	LCD_Init();
 	Adc_Init();		  		//ADC��ʼ��	    
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,60,200,16,16,(uint8_t*)"STM32 ADC TEST");	
	
	//��ʾ��ʾ��Ϣ
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,200,16,16,(uint8_t*)"ADC_CH1_VAL:");	      
	LCD_ShowString(60,150,200,16,16,(uint8_t*)"ADC_CH1_VOL:0.000V");	 
   
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(156,150,adcx,1,16,0);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(172,150,temp,3,16,0X80);
		LED0=!LED0;
		delay_ms(250);	
	}											    
}	











������
{
  ��Ȼ����������Ӱ�����أ�
  �˿����أ�Ӱ�����أ�
  ����������ʽ��������������{
������{
	�Ͷ����ϣ�����������������ᾭ��ʱ���Ŀ͹۸��ݣ�
	�Ͷ�������ʵ�����ı�Ҫǰ�ᣩ
	�Ͷ��ߣ������������Ծ�����أ�
}
������ϵ{
	�������������ƹ�ϵ��������������Ե����ݣ�
	�����������˵Ĺ�ϵ
	��Ʒ�����ϵ
}
  }
}