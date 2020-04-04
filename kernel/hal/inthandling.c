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


//Structs
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

//Global variables in this routine
static idt_descriptor_t _idt[MAX_INTERRUPTS];
static idtr_t _idtr;

//Exception Handlers
void default_handler();
void divide_by_zero_fault (uint32_t eip, uint32_t cs, uint32_t flags) ;
void single_step_trap (uint32_t cs, uint32_t eip, uint32_t flags) ;
void nmi_trap (uint32_t cs, uint32_t eip, uint32_t flags);
void breakpoint_trap (uint32_t cs, uint32_t eip, uint32_t flags) ;
void overflow_trap (uint32_t cs, uint32_t eip, uint32_t flags) ;
void bounds_check_fault (uint32_t cs, uint32_t  eip, uint32_t flags) ;
void invalid_opcode_fault (uint32_t cs, uint32_t  eip, uint32_t flags) ;
void no_device_fault (uint32_t cs, uint32_t eip, uint32_t flags) ;
void double_fault_abort (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void invalid_tss_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) ;
void no_segment_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void stack_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void general_protection_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  ;
void bc_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err);
void fpu_fault  (uint32_t cs, uint32_t  eip, uint32_t flags);
void page_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err);
void machine_check_abort (uint32_t cs, uint32_t  eip, uint32_t flags);
void simd_fpu_fault (uint32_t cs, uint32_t  eip, uint32_t flags);

//Interrupt handler assembly stubs
void isr32();
void isr33();
void isr34();
void isr35();
void isr36();
void isr37();
void isr38();
void isr39();

void isr46(); //Primary ATA bus
void isr47(); //Secondary ATA bus


//Function implementations

void interrupt_init()
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


	install_ir(32,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr32);
	install_ir(33,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr33);
	install_ir(34,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr34);
	install_ir(35,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr35);
	install_ir(36,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr36);
	install_ir(37,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr37);

	install_ir(46,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr46);
	install_ir(47,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)isr47);

	//Exceptions - Need to distinguish between error and no error codes

	install_ir(0,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)divide_by_zero_fault);
	install_ir(1,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)single_step_trap);
	install_ir(2,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)nmi_trap);
	install_ir(3,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)breakpoint_trap);
	install_ir(4,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)overflow_trap);
	install_ir(5,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)bounds_check_fault);
	install_ir(6,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)invalid_opcode_fault);
	install_ir(7,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)no_device_fault);
	install_ir(8,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)invalid_tss_fault);
	install_ir(9,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)no_segment_fault);
	install_ir(10,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)stack_fault);
	install_ir(11,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)general_protection_fault);
	install_ir(12,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)bc_fault);
	install_ir(13,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)fpu_fault);
	install_ir(14,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)page_fault);
	install_ir(15,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)machine_check_abort);
	install_ir(16,IDT_DESC_BIT32|IDT_DESC_PRESENT,0x08,(uint32_t*)simd_fpu_fault);

	init_pic();
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




//These are the simple exception handlers
void default_handler()
{
	monitor_puts("This is the default exception handler");
	for (;;);
}

void divide_by_zero_fault (uint32_t eip, uint32_t cs, uint32_t flags) {

	monitor_puts ("Divide by 0 :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

void single_step_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	monitor_puts ("Single step :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! non maskable interrupt trap
void nmi_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	monitor_puts ("NMI :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! breakpoint hit
void breakpoint_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	monitor_puts ("Breakpoint :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! overflow
void overflow_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	monitor_puts ("Overflow :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! bounds check
void bounds_check_fault (uint32_t cs, uint32_t  eip, uint32_t flags) {

	monitor_puts ("Bounds check :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! invalid opcode / instruction
void invalid_opcode_fault (uint32_t cs, uint32_t  eip, uint32_t flags) {

	monitor_puts ("Invalid opcode :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! device not available
void no_device_fault (uint32_t cs, uint32_t eip, uint32_t flags) {

	monitor_puts ("Invalid device :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! double fault
void double_fault_abort (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	monitor_puts ("Doublefault :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! invalid Task State Segment (TSS)
void invalid_tss_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {

	monitor_puts ("Invalid TSS :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! segment not present
void no_segment_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	monitor_puts ("Invalid segment:");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! stack fault
void stack_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	monitor_puts ("Stack fault :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! general protection fault
void general_protection_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	monitor_puts ("GP :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}


void bc_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {
	monitor_puts ("Page fault :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
       	for (;;);
}

//! Floating Point Unit (FPU) error
void fpu_fault  (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	monitor_puts ("FPU fault :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

void page_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	monitor_puts ("Page fault :");
	printhex(cs);printhex(eip);printhex(flags),printhex(err);
	for (;;);
}
//! machine check
void machine_check_abort (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	monitor_puts ("Machine check :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

void simd_fpu_fault (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	monitor_puts ("FPU SIMD :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

