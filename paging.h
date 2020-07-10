#ifndef _PAGING_H
#define _PAGING_H

#include "common.h"

struct directory {
    u8int present:1;        // bit 0: always 1
    u8int rw:1;             // bit 1: read/write
    u8int us:1;             // bit 2: user or supervisor
    u8int pwt:1;            // bit 3: page-level write-through
    u8int pcd:1;            // bit 4: page-level cache disable
    u8int a:1;              // bit 5: accessed
    u8int ignored:1;        // bit 6:
    u8int ps:1;             // bit 7: page size, 0=4KB 1=4MB, must be 0 for this struct
    u8int ignored2:4;       // bit 8 - 11
    u32int page_table:20;   // bit 12 - 31: physical address of 4KB aligned page table referenced by this entry
} __attribute__((packed));
typedef struct directory directory_t;

struct page {
    u8int present:1;        // bit 0: always 1
    u8int rw:1;             // bit 1: read/write
    u8int us:1;             // bit 2: user or supervisor
    u8int pwt:1;            // bit 3: page-level write-through
    u8int pcd:1;            // bit 4: page-level cache disable
    u8int a:1;              // bit 5: accessed
    u8int d:1;              // bit 6: dirty
    u8int pat:1;            // bit 7: must be 0 unless PAT supported
    u8int g:1;              // bit 8: global translation
    u8int ignored2:3;       // bit 9 - 11
    u32int page_frame:20;   // bit 12 - 31: physical address of 4KB page frame
} __attribute__((packed));
typedef struct page page_t;

void handle_page_fault(void);
void init_paging(void);

#endif