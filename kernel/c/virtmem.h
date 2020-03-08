#ifndef virtmem_h
#define virtmem_h
#include<stdint.h>
void vmmngr_init();
bool map_page(uint32_t vir,uint32_t phy);
//void free_page(uint32_t* entry);
#endif 

