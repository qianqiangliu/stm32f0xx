#ifndef _USART_H_
#define _USART_H_

void usart_init(void);
void usart_send_byte(unsigned char byte);
void usart_send_string(const char *str);

#endif /* _USART_H_ */
