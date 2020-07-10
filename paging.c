#include "paging.h"
#include "serial.h"
#include "kheap.h"
#include "common.h"
#include "log.h"

// pre-allocated by nasm (also page aligned)
extern directory_t boot_page_directory; 

u32int frame_allocations[32767];

#define PAGE_FRAME_SIZE 4096

// addr must be page aligned
/*static int test_frame(u32int addr) {
  u32int frame = addr / PAGE_FRAME_SIZE;
  u32int frame_word = frame / 32;
  u32int bit_offset = frame % 32;
  return  (frame_allocations[frame_word] >> bit_offset) & 1;
}*/

// addr must be page aligned
static void set_frame(u32int addr) {
  u32int frame = addr / PAGE_FRAME_SIZE;
  u32int frame_word = frame / 32;
  u32int bit_offset = frame % 32;
  frame_allocations[frame_word] |= (1 << bit_offset);
}

/*
// addr must be page aligned
static void clear_frame(u32int addr) {
  u32int frame = addr / PAGE_FRAME_SIZE;
  u32int frame_word = frame / 32;
  u32int bit_offset = frame % 32;
  frame_allocations[frame_word] &= ~(1 << bit_offset);
}*/

/*registers_t regs*/
void handle_page_fault(void) {
    debug("Page fault!");
    unsigned char msg[] = "Page Fault";
    serial_write(msg, sizeof(msg));
}

#define PAGE_READONLY   0
#define PAGE_READWRITE  1
#define PAGE_USER       1
#define PAGE_KERNEL     0
#define PAGE_SIZE_4KB   0
#define PAGE_SIZE_4MB   1

void map(directory_t *page_directory, u32int vaddr, u32int paddr) {
    debug("\nidentity mapping %x-%x\n", vaddr & 0xfffff000, (vaddr & 0xfffff000) + 0x1000 - 1);

    u32int directory_offset = vaddr >> 22; // 31:22
    u32int table_offset = (vaddr >> 12) & 0x3ff; // 21:12
    debug("\tdirectory offset: %x\n", directory_offset);
    debug("\ttable offset: %x\n", table_offset);

    directory_t *directory = &page_directory[directory_offset/4];
    page_t *table;
    debug("kernel page directory resides at %x\n", page_directory);
    if (!directory->present) {
        debug("configuring new page directory entry with index %i at %x\n", directory_offset, directory);
        directory->present = 1;
        directory->rw = PAGE_READWRITE;
        directory->us = PAGE_KERNEL;
        directory->ps = PAGE_SIZE_4KB;

        table = (page_t*)kmalloc_page(); // sizeof(page_t)*1024 == 0x1000
        memset(table, 0, 0x1000);

        directory->page_table = (u32int)table >> 12; // table base (20 high bits)
        debug("directory->page_table is now %x\n", directory->page_table << 12);
    } else {
        table = (page_t*)(directory->page_table << 12);
        debug("c directory->page_table already exists at %x\n", table);
    }

    page_t *page = &table[table_offset];
    if (!page->present) {
        debug("configuring new page table entry at %x\n", page);
        page->present = 1;
        page->rw = PAGE_READWRITE;
        page->us = PAGE_KERNEL;
    }

    page->page_frame = paddr >> 12; // frame base (20 high bits)
    debug("page %x is now mapped to frame %x\n", vaddr, page->page_frame << 12);
    set_frame(paddr);
}

extern void load_page_directory(directory_t *directory);
extern void enable_paging();

void init_paging(void) {

    debug("boot_page_directory=%x", &boot_page_directory);

    load_page_directory(&boot_page_directory);
    enable_paging();
}