#include "jmos-stm32-init.h"
#define HIGH 1
#define LOW 0

void init_led3(){
    unsigned long int RCC = 0x40021000;
    unsigned int AHBENR = 0x14;
    unsigned int GPIOC_EN = 0x00080000;
    // led 3 = GPIOC pin 9
    // led 4 = GPIOC pin 8
   
    // Not sure if this pattern is necessary, as this should be a set-enable reg
    // I think this might work equally as well without first reading the value of the ahbenr
    unsigned int* ahb_ptr = (void *)(RCC + AHBENR);
    unsigned int ahb_val = *ahb_ptr;
    ahb_val |= GPIOC_EN;
    *ahb_ptr = ahb_val;

    unsigned long int GPIOC = 0x48000800;
    // unsigned int Pin9 = 0x0200;
    unsigned int MODER = 0x0;
    unsigned int Output = 0x01;
    unsigned int ledPin = 9;
    
    unsigned int* moder_ptr = (void *)(GPIOC + MODER);
    unsigned int moder_val = Output << (ledPin * 2);
    *moder_ptr = moder_val;
}

void set_led3_on(){

    unsigned long int GPIOC = 0x48000800;
    // unsigned int Pin9 = 0x0200;
    unsigned int ODR = 0x14;
    unsigned int ledPin = 9;


    unsigned int* odr_ptr = (void *)(GPIOC + ODR);
    unsigned int odr_val = HIGH << ledPin;
    *odr_ptr = odr_val;
    
    return;
}

void set_led3_off(){

    unsigned long int GPIOC = 0x48000800;
    // unsigned int Pin9 = 0x0200;
    unsigned int ODR = 0x14;
    unsigned int ledPin = 9;


    unsigned int* odr_ptr = (void *)(GPIOC + ODR);
    unsigned int odr_val = LOW << ledPin;
    *odr_ptr = odr_val;
    
    return;
}

void delay(unsigned int ticks){
    for(int i = 0; i < ticks; i++);
}

int main(){
    init();
    init_led3();
    
    while(1){
        set_led3_on();
        delay(100000);
        set_led3_off();
        delay(100000);
    }

    return 0;
}
