#include "timer.h"
#include "usart.h"
#include "commands.h"

extern char rx_buffer[];
extern uint8_t rx_index;

void TIM2_Init(uint16_t timeout_ms) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_Period = timeout_ms * 10 - 1;  // 超时时间计算（单位：0.1ms）
    TIM_InitStructure.TIM_Prescaler = 7200 - 1;          // 72MHz / 7200 = 10kHz → 每0.1ms计数一次
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_InitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void TIM2_Start(void) {
    TIM_SetCounter(TIM2, 0);  // 重置计数器
    TIM_Cmd(TIM2, ENABLE);    // 启动定时器
}

void TIM2_Stop(void) {
    TIM_Cmd(TIM2, DISABLE);   // 停止定时器
}

// 定时器中断服务函数
void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        if (rx_index > 0) { // 缓冲区有数据
            rx_buffer[rx_index] = '\0';
            ProcessCommand(rx_buffer); // 处理指令或数据
            rx_index = 0;              // 重置缓冲区索引
        }
        TIM2_Stop(); // 停止定时器
    }
}
