#include <stdint.h>
#include "hal.h"
#include "dadio.h"

void install_idt(idtr_t* address);


#define MAX_INTERRUPTS 256
#define IDT_DESC_BIT16 0x06	//00000110
#define IDT_DESC_BIT32 0x0E	//00001110
#define IDT_DESC_RING1 0x40	//01000000
#define IDT_DESC_RING2 0x20	//00100000
#define IDT_DESC_RING3 0x60	//01100000
#define IDT_DESC_PRESENT 0x80//10000000

idt_descriptor_t _idt[MAX_INTERRUPTS];
idtr_t _idtr;

static void install_ir(uint32_t index,uint16_t flags, uint16_t sel, uint32_t* handler_address);
static void default_handler();



void idt_init()
{
	_idtr.base = (uint32_t)_idt;
	_idtr.limit = (sizeof (idt_descriptor_t) * MAX_INTERRUPTS) -1 ;
	
	for (int i=0;i<MAX_INTERRUPTS;i++)
	{
		_idt[i].baseLo = 0;
		_idt[i].sel = 0;
		_idt[i].reserved = 0;
		_idt[i].flags = 0;
		_idt[i].baseHi = 0;
	}

	for (int i=0;i<MAX_INTERRUPTS;i++)
		install_ir(i,IDT_DESC_BIT32 | IDT_DESC_PRESENT, 0x08, (uint32_t*) default_handler);
	install_idt( & _idtr);
}
static void install_ir(uint32_t index,uint16_t flags, uint16_t sel, uint32_t* handler_address)
{
	if (index >=MAX_INTERRUPTS) return;

	_idt[index].baseLo = (uint32_t)handler_address & 0xffff;
	_idt[index].baseHi = ((uint32_t)handler_address >> 16) & 0xffff;
	_idt[index].reserved = 0;
	_idt[index].flags = flags;
	_idt[index].sel = sel;
}

static void default_handler()
{
	printf("This is the default exception handler");
	for (;;);
}

