#include<stdint.h> 
#include "dadio.h"
#include "phymem.h"
#include "virtmem.h"
#include "timer.h"
#include "keyboard.h"
#include "hal.h"
#include "inthandling.h"
#include "ATA.h"
#include "FAT12.h"

extern void kshell();
uint8_t array[512];
void initialize_all(uint32_t mmapsize);
void kmain(uint32_t mmapsize,uint32_t data_sect,uint32_t root_sect,uint32_t fat_sect)
{
	pmmngr_init(mmapsize);
	vmmngr_init();
	interrupt_init();
	kbc_init();
	set_timer(0xffff);
	initialize_FAT(data_sect,root_sect,fat_sect);


	clear();
	printf("Data starts: ");printhex(data_sect*512);
	printf("\nRoot starts: ");printhex(root_sect*512);
	printf("\nFAT starts: ");printhex(fat_sect*512);

	get_monitor_char();
	kshell();
	return;
}

