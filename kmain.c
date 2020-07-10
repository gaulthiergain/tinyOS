#include "serial.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"
#include "log.h"
#include "paging.h"
#include "common.h"

int kmain(unsigned int ebx){
    char message[] = "ToysKernel\n";
    
    serial_init();

    fb_clear();
    
    info("initializing gdt...");
    gdt_init();
    info("finish setup gdt...");

    info("initializing idt...");
    idt_init();
    info("finish setup idt...");

    info("initializing paging...");
    init_paging();
    info("finish setup paging...");

    fb_write(message, sizeof(message));
    
    return ebx;
}
