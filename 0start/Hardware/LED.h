#ifndef LED_H__
#define LED_H__
#define GPIO_LED GPIOA
#define LED_PIN 3
void LED_init();
void LED_on();
void LED_off();







#endif

/*
    DOCUMENT
*/
#ifdef GPIO_TYPE_DEF

typedef struct{
    __IO uint32_t CRL;              //0-7号口，MODEn[4*n+1:4*n], CNF[4*n+3:4*n+2]
    /*
CNF:  INPUT MODE (MODE[1:0]=00)
        00: Analog Mode 模拟方式
        01: Floating Input 上浮输入
        10: Input With Pull-up/Pull-down 上拉电阻/下拉电阻输入
      OUTPUT MODE (MODE[1:0]>00)
        00: General purpose ouput push-pull 推挽输出
        01: General Purpose output Open-drain 开漏输出
MODE:   00: Input mode (reset)
        01: Output mode max speed 10Mhz
        10: Output mode max speed 2Mhz
        11: Output mode max speed 50Mhz
**/
    __IO uint32_t CRH;              //8-15号口,
    __IO uint32_t IDR;              //输入数据寄存器, Bits0-15: IDRn[n]
    __IO uint32_t ODR;              //输出数据寄存器, Bits0-15: ODRn[n]
    __IO uint32_t BSRR;             //Bit Set/Reset Register, BSn[n], BRn[16+n]
/*
BS:     0: No action on ODR
        1: Set the ODR
BR:     0: No action on ODR
        1: Set the ODR
**/
    __IO uint32_t BRR;              //Bit Reset Register, BRn[n]
    __IO uint32_t LCKR;             //Configure Lock Register
}GPIO_TypeDef;
#endif

#ifdef GPIO_TYPE_DEF
#define GPIOA       ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB       ((GPIO_TpyeDef*)GPIOB_BASE)
#define GPIOC
#endif

/*
    RCC_TypeDef
*/
#ifdef RCC_TYPE_DEF
typedef struct{
    __IO uint32_t CR;               //Clock Control Register
/*
bit31-30:   reserved
bit29:      PLL3 RDY
*/
    __IO uint32_t CFGR;             //Cofigure Register
/*
    bit26-24: Microcontoller clock output                   * This clock output may have some truncated cycles at startup or during MCO clock source switching.
                00xx: No clock
                0100: SystemColock Selected
                0101: HSI Clock Selected
                0110: HSE Clock Selected
                0111: PLL Clock divided by 2 selected
                1000: PLL2 clock selected
                1001: PLL3 clock selected                   
    bit22:    USB OTG FS prescaler     
    bit21-18: PLL multiplication factor   These bits can be written only when PLL is disabled.
*/
    __IO uint32_t CIR;              //
    __IO uint32_t APB2RSTR;
    __IO uint32_t APB1RSTR;
    __IO uint32_t AHBENR;
    __IO uint32_t APB1ENR;
    __IO uint32_t APB2ENR;
    __IO uint32_t BDCR;
    __IO uint32_t CSR;
}RCC_TypeDef
#endif