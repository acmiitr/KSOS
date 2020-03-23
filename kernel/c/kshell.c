//This is a simple kernel level shell that we're gonna be writing, for the most basic UI.
//This is meant to be used at level 0
#include"dadio.h"
#include"stdbool.h"
#include"timer.h"

#define MAX_COMMAND_SIZE 50
#define MAX_TOKEN_SIZE 25 
#define MAX_NAME_SIZE 20 

//Helper functions
static void extract_token(int token_no);  //Takes token number n from command and puts it into buffer
static void parse_command();
static void flush_token_buffer();
static void flush_command_buffer();
static bool string_compare(char* str1, char* str2);
static void string_copy(char* strd,char* strs);

//Shell functions
static void command_help();
static void command_fresh();
static void command_timer();
static void command_picture();
static void command_name();

//Global variables 
static char _cmd_buffer[MAX_COMMAND_SIZE];
static char _tkn_buffer[MAX_TOKEN_SIZE];
static char _shell_name[MAX_NAME_SIZE] = "shell";

void kshell()
{
	command_fresh();
	//This loop gets the commands from us
	while(1)
	{
		printf("\n"); printf(_shell_name); printf(" >");
		flush_command_buffer();
		for(int i=0;i<MAX_COMMAND_SIZE;i++)
		{
			char input = get_monitor_char();
			if(input == '\b')
			{
				if(i>0){putc('\b');i--; _cmd_buffer[i]=0;}
				i--;
				continue;
			}
			if(input == '\n')
				{parse_command(); break;}
			_cmd_buffer[i] = input;
		       	putc(input);
		}
	}
}

static void parse_command()
{
	extract_token(0);
	if(string_compare(_tkn_buffer,"help")) {command_help();return;}
	if(string_compare(_tkn_buffer,"fresh")){command_fresh();return;}
	if(string_compare(_tkn_buffer,"timer")){command_timer();return;}
	if(string_compare(_tkn_buffer,"picture")){command_picture();return;}
	if(string_compare(_tkn_buffer,"name")){command_name();return;}

	printf(" - Command not found: ");
	printf(_tkn_buffer);
}

static void extract_token(int token_no)  //Takes token number n from command and puts it into buffer
{
	flush_token_buffer();
	char* pointer = _cmd_buffer;
	while( *pointer == ' ')	pointer++;

	for (int i=0;i<token_no;i++)
	{
		while( *pointer != ' ')	{if(*pointer == 0 ) return; pointer++;}
		while( *pointer == ' ')	pointer++;
	}

	for (int i =0;i<MAX_TOKEN_SIZE;i++)
	{
		if(*pointer == 0 || *pointer ==' ') return;
		_tkn_buffer[i] = *(pointer++);
	}

}

static void flush_command_buffer()
{
	for(int i=0;i<MAX_COMMAND_SIZE;i++)
	{ 	
		if (_cmd_buffer[i] == 0) break;
		_cmd_buffer[i] = 0;
	}
}
static void flush_token_buffer()
{
	for(int i=0;i<MAX_TOKEN_SIZE;i++)
	{
		if (_tkn_buffer[i] == 0) break;
		_tkn_buffer[i] = 0;
	}
}

static void command_help()
{
	printf("\nList of commands (use `command` help for usage):");
	printf("\nhelp");
	printf(" fresh");
	printf(" timer");
	printf(" picture");
	printf(" name\n");
}

static void command_fresh()
{
	static int color[2] = {LIGHT_BLUE,BLACK};

	for(int i =0;i<2;i++)
	{
		extract_token(i+1);
		if(string_compare(_tkn_buffer,"black")) color[i] = BLACK;
		if(string_compare(_tkn_buffer,"blue")) color[i] = BLUE;
		if(string_compare(_tkn_buffer,"green")) color[i] = GREEN;
		if(string_compare(_tkn_buffer,"cyan")) color[i] = CYAN;
		if(string_compare(_tkn_buffer,"red")) color[i] = RED;
		if(string_compare(_tkn_buffer,"magenta")) color[i] = MAGENTA;
		if(string_compare(_tkn_buffer,"brown")) color[i] = BROWN;
		if(string_compare(_tkn_buffer,"light_grey")) color[i] = LIGHT_GREY;
		if(string_compare(_tkn_buffer,"dark_grey")) color[i] = DARK_GREY;
		if(string_compare(_tkn_buffer,"light_blue")) color[i] = LIGHT_BLUE;
		if(string_compare(_tkn_buffer,"light_green")) color[i] = LIGHT_GREEN;
		if(string_compare(_tkn_buffer,"light_cyan")) color[i] = LIGHT_CYAN;
		if(string_compare(_tkn_buffer,"light_red")) color[i] = LIGHT_RED;
		if(string_compare(_tkn_buffer,"light_magenta")) color[i] = LIGHT_MAGENTA;
		if(string_compare(_tkn_buffer,"light_brown")) color[i] = LIGHT_BROWN;
		if(string_compare(_tkn_buffer,"white")) color[i] = WHITE;
		if(string_compare(_tkn_buffer,"help"))
		{
			printf("\tUsage: fresh c1 c2\ncolors:");
			printf("  black");
			printf("  blue");
			printf("  green");
			printf("  cyan");
			printf("  red");
			printf("  magenta");
			printf("  brown");
			printf("  light_grey");
			printf("  dark_grey");
			printf("  light_blue");
			printf("  light_green");
			printf("  light_cyan");
			printf("  light_red");
			printf("  light_magenta");
			printf("  light_brown");
			printf("  white");
			return;
		}
	}

	set_fg_color(color[0]);
	set_bg_color(color[1]);
	clear(); // This is the background color

	set_fg_color(color[1]);
	set_bg_color(color[0]);
	for(int i=0;i<80;i++) putc(' ');
	set_cursor(20);
	printf("ACM DOS KERNEL SHELL 0.01 (help displays commands)");

	set_fg_color(color[0]);
	set_bg_color(color[1]);
}

