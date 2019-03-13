//Nowy projekt

#include "delay.h"
#include "stm32f4xx_hal.h"
#include  "usart.h"
#include "core.h"

void LED_init(void);
extern uint16_t counter;
void SysTick_Handler(void);
int executionTime = 0;
char data_cc;

int main(void){
	HAL_Init();
	LED_init();
	USART_Init();
	
	USART_WriteString("Berdzik nie umie w programowanie\n\r");
	while(1)
	{
//		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,GPIO_PIN_SET);
//		delay(1000);
//		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_13,GPIO_PIN_RESET);
//		delay(1000);
//		printf("Program execution time: %ds\n\r", executionTime++);
		if(USART_GetChar(&data_cc)){
			USART_PutChar(data_cc);
}
	}
	
}

void LED_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__GPIOG_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOG,&GPIO_InitStruct);
}

