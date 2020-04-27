/**  
 * @file tss.c
 * @brief ...
 * @see 
 */
#include<stdint.h>
#include<string.h>
#include"hal.h"

#define KERNEL_ESP 0xFFC00000	/**< Description here */
#define KERNEL_SS 0x10	/**< Description here */

/** Description here */
typedef struct  __attribute__((packed)) tss_entry {
	uint32_t prevTss;
	uint32_t esp0;
	uint32_t ss0;
	uint32_t esp1;
	uint32_t ss1;
	uint32_t esp2;
	uint32_t ss2;
	uint32_t cr3;
	uint32_t eip;
	uint32_t eflags;
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t es;
	uint32_t cs;
	uint32_t ss;
	uint32_t ds;
	uint32_t fs;
	uint32_t gs;
	uint32_t ldt;
	uint16_t trap;
	uint16_t iomap;
}tss_entry_t;

__attribute__((aligned(4096))) static tss_entry_t _kernel_tss;


extern void gdt_set_descriptor(uint16_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t grand);
/** @brief ...
 * 
 * @return  
 * */
void tss_kernel_init()
{
	//! install _kernel_tss descriptor
	uint32_t base = (uint32_t) &_kernel_tss;
	gdt_set_descriptor (5, base, base + sizeof (tss_entry_t),0xE9,0);  //_kernel_tss hardcoded

	//! initialize _kernel_tss
	memset ((void*) &_kernel_tss, 0, sizeof (tss_entry_t));

	_kernel_tss.ss0 = KERNEL_SS;
	_kernel_tss.esp0 = KERNEL_ESP;

	_kernel_tss.cs=0x08;
	_kernel_tss.ss = 0x10;
	_kernel_tss.es = 0x10;
	_kernel_tss.ds = 0x10;
	_kernel_tss.fs = 0x10;
	_kernel_tss.gs = 0x10;

	install_tss(5*8);
}
