// Standard includes:
#include<stdint.h> 
#include<stdbool.h>
#include"phymem.h"
#include"dadio.h"

// Constant definitions:
#define PMMAP 0x1000
#define KERNEL_P 0x100000
#define BLOCK_SIZE 4096
#define SECTOR_SIZE 512
#define SECTORS_PER_BLOCK 8
#define BLOCK_SIZE_B 12
#define SECTOR_SIZE_B 9
#define SECTORS_PER_BLOCK_B 3

// External variables:
extern uint32_t __begin[], __end[];  //Why arrays? This is a pretty cool concept to distinguish pointers

// Routines internal to object:
static void pmmngr_toggle_range(uint32_t start,uint32_t end);
static inline void pmmngr_toggle_block(uint32_t block_number);
static inline uint32_t block_number(uint32_t address);
static uint8_t get_lowest_bit(uint32_t hexinp);
static uint8_t extract_bit(uint32_t hexinp,uint8_t bitnumber); 


// Data structues and user defined data types:

//static uint32_t _mapentrycount;
static uint32_t physical_memory_bitmap[0x8000];   //Why 8000? This is a hardcoded value (4GB needs this much)

typedef struct mmap_entry
{
    uint32_t  startLo;
    uint32_t  startHi;
    uint32_t  sizeLo;
    uint32_t  sizeHi;
    uint32_t  type;
    uint32_t  acpi_3_0;
} mmap_entry_t;


// Function implementations:

void  pmmngr_init(uint32_t mapentrycount)   //kernel size in 512 byte sectors - I'm not taking high into consideration because 32 bit
{ 
	//_mapentrycount = mapentrycount;
	mmap_entry_t* map_ptr= (mmap_entry_t*)PMMAP;


	for (uint32_t i=0;i<0x8000;i++)
	       	physical_memory_bitmap[i] = 0xffffffff; //Make everything 1 -- Everything is occupied initially
/*
	printhex((uint32_t)physical_memory_bitmap);


	for (int i = 0; i< mapentrycount ; i++)
        {
                printf("\nStarting address:"); printhex((map_ptr+i) -> startLo);
                printf("\tSize: "); printhex((map_ptr+i) -> sizeLo);
                printf("\tType:"); printhex((map_ptr+i) -> type);
         }
*/
	for(uint32_t i=0;i<mapentrycount;i++)
	{
		if((map_ptr -> type == 1)&&(map_ptr -> startLo >= KERNEL_P) && !(map_ptr -> startHi))
			pmmngr_toggle_range(map_ptr->startLo, map_ptr->startLo + map_ptr ->sizeLo);
		map_ptr ++;
	}				
	//Now we free the space occupied by the kernel and this memory manager :)
	uint32_t kernel_start = (uint32_t)__begin;
	uint32_t kernel_end = (uint32_t)__end;
	pmmngr_toggle_range (KERNEL_P,KERNEL_P + kernel_end - kernel_start);
}

uint32_t* pmmngr_allocate_block()
{
	uint32_t* address;
	for( uint32_t i=0;i<0x8000;i++)
		if (physical_memory_bitmap[i] < 0xffffffff)
		{
			uint8_t bit = get_lowest_bit(physical_memory_bitmap[i]);  //bit lies from 0 to 31
				if(bit == 0xff) return 0;
			address = (uint32_t*)((i << 17) + (bit << 12));
			pmmngr_toggle_block(block_number((uint32_t)address));
			return address;
		}
	return 0;
}
bool pmmngr_free_block(uint32_t* address)
{
	if((uint32_t)address % BLOCK_SIZE != 0) return 0;
	
	/*
	mmap_entry_t* map_ptr= (mmap_entry_t*)PMMAP;
	for( uint32_t i=0;i<_mapentrycount;i++)
	{
		if(((map_ptr->startLo) <= (uint32_t)address)&& (((uint32_t)address-map_ptr->startLo) < map_ptr->sizeLo))
		{
			if (map_ptr -> type ==1)
			{

				uint32_t block = block_number((uint32_t)address);
				uint32_t dword = block >> 5;
				uint8_t offset = block % 32;
				if(extract_bit((uint32_t)(physical_memory_bitmap + dword),offset)) return 0;
				pmmngr_toggle_block(block);
				return 1;

			}
			else return 0;
		}
		map_ptr ++;
	}
	*/
	uint32_t block = block_number((uint32_t)address);
	uint32_t dword = block >> 5;
	uint8_t offset = block % 32;
	if(!extract_bit((uint32_t)(physical_memory_bitmap + dword),offset)) return 0;
	pmmngr_toggle_block(block);
	return 1;

//	return 0;

}
// Helper function implementations:
static uint8_t get_lowest_bit(uint32_t hexinp)
{
	for(int i=0;i<32;i++)
	{
		if ((hexinp%2) == 0)
			return i;
		hexinp >>= 1;
	}
	return 0xff;
}
static inline uint8_t extract_bit(uint32_t hexinp,uint8_t bitnumber)  //bitnumber < 32
{
	return (hexinp >> bitnumber) & 1;
}
static inline uint32_t block_number(uint32_t address)
{
	return address >> BLOCK_SIZE_B;
}

static inline void pmmngr_toggle_block(uint32_t block_number)   //This must not be exposed to the programmer!!!
{
	physical_memory_bitmap[block_number >> 5] ^= (1ul << (block_number & 31));
//	uint8_t bit = block_number % 8; 
//	uint8_t* byte = (uint8_t*)(block_number >> 3);
//	byte += (uint32_t)physical_memory_bitmap;
//	*byte ^= (1<<bit);
}
/** start and end are addresses**/
static void pmmngr_toggle_range(uint32_t start,uint32_t end)    //Optimize the crap out of this later
{
	if (start % BLOCK_SIZE != 0){start -= (start%BLOCK_SIZE_B);}
	if (end % BLOCK_SIZE != 0){end -= (end%BLOCK_SIZE_B); end += BLOCK_SIZE;}
	while((end - start) >= BLOCK_SIZE)
	{
		
		if((end - start) >= 32* BLOCK_SIZE)
		{
			uint32_t* byte = (uint32_t*)(block_number(start) >> 3);
			byte = (uint32_t*)((uint8_t*)byte +(uint32_t)physical_memory_bitmap);
			*byte ^= 0xffffffff;
			start += (BLOCK_SIZE<<5);
			
		}
		else
		{
			pmmngr_toggle_block(block_number(start));
			start += BLOCK_SIZE;
		}
	}
}

//	_lazy_byte = (uint32_t*)start;
//static uint32_t* _lazy_byte;
//	physical_memory_bitmap = __end;   //Debug here!
//	uint32_t kernel_block_count  = kernelsize >> SECTORS_PER_BLOCK_B;
