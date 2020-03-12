;This file will be assembled to object format, i.e, elf later
[bits 32]

extern kmain
global _start

section .text.entry

_start:
	call kmain
	add esp,0x04;   I have a single argument... This is all making sure everything is chill :)

intloop:
	hlt
	jmp intloop

