global loader                       ; the entry symbol for ELF
extern kmain                        ; function kmain is defined elsewhere

MAGIC_NUMBER    equ 0x1BADB002      ; define the magic number constant
ALIGN_MODULES   equ 0x00000001      ; tell GRUB to align modules
FLAGS           equ 0x0             ; multiboot flags
CHECKSUM        equ -MAGIC_NUMBER   ; calculate the checksum
                                    ; (magic number + checksum + flags should equal 0)
section .text:                      ; start of the text (code) section
    align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER                 ; write the magic number to the machine code
    dd FLAGS                        ; the flags
    dd CHECKSUM                     ; and the checksum

loader:                             ; the loader label (defined as entry
                                    ; point in linker script)
    mov esp, kernel_stack+KERNEL_STACK_SIZE ; point esp
    ;add  esp, 4
    push ebx                        ; multiboot info in ebx
    call kmain
.loop:
    jmp .loop                   ; loop forever

KERNEL_STACK_SIZE equ 8192          ; size of stack in bytes

section .bss:
    align 4                         ; align at 4 bytes
kernel_stack:                       ; label points to beginning of memory
    resb KERNEL_STACK_SIZE          ; reserve stack for the kernel
                                    ; stack (end of memory area)
