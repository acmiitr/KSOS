#include<stdint.h>
#include "dadio.h"

#define VIDEO_MEMORY 0xb8000
#define ROW 80
#define COL 25

uint32_t get_cursor();
void set_cursor(uint32_t);

static char current_color = 0xf8;

void clear()
{
	char* cursor=(char*)VIDEO_MEMORY;
	*cursor=' ';
	cursor++;*cursor=current_color;cursor++;
	while((uint32_t)(cursor-VIDEO_MEMORY)<2*ROW*COL)
		{
			*cursor=' ';cursor++;
			*cursor=current_color;cursor++;
		}
	set_cursor(0);
}

void printf(char* Message)
{
	uint32_t pointer = get_cursor();
	pointer <<= 1;
	char* vga_cursor = (char*) VIDEO_MEMORY;
	vga_cursor += pointer;
	while	(*Message)
	{
		char c=*Message;
		switch(c)
		{
		 case '\n':
		 	pointer=(uint32_t)(vga_cursor-VIDEO_MEMORY);
		 	while(pointer%(2*ROW)){
			pointer++;
			if(pointer==2*ROW*COL)
			{pointer=0;break;}
			}	
		 	Message++;
		 	vga_cursor=(char *)(VIDEO_MEMORY+pointer);

    			break;
		case '\t':
			pointer=(uint32_t)(vga_cursor-VIDEO_MEMORY);
			pointer+=16;
			vga_cursor=(char*)(VIDEO_MEMORY+pointer);
			Message++;
	       		break;
		default:
			  *vga_cursor = *Message;
               		 Message++;
               		 vga_cursor ++;
               		 *vga_cursor = current_color;
               		 vga_cursor ++;
		}
	}
	vga_cursor -= VIDEO_MEMORY;
	pointer = (uint32_t)vga_cursor;
	pointer >>= 1;
	set_cursor(pointer);
}


void printhex(uint32_t input)
{
	char buffer[11];  //0x + 8 + null
	uint8_t pointer = 9;
	for(int i=0;i<8;i++)
	{
		int c = input & 0xF;
		if(c<10)
			c+=0x30;
		else
			c+=55;
		buffer[pointer] = (char)c;
		pointer --;
		input >>=4;
	}
	
//This is to make the thing smaller
	pointer = 2;
	while(buffer[pointer] == '0') pointer ++;
	pointer--;buffer[pointer] = 'x';
	pointer--;buffer[pointer] = '0';
	printf(buffer + pointer);
}

void putc (char x)
{
	uint32_t pointer = get_cursor();
	char* vga_cursor = (char*) VIDEO_MEMORY;
	vga_cursor += (pointer<<1);
	*vga_cursor = x;
	set_cursor(pointer+1);
}

void set_fg_color (enum vga_color c)
{
	current_color &= 0xf0;
	current_color |= c;
}

void set_bg_color (enum vga_color c)
{
	current_color &= 0x0f;
	current_color |= (c<<4);
}
