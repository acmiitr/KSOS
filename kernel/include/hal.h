#ifndef HAL_H
#define HAL_H

//Structure definitions
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


void init_pic();
void send_EOI_master();
void send_EOI_slave();
void gdt_init();

//Assembly defined
void kernel_wait();
uint8_t read_port(uint32_t);
void write_port(uint32_t port,uint32_t data);
uint16_t read_port_word(uint32_t);
void write_port_word(uint32_t port,uint32_t data);
void install_idt(idtr_t* address);
void install_gdt(uint32_t address);
void enable_interrupts();
void gen_interrupt(uint8_t intnumber);
void enable_interrupts();
void clear_interrupts();
void kernel_wait();
uint32_t get_pdbr();
void flush_tlb_entry(uint32_t address);
void flush_tlb();


#endif
