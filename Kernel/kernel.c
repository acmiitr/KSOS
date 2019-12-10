#define VIDEO_MEMORY 0xb8000
#define BLACK_ON_WHITE 0x0f

void printf(char* Message,char* VGA_CURSOR);
void main()
{
	static char* VGA_CURSOR = (char*) VIDEO_MEMORY;
	printf("G",VGA_CURSOR);
}

void printf(char* Message,char* VGA_CURSOR)
{
	while(*Message)
	{
		*VGA_CURSOR = *Message;
		Message++;
		VGA_CURSOR += 2;
	}
}
