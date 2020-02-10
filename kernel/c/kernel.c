#include<stdint.h> 
#include "dadio.h"

//---------------------------------------------
#define PMMAP 0x1000
#define KERNEL_P 0x100000
#define BLOCK_SIZE 4096
#define SECTOR_SIZE 512
#define SECTORS_PER_BLOCK 8
#define BLOCK_SIZE_B 12
#define SECTOR_SIZE_B 9
#define SECTORS_PER_BLOCK_B 3

void  pmmngr_init(uint32_t mapentrycount);
uint32_t* _physical_memory_table;
void pmmgr_free_range(uint32_t start,uint32_t end);

extern uint32_t __begin[], __end[];  //Why arrays? This is a pretty cool concept to distinguish pointers

//---------------------------------------------
void kmain()
{
	clear();
	printf("This is your C code executing! Time to party!\n");
	printf("The next target is to get a working memory manager...");
	pmmngr_init(6);
	return;
}



typedef struct mmap_entry {
    uint32_t  startLo;
    uint32_t  startHi;
    uint32_t  sizeLo;
    uint32_t  sizeHi;
    uint32_t  type;
    uint32_t  acpi_3_0;
  } mmap_entry_t;
void  pmmngr_init(uint32_t mapentrycount)   //kernel size in 512 byte sectors - I'm not taking high into consideration because 32 bit
{ 
//	uint32_t kernel_block_count  = kernelsize >> SECTORS_PER_BLOCK_B;
	mmap_entry_t* map_ptr= (mmap_entry_t*)PMMAP;
	_physical_memory_table = __end;   //Debug here!

	for (uint32_t i=0;i<0x8000;i++)
	       	_physical_memory_table[i] = 0xffffffff; //Make everything 1 -- Everything is occupied initially; I'd missed the i before
	for( uint32_t i=0;i<mapentrycount;i++)
	{
		if((map_ptr -> type == 1)&&(map_ptr -> startLo >= 0x100000))
		{
			pmmgr_free_range(map_ptr->startLo, map_ptr->startLo + map_ptr ->sizeLo);

		}
	map_ptr ++;
	}				
}

static inline uint32_t block_number(uint32_t address)
{
	return address >> BLOCK_SIZE_B;
}

static inline void pmmngr_toggle_block(uint32_t block_number)   //This must not be exposed to the programmer!!!
{
	uint8_t bit = block_number % 8; 
	uint8_t* byte = (uint8_t*)(block_number >> 3);
	byte += (uint32_t)_physical_memory_table;
	uint8_t mask = 1<<bit;
	*byte ^= mask;
}
/** start and end are addresses**/
void pmmgr_free_range(uint32_t start,uint32_t end)    //Optimize the crap out of this later
{
	while((end - start) >= BLOCK_SIZE)
	{
		pmmngr_toggle_block(block_number(start));
		start += BLOCK_SIZE;
	}
}
