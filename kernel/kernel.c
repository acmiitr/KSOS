#include<stdint.h> 
#define COLOR 0x39
#define VIDEO_MEMORY 0xb8000
#define row 80
#define col 25
uint32_t get_cursor();
void set_cursor(uint32_t);
void printf(char* Message);
void clear();
void kmain()
{
	printf("This is working, so I'm\n \t losing my shit :)");
	for(int i=0;i<1000000000;i++);
	clear();
	return;
}
void clear()
{
	char* cursor=(char*)VIDEO_MEMORY;
	*cursor=' ';
	cursor++;*cursor=COLOR;cursor++;
	while((uint32_t)(cursor-VIDEO_MEMORY)<2*row*col)
		{
			*cursor=' ';cursor++;
			*cursor=COLOR;cursor++;
		}
	set_cursor(0);
}

void printf(char* Message)
{
	uint32_t pointer = get_cursor();
	pointer <<= 1;
	char* VGA_CURSOR = (char*) VIDEO_MEMORY;
	VGA_CURSOR += pointer;
	while	(*Message)
	{
		char c=*Message;
		switch(c)
		{
		 case '\n':
		 	pointer=(uint32_t)(VGA_CURSOR-VIDEO_MEMORY);
		 	while(pointer%(2*row)){
			pointer++;
			if(pointer==2*row*col)
			{pointer=0;break;}
			}	
		 	Message++;
		 	VGA_CURSOR=(char *)(VIDEO_MEMORY+pointer);

    			break;
		case '\t':
			pointer=(uint32_t)(VGA_CURSOR-VIDEO_MEMORY);
			pointer+=16;
			VGA_CURSOR=(char*)(VIDEO_MEMORY+pointer);
			Message++;
	       		break;
		default:
			  *VGA_CURSOR = *Message;
               		 Message++;
               		 VGA_CURSOR ++;
               		 *VGA_CURSOR = COLOR;
               		 VGA_CURSOR ++;
		}
	}
	VGA_CURSOR -= VIDEO_MEMORY;
	pointer = (uint32_t)VGA_CURSOR;
	pointer >>= 1;
	set_cursor(pointer);
}
