#ifndef _GDT_H
#define _GDT_H

struct GDT {
    unsigned short size;
    unsigned int address;
} __attribute__((packed));

struct GDTDescriptor{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access_byte;
    unsigned char limit_and_flags;
    unsigned char base_high;
} __attribute__((packed));

void gdt_init(void);

// Wrappers around ASM.
void segments_load_gdt(struct GDT gdt);
void segments_load_registers();

#endif /* _GDT_H */