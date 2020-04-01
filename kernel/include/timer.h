#ifndef TIMER_H
#define TIMER_H


#include<stdint.h>

extern bool _is_timer_interrupt;

void set_timer(uint16_t delay); 
void wait_for_timer();
uint32_t get_tick_count();
	
#endif
