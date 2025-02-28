#include "stm32f10x.h"
#include "usart.h"

int main(void) {
    // 初始化串口
    USART1_Init();

    // 发送欢迎信息
    USART1_SendString("System Started!\r\n");

    while (1) {
        // 主循环可以执行其他任务
        // 串口接收和发送功能已经在中断中处理
    }
}
