#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <string.h>

#define BUFFER_SIZE 128

void USART1_Init(void);
void USART1_SendString(char *str);

#endif
