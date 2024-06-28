#include "sys.h"

//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//�ر������ж�
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//���������ж�
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

//ϵͳʱ�ӳ�ʼ������
//pll:ѡ��ı�Ƶ������2��ʼ�����ֵΪ16		 
//void Stm32_Clock_Init(u8 PLL)
//{
//	unsigned char temp=0;   
//	MYRCC_DeInit();		  //��λ������������
// 	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
//	while(!(RCC->CR>>17));//�ȴ��ⲿʱ�Ӿ���
//	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
//	PLL-=2;//����2����λ
//	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
//	RCC->CFGR|=1<<16;	  //PLLSRC ON 
//	FLASH->ACR|=0x32;	  //FLASH 2����ʱ����

//	RCC->CR|=0x01000000;  //PLLON
//	while(!(RCC->CR>>25));//�ȴ�PLL����
//	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
//	while(temp!=0x02)     //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
//	{   
//		temp=RCC->CFGR>>2;
//		temp&=0x03;
//	}    
//}	
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
	AFIO->MAPR|=temp;       //����jtagģʽ
} 

