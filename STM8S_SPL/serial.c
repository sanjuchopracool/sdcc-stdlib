#include "serial.h"

#define UART1_SR	*(__IO uint8_t*)0x5230
#define UART1_DR	*(__IO uint8_t*)0x5231
#define UART1_BRR1	*(__IO uint8_t*)0x5232
#define UART1_BRR2	*(__IO uint8_t*)0x5233
#define UART1_CR2	*(__IO uint8_t*)0x5235
#define UART1_CR3	*(__IO uint8_t*)0x5236

#define UART_CR2_TEN (1 << 3)
#define UART_SR_TXE (1 << 7)

void putchar(char c)
{
    while(!(UART1_SR & UART_SR_TXE));
    UART1_DR = c;
}

void setUpSerial()
{
    UART1_CR2 = UART_CR2_TEN; //enable tx

    // 9600 baud
    UART1_BRR2 = 0x03;
    UART1_BRR1 = 0x68;
}
