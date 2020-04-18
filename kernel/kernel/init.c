#include <stdint.h>

extern uint32_t system_call(uint32_t eax,uint32_t esi, uint32_t edi);

__attribute__((section (".user")))void init()
{
//	system_call (0,(uint32_t)"Daddy",0);
	for(;;);
}
