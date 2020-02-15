#include<stdint.h> 
#include "dadio.h"
#include "phymem.h"
#include "virtmem.h"

void kmain(uint32_t mmapsize)
{
	clear();
	printf("This is your C code executing! Time to party!\n");
	printf("Hello Divyanshu!");
	pmmngr_init(mmapsize);
	vmmngr_init();
	map_page(0xD0000000,0xb8000);
	*(char*)0xD0000000 = 'm';

	return;
}

