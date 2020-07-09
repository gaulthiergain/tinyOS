#include "serial.h"
#include "fb.h"
#include "gdt.h"
#include "interrupt.h"

int kmain(unsigned int ebx){
    unsigned char message[] = "GauOS";
    
    fb_init();
    fb_clean_screen();
    fb_write(message, sizeof(message));
    //serial_init();
    //serial_write(message, sizeof(message));
    gdt_init();
    interrupts_install_idt();

    return ebx;
}
