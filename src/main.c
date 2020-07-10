#include <stm32f0xx.h>

#include "led.h"

int main()
{
	led_init();

    if (SysTick_Config(8000)) {
        while (1);
    }

	for (;;) {
	}

	return 0;
}

void SysTick_Handler(void)
{
    led_toggle();
}
