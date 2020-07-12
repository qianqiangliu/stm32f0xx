#include <stm32f0xx.h>

#include "os.h"

#ifndef OS_CONFIG_MAX_TASKS
#define OS_CONFIG_MAX_TASKS 8
#endif

struct task {
	uint32_t sp;
	void (*handler)(void);
};

struct task_table {
	struct task tasks[OS_CONFIG_MAX_TASKS];
	uint32_t current_task;
	uint32_t size;
};

struct task *os_curr_task;
struct task *os_next_task;

static struct task_table task_table;

static void task_finished(void)
{
	while (1);
}

int os_task_create(void (*handler)(void), uint32_t *stack, uint32_t stack_size)
{
	struct task *task;

	if (task_table.size >= OS_CONFIG_MAX_TASKS)
		return -1;

	task = &task_table.tasks[task_table.size];
	/* reserve 16 word to store registers */
	task->sp = (uint32_t)(stack + stack_size - 16);
	task->handler = handler;

	/* XPSR */
	stack[stack_size - 1] = 0x01000000;
	/* PC */
	stack[stack_size - 2] = (uint32_t)task->handler;
	/* LR */
	stack[stack_size - 3] = (uint32_t)task_finished;

	task_table.size++;

	return 0;
}

int os_start(void)
{
	NVIC_SetPriority(PendSV_IRQn, 0xff);

	if (SysTick_Config(24000))
		return -1;

	os_curr_task = &task_table.tasks[task_table.current_task];
	if (!os_curr_task)
		return -1;

	/* set PSP to the top of the task's stack */
	__asm volatile ("msr PSP, %0\n" : : "r" (os_curr_task->sp));
	/* switch to PSP, unprivilleged mode */
	__asm volatile ("msr control, %0" : : "r" (0x03) : "memory");
	/* exec. ISB after changing CONTORL (recommended) */
	__asm volatile ("isb");

	os_curr_task->handler();

	return 0;
}

void SysTick_Handler(void)
{
	os_curr_task = &task_table.tasks[task_table.current_task];
	task_table.current_task++;
	if (task_table.current_task >= task_table.size)
		task_table.current_task = 0;
	os_next_task = &task_table.tasks[task_table.current_task];
	/* trigger PendSV */
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
}
