
#ifndef TIMER_H
#define TIMER_H


#include<stdint.h>

void set_timer(uint32_t delay); //Assembly defined function

uint32_t get_tick_count();
	
#endif
