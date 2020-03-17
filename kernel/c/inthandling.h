#ifndef INTHANDLING_H
#define INTHANDLING_H
#include<stdint.h>
void install_ir(uint32_t index,uint16_t flags, uint16_t sel, uint32_t* handler_address);
void interrupt_init();
#endif
