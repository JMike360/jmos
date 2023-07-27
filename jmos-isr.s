
.syntax unified
.cpu cortex-m0
.thumb

.section .text.isr,"ax",%progbits

.type X_ISR, %function
X_ISR: /* Generic isr inf loop */
    x_isr_loop:
    b x_isr_loop


.thumb_set NMI_ISR,         X_ISR
.thumb_set HardFault_ISR,   X_ISR
.thumb_set SVC_ISR,         X_ISR
.thumb_set PendSV_ISR,      X_ISR
.thumb_set SysTick_ISR,     X_ISR
.thumb_set WWDG_ISR,        X_ISR
.thumb_set PVD_ISR,         X_ISR
.thumb_set RTC_ISR,         X_ISR
.thumb_set FLASH_ISR,       X_ISR
.thumb_set RCC_ISR,         X_ISR
.thumb_set EXTI0_1_ISR,     X_ISR
.thumb_set EXTI2_3_ISR,     X_ISR
.thumb_set EXTI4_15_ISR,    X_ISR
.thumb_set TS_ISR,          X_ISR
.thumb_set DMA1_Channel1_ISR,X_ISR
.thumb_set DMA1_Channel2_3_ISR,X_ISR
.thumb_set DMA1_Channel4_5_ISR,X_ISR
.thumb_set ADC1_COMP_ISR,   X_ISR
.thumb_set TIM1_BRK_UP_TRG_COM_ISR,X_ISR
.thumb_set TIM1_CC_ISR,     X_ISR
.thumb_set TIM2_ISR,        X_ISR
.thumb_set TIM3_ISR,        X_ISR
.thumb_set TIM6_DAC_ISR,    X_ISR
.thumb_set TIM14_ISR,       X_ISR
.thumb_set TIM15_ISR,       X_ISR
.thumb_set TIM16_ISR,       X_ISR
.thumb_set TIM17_ISR,       X_ISR
.thumb_set I2C1_ISR,        X_ISR
.thumb_set I2C2_ISR,        X_ISR
.thumb_set SPI1_ISR,        X_ISR
.thumb_set SPI2_ISR,        X_ISR
.thumb_set USART1_ISR,      X_ISR
.thumb_set USART2_ISR,      X_ISR
.thumb_set CEC_ISR,         X_ISR

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



