;This is our bootloader assembly code
;I am trying to include a 2 stage bootloader to not worry about space issues in the future -- Maybe we might use a filesystem

KERNEL_MEM equ 0x1000
[org 0x7c00]
[bits 16]

jmp boot_stage_1
;---------------------------------------------------------------------------------------

;This is for any filesystem information that we may input later
;This is for any filesystem information that we may input later
;This is for any filesystem information that we may input later
;This is for any filesystem information that we may input later

;---------------------------------------------------------------------------------------
boot_stage_1:
mov bp,0x9000
mov sp,bp

;---------------------------------------------------------------------------------------
mov cl,2 ;All these are the arguments that one passes to the disk_read function
mov al,9
xor bx,bx
mov es,bx
mov bx,boot_stage_2
call disk_read_16
;---------------------------------------------------------------------------------------

jmp boot_stage_2
;---------------------------------------------------------------------------------------
;Functions and magic bytes
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/disk_read.asm"
times 510 - ($-$$) db 0
dw 0xaa55
;---------------------------------------------------------------------------------------
;Bootsector over
;This is sector 2 of the hard disk
;---------------------------------------------------------------------------------------
boot_stage_2:
mov si,Message1
call print_si_16
;---------------------------------------------------------------------------------------
call get_cursor_16
call print_hex_bx

call print_si_16

call get_cursor_16
call print_hex_bx


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

;---------------------------------------------------------------------------------------
mov al, 0x0f ;Refer to the index register table port mapping for CRT (low byte)
mov dx, 0x3d4 ; port number CRT index
out dx,al   ;Write 0x0f in port 0x3D4  --- note that the port registers are 1 byte in size
mov dx,0x3d5 ;port number CRT data
mov al,0x70    ;Trial run
out dx,al

mov al, 0x0e ;Refer to the index register table port mapping for CRT (high byte)
mov dx, 0x3d4 ; port number CRT index
out dx,al   
mov dx,0x3d5 ;port number CRT data
mov al,0x03    ;Trial run
out dx,al

jmp $

%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/print.asm"
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/GDT.asm"

Message1: db 'Welcome to your OS - 16 bit, press any key to continue...',0
Message2: db 'Rishi is one gay boi',0