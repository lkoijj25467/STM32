#ifndef __DELAY_H
#define __DELAY_H 			   
#include "sys.h"  

#define Delay_ms delay_ms
#define Delay_us delay_us

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























