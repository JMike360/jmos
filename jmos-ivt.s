
.syntax unified
.cpu cortex-m0
.thumb

/* Cortex-M0 processors expect this table to always exist at addr 0x0
 * Each row points to the entry point of the corresponding interrupt's handler
 * Row 0 is special, and points to the initial stack pointer value
*/
.section .isr_vector,"a",%progbits
.type cortexm0_vectortable, %object
.size cortexm0_vectortable, .-cortexm0_vectortable

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

/* Stop compiler from complaining about undefined references
 * while also allowing any function to override these labels
 */
.weak Reset_ISR
.weak NMI_ISR
.weak HardFault_ISR
.weak SVC_ISR
.weak PendSV_ISR
.weak SysTick_ISR
.weak WWDG_ISR
.weak PVD_ISR
.weak RTC_ISR
.weak FLASH_ISR
.weak RCC_ISR
.weak EXTI0_1_ISR
.weak EXTI2_3_ISR
.weak EXTI4_15_ISR
.weak TS_ISR
.weak DMA1_Channel1_ISR
.weak DMA1_Channel2_3_ISR
.weak DMA1_Channel4_5_ISR
.weak ADC1_COMP_ISR
.weak TIM1_BRK_UP_TRG_COM_ISR
.weak TIM1_CC_ISR
.weak TIM2_ISR
.weak TIM3_ISR
.weak TIM6_DAC_ISR
.weak TIM14_ISR
.weak TIM15_ISR
.weak TIM16_ISR
.weak TIM17_ISR
.weak I2C1_ISR
.weak I2C2_ISR
.weak SPI1_ISR
.weak SPI2_ISR
.weak USART1_ISR
.weak USART2_ISR
.weak CEC_ISR
