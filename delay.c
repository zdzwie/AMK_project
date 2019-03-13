 #include "stm32f4xx_hal.h"
 #include "delay.h"
 
 static volatile uint16_t counter = 0;
 void SysTick_Handler(void)
{
	counter++;
}
void delay(int milisekundy)
{
	uint16_t count = counter + milisekundy;
	while(counter <= count) 
	{}
	
}
