#ifndef HAL_H
#define HAL_H

#include<stdint.h>

typedef struct __attribute__ ((__packed__)) idtr {
	uint16_t		limit;
	uint32_t		base;
}idtr_t;

typedef struct __attribute__ ((__packed__)) gdtr {
	uint16_t		limit;
	uint32_t		base;
}gdtr_t;

typedef struct __attribute__ ((__packed__)) idt_descriptor {
uint16_t		baseLo;
uint16_t		sel;
uint8_t			reserved;
uint8_t			flags;
uint16_t		baseHi;
}idt_descriptor_t;

typedef struct __attribute__((__packed__)) gdt_descriptor {
uint16_t		limit;
uint16_t		baseLo;
uint8_t			baseMid;
uint16_t		flags;
uint8_t			baseHi;
} gdt_descriptor_t;

void idt_init();
#endif
