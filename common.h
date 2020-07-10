#ifndef _COMMON_H
#define _COMMON_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

typedef unsigned int    size_t;

void *memset(void *s, int c, size_t n);
void *memmove(void *dst, const void *src, size_t len);

char *uitoa(u32int val, char *buf, int radix);
char *itoa(int val, char *buf, int radix);
size_t strlen(const char *buf);
int printf(const char *format, ...);

#endif // _COMMON_H
