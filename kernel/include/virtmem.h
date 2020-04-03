#ifndef virtmem_h
#define virtmem_h
#include<stdint.h>
#include<stdbool.h>
void vmmngr_init();
bool map_page(uint32_t vir,uint32_t phy);
void remove_identity_map();
//void free_page(uint32_t* entry);
#endif 

