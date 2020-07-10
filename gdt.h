#ifndef _GDT_H
#define _GDT_H

struct GDT {
    unsigned short size;            // The upper 16 bits of all selector limits.
    unsigned int address;           // The address of the first gdt_entry_t struct.
} __attribute__((packed));

struct GDTDescriptor{
    unsigned short limit_low;       // The lower 16 bits of the limit.
    unsigned short base_low;        // The lower 16 bits of the base.
    unsigned char base_middle;      // The lower 16 bits of the base.
    unsigned char access_byte;      // Access flags, determine what ring this segment can be used in.
    unsigned char limit_and_flags;
    unsigned char base_high;        // The last 8 bits of the base.
} __attribute__((packed));

void gdt_init(void);

// Wrappers around ASM.
void segments_load_gdt(struct GDT gdt);
void segments_load_registers();

#endif /* _GDT_H */