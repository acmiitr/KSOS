;This is sector 2 of the hard disk
;---------------------------------------------------------------------------------------
boot_stage_2:
mov si,Message16
call print_si_16
;---------------------------------------------------------------------------------------
mov ah,0x00  ;This is a cool thing... It waits for user input before going into 32 bit mode
int 0x16
;---------------------------------------------------------------------------------------
cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax,1
mov cr0,eax ;This makes it protected
jmp 0x08:pm_32_start ;This jumps to 32 bit segment looking at the descriptor table values and all
;---------------------------------------------------------------------------------------

[bits 32] ;why 32 here???? This is the answer to life love and everything in between
pm_32_start:
mov ebp,0x90000
mov esp,ebp
mov ax,0x10
mov ds,ax
mov ss,ax
mov es,ax
mov fs,ax
mov gs,ax


;We need to enable address line A20 here  - We will use keyboard controller to do this
mov al,0xdd
;out 0x64,al

;---------------------------------------------------------------------------------------
;--------------Welcome screen for our bootloader----------------------------------------
;---------------------------------------------------------------------------------------

mov ah,0x30
call clrscr_32


mov ah,0x37 ; Our printsi function is using this to do some crap
mov bx, (80*9)+15
call set_cursor_32
mov si,Stars
call print_esi_32
mov bx, (80*11)+25
call set_cursor_32
mov si,Welcome
call print_esi_32
mov bx, (80*13)+27
call set_cursor_32
mov si,DaddyOsWelcome
call print_esi_32
mov bx, (80*15)+15
call set_cursor_32
mov si,Stars
call print_esi_32

cli
hlt

%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/func16.asm"
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/func32.asm"
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/GDT.asm"

Message16: db 'Welcome to your OS - 16 bit, press any key to continue...',0
Welcome: db 'Rishi is one gay boi',0
Stars: db '***********************************************',0
DaddyOsWelcome: db 'This is DADDY-OS',0

