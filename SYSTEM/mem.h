#ifndef _MEM_H_
#define _MEM_H_
#include "common.h"

void* memcpy(void *dst, const void *src, uint32_t size);

void* memset(void *dst, int val, unsigned size); 

uint32_t strlen(char *str);

#endif
