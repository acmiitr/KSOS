;This is stage 2 of the Bootloader
;-------------------------------------------------------------------------------------
bits 16
org 0x7e00

FinalKernel equ 0x100000
TempKernel equ 0X30000
KernelVirt equ 0xC0000000
MemMap equ 0x1000   ;Get the mapping table here.....


start:
mov [KernelSize],cx
mov bx,[KernelSize]


EnableA20:
in al, 0x92
or al, 2
out 0x92, al  ;This enables A20 on my acer PC -- A potential source for errors :(


;--------Need to get memory map-------
GetMemoryMap:
  xor ebx,ebx
  mov es,bx
  mov edi,MemMap
.loop:
  mov eax,0xe820 ;mov bx,0 is implicit
  mov ecx,24
  mov edx,'PAMS'
  mov dword[es:edi + 20],0  ;Zeroing out 20-24
  int 0x15
  jc .error
  cmp eax,'PAMS'
  jne .error
  cmp ebx,0
  je .done
  add edi,24
  mov [.count],ebx
  jmp .loop

.error:
  mov si,.error_msg
  call print_si_16
  jmp .done
.error_msg: db 'Cannot read memory map, Aborting....',0
;.success_msg: db 'Read complete!, Count = ',0
.count: dd 0    ;Returns the number-1
.done:
;  mov si,.success_msg
;  call print_si_16
  mov bx,[.count]
  inc bx
  mov [.count],bx
;  call print_hex_bx


		
switch_to_pm:
  mov si,Message16
  call print_si_16
  mov ah,0x00  ;It waits for user input before going into 32 bit mode
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
	shl ecx,7  ;dwords
	mov esi,TempKernel
	mov edi,FinalKernel
	rep movsd


;---------------------------------------------------------------------------------------
;--------------Welcome screen for our bootloader----------------------------------------
;---------------------------------------------------------------------------------------
mov ah,0x37
mov ecx,4
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
mov bx, (80*11)+23
call set_cursor_32
mov esi,Welcome
call print_esi_32
mov bx, (80*13)+25
call set_cursor_32
mov esi,DaddyOsWelcome
call print_esi_32
mov bx, (80*15)+15
call set_cursor_32
mov esi,Stars
call print_esi_32
add ah,0x10 
loop flashing_screen
;----------------------Virtual memory!--------------------------

call EnablePaging

;------------------Prepare to jump into kernel-------------------

mov eax,[GetMemoryMap.count]
push eax
jmp 0x08:KernelVirt
;cli
;hlt

%include "boot/stage2/func16.asm"
%include "boot/stage2/func32.asm"
%include "boot/stage2/GDT.asm"
%include "boot/stage2/pagingsetup.asm"
Message16: db 0xa,0xd,'Welcome to Stage2!!',0xa,0xd,'Press any key to continue...',0
Welcome: db 'Everyone likes Flashiing Lights ;)',0
Stars: db '***********************************************',0
DaddyOsWelcome: db 'Welcome to ACM DOS',0
KernelSize: dw 0

