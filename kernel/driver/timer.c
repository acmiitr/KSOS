/**  
 * @file timer.c
 * @brief Handles the operating systems's Timer
 * 
 * @see 
 */
#include <stdint.h>
#include <stdbool.h>
#include "hardware.h"
#include "hal.h"

#define TIMER_CONTROL_PORT 0x43/**<Variable description here*/
#define TIMER_DATA_PORT 0x40/**<Variable description here*/

/**Video memory*/
extern char __VGA_text_memory[];
/**Variable description here*/
static uint32_t tick_counter = 0;
/**Variable description here*/
bool _is_timer_interrupt = false;

//Helper functions
static void rotate_pole(int x, int y);
/**
 * @brief 
 * @param 
 * @return 
*/
uint32_t get_tick_count()
{
	return tick_counter;
}
/**
 * @brief 
 * @param 
 * @return 
*/
void timer_handler(){
	send_EOI_master();
	_is_timer_interrupt = true;
	tick_counter ++;
	rotate_pole(79,0);
}
/**
 * @brief 
 * @param 
 * @return 
*/
void set_timer(uint16_t count)
{
// FIRST send the command word to the PIT. Sets binary counting,
//	 Mode 3, Read or Load LSB first then MSB, Channel 0
 
	write_port(TIMER_CONTROL_PORT,0x36);
//	mov	al, 110110b
//	out	0x43, al
	write_port(TIMER_DATA_PORT, count & 0xff);
	write_port(TIMER_DATA_PORT, count >> 8);
}
/**
 * @brief 
 * @param 
 * @return 
*/
void wait_for_timer()
{
	_is_timer_interrupt = false;
	while(1)
	{
		kernel_wait();
		if(_is_timer_interrupt)
		{
			_is_timer_interrupt = false;
			return;
		}
	}
}

static void rotate_pole(int x, int y) 
{
	char* sym = (char*)(__VGA_text_memory + 2*(x+80*y));
	switch(*sym){
		case '|':
			*sym = '/';
			break;
		case '/':
			*sym = '-';
			break;
		case '-':
			*sym = '\\';
			break;
		case '\\':
			*sym = '|';
			break;
		default:
			*sym = '|';
	}

}
