#ifndef USART_H
#define USART_H

#include "jmos-stm32-periph.h"

#define USART_EN ((uint32)0x00004000)
#define GPIOA_EN ((uint32)0x00020000)
#define USART_ALTFN ((uint32)0x02)
#define RX_PIN 10
#define TX_PIN 9

#define AFR_USART ((uint32)0x01)
#define AFR_SEL_SIZE 4

#define TX_EN ((uint32)(HIGH << 3))
#define RX_EN ((uint32)(HIGH << 2))
#define UE_EN ((uint32)(HIGH << 0))

#define USART_TXE  ((uint32)(HIGH << 7))
#define USART_TC   ((uint32)(HIGH << 6))
#define USART_RXNE ((uint32)(HIGH << 5))

void init_usart();
         
int putchar(unsigned char c);

int finish_tx();

unsigned char getchar();

#endif