static void command_timer()
{
	extract_token(1);
	if(string_compare(_tkn_buffer,"fast")) set_timer(0xff);
	if(string_compare(_tkn_buffer,"medium")) set_timer(0xfff);
	if(string_compare(_tkn_buffer,"slow")) set_timer(0xffff);
	if(string_compare(_tkn_buffer,"help")) printf("\tUsage: timer fast/medium/slow");
}

static void command_picture()
{
	printf("\nx;;;.',,,,,,,,;,;ckO000000000OxddddxxxkkkkkkkkOOOOOOO00OOOO00OOOkx");
	printf("\nx;;'.,,,,,,,,,,,,',oOOOOO0000000OOO00OOOOOOOOOOOOO0OOO00OOOOOOxl::");
	printf("\nx;,.',,,,,,,,,,,,,,,;ldxO0000000000000OOO0000000000000OOOOOkoc;;,,");
	printf("\nx;'.,,,''','''''''',''lkO0000000000000OOO00OOOO0000000Okdoc;;;;;,,");
	printf("\nx,.''''''''','.....'':kOOOOOOO00000000OO00OOOOOkkOOOO0OOkc,;;;;;,,");
	printf("\nx..'''''''',,'....'',dOOOOddc,oOO0000OOOOOOOOddl':xOOOOOOkc,;;;;;;");
	printf("\no.'''......'',,,,;;':kOOOkc,..;kOOOOOOOOOOOOOo,'.'dOOOOOOOx;;:cccc");
	printf("\no.''.........,,,;;,'dOOOO0OdoldOOOkxxkOOOOOOOOxoldOOOOOOOOOl;ccccc");
	printf("\nd,'..........,,;;;',loxkO00000OOOOxl:lkOOOOOOOOOOOOkxxxkOOOx:ccccc");
	printf("\nx,,'''',,,,,;;;:;,.,::::dO0000000OOOOOOOOOOOOOOOOOdc::ccdOOkc:cccc");
	printf("\nx,,,,,,,,,,;:::;;..;ccc:dO000000OkolclodxkOOOOOOOkl:ccc:ckOOx;;:::");
	printf("\nx,,,,,,,,,,,,,,,,.;c::cokO000000Ol':odddlokOO000OOdccccldOOOOo;:::");
	printf("\nx,,,,,,,,,,,,,,,''ckkkOO00000000Od:ldxxdookOO0000OOOkkkkOOOOOk::cc");
	printf("\nx;;;;,,,;;;;;;;;;;,lOO00000000000OkolllllxOOOOOOOOOOOOOOOOOOOOo;::");
	printf("\nd,,;::cccccccccccc:;oOOO0000OOOO00OOOOOOOOOOOOOOOOOOOOOOOOOOOOx;;;");
	printf("\noo'',,,;;:::::::;,,,;dkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkx:,,");
}

static void command_name()
{
	extract_token(1);
	if(string_compare(_tkn_buffer,"help"))
		{printf("\tUsage: name string"); return;}
	if(string_compare(_tkn_buffer,"masih"))
		string_copy(_tkn_buffer,"asshole");
			
	for(int i=0;i<MAX_NAME_SIZE;i++) _shell_name[i] = 0; //Flush
	string_copy(_shell_name,_tkn_buffer);
}

static void string_copy(char* strd,char* strs)
{
	for(int i=0;strs[i];i++)
	{
		strd[i]=strs[i];
	}
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


