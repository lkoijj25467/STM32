#include "led.h"
#include "key.h"
#include "exti.h"
#include "delay.h"
#include "sys.h"
#include "includes.h" 
#include "usart.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"

//ALIENTEK Mini STM32开发板范例代码35  UCOSII实验1-任务调度  


/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			60 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	
 			   
//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			8 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);


//tim2定时器2任务
//设置任务优先级
#define tim2_TASK_PRIO       			6 
//设置任务堆栈大小
#define tim2_STK_SIZE  					64
//任务堆栈
OS_STK tim2_TASK_STK[tim2_STK_SIZE];
//任务函数
void tim2_task(void *pdata);

//KEY任务
//设置任务优先级
#define KEY_TASK_PRIO 		13
//任务堆栈大小
#define KEY_STK_SIZE		64	
//任务堆栈
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void key_task(void *pdata); 

// ADC任务
#define ADC_TASK_PRIO 		4
#define ADC_STK_SIZE			256
OS_STK ADC_TASK_STK[ADC_STK_SIZE];


float temp;
u16 adcx;
void adc_task(void *pdata);

 int main(void)
 {	
		uart_init(9600);	 	//串口初始化为9600
	delay_init();	    	 //延时函数初始化	
 	EXTIX_Init();		//外部中断初始化
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	LED_Init();		  	//初始化与LED连接的硬件接口
  KEY_Init();
	Adc_Init();
	LCD_Init();
	POINT_COLOR=RED;
	LCD_ShowString(60,60,200,16,16,(uint8_t*)"STM32 ADC TEST");	
	LCD_ShowString(60,150,200,16,16,(uint8_t*)"ADC_CH1_VOL:0.000V");	

	TIM2Int_Init(1999,35999);    //10Khz的计数频率，计数到10000为1000ms   
 
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	
 }

	  
//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	OSTaskCreate(tim2_task,(void *)0,(OS_STK*)&tim2_TASK_STK[tim2_STK_SIZE-1],tim2_TASK_PRIO);	 	
	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	
	OSTaskCreate(adc_task, (void *)0, (OS_STK*)&ADC_TASK_STK[ADC_STK_SIZE-1], ADC_TASK_PRIO);
	
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//LED0任务--由中断控制LED0
void led0_task(void *pdata)
{	 	
	while(1)
	{
		//LED0=0;
		//OSTimeDlyHMSM(0,0,3,0);
		//LED0=1;
		OSTimeDlyHMSM(0,0,5,0);
	};
}

//定时器控制LED1任务
void tim2_task(void *pdata)
{	  
	while(1)
	{
		printf("\r\n TIM2_INT_Run  \r\n");	
		OSTimeDlyHMSM(0,0,5,0);
	};
}

//KEY任务--按键控制LED0的任务 
void key_task(void *pdata) 
{   
	while(1)
	{	    
		printf("\r\n                  KEY_INT_OK  \r\n");	
		OSTimeDlyHMSM(0,0,5,500);
	} 
} 

void adc_task(void *pdata){
	while(1)
	{
		 printf("\r\n                               ADC_RUN  \r\n");	
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		LCD_ShowxNum(156,130,adcx,4,16,0);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(156,150,adcx,1,16,0);//显示电压值
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(172,150,temp,3,16,0X80);
		LED0=!LED0;
	
		OSTimeDlyHMSM(0, 0, 5, 0);
	}	
}
