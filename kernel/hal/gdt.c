/**  
 * @file gdt.c
 * @brief ...
 * @see 
 */
#include <stdint.h>
#include "hal.h"

#define GDT_DESCRIPTOR_COUNT 6/**< Description here */ 

#define I86_GDT_DESC_ACCESS		0x0001		//00000001
#define I86_GDT_DESC_READWRITE		0x0002		//00000010
#define I86_GDT_DESC_EXPANSION		0x0004		//00000100
#define I86_GDT_DESC_EXEC_CODE		0x0008		//00001000
#define I86_GDT_DESC_CODEDATA		0x0010		//00010000
#define I86_GDT_DESC_DPL		0x0060		//01100000
#define I86_GDT_DESC_MEMORY		0x0080		//10000000
#define I86_GDT_GRAND_LIMITHI_MASK	0x0f		//00001111
#define I86_GDT_GRAND_OS		0x10		//00010000
#define I86_GDT_GRAND_32BIT		0x40		//01000000
#define I86_GDT_GRAND_4K		0x80		//10000000

//Custom Variable types
/** Description here */
typedef struct __attribute__ ((__packed__)) gdtr
{
	uint16_t	limit;
	uint32_t	base;
}gdtr_t;
/** Description here */
typedef struct __attribute__((__packed__)) gdt_descriptor
{
	uint16_t	limit;
	uint16_t	baseLo;
	uint8_t		baseMid;
	uint8_t		flags;
	uint8_t		grand;
	uint8_t		baseHi;
}gdt_descriptor_t;

//Global variables
static gdt_descriptor_t _gdt[GDT_DESCRIPTOR_COUNT];
static gdtr_t _gdtr;
/** @brief ...
 * @param i ..
 * @param base ...
 * @param limit ...
 * @param access ...
 * @param grand ..
 * @return  
 * */
void gdt_set_descriptor(uint16_t i, uint32_t base, uint32_t limit, uint8_t access, uint8_t grand)
{ 	
	if (i > GDT_DESCRIPTOR_COUNT)
		return;

	//! set limit and base addresses
	_gdt[i].baseLo	= (uint16_t)(base & 0xffff);
	_gdt[i].baseMid	= (uint8_t)((base >> 16) & 0xff);
	_gdt[i].baseHi	= (uint8_t)((base >> 24) & 0xff);
	_gdt[i].limit	= (uint16_t)(limit & 0xffff);

	//! set flags and grandularity bytes
	_gdt[i].flags = access;
	_gdt[i].grand = (uint8_t)((limit >> 16) & 0x0f);
	_gdt[i].grand |= grand & 0xf0;
}


/*
//! returns descriptor in gdt
gdt_descriptor* i86_gdt_get_descriptor (int i) {

	if (i > MAX_DESCRIPTORS)
		return 0;

	return &_gdt[i];
}
*/
/** @brief ...
 * 
 * @return  
 * */
void gdt_init() 
{

	_gdtr.limit = (sizeof (struct gdt_descriptor) * GDT_DESCRIPTOR_COUNT)-1;
	_gdtr.base = (uint32_t)&_gdt[0];

	gdt_set_descriptor(0, 0, 0, 0, 0);

	gdt_set_descriptor (1,0,0xffffffff,
		I86_GDT_DESC_READWRITE|I86_GDT_DESC_EXEC_CODE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_MEMORY,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	gdt_set_descriptor (2,0,0xffffffff,
		I86_GDT_DESC_READWRITE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_MEMORY,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	gdt_set_descriptor (3,0,0xffffffff,
		I86_GDT_DESC_READWRITE|I86_GDT_DESC_EXEC_CODE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_MEMORY|I86_GDT_DESC_DPL,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	gdt_set_descriptor (4,0,0xffffffff,
		I86_GDT_DESC_READWRITE|I86_GDT_DESC_CODEDATA|I86_GDT_DESC_MEMORY|I86_GDT_DESC_DPL,
		I86_GDT_GRAND_4K | I86_GDT_GRAND_32BIT | I86_GDT_GRAND_LIMITHI_MASK);

	install_gdt((uint32_t)&_gdtr);
}
