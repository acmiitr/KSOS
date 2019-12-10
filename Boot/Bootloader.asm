;This is our bootloader assembly code
;I am trying to include a 2 stage bootloader to not worry about space issues in the future -- Maybe we might use a filesystem

[org 0x7c00]
KERNEL_MEM equ 0x1000
[bits 16]
mov bp,0x9000
mov sp,bp

call disk_read_16

mov si,Message1
call print_si_16

mov ah,0x00
int 0x16

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax,1
mov cr0,eax ;This makes it protected

jmp 0x08:pm_32_start ;This jumps to 32 bit segment
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

work_start:
mov al, 0x0f ;Refer to the index register table port mapping for CRT (low byte)
mov dx, 0x3d4 ; port number CRT index
out dx,al   ;Write 0x0f in port 0x3D4  --- note that the port registers are 1 byte in size
mov dx,0x3d5 ;port number CRT data
mov al,0    ;Trial run
out dx,al
jmp $
jmp KERNEL_MEM


;
;functions
;
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/functions.asm"
;
;Data
;
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/GDT.asm"
Message1: db 'Welcome to your OS - 16 bit, press any key to continue...',0
Message2: db 'Rishi is one gay boi',0
times 510 - ($-$$) db 0
dw 0xaa55
;Bootsector over
;kernel is present here in hard disk.... but will be loaded at 0x1000
