#include "os.h"
#include "led.h"
#include "usart.h"

#define TASK_STACK_SIZE 256

static uint32_t task1_stack[TASK_STACK_SIZE];
static uint32_t task2_stack[TASK_STACK_SIZE];

static void task1_handler(void)
{
	for (;;) {
		led_on();
		usart_send_byte('A');
	}
}

static void task2_handler(void)
{
	for (;;) {
		led_off();
		usart_send_byte('B');
	}
}

int main()
{
	led_init();
	usart_init();

	os_task_create(task1_handler, task1_stack, TASK_STACK_SIZE);
	os_task_create(task2_handler, task2_stack, TASK_STACK_SIZE);
	os_start();

	return 0;
}
