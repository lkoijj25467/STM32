/***********************************************
公司：轮趣科技(东莞)有限公司
品牌：WHEELTEC
官网：wheeltec.net
淘宝店铺：shop114407458.taobao.com
版本V1.0
修改时间：2020-06-30
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

int PWM=7000;          //PWM控制变量
int Step=500;   //速度渐变速率 相当于加速度
int MortorRun;  //允许电机控制标志位

/**************************************************************************
函数功能：OLED显示屏显示内容
入口参数：无
返回  值：无
**************************************************************************/
void Oled_Show(void)
{  
		OLED_Refresh_Gram(); //刷新显示屏
		OLED_ShowString(00,00,"VelocityDire"); //速度开环控制
			
		
		//显示速度控制值，即PWM值，分正负
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
函数功能：主函数
入口参数：无
返回  值：无
**************************************************************************/
int main(void)
{
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //中断优先级分组
	 delay_init();                //延迟函数初始化
	 JTAG_Set(JTAG_SWD_DISABLE);  //关闭JTAG才能开启OLED显示屏 
	 LED_Init();                  //LED灯初始化
	 KEY_Init();
   OLED_Init();                 //OLED显示屏初始化
   //uart_init(9600);           //串口初始化	 
   TB6612_Init(7199, 0);        //电机驱动外设初始化 使用定时器3 
	 delay_ms(2000);              //延迟等待初始化完成
	
	 while(1)
	  {		
			delay_ms(200);	//延迟1秒
			LED=!LED;    //LED灯闪烁		
		  if(KEY_Scan())MortorRun=!MortorRun; //按下按键MortorRun取反
				
			if(MortorRun)
			{
				//速度循环变化 
				if(PWM<=-7000)Step=500;      //减速到反转最大速度后加速
				else if(PWM>=7000)Step=-500; //加速到正转最大速度后减速
				
				PWM=PWM+Step; //速度渐变
				SetPWM(PWM);  //设置PWM
			}
			else PWM=0,SetPWM(PWM); //电机停止
			
			Oled_Show();  //OLED显示屏显示内容
	  }
}

