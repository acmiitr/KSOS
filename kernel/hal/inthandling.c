#include<stdint.h>
#include"dadio.h"
#include"hal.h"
#include"inthandling.h"
#include"hardware.h"

#define MAX_INTERRUPTS 256
#define IDT_DESC_TRAP 0x01	//00000001
#define IDT_DESC_BIT16 0x06	//00000110
#define IDT_DESC_BIT32 0x0E	//00001110
#define IDT_DESC_RING1 0x40	//01000000
#define IDT_DESC_RING2 0x20	//00100000
#define IDT_DESC_RING3 0x60	//01100000
#define IDT_DESC_PRESENT 0x80	//10000000


//User-defined variables and structs

typedef uint32_t reg32_t;
typedef uint32_t seg16_t;

typedef struct __attribute__ ((__packed__)) idtr {
	uint16_t		limit;
	uint32_t		base;
}idtr_t;

typedef struct __attribute__ ((__packed__)) idt_descriptor {
uint16_t		baseLo;
uint16_t		sel;
uint8_t			reserved;
uint8_t			flags;
uint16_t		baseHi;
}idt_descriptor_t;

typedef struct itrpt_reg_state {
	seg16_t gs;
	seg16_t fs;
	seg16_t es;
	seg16_t ds;

	reg32_t edi;
	reg32_t esi;
	reg32_t ebp;
	reg32_t esp; //Ignore this
	reg32_t ebx;
	reg32_t edx;
	reg32_t ecx;
	reg32_t eax;

	uint32_t vector_number;
	uint32_t error_code;
	reg32_t eip;
	seg16_t cs;
	uint32_t flag;
}itrpt_reg_state_t;


//Global variables in this routine
static idt_descriptor_t _idt[MAX_INTERRUPTS];
static idtr_t _idtr;

void default_handler();
void system_call_handler(itrpt_reg_state_t* inp_ptr);
void isr0(); void isr1(); void isr2(); void isr3(); void isr4(); void isr5(); void isr6(); void isr7(); void isr8(); 
void isr9(); void isr10(); void isr11(); void isr12(); void isr13(); void isr14(); void isr15(); void isr16(); 
void isr17(); void isr18(); void isr19(); void isr20(); void isr21(); void isr22(); void isr23(); void isr24();
void isr25(); void isr26(); void isr27(); void isr28(); void isr29(); void isr30(); void isr31(); void isr32(); 
void isr33(); void isr34(); void isr35(); void isr36(); void isr37(); void isr38(); void isr39(); void isr40(); 
void isr41(); void isr42(); void isr43(); void isr44(); void isr45(); void isr46(); void isr47(); 

void isr128(); //int 0x80

//Function implementations
void interrupt_init()
{
	_idtr.base = (uint32_t)_idt;
	_idtr.limit = (sizeof (idt_descriptor_t) * MAX_INTERRUPTS) -1 ;
	
	for (int i=0;i<MAX_INTERRUPTS;i++) //TODO: Memset this
	{
		_idt[i].baseLo = 0;
		_idt[i].sel = 0;
		_idt[i].reserved = 0;
		_idt[i].flags = 0;
		_idt[i].baseHi = 0;
	}

	for (int i=0;i<MAX_INTERRUPTS;i++)
		install_ir(i,IDT_DESC_BIT32 | IDT_DESC_PRESENT, 0x08, (uint32_t*) default_handler);

	//Exceptions - Need to distinguish between error and no error codes

	install_ir(0,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr0);
	install_ir(1,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr1);
	install_ir(2,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr2);
	install_ir(3,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr3);
	install_ir(4,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr4);
	install_ir(5,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr5);
	install_ir(6,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr6);
	install_ir(7,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr7);
	install_ir(8,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr8);
	install_ir(10,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr10);
	install_ir(11,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr11);
	install_ir(12,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr12);
	install_ir(13,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr13);
	install_ir(14,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr14);
	install_ir(16,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr16);
	
	install_ir(32,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr32);
	install_ir(33,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr33);
	install_ir(34,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr34);
	install_ir(35,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr35);
	install_ir(36,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr36);
	install_ir(37,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr37);

	install_ir(46,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr46);
	install_ir(47,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr47);
	
//User mode interrupts
	install_ir(0x80,IDT_DESC_BIT32|IDT_DESC_PRESENT|IDT_DESC_RING3|IDT_DESC_TRAP,0x08,(uint32_t*)isr128); //This is syscall


	pic_init();
	kbc_init();
	set_timer(0xFFFF);
	install_idt((uint32_t)&_idtr);
	enable_interrupts();
}


void install_ir(uint32_t index,uint16_t flags, uint16_t sel, uint32_t* handler_address)
{
	if (index >=MAX_INTERRUPTS) return;

	_idt[index].baseLo = (uint32_t)handler_address & 0xffff;
	_idt[index].baseHi = ((uint32_t)handler_address >> 16) & 0xffff;
	_idt[index].reserved = 0;
	_idt[index].flags = flags;
	_idt[index].sel = sel;
}

void general_interrupt_handler(itrpt_reg_state_t input)
{
	switch (input.vector_number)
	{
		case 32:
			timer_handler();
			break;
		case 33:
			keyboard_handler();
			break;


		case 46:
		case 47:
			send_EOI_master();
			send_EOI_slave();
			break;

		case 0x80:
			system_call_handler(&input);
			break;
		default:
			monitor_puts("\nException number:"); printhex(input.vector_number);
			monitor_puts("\nError code:"); printhex(input.error_code);
			monitor_puts("\nProgram counter:"); printhex(input.cs);putc(':');printhex(input.eip);
			monitor_puts("\nHandling support not present yet :(");
			for(;;);
	}
}

void default_handler()
{
	monitor_puts("This is the default handler - This is a really messed up interrupt");
	for(;;);
}

void system_call_handler(itrpt_reg_state_t* inp_ptr)  //Kernel-level
{

	switch(inp_ptr->eax)
	{
		case 0:
			monitor_puts((char*)inp_ptr->esi);
			break;

		default:
			monitor_puts("Welcome to the syscall interface\nSyscall_number:");
			printhex(inp_ptr->eax);
	}

}
