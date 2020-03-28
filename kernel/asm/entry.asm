;This file will be assembled to object format, i.e, elf later
[bits 32]

extern kmain
global _start

section .text.entry

_start:
	call kmain
	add esp,4*4
	cli
	hlt

