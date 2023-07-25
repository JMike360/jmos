/*
 * Linker script to define memory regions and section definitions 
 * for the stm32F051 discovery platform
 *
 */

MEMORY
	{
		FLASH (rx):  ORIGIN = 0x08000000, LENGTH = 64K
		SRAM  (wrx): ORIGIN = 0x20000000, LENGTH = 8K
	}

    _esram = 0x20002000;
    PROC_STACK_SIZE = 0x0E00;
    HEAP_SIZE = 0x0400;

SECTIONS
    {
        .isr_vector :
        {
            . = ALIGN(4);
            KEEP(*(.isr_vector))            /* Startup code */
            . = ALIGN(4);
        } >FLASH
        
        .text :
        {
            *(.text*)
            *(.rodata*)
            . = ALIGN(4);
            _etext = .;
            _ssdata = _etext;
        } > FLASH

        .data : AT (_ssdata)
        {
            . = ALIGN(4);
            _sdata = .;
            *(.data*)
            . = ALIGN(4);
            _edata = .;
        } > SRAM

        .bss (NOLOAD) :
        {
            . = ALIGN(4);
            _sbss = .;
            *(.bss*)
            *(COMMON)
            . = ALIGN(4);
            _ebss = .;
        } > SRAM

        .heap (NOLOAD): /* heap should start right after data and bss in SRAM */
        {
            . = ALIGN(4);
            _sheap = .;
            . = . + HEAP_SIZE;
            . = ALIGN(4);
            _eheap = .;
        } > SRAM

        .proc_stack (NOLOAD): /* process stack should be fairly large, I think the bulk of SRAM that isn't used for data */
        {   
            . = ALIGN(4);
            _sproc_stack = .;
            . = . + PROC_STACK_SIZE;
            . = ALIGN(4);
            _eproc_stack = .;
        }

        main_stack_size = _esram - _eproc_stack;
        .main_stack (NOLOAD): /* stack for OS kernel and ISR handlers, takes up whatever space remains up to the end of SRAM */
        {
            . = ALIGN(4);
            _smain_stack = .;
            . = . + main_stack_size;
            . = ALIGN(4);
            _emain_stack = .;
        } > SRAM 

        . = _esram;

    }

