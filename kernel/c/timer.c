#include <stdint.h>
#define VIDEO_MEMORY 0xb8000

//Global variables
static uint32_t tick_counter = 0;



//Helper functions
static void rotate_pole(int x, int y);

uint32_t get_tick_count()
{
	return tick_counter;
}

void timer_handler(){
	tick_counter ++;
	rotate_pole(79,0);
}

static void rotate_pole(int x, int y)
{
	char* sym = (char*)(VIDEO_MEMORY + 2*(x+80*y));
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
