;Paging is enabled by writing the address of a page directory to cr3 
;and then setting bit 31 (the PG “paging-enable” bit) of cr0 to 1.
;For 4 MB pages, set the PSE bit (Page Size Extensions, bit 4) of cr4.

global load_page_directory
global enable_paging
global boot_page_directory

PAGING_PRESENT equ 1b
PAGING_WRITABLE equ 10b
PAGING_USER_ACCESSIBLE equ 100b
PAGING_SIZE_4MB equ 10000000b
; identity map 0x00000000 - 0x00400000 (first 4MB) which includes kernel
; and paging data structures

section .data
align 4096
boot_page_directory:
    pde_frame_addr equ 0x0
    dd (pde_frame_addr & 0xfff00000) + (PAGING_PRESENT | PAGING_WRITABLE | PAGING_SIZE_4MB)
    times 0x3ff dd 0        ; allocate remaining page directory entries

section .text
load_page_directory:        ; put &boot_page_directory in high 20 bits of cr3 register
    mov eax, [esp+4]
    mov ebx, cr3
    and ebx, 0xfff          ; zero out existing 20 high bits
    and eax, 0xfffff000
    or ebx, eax
    mov cr3, ebx
    ret

enable_paging:
    ; enable 4MB paging
    mov eax, cr4
    or eax, 0x10
    mov cr4, eax

    ; enable paging (PG bit)
    mov eax, cr0
    or eax, 0x80000001  ; set PE (bit 0) and PG (bit 31)
    mov cr0, eax
    ret