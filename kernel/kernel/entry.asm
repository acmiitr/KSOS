;This file will be assembled to object format, i.e, elf later
[bits 32]

extern kmain
global __start

section .text.entry

__start:
	sub esp,4 ;For the ABI
	jmp kmain
;We had a call followed by cli,hlt... The kernel takes it up from here
