#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "ADC.h"
#include "GPIO.h"
// ADC≤‚¡øµÁ—π  
 int main(void)
{	
	uint16_t adcx;
	float temp;
	delay_init();
	ADC_Config();
	GPIO_Config();
	while(1){
		adcx = Get_ADC_Average(ADC_Channel_1, 10);
		temp = (float)adcx*(3.3/4096);
		printf("%f", temp);
	}
}


