
.syntax unified
.cpu cortex-m0
.thumb

/*--------- Variables defined by linker script -------*/
.word _esram

.word _etext

.word _ssdata
.word _sdata
.word _edata

.word _sbss
.word _ebss

.word _sheap
.word _eheap

.word _sproc_stack
.word _eproc_stack

.word _smain_stack
.word _emain_stack
/*----------------------------------------------------*/


.section .text.Startup
.type Reset_ISR, %function

Reset_ISR:
    b Setup_BSS
    Setup_BSS_Ret:
    
    b Setup_Data
    Setup_Data_Ret:

    b Enter_Main
    Enter_Main_Ret:

    b END

Setup_BSS: /* Initialize .bss SRAM region with zeros */
    ldr r0, =_sbss
    ldr r2, =_ebss
    movs r1, 0
bss_loop:
    cmp r0, r2
    bhs Setup_BSS_Ret /* unsigned >= */
    str r1, [r0]
    adds r0, r0, 4
    b bss_loop

Setup_Data: /* Initialize .data SRAM region with static data from Flash */
    ldr r0, =_sdata
    ldr r1, =_ssdata
    ldr r2, =_edata
data_loop:
    cmp r0, r2
    bhs Setup_Data_Ret /* unsigned >= */
    ldr r3, [r1]
    str r3, [r0]
    adds r0, r0, 4
    adds r1, r1, 4
    b data_loop

Enter_Main: /* Branch to the C code entry point */
    ldr r0, =main
    blx r0 
    b Enter_Main_Ret

END:
    b END

.size Reset_ISR, .-Reset_ISR

