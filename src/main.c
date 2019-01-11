#include "led.h"

void delay(int n)
{
	while (n != 0) {
		n--;
	}
}

int main()
{
	led_init();

	for (;;) {
		delay(800000);
		led_toggle();
	}

	return 0;
}
