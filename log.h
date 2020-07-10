#ifndef _LOG_H_
#define _LOG_H_

#include "common.h"

#if DEBUG >= 0
#define debug(msg, ...) printf("[debug] %s:%i " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug(msg, ...)
#endif

#if DEBUG >= 0
#define info(msg, ...) printf("[info] " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define info(msg, ...)
#endif

#if DEBUG >= 0
#define warn(msg, ...) printf("[warn] %s:%i " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define warn(msg, ...)
#endif

#if DEBUG >= 0
#define error(msg, ...) printf("[error] %s:%i " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define error(msg, ...)
#endif

#define PANIC_MSG \
  " KERNEL PANIC \n"


#define PANIC(msg) { printf(PANIC_MSG "PANIC! %s at %s:%i\n", msg, __FILE__, __LINE__); asm volatile("cli\nhlt"); }

#endif /* include _LOG_H_ */