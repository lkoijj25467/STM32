#include "key.h"
#include "delay.h"
//����"key.h"��������"stm32f10x.h" ����˴������ظ�����

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO5_InitStructure; //����һ�����ų�ʼ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ�ӣ���STM32��ʹ��IO��ǰ��Ҫʹ�ܶ�Ӧʱ��
	
	GPIO5_InitStructure.GPIO_Pin=GPIO_Pin_5; //����5
	GPIO5_InitStructure.GPIO_Mode=GPIO_Mode_IPU; //�����������ģʽΪ��������ģʽ��Ĭ��Ϊ�ߵ�ƽ����ӵغ�Ϊ�͵�ƽ
	GPIO_Init(GPIOA, &GPIO5_InitStructure); //�����������úõ�GPIO_InitStructure��������ʼ������GPIOA_PIN4
}

u8 KEY_Scan()
{
	static u8 flag_key=1;//�����ɿ���־��staticʹflag_key�ں���ִ�������Ȼ���ڣ�ֵ��Ȼ����
	if(flag_key==1&&KEY==0) //flag_key==1������״̬Ϊ�ɿ���KEY==0�����⵽�������ڰ���״̬�����߽�ϴ���һ�ΰ��¶���
	{                      //��flag_key==0&&KEY==0�����ʾ����һֱ���ڰ��¡�û���ɿ���״̬
		delay_ms(1); //����
		if(KEY==0)
	  {
			flag_key=0; //ȷ�ϰ������£������ɿ���־��0
	    return 1;	  //�������£���������ֵ1
		}
	}
  else if(KEY==1) flag_key=1; //��⵽�����ɿ��������ɿ���־��1
	return 0;//�ް������£���������ֵ0
}
