#include "serial.h"
#include "fb.h"
#include "gdt.h"
#include "idt.h"
#include "log.h"
#include "paging.h"
#include "common.h"

int kmain(unsigned int ebx){
    char message[] = "tinyOS\n";
    
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

    // Perform a page_fault
    u32int *ptr = (u32int*)0xA0000000;
    u32int do_page_fault = *ptr;
    printf("%d\n", do_page_fault);

    return ebx;
}
