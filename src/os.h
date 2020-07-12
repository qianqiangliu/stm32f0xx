#ifndef _OS_H_
#define _OS_H_

#include <stdint.h>

int os_task_create(void (*handler)(void), uint32_t *stack, uint32_t stack_size);
int os_start(void);

#endif /* _OS_H_ */
