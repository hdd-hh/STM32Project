#include "commands.h"
#include "usart.h"

void ProcessCommand(char *command) {
    if (strncmp(command, "AT+", 3) == 0) {
        // 判断指令类型
        if (strcmp(command, "AT+TEST") == 0) {
            USART1_SendString("OK: TEST command received\r\n");
        } else if (strcmp(command, "AT+HELP") == 0) {
            USART1_SendString("OK: Available commands: AT+TEST, AT+HELP\r\n");
        } else {
            USART1_SendString("ERROR: Unknown command\r\n");
        }
    } else {
        // 如果不是AT指令，直接返回接收到的内容
        USART1_SendString("Received: ");
        USART1_SendString(command);
        USART1_SendString("\r\n");
    }
}
