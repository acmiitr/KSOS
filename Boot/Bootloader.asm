[org 0x7c00]
[bits 16]
mov bp, 0x9000
mov sp,bp

mov si,Message ;Welcome message
call print_si

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax,1
mov cr0,eax

jmp 0x08:pipeline_flush ;This is just to test out my understanding
pipeline_flush:
[bits 32]

mov ebp, 0x90000
mov esp,ebp

mov ax, 0x10
mov ds,ax
mov es,ax
mov fs,ax
mov gs,ax
mov ss,ax

mov esi,Message
call print_pm_esi


jmp $


;Functions


%include "functions.asm"
%include "GDT.asm"



;Data

Message:
db 'Welcome to your OS, Rishi is gay',0



times 510 -( $ - $$ ) db 0
dw 0xaa55

