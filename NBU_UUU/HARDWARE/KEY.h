#ifndef __KEY_H
#define __KEY_H	
#include "sys.h"
#include "stm32f10x_gpio.h" 

#define KEY GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//�궨��KEYΪ��ȡ����״̬���궨�������߳���ɶ���
//#define KEY PAin(5) //����sys.hͷ�ļ��󣬿���ֱ��ʹ��PAin(5)��ȡ����״̬

void KEY_Init(void);    //KEY����ʼ��
u8 KEY_Scan(void);  	//����ɨ�躯��	

#endif
