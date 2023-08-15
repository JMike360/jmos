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

        __exidx_start = .;
        __exidx_end = .;

		/* Stabs debugging sections.  */
		.stab          0 : { *(.stab) }
		.stabstr       0 : { *(.stabstr) }
		.stab.excl     0 : { *(.stab.excl) }
		.stab.exclstr  0 : { *(.stab.exclstr) }
		.stab.index    0 : { *(.stab.index) }
		.stab.indexstr 0 : { *(.stab.indexstr) }
		.comment       0 : { *(.comment) }
		/* DWARF debug sections.
		   Symbols in the DWARF debugging sections are relative to the beginning
		   of the section so we begin them at 0.  */
		/* DWARF 1 */
		.debug          0 : { *(.debug) }
		.line           0 : { *(.line) }
		/* GNU DWARF 1 extensions */
		.debug_srcinfo  0 : { *(.debug_srcinfo) }
		.debug_sfnames  0 : { *(.debug_sfnames) }
		/* DWARF 1.1 and DWARF 2 */
		.debug_aranges  0 : { *(.debug_aranges) }
		.debug_pubnames 0 : { *(.debug_pubnames) }
		/* DWARF 2 */
		.debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
		.debug_abbrev   0 : { *(.debug_abbrev) }
		.debug_line     0 : { *(.debug_line) }
		.debug_frame    0 : { *(.debug_frame) }
		.debug_str      0 : { *(.debug_str) }
		.debug_loc      0 : { *(.debug_loc) }
		.debug_macinfo  0 : { *(.debug_macinfo) }
		/* SGI/MIPS DWARF 2 extensions */
		.debug_weaknames 0 : { *(.debug_weaknames) }
		.debug_funcnames 0 : { *(.debug_funcnames) }
		.debug_typenames 0 : { *(.debug_typenames) }
		.debug_varnames  0 : { *(.debug_varnames) }

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

