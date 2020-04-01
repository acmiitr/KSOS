OUTPUT_FORMAT(elf32-i386)
ENTRY(kmain)

SECTIONS {

. = 0xC0000000;

__begin = .;
.text : SUBALIGN(16)
	{
		*(.text.entry)       /* Ensure .text.entry appears first */
		*(.text*)
	}
.data : SUBALIGN(16)
	{
		*(.rodata)
		*(.data)
	}
.bss : SUBALIGN(16)
	{
		__bss_start = .;
		*(COMMON)            /* all COMMON sections from all files */
		*(.bss)              /* all BSS sections from all files */
	}

. = ALIGN(4k);
__VGA_text_memory = .;

/*    __bss_end = .;
    __bss_sizeb = __bss_end - __bss_start;        BSS size in bytes 
    __bss_sizel = (__bss_end - __bss_start) / 4;  BSS size in longs/DWORDs */

    /DISCARD/ : {            /* Remove Unneeded sections */
        *(.eh_frame);
        *(.comment);
    }

     __end = .; 
}
