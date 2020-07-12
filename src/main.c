#include "led.h"
#include "os.h"

#define TASK_STACK_SIZE 256

static uint32_t task1_stack[TASK_STACK_SIZE];
static uint32_t task2_stack[TASK_STACK_SIZE];

static void task1_handler(void)
{
	for (;;) {
		led_on();
	}
}

static void task2_handler(void)
{
	for (;;) {
		led_off();
	}
}

int main()
{
	led_init();

	os_task_create(task1_handler, task1_stack, TASK_STACK_SIZE);
	os_task_create(task2_handler, task2_stack, TASK_STACK_SIZE);
	os_start();

	return 0;
}
