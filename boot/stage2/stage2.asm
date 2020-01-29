;This is stage 2 of the Bootloader
;---------------------------------------------------------------------------------------
FinalKernel equ 0X100000
TempKernel equ 0X3000
[bits 16]
[org 0x7e00]
start:
mov [KernelSize],cx
mov bx,[KernelSize]

jmp boot_stage_2

KernelSize: dw 0
		
boot_stage_2:
mov si,Message16
call print_si_16

;in al, 0x92
;or al, 2
;out 0x92, al  ;This enables A20 on my acer PC



;---------------------------------------------------------------------------------------
mov ah,0x00  ;This is a cool thing... It waits for user input before going into 32 bit mode
int 0x16

;---------------------------------------------------------------------------------------
;This is the switch to PMode
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

;-------------Moving our kernel to it's rightful place---------------

KernelTransfer:
	cld
	xor ecx,ecx
	mov cx,[KernelSize]
	shl ecx,9  ;Double words
	mov esi,TempKernel
	mov edi,FinalKernel
	rep movsb

;---------------------------------------------------------------------------------------
;--------------Welcome screen for our bootloader----------------------------------------
;---------------------------------------------------------------------------------------
mov ah,0x37
mov ecx,2
flashing_screen:
push ecx
mov ecx, 0x00ffffff
timer:
loop timer
pop ecx

;mov ah,0x30
sub ah,0x07
call clrscr_32
add ah,0x07


;mov ah,0x37 ; Our printsi function is using this to do some crap
mov bx, (80*9)+15
call set_cursor_32
mov esi,Stars
call print_esi_32
mov bx, (80*11)+25
call set_cursor_32
mov esi,Welcome
call print_esi_32
mov bx, (80*13)+27
call set_cursor_32
mov esi,DaddyOsWelcome
call print_esi_32
mov bx, (80*15)+15
call set_cursor_32
mov esi,Stars
call print_esi_32
add ah,0x10 
loop flashing_screen
jmp 0x08:FinalKernel
;cli
;hlt

%include "boot/stage2/func16.asm"
%include "boot/stage2/func32.asm"
%include "boot/stage2/GDT.asm"
Message16: db 0xa,0xd,'Welcome to your OS - 16 bit, press any key to continue...',0
Welcome: db 'Rishi Ranjan is a Gay Boi',0
Stars: db '***********************************************',0
DaddyOsWelcome: db 'This is DADDY-OS',0

