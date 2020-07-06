//#include "serial.h"
#include "fb.h"

void kmain(){
    unsigned char s[] = "GauOS";

    fb_init();
    fb_clean_screen();
    fb_write(s, sizeof(s));
    
    //serial_init();                // init serial (with bochs)
    //serial_write(s, sizeof(s));   // write on serial (with bochs)

    while(1);
}
