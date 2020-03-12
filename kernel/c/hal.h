#ifndef HAL_H
#define HAL_H

void interrupt_init();

void kernel_wait(); //Assembly defined
uint8_t read_port(uint32_t);
void write_port(uint32_t port,uint32_t data);
#endif
