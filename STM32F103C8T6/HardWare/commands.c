#include "commands.h"
#include "usart.h"

void ProcessCommand(char *command) {
	if (strlen(command) == 0) return; // 忽略空指令
	if (strncmp(command, "AT+", 3) == 0) {
        // 判断指令类型
		if (strcmp(command, "AT+OK?") == 0) {
			USART1_SendString("OK!\r\n");
		} else if (strcmp(command, "AT+FACTORYRESET") == 0) {
			USART1_SendString("System Factory Reset Success!\r\n");
		} else if (strcmp(command, "AT+RESET") == 0) {
			USART1_SendString("System Started!\r\n");
		}else {
			USART1_SendString("ERROR: Unknown command\r\n");
		}
	} else {
        // 如果不是AT指令，直接返回接收到的内容
        USART1_SendString("Received: ");
        USART1_SendString(command);
        USART1_SendString("\r\n");
	}
}
