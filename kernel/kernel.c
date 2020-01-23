#include<stdint.h> 
#define COLOR 0x39
#define VIDEO_MEMORY 0xb8000

uint32_t get_cursor();
void set_cursor(uint32_t);
void printf(char* Message);
void kmain()
{
	printf("This is working, so I'm losing my shit :)");
	return;
}

void printf(char* Message)
{
	uint32_t pointer = get_cursor();
	pointer <<= 1;
	char* VGA_CURSOR = (char*) VIDEO_MEMORY;
	VGA_CURSOR += pointer;
	while	(*Message)
	{
		*VGA_CURSOR = *Message;
		Message++;
		VGA_CURSOR ++;
		*VGA_CURSOR = COLOR;
		VGA_CURSOR ++;
	}
	VGA_CURSOR -= VIDEO_MEMORY;
	pointer = (uint32_t)VGA_CURSOR;
	pointer >>= 1;
	set_cursor(pointer);
}
