#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

void TIM2_Init(uint16_t timeout_ms);
void TIM2_Start(void);
void TIM2_Stop(void);

#endif
