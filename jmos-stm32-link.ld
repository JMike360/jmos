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

    _estack = 0x20002000;

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
        } > FLASH

        .bss (NOLOAD) :
        {
            . = ALIGN(4);
            _sbss = .;
            *(.bss*)
            *(COMMON)
            . = ALIGN(4);
            _ebss = .;
        } > SRAM

        .data : AT (_etext)
        {
            . = ALIGN(4);
            _sdata = .;
            *(.data*)
            . = ALIGN(4);
            _edata = .;
        } > SRAM
    }
