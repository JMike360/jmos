
.syntax unified
.cpu cortex-m0
.thumb

/* Cortex-M0 processors expect this table to always exist at addr 0x0
 * Each row points to the entry point of the corresponding interrupt's handler
 * Row 0 is special, and points to the initial stack pointer value
*/
.section .isr_vector,"a",%progbits
.type cortexm0_vectortable, %object

cortexm0_vectortable:
    .word _emain_stack
    .word Reset_ISR
    .word NMI_ISR
    .word HardFault_ISR
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_ISR
    .word 0
    .word 0
    .word PendSV_ISR
    .word SysTick_ISR
    .word WWDG_ISR
    .word PVD_ISR
    .word RTC_ISR
    .word FLASH_ISR
    .word RCC_ISR
    .word EXTI0_1_ISR
    .word EXTI2_3_ISR
    .word EXTI4_15_ISR
    .word TS_ISR
    .word DMA1_Channel1_ISR
    .word DMA1_Channel2_3_ISR
    .word DMA1_Channel4_5_ISR
    .word ADC1_COMP_ISR
    .word TIM1_BRK_UP_TRG_COM_ISR
    .word TIM1_CC_ISR
    .word TIM2_ISR
    .word TIM3_ISR
    .word TIM6_DAC_ISR
    .word 0
    .word TIM14_ISR
    .word TIM15_ISR
    .word TIM16_ISR
    .word TIM17_ISR
    .word I2C1_ISR
    .word I2C2_ISR
    .word SPI1_ISR
    .word SPI2_ISR
    .word USART1_ISR
    .word USART2_ISR
    .word 0
    .word CEC_ISR
    .word 0
    .word 0 /*BootRam*/
.size cortexm0_vectortable, .-cortexm0_vectortable
