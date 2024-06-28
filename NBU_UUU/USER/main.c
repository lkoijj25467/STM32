/***********************************************
��˾����Ȥ�Ƽ�(��ݸ)���޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com
�汾V1.0
�޸�ʱ�䣺2020-06-30
Allrightsreserved
***********************************************/

#include "delay.h"
#include "usart.h"			
#include "TB6612.h"
#include "motorencoder.h"
#include "usart.h"
#include "led.h"
#include "oled.h"
#include "key.h"

int PWM=7000;          //PWM���Ʊ���
int Step=500;   //�ٶȽ������� �൱�ڼ��ٶ�
int MortorRun;  //���������Ʊ�־λ

/**************************************************************************
�������ܣ�OLED��ʾ����ʾ����
��ڲ�������
����  ֵ����
**************************************************************************/
void Oled_Show(void)
{  
		OLED_Refresh_Gram(); //ˢ����ʾ��
		OLED_ShowString(00,00,"VelocityDire"); //�ٶȿ�������
			
		
		//��ʾ�ٶȿ���ֵ����PWMֵ��������
		OLED_ShowString(00,20,"PWM      :"); 		
		if(PWM>=0)
		{
			OLED_ShowString(80,20,"+");
			OLED_ShowNumber(100,20,PWM,4,12);
		}
		else
		{
			OLED_ShowString(80,20,"-");
			OLED_ShowNumber(100,20,-PWM,4,12);
		}
}

/**************************************************************************
�������ܣ�������
��ڲ�������
����  ֵ����
**************************************************************************/
int main(void)
{
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�ж����ȼ�����
	 delay_init();                //�ӳٺ�����ʼ��
	 JTAG_Set(JTAG_SWD_DISABLE);  //�ر�JTAG���ܿ���OLED��ʾ�� 
	 LED_Init();                  //LED�Ƴ�ʼ��
	 KEY_Init();
   OLED_Init();                 //OLED��ʾ����ʼ��
   //uart_init(9600);           //���ڳ�ʼ��	 
   TB6612_Init(7199, 0);        //������������ʼ�� ʹ�ö�ʱ��3 
	 delay_ms(2000);              //�ӳٵȴ���ʼ�����
	
	 while(1)
	  {		
			delay_ms(200);	//�ӳ�1��
			LED=!LED;    //LED����˸		
		  if(KEY_Scan())MortorRun=!MortorRun; //���°���MortorRunȡ��
				
			if(MortorRun)
			{
				//�ٶ�ѭ���仯 
				if(PWM<=-7000)Step=500;      //���ٵ���ת����ٶȺ����
				else if(PWM>=7000)Step=-500; //���ٵ���ת����ٶȺ����
				
				PWM=PWM+Step; //�ٶȽ���
				SetPWM(PWM);  //����PWM
			}
			else PWM=0,SetPWM(PWM); //���ֹͣ
			
			Oled_Show();  //OLED��ʾ����ʾ����
	  }
}

