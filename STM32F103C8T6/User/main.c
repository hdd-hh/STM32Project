#include "stm32f10x.h"
#include "usart.h"
#include "timer.h"

int main(void) {

    USART1_Init();   // 初始化串口
    TIM2_Init(10);   //初始化定时器

    // 发送欢迎信息
    USART1_SendString("System Started!\r\n");

    while (1) {
        // 主循环可以执行其他任务
        // 串口接收和发送功能已经在中断中处理
    }
}
