#ifndef memory_h
#define memory_h

#include <stdint.h>
void  pmmngr_init(uint32_t mapentrycount);
uint32_t* pmmngr_allocate_block();
uint8_t pmmngr_free_block(uint32_t* address);
#endif
