#include "jmos-stm32-usart.h"

void init_usart(uint32 brr){
	// need to first make sure it's off
	RCC->APB2ENR &= ~USART_EN;

	// --- Configure the USART1 GPIO block --- //
    RCC->AHBENR |= GPIOA_EN;
    
    uint32 moder_val = (USART_ALTFN << RX_PIN*2) | (USART_ALTFN << TX_PIN*2);       
    GPIOA->MODER &= ~moder_val;
	GPIOA->MODER |= moder_val; // MODER, because alternate gpio fns :)
                                                                       
	uint32 tx_afr_offset = (TX_PIN % 8) * AFR_SEL_SIZE;
	uint32 rx_afr_offset = (RX_PIN % 8) * AFR_SEL_SIZE;
	
    uint32 afrh_val = (AFR_USART << tx_afr_offset) | (AFR_USART << rx_afr_offset);
    GPIOA->AFRH &= ~afrh_val;
    GPIOA->AFRH |= afrh_val;
     
	RCC->APB2ENR |= USART_EN; 
                                                                                                                                                                                                    
    // --- Configure Baud to 9600 --- //
    USART1->BRR = brr;
        // 0x1368; // baud = fclk / BRR ::: 0x1388 * 0d9600 = fclk
 
    // --- Enable basic fns in USART1 register --- //
    uint32 cr1_val = TX_EN | RX_EN | UE_EN;
    USART1->CR1 &= ~cr1_val;
    USART1->CR1 |= cr1_val;
}

int putchar(unsigned char c){
    while((USART1->ISR & USART_TXE) != USART_TXE); // wait for TDR to be empty
    USART1->TDR = (uint32)c;
    return c;
}

int finish_tx(){
   while((USART1->ISR & USART_TC) != USART_TC);
   return 0;
}

unsigned char getchar(){
    while((USART1->ISR & USART_RXNE) != USART_RXNE);
    uint32 c = USART1->RDR;
    return (unsigned char)c;
}

void print(const char * str){
    int i = 0;
    while(str[i] != '\0'){
        putchar(str[i]);
        i++;
    }
    finish_tx();
}

void println(const char * str){
    print(str);
    putchar('\n');
    putchar('\r');
    finish_tx();
}
