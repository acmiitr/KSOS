#include<stdint.h> 
#include "dadio.h"
#include "memory.h"

void kmain()
{
	clear();
	printf("This is your C code executing! Time to party!\n");
	printf("The next target is to get a working memory manager...");
	pmmngr_init(6);
	uint32_t* chunk = pmmngr_allocate_block();
	printf((char*) chunk);
	pmmngr_free_block(chunk);
	return;
}

