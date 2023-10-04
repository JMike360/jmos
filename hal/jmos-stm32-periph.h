
#ifndef _PERIPH_H
#define _PERIPH_H

#define HIGH 1
#define LOW 0

typedef unsigned long int uint32;
typedef volatile uint32 reg_t;
typedef unsigned short int uint16;

typedef struct rcc_t {
    reg_t CR;        // 0x00
    reg_t CFGR;      // 0x04
    reg_t CIR;       // 0x08
    reg_t APB2RSTR;  // 0x0C
    reg_t APB1RSTR;  // 0x10
    reg_t AHBENR;    // 0x14
    reg_t APB2ENR;   // 0x18
    reg_t APB1ENR;   // 0x1C
    reg_t BDCR;      // 0x20
    reg_t CSR;       // 0x24
    reg_t AHBRSTR;   // 0x28
    reg_t CFGR2;     // 0x2C
    reg_t CFGR3;     // 0x30
    reg_t CR2;       // 0x34
}rcc_t;

typedef struct gpio_t{
    reg_t MODER;    // 0x00
    reg_t OTYPER;   // 0x04
    reg_t OSPEEDR;  // 0x08
    reg_t PUPDR;    // 0x0C
    reg_t IDR;      // 0x10
    reg_t ODR;      // 0x14
    reg_t BSRR;     // 0x18
    reg_t LCKR;     // 0x1C
    reg_t AFRL;     // 0x20
    reg_t AFRH;     // 0x24
    reg_t BRR;      // 0x28
}gpio_t;

typedef struct usart_t{
    reg_t CR1;       // 0x00
    reg_t CR2;       // 0x04
    reg_t CR3;       // 0x08
    reg_t BRR;       // 0x0C
    reg_t GTPR;      // 0x10
    reg_t RTOR;      // 0x14
    reg_t RQR;       // 0x18
    reg_t ISR;       // 0x1C
    reg_t ICR;       // 0x20
    reg_t RDR;       // 0x24
    reg_t TDR;       // 0x28
}usart_t;

#define RCC     ((rcc_t *)  (0x40021000))
#define GPIOA   ((gpio_t *) (0x48000000))
#define GPIOB   ((gpio_t *) (0x48000400))
#define GPIOC   ((gpio_t *) (0x48000800))
#define GPIOD   ((gpio_t *) (0x48000C00))
#define GPIOF   ((gpio_t *) (0x48001400))
#define USART1  ((usart_t *)(0x40013800))


#endif
