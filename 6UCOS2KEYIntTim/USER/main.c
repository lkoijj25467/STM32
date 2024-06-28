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

//ALIENTEK Mini STM32�����巶������35  UCOSIIʵ��1-�������  


/////////////////////////UCOSII��������///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			60 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�����ջ	
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);	
 			   
//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO       			8 
//���������ջ��С
#define LED0_STK_SIZE  		    		64
//�����ջ	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);


//tim2��ʱ��2����
//�����������ȼ�
#define tim2_TASK_PRIO       			6 
//���������ջ��С
#define tim2_STK_SIZE  					64
//�����ջ
OS_STK tim2_TASK_STK[tim2_STK_SIZE];
//������
void tim2_task(void *pdata);

//KEY����
//�����������ȼ�
#define KEY_TASK_PRIO 		13
//�����ջ��С
#define KEY_STK_SIZE		64	
//�����ջ
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void key_task(void *pdata); 

// ADC����
#define ADC_TASK_PRIO 		4
#define ADC_STK_SIZE			256
OS_STK ADC_TASK_STK[ADC_STK_SIZE];


float temp;
u16 adcx;
void adc_task(void *pdata);

 int main(void)
 {	
		uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	delay_init();	    	 //��ʱ������ʼ��	
 	EXTIX_Init();		//�ⲿ�жϳ�ʼ��
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
  KEY_Init();
	Adc_Init();
	LCD_Init();
	POINT_COLOR=RED;
	LCD_ShowString(60,60,200,16,16,(uint8_t*)"STM32 ADC TEST");	
	LCD_ShowString(60,150,200,16,16,(uint8_t*)"ADC_CH1_VOL:0.000V");	

	TIM2Int_Init(1999,35999);    //10Khz�ļ���Ƶ�ʣ�������10000Ϊ1000ms   
 
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	
 }

	  
//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	OSTaskCreate(tim2_task,(void *)0,(OS_STK*)&tim2_TASK_STK[tim2_STK_SIZE-1],tim2_TASK_PRIO);	 	
	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	
	OSTaskCreate(adc_task, (void *)0, (OS_STK*)&ADC_TASK_STK[ADC_STK_SIZE-1], ADC_TASK_PRIO);
	
	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}

//LED0����--���жϿ���LED0
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

//��ʱ������LED1����
void tim2_task(void *pdata)
{	  
	while(1)
	{
		printf("\r\n TIM2_INT_Run  \r\n");	
		OSTimeDlyHMSM(0,0,5,0);
	};
}

//KEY����--��������LED0������ 
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
		LCD_ShowxNum(156,130,adcx,4,16,0);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		adcx=temp;
		LCD_ShowxNum(156,150,adcx,1,16,0);//��ʾ��ѹֵ
		temp-=adcx;
		temp*=1000;
		LCD_ShowxNum(172,150,temp,3,16,0X80);
		LED0=!LED0;
	
		OSTimeDlyHMSM(0, 0, 5, 0);
	}	
}
