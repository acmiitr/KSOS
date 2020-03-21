//This is a simple kernel level shell that we're gonna be writing, for the most basic UI.
//This is meant to be used at level 0
#include"dadio.h"
#include"stdbool.h"

#define MAX_COMMAND_SIZE 50

//Helper functions
static void flush_buffer();
static void parse_command();
static void command_help();

//Global variables 
static char cmd_buffer[MAX_COMMAND_SIZE];
static bool string_compare(char* str1, char* str2);

void kshell()
{
	set_fg_color(BLUE);
	set_bg_color(WHITE);
	clear(); // This is the background color

	set_fg_color(WHITE);
	set_bg_color(BLUE);
	for(int i=0;i<80;i++) putc(' ');
	set_cursor(20);
	printf("ACM DOS KERNEL SHELL 0.01");

	set_fg_color(BLUE);
	set_bg_color(WHITE);
	//This loop gets the commands from us
	while(1)
	{
		printf("\nshell >");
		flush_buffer();
		for(int i=0;i<MAX_COMMAND_SIZE;i++)
		{
			char input = get_monitor_char();
			if(input == '\b')
			{
				if(i>0){putc('\b');i--; cmd_buffer[i]=0;}
				i--;
				continue;
			}
			if(input == '\n')
				{parse_command(); break;}
			cmd_buffer[i] = input;
		       	putc(input);
		}
	}
}

static void parse_command()
{
	char* pointer = cmd_buffer;
	while( *pointer == ' ')	pointer++;
	if(string_compare(pointer,"help")) command_help();

	else
	{
		printf(" - Command not found: ");
		printf(cmd_buffer);
	}
}
static void flush_buffer()
{
	for(int i=0;i<MAX_COMMAND_SIZE;i++)
		cmd_buffer[i] = 0;
}
static bool string_compare(char* str1, char* str2)
{
	int i = 0;
	while (str1[i])
	{
		if(str1[i] != str2[i]) return false;
		i++;
	}
	if(str2[i]) return false;
	return true;
}

static void command_help()
{
	printf("\nHelp yourself bitch");
}
