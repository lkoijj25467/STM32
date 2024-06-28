#include "TB6612.h"  

/**************************************************************************
�������ܣ�TB6612��ʼ������
��ڲ�������ʱ��3�������� ��ʱ��3Ԥ��Ƶϵ��
����  ֵ����
**************************************************************************/
void TB6612_Init(int arr, int psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ�����ų�ʼ���Ľṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue; //����һ����ʱ�жϵĽṹ��	
	TIM_OCInitTypeDef TIM_OCInitTypeStrue; //����һ��PWM����Ľṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //ʹ��GPIOBʱ�ӣ�GPIOB������APB2ʱ���£���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ��ͨ�ö�ʱ��3ʱ��
	
	//TB6612���Ʒ�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP; //�����������ģʽΪ�������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //��������ٶ�Ϊ50MHZ
	GPIO_Init(GPIOB, &GPIO_InitStructure); //�����������úõ�GPIO_InitStructure��������ʼ������
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_12|GPIO_Pin_13); //��ʼ���������ŵ͵�ƽ

	//TB6612PWM�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//����0
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //�����������ģʽ����ʱ������ΪB1���Ÿ��ù���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz; //�������������ٶ�Ϊ50MHZ
  GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ������GPIOB1
	
	TIM_TimeBaseInitStrue.TIM_Period=arr; //����ģʽΪ���ϼ���ʱ����ʱ����0��ʼ����������������arrʱ������ʱ�жϷ�����
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc; //Ԥ��Ƶϵ��������ÿһ��������ʱ��
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up; //����ģʽ�����ϼ���
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1; //һ�㲻ʹ�ã�Ĭ��TIM_CKD_DIV1
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStrue); //����TIM_TimeBaseInitStrue�Ĳ�����ʼ����ʱ��TIM3
	
	TIM_OCInitTypeStrue.TIM_OCMode=TIM_OCMode_PWM1; //PWMģʽ1������ʱ������С��TIM_Pulseʱ����ʱ����ӦIO�����Ч��ƽ
	TIM_OCInitTypeStrue.TIM_OCPolarity=TIM_OCNPolarity_High; //�����Ч��ƽΪ�ߵ�ƽ
	TIM_OCInitTypeStrue.TIM_OutputState=TIM_OutputState_Enable; //ʹ��PWM���
	TIM_OCInitTypeStrue.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OC4Init(TIM3, &TIM_OCInitTypeStrue); //��TIM_OCInitTypeStrue������ʼ����ʱ��3ͨ��4

  //TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��

	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Disable); //CH4Ԥװ��ʹ�� ʹ�ܺ�ı�TIM_Pulse(��PWM)��ֵ������Ч����ʹ�����¸�������Ч
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //TIM3Ԥװ��ʹ��
	
	TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��TIM3
}

/**************************************************************************
�������ܣ�����TIM3ͨ��4PWMֵ
��ڲ�����PWMֵ
����  ֵ����
**************************************************************************/
void SetPWM(int pwm)
{
  if(pwm>=0)//pwm>=0 (BIN1, BIN2)=(0, 1) ��ת ˳ʱ��
  {
		PBout(13)=0; //BIN1=0
		PBout(12)=1; //BIN2=1
		TIM3->CCR4=pwm;
		TIM_SetCompare4(TIM3, pwm);
  }
  else if(pwm<0)//pwm<0 (BIN1, BIN2)=(1, 0) ��ת ��ʱ��
  {
		PBout(13)=1; //BIN1=1
		PBout(12)=0; //BIN2=0
		TIM3->CCR4=-pwm;
		TIM_SetCompare4(TIM3, -pwm);
  }
}

