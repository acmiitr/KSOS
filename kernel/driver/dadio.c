/**  
 * @file dadio.c
 * @brief File containing functions that help display on VGA display
 * @see 
 */


#include <stdint.h>
#include "dadio.h"
#include "hardware.h"
#include "hal.h"

#define ROW 80/**< Number of Rows on the screen*/
#define COL 25/**< Number of Columns on the screen*/

extern char __VGA_text_memory[];/**< Stores the starting address of a display screen*/ 
static char current_color = 0xf8;/**< Current Color */
/** @brief A function to clear the output display 
 * @return Should not return
 * */
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
/** @brief A function that prints a given string on the VGA Display
*
* @param Message Input the given string
* @return  
*/
void monitor_puts(char* Message)
{
	uint32_t pointer = get_cursor();
	pointer <<= 1;
	char* vga_cursor = (char*) __VGA_text_memory;
	vga_cursor += pointer;
	while (*Message)
	{
		char c = *Message;
		switch (c)
		{
		 case '\n':
			pointer = (uint32_t)(vga_cursor - __VGA_text_memory);
			pointer -= (pointer % (2 * ROW));
			pointer += (2 * ROW);
			if (pointer == 2 * ROW * COL) //This is to control overflow
				pointer = 0;
			vga_cursor = (char *)(__VGA_text_memory + pointer);
			break;
		case '\t':
			pointer=(uint32_t)(vga_cursor-__VGA_text_memory);
			pointer+=16;
			vga_cursor=(char*)(__VGA_text_memory+pointer);
			break;
		default:
			*vga_cursor = *Message;
			vga_cursor++;
			*vga_cursor = current_color;
			vga_cursor++;
		}
		Message++;
	}
	//Resetting the pointer
	vga_cursor -= (uint32_t)__VGA_text_memory;
	pointer = (uint32_t)vga_cursor;
	pointer >>= 1;
	set_cursor(pointer);
}
/** @brief A function to print hexadecimal numbers
 * @param input	A 32 bit integer to print in hexadecimal 
 * @return Should not return
 * */
void printhex(uint32_t input)
{
	char buffer[11]  = "0x00000000";
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
/** @brief A function to print integer datatype
 * @param input	A 32 bit integer to print on the screen
 * @return Should not return
 * */
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
/** @brief A function to print a character on the screen
 * @param x	A character to print on the screen 
 * @return Should not return
 * */
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
			 pointer=pointer-(pointer%ROW)+ROW;
			 if(pointer==ROW*COL)
			 	pointer=0;
			 set_cursor(pointer);
		}
	else
	{
		vga_cursor += (pointer << 1);
		vga_cursor[1] = (char)current_color;
		*vga_cursor = x;
		set_cursor(pointer + 1);
	}
}
/** @brief A function to set the foreground color to specified value
 * @param c	A color name chosen from the predefined color 
 * @return Should not return
 * */
void set_fg_color(enum vga_color c)
{
	current_color &= 0xf0;
	current_color |= c;
}
/** @brief A function to set the background color to specified value
 * @param c	A color name chosen from the predefined color 
 * @return Should not return
 * */
void set_bg_color(enum vga_color c)
{
	current_color &= 0x0f;
	current_color |= (c << 4);
}
/** @brief A function that returns the current monitor character printed
 * 
 * @return Current monitor character
 * */
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
