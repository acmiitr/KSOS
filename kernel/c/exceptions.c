#include<stdint.h>
#include"dadio.h"

void default_handler()
{
	printf("This is the default exception handler");
	for (;;);
}

void divide_by_zero_fault (uint32_t eip, uint32_t cs, uint32_t flags) {

	printf ("Divide by 0 :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

void single_step_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	printf ("Single step :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! non maskable interrupt trap
void nmi_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	printf ("NMI :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! breakpoint hit
void breakpoint_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	printf ("Breakpoint :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! overflow
void overflow_trap (uint32_t cs, uint32_t eip, uint32_t flags) {

	printf ("Overflow :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! bounds check
void bounds_check_fault (uint32_t cs, uint32_t  eip, uint32_t flags) {

	printf ("Bounds check :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! invalid opcode / instruction
void invalid_opcode_fault (uint32_t cs, uint32_t  eip, uint32_t flags) {

	printf ("Invalid opcode :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! device not available
void no_device_fault (uint32_t cs, uint32_t eip, uint32_t flags) {

	printf ("Invalid device :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! double fault
void double_fault_abort (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	printf ("Doublefault :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! invalid Task State Segment (TSS)
void invalid_tss_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {

	printf ("Invalid TSS :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! segment not present
void no_segment_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	printf ("Invalid segment:");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! stack fault
void stack_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	printf ("Stack fault :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}

//! general protection fault
void general_protection_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	printf ("GP :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
	for (;;);
}


//! page fault
void page_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err) {
	printf ("Page fault :");
	printhex(cs);printhex(eip);printhex(flags);printhex(err);
       	for (;;);
}

//! Floating Point Unit (FPU) error
void fpu_fault  (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	printf ("FPU fault :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

//! alignment check
void alignment_check_fault (uint32_t eip,uint32_t cs,uint32_t flags,uint32_t err)  {

	printf ("Alignment check :");
	printhex(cs);printhex(eip);printhex(flags),printhex(err);
	for (;;);
}
//! machine check
void machine_check_abort (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	printf ("Machine check :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}

void simd_fpu_fault (uint32_t cs, uint32_t  eip, uint32_t flags)  {

	printf ("FPU SIMD :");
	printhex(cs);printhex(eip);printhex(flags);
	for (;;);
}
