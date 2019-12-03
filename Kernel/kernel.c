#define VIDEO_MEMORY 0xb8000
#define BLACK_ON_WHITE 0x0f
void printf(char *);
void main()
{
	printf("Chordia is a gay boiiiii");
}

void printf(char* Message)
{
	char* ptr = (char*) VIDEO_MEMORY;
	while(*Message)
	{
		*ptr = *Message;
		Message++;
		ptr += 2;
	}
}
