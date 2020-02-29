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


typedef struct mmap_entry
{
    uint32_t  startLo;
    uint32_t  startHi;
    uint32_t  sizeLo;
    uint32_t  sizeHi;
    uint32_t  type;
    uint32_t  acpi_3_0;
} mmap_entry_t;

void print_memory_map(uint32_t mmapsize);

void kmain(uint32_t mmapsize)
{
	set_fg_color(CYAN);
	set_bg_color(LIGHT_GREY);
	clear();
 
	pmmngr_init(mmapsize);
	vmmngr_init();
	return;
}
/*
void print_memory_map(uint32_t mmapsize)
{
        mmap_entry_t* map= (mmap_entry_t*)0x1000;
        for (int i = 0; i< mmapsize ; i++)
        {
                printf("\nStarting address:"); printhex((map+i) -> startLo);
                printf("\tSize: "); printhex((map+i) -> sizeLo);
                printf("\tType:"); printhex((map+i) -> type);
         }
}       
 
*/
