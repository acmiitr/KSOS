#include<stdint.h> 
#include "dadio.h"
#include "phymem.h"

void kmain(uint32_t mmapsize)
{
	clear();
	printf("This is your C code executing! Time to party!\n");
	printf("Hello Divyanshu!");
	pmmngr_init(mmapsize);
	uint32_t* chunk = pmmngr_allocate_block();
	uint32_t* chunk2 = pmmngr_allocate_block();
	printf((char*) chunk);
	printf((char*) chunk2);
	pmmngr_free_block(chunk);
	chunk = pmmngr_allocate_block();
	return;
}

