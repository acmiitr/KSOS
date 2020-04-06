%define KSTACK 0xFFC00000
%define KSTACK_PHY 0x90000

global refresh_stack ;A solution for switching stacks

section .text
refresh_stack:  ;NEVER STI HERE, WE HAVEN'T ENABLED INTERRUPTS YET
	mov eax,[esp] ;Return address
	mov esp,KSTACK
	mov ebp,KSTACK
	jmp eax


