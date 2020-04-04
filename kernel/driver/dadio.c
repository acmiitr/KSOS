#include <stdint.h>
#include "dadio.h"
#include "keyboard.h"
#include "hal.h"

#define ROW 80
#define COL 25

extern char __VGA_text_memory[];
static char current_color = 0xf8;

void clear()
{
	char* cursor=(char*)__VGA_text_memory;
	*cursor=' ';
	cursor++;*cursor=current_color;cursor++;
	while((uint32_t)(cursor-__VGA_text_memory)<2*ROW*COL)
		{
			*cursor=' ';cursor++;
			*cursor=current_color;cursor++;
		}
	set_cursor(0);
}

void monitor_puts(char* Message)
{
	while (*Message)
	{
		char c = *Message;
		putc(c);
		Message++;
	}
}

void printhex(uint32_t input)
{
	char buffer[11]; //0x + 8 + null
	uint8_t pointer = 9;
	for (int i = 0; i < 8; i++)
	{
		int c = input & 0xF;
		if (c < 10)
			c += 0x30;
		else
			c += 55;
		buffer[pointer] = (char)c;
		pointer--;
		input >>= 4;
	}

	//This is to make the thing smaller
	pointer = 2;
	while((buffer[pointer] == '0')&& (pointer < 9)) pointer ++;
	pointer--;buffer[pointer] = 'x';
	pointer--;buffer[pointer] = '0';
	monitor_puts(buffer + pointer);
}

void printint(uint32_t input)
{
	char buffer[11] = "0000000000";
	for (int i = 0; i < 10; i++)
	{
		int temp = input % 10;
		buffer[10 - i] = (char)(temp + 0x30);
		input /= 10;
	}
	monitor_puts(buffer);
}

void putc(char x)
{
	uint32_t pointer = get_cursor();
	char* vga_cursor = __VGA_text_memory;
	if(x == '\b')
	{
		if (pointer)
		{
			pointer--;
			vga_cursor += (pointer << 1);
			*vga_cursor = 0;
			vga_cursor[1] = vga_cursor[3];
			set_cursor(pointer);
		}
	}
	else if(x == '\n')
	{
		if(!(pointer % ROW))
			pointer++;
	 	while(pointer % ROW)
		{	
			pointer++;
			if(pointer == ROW*COL)
			{
				pointer = 0;
				break;
			}
		}	
		vga_cursor += pointer<<1;
		set_cursor(pointer+1);
	}
	else
	{
		vga_cursor += (pointer << 1);
		vga_cursor[1] = (char)current_color;
		*vga_cursor = x;
		set_cursor(pointer + 1);
	}
}

void set_fg_color(enum vga_color c)
{
	current_color &= 0xf0;
	current_color |= c;
}

void set_bg_color(enum vga_color c)
{
	current_color &= 0x0f;
	current_color |= (c << 4);
}

char get_monitor_char()
{
	while (1)
	{
		wait_for_keyboard();
		char x = get_latest_char();
		uint8_t scanned=get_latest_scan_code();
		if(scanned==0x4b)
			{if(x=='4')
			return x;else
			return 17;}
		else if(scanned==0x4d){if(x=='6')
			return x;else return 18;}
		if (x)
			return (x);
	}
}
