ENTRY(loader)                   /* the name of the entry label */

. = 0x00100000;                 /* the code should be loaded at 1MB */

kernel_start = .;               /* this label get exported to the code files */

SECTIONS {

    .multiboot ALIGN (0x1000): { multiboot.o }

    .text ALIGN (0x1000) :      /* align at 4KB */
    {
        *(.text)                /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) :    /* align at 4KB */
    {
        *(.rodata*)             /* all ro data sections from all files */
    }

    .data ALIGN (0x1000) :      /* align at 4KB */
    {
        *(.data)                /* all data sctions from all files */
    }

    .bss ALIGN (0x1000) :       /* align at 4KB */   
    {
        *(COMMON)               /* all COMMON sections from all files */
        *(.bss)                 /* all bss sections from all files */
    }

}

kernel_end = .;
