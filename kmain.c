#include "serial.h"
#include "fb.h"
#include "gdt.h"
#include "interrupt.h"

void kmain(){
    unsigned char message[] = "GauOS";
    
    fb_init();
    fb_clean_screen();
    fb_write(message, sizeof(message));
    //serial_init();                // init serial (with bochs)
    //serial_write(s, sizeof(s));   // write on serial (with bochs)
    gdt_init();
    interrupts_install_idt();

    while(1);
}
