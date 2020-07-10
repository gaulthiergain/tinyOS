#include "serial.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"

int kmain(unsigned int ebx){
    unsigned char message[] = "ToysKernel";
    
    serial_init();

    fb_init();
    fb_clean_screen();
    fb_write(message, sizeof(message));
    
    gdt_init();
    idt_init();

    return ebx;
}
