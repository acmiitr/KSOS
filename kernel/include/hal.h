#ifndef HAL_H
#define HAL_H
#include<stdint.h>

void gdt_init();
void tss_kernel_init();

//Assembly defined
void kernel_wait();
uint8_t read_port(uint32_t);
void write_port(uint32_t port,uint32_t data);
uint16_t read_port_word(uint32_t);
void write_port_word(uint32_t port,uint32_t data);
void install_idt(uint32_t address);
void install_gdt(uint32_t address);
void install_tss(uint32_t address);
void enable_interrupts();
void gen_interrupt(uint8_t intnumber);
void enable_interrupts();
void clear_interrupts();
void kernel_wait();
uint32_t get_pdbr();
void flush_tlb_entry(uint32_t address);
void flush_tlb();

#endif
