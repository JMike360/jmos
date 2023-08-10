#include "jmos-stm32-init.h"
#include "jmos-stm32-periph.h"
#define HIGH 1
#define LOW 0

void init_led3(){
    // unsigned long int RCC = 0x40021000;
    // unsigned int AHBENR = 0x14;
    unsigned int GPIOC_EN = 0x00080000;
    // led 3 = GPIOC pin 9
    // led 4 = GPIOC pin 8
   
    // Not sure if this pattern is necessary, as this should be a set-enable reg
    // I think this might work equally as well without first reading the value of the ahbenr
    /* unsigned int* ahb_ptr = (void *)(RCC->AHBENR);
    unsigned int ahb_val = *ahb_ptr;
    ahb_val |= GPIOC_EN;
    *ahb_ptr = ahb_val; */
    RCC->AHBENR |= GPIOC_EN;

    // unsigned long int GPIOC = 0x48000800;
    // unsigned int Pin9 = 0x0200;
    // unsigned int MODER = 0x0;
    unsigned int Output = 0x01;
    unsigned int ledPin = 9;
    
    // unsigned int* moder_ptr = (void *)(GPIOC->MODER);
    unsigned int moder_val = Output << (ledPin * 2);
    // *moder_ptr = moder_val;
   
    GPIOC->MODER &= ~moder_val;
    GPIOC->MODER |= moder_val;
}

void set_led3_on(){

    // unsigned long int GPIOC = 0x48000800;
    // unsigned int Pin9 = 0x0200;
    // unsigned int ODR = 0x14;
    unsigned int ledPin = 9;


    // unsigned int* odr_ptr = (void *)(GPIOC->ODR);
    // unsigned int odr_val = HIGH << ledPin;
    // *odr_ptr = odr_val;
    
    GPIOC->ODR |= HIGH << ledPin;
    
    return;
}

void set_led3_off(){

    // unsigned long int GPIOC = 0x48000800;
    // unsigned int Pin9 = 0x0200;
    // unsigned int ODR = 0x14;
    unsigned int ledPin = 9;


    // unsigned int* odr_ptr = (void *)GPIOC->ODR; // (void *)(GPIOC + ODR);
    // unsigned int n_odr_val = HIGH << ledPin;
    // *odr_ptr = (*odr_ptr) & ~n_odr_val;
   
    GPIOC->ODR &= ~(HIGH << ledPin);
    return;
}

void init_usart(){
    // need to first make sure it's off
    uint32 USART_EN = 0x00004000;
    RCC->APB2ENR &= ~USART_EN;

    // --- Configure the USART1 GPIO block --- //
    uint32 GPIOA_EN = 0x00020000;
    RCC->AHBENR |= GPIOA_EN;

    uint32 altfn = 0x02; //? documentation is a bit unclear what the alternate fn value should be, I think this is right tho
    uint32 rxPin = 10;
    uint32 txPin = 9;
    uint32 moder_val = (altfn << rxPin*2) | (altfn << txPin*2);

    GPIOA->MODER &= ~moder_val;
    GPIOA->MODER |= moder_val; // MODER, because alternate gpio fns :)

    uint32 afr_usart = 0x01;
    int afr_sel_size = 4;
    uint32 tx_afr_offset = (txPin % 8) * afr_sel_size;
    uint32 rx_afr_offset = (rxPin % 8) * afr_sel_size;

    uint32 afrh_val = (afr_usart << tx_afr_offset) | (afr_usart << rx_afr_offset);
    GPIOA->AFRH &= ~afrh_val;
    GPIOA->AFRH |= afrh_val;

    RCC->APB2ENR |= USART_EN;
    
    // --- Configure Baud to 9600 --- //
    USART1->BRR = 0x1388; // baud = fclk / BRR ::: 0x1388 * 0d9600 = fclk

    // --- Enable basic fns in USART1 register --- //
    uint32 TX_EN = HIGH << 3;
    uint32 RX_EN = HIGH << 2;
    uint32 UE_EN = HIGH << 0;

    uint32 cr1_val = TX_EN | RX_EN | UE_EN;
    USART1->CR1 &= ~cr1_val;
    USART1->CR1 |= cr1_val;

   
    // --- CR1 --- //
    // USART on reset:
    // Word length: 1 st bit, 8 data bits, n stop bits
    // No interrupts
    // Driver enable on/off time 0
    // Oversample by 16
    // Unmuted
    // Mute wakeup set to idle line
    // No parity control
    // Even parity
    // Tx disabled (bit 3)
    // Rx disabled (bit 2)
    // USART disabled (bit 0)
    // --- CR2 --- //
    // Unique id 0
    // rx timeout disabled
    // auto baud rate: detected by start bit
    // auto baud rate disabled
    // MSB first: off
    // rx/tx data where 1=High 0=Low
    // rx pin signal Vdd=1 (idle)
    // rx/tx swap: off
    // LIN mode: off
    // 1 stop bit
    // CLK disabled (Synch or Smartcard mode only)
    // CLK polarity: steady low
    // CLK phase: 1st clk transistion = 1st data capture edge
    // Last bit CLK phase: clk pulse of last bit is not output to CLK pin
    // No interrupts
    // 4bit unique address mode
    // --- CR3 --- //
    // No interrupts
    // No smartcard auto-retry
    // Driver enable polarity: active high
    // Driver enable mode: disabled
    // DMA disable on rx error: off
    // Rx disable on overrun: on
    // Sample method: three bit
    // Clear to send (CTS) mode: disabled
    // RTS mode: disabled
    // tx DMA mode: disabled
    // rx DMA mode: disabled
    // smartcard mode: disabled
    // smartcard nack mode: disabled
    // half-duplex mode: disabled
    // IrDA low power mode: disabled
    // IrDA mode: disabled
}

int finish_tx(){
    uint32 TC = HIGH << 6;
    while((USART1->ISR & TC) != TC); // wait for transmission complete
    return 0;
}

int putchar(unsigned char c){
    uint32 TXE = HIGH << 7;
    finish_tx();
    while((USART1->ISR & TXE) != TXE); // wait for TDR to be empty
    USART1->TDR = (uint32)c;
    while((USART1->ISR & TXE) != TXE); // wait for TDR to be empty
    finish_tx();
    return c;
}


void delay(unsigned int ticks){
    for(int i = 0; i < ticks; i++);
}

void print_sequence(){
    for(unsigned char i = 'A'; i < '['; i++){
        putchar(i);
    }
    finish_tx();
    for(unsigned char i = 'a'; i < '{'; i++){
        putchar(i);
    }
    finish_tx();
    for(unsigned char i = '0'; i < ':'; i++){
        putchar(i);
    }
    finish_tx();
    putchar('\n');
    putchar('\r');
    finish_tx();
}

int main(){
    init();
    init_led3();
    init_usart();
    
    while(1){
        set_led3_on();
        print_sequence();
        delay(1000000);

        set_led3_off();
        print_sequence();
        delay(1000000);
    }

    return 0;
}
