#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

#include "led.h"

#define LED_RCC		RCC_AHBPeriph_GPIOC
#define LED_PORT	GPIOC
#define LED_PIN		GPIO_Pin_13

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(LED_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = LED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(LED_PORT, &GPIO_InitStructure);
}

void led_on(void)
{
	LED_PORT->BSRR = LED_PIN;
}

void led_off(void)
{
	LED_PORT->BRR = LED_PIN;
}

void led_toggle(void)
{
	if (LED_PORT->ODR & LED_PIN)
		LED_PORT->BRR = LED_PIN;
	else
		LED_PORT->BSRR = LED_PIN;
}
