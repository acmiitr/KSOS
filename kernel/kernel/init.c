#include <stdint.h>
#include "virtmem.h"
#include "phymem.h"
#include "dadio.h"
#define USERSTACK 0xC0000000
#define USERSTACK_PHY 0x40000
#define PAGE_SIZE 4096

extern void switch_to_user();

extern uint32_t __user_begin[];

__attribute__((section (".user")))void init()
{
	map_page(USERSTACK - PAGE_SIZE,USERSTACK_PHY - PAGE_SIZE,true);
	printhex ((uint32_t)__user_begin);
	printhex (virtual_to_physical(__user_begin));
	map_page((uint32_t)__user_begin,0x103000,true);
	switch_to_user();
	for(;;);
}
