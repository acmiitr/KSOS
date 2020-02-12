;This file will be assembled to object format, i.e, elf later
[bits 32]
;[org 0x100000]  ;Our code is located here

extern kmain
global _start

section .text.entry

_start:
	call kmain
	add esp,0x04;   I have a single argument... This is all making sure everything is chill :)

	cli
	hlt

;-----------Functions--------------
;%include "Kernel/print.asm"

;-----------Data------------------
;Welcome: db 'Welcome to Kernel Land at last :) ',0
;MovingToC: db 'Executing C guys....',0
;[extern print_esi]
;[extern set_cursor]
;[extern clrscr]
;	mov ah,0x00
;	call clrscr
;	mov ah,0x09
;	mov bx,0
;	call set_cursor
;	mov esi, Welcome
;	call print_esi
;	mov bx,80
;	call set_cursor
;	mov esi, MovingToC
;	call print_esi

