#include<stdint.h> 
#include<string.h>
#include "dadio.h"
#include "phymem.h"
#include "virtmem.h"
#include "hardware.h"
#include "hal.h"
#include "inthandling.h"
#include "FAT12.h"

#define USERSTACK_PHY 0x40000
#define USERSTACK 0xC0000000
#define PAGE_SIZE 4096

//Are all part of /kernel
extern void kshell();
extern void refresh_stack();
extern void switch_to_user(uint32_t* address);
extern void init();

//Linker defined symbol
extern uint32_t __user_begin[];

void kmain(uint32_t mmapsize,uint32_t data_sect,uint32_t root_sect,uint32_t fat_sect)
{
	gdt_init();
	pmmngr_init(mmapsize); //Uses 0x1000... Don't remove identity map before that
	vmmngr_init();  //Sets recursive map, remaps stack and vidmem
	clear();

	monitor_puts("Data starts: ");printhex(data_sect*512);
	monitor_puts("\nRoot starts: ");printhex(root_sect*512);
	monitor_puts("\nFAT starts: ");printhex(fat_sect*512);
	
	initialize_FAT (data_sect,root_sect,fat_sect);
	read_file("ABCDEFGH.TXT");
	refresh_stack(); //This is some next level function: It forces stack remapping, some legend.. Debugging will get confused here
	remove_identity_map();

	interrupt_init();
	tss_kernel_init();
	set_timer(0xffff);
		
	if(get_monitor_char() == 's') kshell();
	
	map_page(USERSTACK - PAGE_SIZE,USERSTACK_PHY - PAGE_SIZE,true,true);
	map_page((uint32_t)__user_begin,virtual_to_physical(__user_begin),true,true);

	switch_to_user((uint32_t*)init);  //TODO: Make this a function pointer instead of uint32_t*

	clear_interrupts();
	kernel_wait();
	
}

