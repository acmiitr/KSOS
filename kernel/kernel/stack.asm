STACK equ 0xFFC00000
STACK_PHY equ 0x90000

global refresh_stack ;A solution for switching stacks

refresh_stack:
	mov ebx,[esp] ;Return address
	mov esp,STACK
	mov ebp,STACK
	jmp ebx

