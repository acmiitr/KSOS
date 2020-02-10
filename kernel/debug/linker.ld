/*This is Michael Petch's linker from a stackoverflow answer*/


OUTPUT_FORMAT(elf32-i386)

SECTIONS {
    . = 0x1000;

    .text : SUBALIGN(4)
    {
        *(.text.entry)       /* Ensure .text.entry appears first */
        *(.text*)
        *(.rodata*)
        *(.data)
    }

    .bss : SUBALIGN(4) {
        __bss_start = .;
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all BSS sections from all files */
    }
    . = ALIGN(4);
    __bss_end = .;
    __bss_sizeb = __bss_end - __bss_start;       /* BSS size in bytes */
    __bss_sizel = (__bss_end - __bss_start) / 4; /* BSS size in longs/DWORDs */

    /DISCARD/ : {            /* Remove Unneeded sections */
        *(.eh_frame);
        *(.comment);
    }

    end = .; _end = .; __end = .;
}
