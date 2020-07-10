#ifndef _KHEAP_H
#define _KHEAP_H

#include "common.h"

void *kmalloc(size_t size);
void *kmalloc_page();

#endif // _KHEAP_H