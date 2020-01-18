;This file will be assembled to object format, i.e, elf
[bits 32]
[org 0x100000]  ;Our code is located here

;[extern main]
;call main
mov ah,0x00
call clrscr_32
mov ah,0x09
mov bx,0
call set_cursor_32
mov esi, Welcome
call print_esi_32
mov bx,80
call set_cursor_32
mov esi, MovingToC
call print_esi_32

cli
hlt

;-----------Functions--------------
%include "Kernel/func32.asm"

;-----------Data------------------
Welcome: db 'Welcome to Kernel Land at last :) ',0
MovingToC: db 'Executing C code guys....',0
