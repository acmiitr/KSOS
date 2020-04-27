/**  
 * @file virtualmem.c
 * @brief ...
 * @see 
 */
/* Don't do a permanent identity map dude
 * Our strategy will be recursive identity map
 * You need this or else you're dead
 */

#define BLOCK_SIZE 4096				/**< Description here */
#define PAGE_TABLE 0xFFC00000		/**< Description here */
#define PAGE_DIRECTORY 0xFFFFF000	/**< Description here */
#define STACK 0xFFC00000			/**< Description here */
#define STACK_PHY 0x90000			/**< Description here */
#define VGA_TEXT 0xB8000			/**< Description here */
#define PAGE_SIZE (1<<12)			/**< Description here */

#include <stdint.h>
#include <stdbool.h>
#include "dadio.h"
#include "hal.h"
#include "phymem.h"
#include "virtmem.h"

static uint32_t* _page_directory = (uint32_t*)0x9C000;  //This is the initial virtual address of the page directory


/** Source: BrokenThorn 
A page table entry is just a 32 bit integer in our case :) */
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
/**< Description here */
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
//Helper functions
static void set_recursive_map();   //Sets the virtual address of the page directory to 0xFFFFF000 -- Some kind of dual reference XD
static bool alloc_page(uint32_t* table_entry);

//External linker symbols
extern uint32_t __begin[];
extern uint32_t __end[];
extern char  __VGA_text_memory[];  //This is the virtual address of the VGA memory

//Implementations
/** @brief ...
 *
 * @return  
 * */
void vmmngr_init() 
{
	set_recursive_map();
	//Need to remap video memory...
	if(!map_page((uint32_t)__VGA_text_memory,VGA_TEXT,false,true))
		for(;;); //monitor_puts("VGA remap failed");  //Keep another debug print
	if(!map_page(STACK-PAGE_SIZE,STACK_PHY-PAGE_SIZE,false,true))
		monitor_puts("Stack remap failed");
	if ((uint32_t)__end - (uint32_t)__begin > (2<<22))  
	{
		monitor_puts("Kernel spans more than 4M");
		for(;;);
	}
	//Need to set all the page frames that are in use by the kernel
}
/** @brief ...
 * 
 * @return  
 * */
void remove_identity_map()  //This would remove the 4M identity map
{
	//This requires a stack_reset, and gdt reset so far.
	_page_directory[0] = 0;
	flush_tlb();  //Clean that boi
}
/** @brief ...
 * @param virtual_address
 * @param physical_address
 * @param isUser
 * @param isWritable
 * @return  
 * */
bool map_page(uint32_t virtual_address,uint32_t physical_address,bool isUser,bool isWritable)   //TODO: Need to deal with freed frames  && Make this cleaner!!
{
	virtual_address -= (virtual_address%BLOCK_SIZE) ? virtual_address%BLOCK_SIZE : 0;
	physical_address -= (physical_address%BLOCK_SIZE) ? physical_address%BLOCK_SIZE : 0;

	uint32_t pd_index = virtual_address >> 22;
	if (!(_page_directory[pd_index] & PDE_PRESENT))
		if(!alloc_page(_page_directory+pd_index)) return false;

	if(isWritable) _page_directory[pd_index] |= PDE_WRITABLE;
	if(isUser) _page_directory[pd_index]|= PDE_USER;

	uint32_t* page_table = (uint32_t*)(PAGE_TABLE | (pd_index<<12)); //This is the virtual address of the page table 
	uint32_t pt_index = ((virtual_address >> 12) & 0x3FF); //Using recursive page table technique

	page_table[pt_index] = physical_address;
	page_table[pt_index] |= PTE_PRESENT;
	page_table[pt_index] |= PTE_WRITABLE;
	
	if(isUser)
       	{
		page_table[pt_index]|= PTE_USER;
	       	if(isWritable) page_table[pt_index] |= PTE_WRITABLE;
		else page_table[pt_index] &= ~PTE_WRITABLE;
	}
	else 
	{
		page_table[pt_index] &= ~PTE_USER;
	       	page_table[pt_index] |= PTE_WRITABLE;   //Writable anyway in kmode
	}

	flush_tlb_entry(virtual_address);
	return true;
}
/** @brief ...
 * 
 * @return  
 * */
static void set_recursive_map()   //Sets the virtual address of the page directory to 0xFFFFF000 -- Some kind of dual reference XD
{
	uint32_t phy_dir = get_pdbr();
	uint32_t* vir_dir = _page_directory;
	vir_dir[1023]=phy_dir;
	vir_dir[1023]|=PDE_PRESENT;
	vir_dir[1023]|=PDE_WRITABLE;
	_page_directory = (uint32_t*)PAGE_DIRECTORY; //Page directory is the last address
	flush_tlb();
}
/** @brief ...
 * @param virt
 * 
 * @return  
 * */
uint32_t virtual_to_physical (uint32_t* virt)
{
	uint32_t virtual_address = (uint32_t)virt;
	uint32_t pd_index = virtual_address >> 22;

	if (!(_page_directory[pd_index] & PDE_PRESENT)) return 0;

	uint32_t* page_table = (uint32_t*)(PAGE_TABLE | (pd_index<<12)); //This is the virtual address of the page table 
	uint32_t pt_index = ((virtual_address >> 12) & 0x3FF); //Using recursive page table technique

	if (!(page_table[pt_index] & PTE_PRESENT)) return 0;
	return ((page_table[pt_index] & PTE_FRAME) | (virtual_address & ~PTE_FRAME));
}
/** @brief ...
 * @param table_entry
 * 
 * @return  
 * */
static bool alloc_page(uint32_t* table_entry)   //Given a page table/directory entry, 'fill' it automatically
{
	uint32_t physical_address = pmmngr_allocate_block();
	if(!physical_address) return 0;

	*table_entry = physical_address;
	*table_entry |= PTE_PRESENT;
	return 1;

}

/*
void free_page(uint32_t* table_entry)  //Makes any entry free
{
	if(!entry_is_present(*table_entry)) return;
	uint32_t physical_address = *table_entry & PTE_FRAME;
	pmmngr_free_block( (uint32_t*) physical_address);
	entry_toggle_attrib (table_entry,PDE_PRESENT); //This seems like a bad idea?? Not flexible enough
}*/

/*
static inline void entry_toggle_attrib (uint32_t* e, uint8_t attrib)  //uint8_t or 32? Maybe change this .... 
{
	*e ^= attrib;
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


static inline uint32_t entry_physical (uint32_t e)  //Extract the physical address of the 32 bit entry
{
	return (e & PTE_FRAME);
}
*/

