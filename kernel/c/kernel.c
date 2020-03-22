#include<stdint.h> 
#include "dadio.h"
#include "phymem.h"
#include "virtmem.h"
#include "timer.h"
#include "keyboard.h"
#include "hal.h"
#include "inthandling.h"

extern void kshell();

void initialize_all(uint32_t mmapsize);
void kmain(uint32_t mmapsize)
{
	initialize_all(mmapsize);

	kshell();
	return;
}

void initialize_all(uint32_t mmapsize)
{
	pmmngr_init(mmapsize);
	vmmngr_init();
	interrupt_init();
	kbc_init();
	set_timer(0xffff);
}
