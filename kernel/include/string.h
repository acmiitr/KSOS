#ifndef _STRING_H
#define _STRING_H
#include <stdint.h>

typedef unsigned size_t;

char *strcpy(char *s1, const char *s2);
size_t strlen ( const char* str );
void* memcpy(void *dest, const void *src, size_t count);
void *memset(void *dest, char val, size_t count);
unsigned short* memsetw(unsigned short *dest, unsigned short val, size_t count);

#endif
