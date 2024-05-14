#include "mem.h"
/* Memroy management function definitions */
void* memcpy(void *dst, const void *src, uint32_t size) {
    char *d = (char*) dst;
    const char *s = (const char*) src;

    for (int i = 0; i < size; ++i) {
        *d++ = *s++;
    }

    return dst;
}
void* memset(void *dst, int val, unsigned size) {
    uint8_t *byte_dst = (uint8_t*) dst; // Cast to uint8_t* for byte-level access

    for (unsigned i = 0; i < size; ++i) {
        byte_dst[i] = (uint8_t) val; // Assign the value to each byte, casting to uint8_t to ensure it's within range
    }

    return dst; // Return the destination pointer
}
uint32_t strlen(char *str)
{
  uint32_t len = 0;
  while(str[len] != '\0')
  {
    len++;
  }
  return len;
}

