/*
enum vga_color {
         BLACK = 0,
         BLUE = 1,
         GREEN = 2,
         CYAN = 3,
         RED = 4,
         MAGENTA = 5,
         BROWN = 6,
         LIGHT_GREY = 7,
         DARK_GREY = 8,
         LIGHT_BLUE = 9,
         LIGHT_GREEN = 10,
         LIGHT_CYAN = 11,
         LIGHT_RED = 12,
         LIGHT_MAGENTA = 13,
         LIGHT_BROWN = 14,
         WHITE = 15,
 };      
*/
#include<stdint.h> 
#include "dadio.h"
#include "phymem.h"
#include "virtmem.h"
#include "timer.h"
#include "keyboard.h"
#include "hal.h"
#include "inthandling.h"

void initialize_all(uint32_t mmapsize);
void kmain(uint32_t mmapsize)
{
	initialize_all(mmapsize);

	set_fg_color(CYAN);
	set_bg_color(LIGHT_GREY);
	clear();
	printf("Start typing now!\n");
	set_fg_color(BLUE);
	set_bg_color(WHITE);
	while(1)
		putc(get_monitor_char());
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
