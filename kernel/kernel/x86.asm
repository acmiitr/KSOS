KSTACK equ 0xFFC00000
USTACK equ 0xC0000000
KSTACK_PHY equ 0x90000
USTACK_PHY equ 0x40000

global refresh_stack ;A solution for switching stacks

section .text
refresh_stack:  ;Asshole, NEVER STI HERE, WE HAVEN'T ENABLED INTERRUPTS YET
	mov eax,[esp] ;Return address
	mov esp,KSTACK
	mov ebp,KSTACK
	jmp eax

section .user
global switch_to_user
switch_to_user:
	cli
	mov ecx,[esp]   ;Return address

    	mov ax, 0x23	;user mode data selector is 0x20 (GDT entry 3). Also sets RPL to 3
    	mov ds, ax
    	mov es, ax
    	mov fs, ax
    	mov gs, ax

    	push 0x23	; SS, notice it uses same selector as above
    	push USTACK	; ESP
    	pushfd		; EFLAGS
    	push 0x1b	; CS, user mode code selector is 0x18. With RPL 3 this is 0x1b
    	push ecx
   	iret
