ENTRY(main)

MEMORY {
	SRAM(rwx):ORIGIN = 0x20000000, LENGTH = 20K
	FLASH(rx):ORIGIN = 0x08000000, LENGTH = 128K
}

SECTIONS {
	.text : {
		KEEP(*(.vtab))
		*(.text*)
		*(.rodata*)
		. = ALIGN(4);
	} > FLASH

	.data : {
		*(.data*)
		. = ALIGN(4);
	} > SRAM AT > FLASH

	.bss : {
        . = ALIGN(4);
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
/* Define the start of the heap for newlib sbrk. */
       end = . ;
    } > SRAM
}
