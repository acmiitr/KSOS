#include <stdint.h>
#include <stdbool.h>
#include "phymem.h"


//Source: BrokenThorn 
//A page table entry is just a 32 bit integer in our case :)
typedef uint32_t pt_entry;  //It's the data, not pointer or anything
enum PAGE_PTE_FLAGS {
	PTE_PRESENT		=	1,		//0000000000000000000000000000001
	PTE_WRITABLE		=	2,		//0000000000000000000000000000010
	PTE_USER		=	4,		//0000000000000000000000000000100
	PTE_WRITETHOUGH		=	8,		//0000000000000000000000000001000
	PTE_NOT_CACHEABLE	=	0x10,		//0000000000000000000000000010000
	PTE_ACCESSED		=	0x20,		//0000000000000000000000000100000
	PTE_DIRTY		=	0x40,		//0000000000000000000000001000000
	PTE_PAT			=	0x80,		//0000000000000000000000010000000
	PTE_CPU_GLOBAL		=	0x100,		//0000000000000000000000100000000
	PTE_LV4_GLOBAL		=	0x200,		//0000000000000000000001000000000
   	PTE_FRAME		=	0x7FFFF000 	//1111111111111111111000000000000
};
//Responsibitities
void pt_entry_add_attrib (pt_entry* e, uint32_t attrib);
void pt_entry_del_attrib (pt_entry* e, uint32_t attrib);
void pt_entry_set_frame (pt_entry*, physical_addr);
bool pt_entry_is_present (pt_entry e);
bool pt_entry_is_writable (pt_entry e);
uint32_t pt_entry_physical (pt_entry e);

void pt_entry_add_attribute(pt_entry entry_pointer,


