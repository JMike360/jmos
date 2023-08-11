#include "jmos-stm32-init.h"
#include "jmos-stm32-periph.h"

#define PLL_EN  ((uint32)0x1 << 24)
#define PLL_RDY ((uint32)0x1 << 25)

#define HSI_ON  ((uint32)0x1 << 0)
#define HSI_RDY ((uint32)0x1 << 1)

#define RCC_CR_RESET ((uint32)0x0)

#define SWS_PLL ((uint32)0x2 << 2)
#define SW_PLL  ((uint32)0x2 << 0)

void set_pll_48mhz(){
    RCC->CR &= ~PLL_EN;
    while((RCC->CR & PLL_RDY) == PLL_RDY);
    
    // Need PLL * HSI = 48MHz
    // PLL = 48MHz / 8MHz = 6, except that the input to PLL is actually HSI/2 = 4MHz by default, so x12?
    unsigned char pll_12x = 0x0A; // See RM0091 pg 113 of 1017 https://www.st.com/resource/en/reference_manual/rm0091-stm32f0x1stm32f0x2stm32f0x8-advanced-armbased-32bit-mcus-stmicroelectronics.pdf

    uint32 cfgr_val = ((uint32)pll_12x) << 18; // Omitting PLL src bits (they're 0 anyway) as HSI/2 is the default src

    RCC->CFGR &= ~cfgr_val;
    RCC->CFGR |= cfgr_val;
    RCC->CR |= PLL_EN;
    while((RCC->CR & PLL_RDY) != PLL_RDY);
}

void init(){
    RCC->CR = RCC_CR_RESET; 

    // enable High Speed Internal (HSI) CLK (8MHz)
    // Use PLL to mult HSI clk to 48MHz
    RCC->CR |= HSI_ON;
    while((RCC->CR & HSI_RDY) != HSI_RDY);

    set_pll_48mhz();

    // configure sys clk to use PLL output
    RCC->CFGR &= ~SW_PLL;
    RCC->CFGR |= SW_PLL;

    while((RCC->CFGR & SWS_PLL) != SWS_PLL); // Have to read status bits from a different place than where the setting is written
}
