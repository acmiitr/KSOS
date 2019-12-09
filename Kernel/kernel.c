#define VIDEO_MEMORY 0xb8000
#define BLACK_ON_WHITE 0x0f
void printf(char* Message,char* cursor)
{
	while(*Message)
	{
		*cursor = *Message;
		Message++;
		cursor += 2;
	}
}
void clrscr()
{
	for(int i=0;i<80*24;i++) printf(" ",VIDEO_MEMORY + 2*i);
}
void main()
{
	clrscr();
	char* VGA_CURSOR = (char*) VIDEO_MEMORY;
	printf("G",VGA_CURSOR);
}


