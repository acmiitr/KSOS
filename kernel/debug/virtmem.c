#include <stdint.h>
#include <stdbool.h>
#include "phymem.h"

uint32_t* get_pd_linear();
uint32_t* _page_directory;

   	

//Source: BrokenThorn 
//A page table entry is just a 32 bit integer in our case :)
enum PAGE_PTE_FLAGS {
	PTE_PRESENT		=	1,
	PTE_WRITABLE		=	2,
	PTE_USER		=	4,
	PTE_WRITETHOUGH		=	8,
	PTE_NOT_CACHEABLE	=	0x10,
	PTE_ACCESSED		=	0x20,
	PTE_DIRTY		=	0x40,
	PTE_PAT			=	0x80,
	PTE_CPU_GLOBAL		=	0x100,
	PTE_LV4_GLOBAL		=	0x200,
   	PTE_FRAME		=	0xFFFFF000 
};

enum PAGE_PDE_FLAGS {
 
	PDE_PRESENT		=	1,
	PDE_WRITABLE		=	2,
	PDE_USER		=	4,
	PDE_PWT			=	8,	
	PDE_PCD			=	0x10,
	PDE_ACCESSED		=	0x20,
	PDE_DIRTY		=	0x40,
	PDE_4MB			=	0x80,
	PDE_CPU_GLOBAL		=	0x100,
	PDE_LV4_GLOBAL		=	0x200,	
   	PDE_FRAME		=	0xFFFFF000 
};
//Responsibitities
static inline void entry_toggle_attrib (uint32_t* e, uint32_t attrib);  //This seems to be common for both the tables lol
static void entry_set_frame (uint32_t*, uint32_t);
static inline bool entry_is_present (uint32_t e);
static inline bool entry_is_writable (uint32_t e);
static inline uint32_t entry_physical (uint32_t e);  //Extract the physical address of the 32 bit entry

//Implementations
static inline void entry_toggle_attrib (uint32_t* e, uint8_t attrib)  //uint8_t or 32? Maybe change this .... 
{
	*e ^= attrib;
	return true;
}

static inline void entry_set_frame (uint32_t* e, uint32_t physical_address)
{
	*e = (physical_address & PTE_FRAME)|( (*e) & (~PTE_FRAME) );
}

static inline bool entry_is_present (uint32_t e)
{
	return (e & PTE_PRESENT);

}
static inline bool entry_is_writable (uint32_t e)
{
	return (e & PTE_WRITABLE);
}


static inline uint32_t entry_physical (uint32_t e);  //Extract the physical address of the 32 bit entry
{
	return (e & PTE_FRAME);
}

uint32_t virtual_to_physical (uint32_t virtual_address)
{
	uint32_t tab_entry = virtual_address >> 12;
	uint32_t dir_entry = tab_entry  >> 10;
	uint32_t* page_table = _page_directory[dir_entry] & PDE_FRAME;
	uint32_t physical_address = page_table[tab_entry] & PTE_FRAME;
	physical_address += (virtual_address & 0xFFF);
	return physical_address;
}







