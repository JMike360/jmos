#include "../hal/jmos-stm32-init.h"
#include "../hal/jmos-stm32-periph.h"
#include "../hal/jmos-stm32-usart.h"

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

void printstrlen(char* s, int len){
    char* end = s + len;
    while(s < end){
        if(*s == '\0'){
            break;
        }
        putchar(*s);
        s++;
    }
    finish_tx();
}

int main(){
    init();
    init_led3();
    init_usart(0x1358);
    
    unsigned char c;
    while(1){
        set_led3_on();
        c = getchar();
        if(c == '\r'){
            putchar('\n');
            putchar(c);
        }
        else if(c == 127){
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }
        else{
            putchar(c);
        }

        set_led3_off();
        c = getchar();
        if(c == '\r'){
            putchar('\n');
            putchar(c);
        }
        else if(c == 127){
            putchar('\b');
            putchar(' ');
            putchar('\b');
        }
        else{
            putchar(c);
        }
    }

    return 0;
}
