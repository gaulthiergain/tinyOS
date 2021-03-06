#include "stdarg.h"
#include "common.h"
#include "fb.h"

void *memset(void *s, int c, size_t n) {
    char *mem = (char*)s;
    size_t i;
    for (i = 0; i < n; i++) {
        mem[i] = (u8int)c;
    }
    return s;
}

void *memmove(void *dst, const void *src, size_t len) {
    char *dst_mem = (char*)dst;
    char *src_mem = (char*)src;
    size_t i;
    for (i = 0; i < len; i++) {
        dst_mem[i] = src_mem[i];
    }
    return dst_mem;
}

char *itoa(int val, char *buf, int radix) {
    u32int i = 0;
    u32int start = i;
    if (val < 0 && radix == 10) {
        buf[i++] = '-';
        start = i;
    }

    if (radix == 16) {
        buf[i++] = '0';
        buf[i++] = 'x';
        start = i;
    }

    int x = val;
    do {
        int a = x % radix;
        if (a < 10) 
            buf[i++] = a + '0';
        else 
            buf[i++] = a + 'a' - 10;
    } while (x /= radix);

    char *s = buf+start;
    char *e = buf+(i-1);

    while(s < e) {
        char t = *s;
        *s = *e;
        *e = t;
        s++;
        e--;
    }

    buf[i] = 0;
    return buf;
}

char *uitoa(u32int val, char *buf, int radix) {
    u32int i = 0;
    u32int start = i;

    if (radix == 16) {
        buf[i++] = '0';
        buf[i++] = 'x';
        start = i;
    }

    u32int x = val;
    do {
        u32int a = x % radix;
        if (a < 10) 
            buf[i++] = a + '0';
        else 
            buf[i++] = a + 'a' - 10;
    } while (x /= radix);

    char *s = buf+start;
    char *e = buf+(i-1);

    while(s < e) {
        char t = *s;
        *s = *e;
        *e = t;
        s++;
        e--;
    }

    buf[i] = 0;
    return buf;
}

size_t strlen(const char *buf) {
    unsigned int i=0;
    while(buf[i] != 0) i++;
    return i;
}

#ifdef DEBUG_PRINTF_LINE_NO
static u32int line_count = 0;
#endif

int printf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);

#ifdef DEBUG_PRINTF_LINE_NO
    char line_count_str[20];
    fb_write_str(uitoa(line_count++, line_count_str, 10));
    fb_write_str(": ");
#endif

    size_t i;
    char buf[20];
    int val;
    u32int uval;
    char c, *s;
    for (i=0; i<strlen(format); i++) {
        if (format[i] == '%') {
            i++;
            while (format[i] == ' ') i++;

            switch(format[i]) {
            case 'i':
                val = va_arg(ap, int);
                itoa(val, buf, 10);
                fb_write_str(buf);
                break;
            case 'x':
                uval = va_arg(ap, u32int);
                uitoa(uval, buf, 16);
                fb_write_str(buf);
                break;
            case 'c':
                c = (char)va_arg(ap, int);
                fb_write(&c, 1);
                break;
            case 's':
                s = va_arg(ap, char*);
                fb_write_str(s);
                break;
            default:
                fb_write((char*)format+i, 1);
            }
        } else {
            fb_write((char*)format+i, 1);
        }
    }

    va_end(ap);
    return 0;
}