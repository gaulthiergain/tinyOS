#include "serial.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"
#include "log.h"
#include "common.h"

int kmain(unsigned int ebx){
    char message[] = "ToysKernel\n";
    
    serial_init();

    fb_clear();
    fb_write(message, sizeof(message));
    
    info("initializing gdt...");
    gdt_init();
    info("finish setup gdt...");

    info("initializing idt...");
    idt_init();
    info("finish setup idt...");



    return ebx;
}
