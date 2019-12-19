[bits 32]  
print_esi_32:   ;--------------ah = attribute
	pusha
	call get_cursor_32
;	mov ah,0x0f  ;Background on foreground --------Keep this as a user input
	shl ebx,1   ;Multiply by 2
	add ebx,0xb8000 ;Starting address

	_print_pm_loop:
		mov al,[esi]
		mov [ebx],ax
		add esi,1
		add ebx,2
		cmp al,0
		je _print_pm_end
	jmp _print_pm_loop
	_print_pm_end:
	sub ebx,0xb8000
	shr ebx,1   ;Divide by 2
	dec ebx
	call set_cursor_32

	popa
	ret

set_cursor_32:   ;bx is the location
	push dx
	push ax
	mov al, 0x0f ;Refer to the index register table port mapping for CRT (low byte)
	mov dx, 0x3d4 ; port number CRT index
	out dx,al   ;Write 0x0f in port 0x3D4  --- note that the port registers are 1 byte in size
	mov dx,0x3d5 ;port number CRT data
	mov al,bl 
	out dx,al

	mov al, 0x0e ;Refer to the index register table port mapping for CRT (high byte)
	mov dx, 0x3d4 ; port number CRT index
	out dx,al
	mov dx,0x3d5 ;port number CRT data
	mov al,bh
	out dx,al

	pop ax
	pop dx
	ret

get_cursor_32:
	;pusha can't use this becuase we expect a return vlaue in bx
	push dx
	push ax
	mov al, 0x0f ;Refer to the index register table port mapping for CRT (low byte)
	mov dx, 0x3d4 ; port number CRT index
	out dx,al   ;Write 0x0f in port 0x3D4  --- note that the port registers are 1 byte in size
	mov dx,0x3d5 ;port number CRT data
	in al,dx   ;Store the low byte in al -- Hardware forced to use al
	mov bl,al

	mov al, 0x0e ;Refer to the index register table port mapping for CRT (high byte)
	mov dx, 0x3d4 ; port number CRT index
	out dx,al   ;Write 0x0f in port 0x3D4  --- note that the port registers are 1 byte in size
	mov dx,0x3d5 ;port number CRT data
	in al,dx   ;Store the high byte in al -- Hardware forced to use al
	mov bh,al   ;Store the high byte in bh
	
	pop ax
	pop dx
	ret

clrscr_32:
	pusha
	mov ebx,0xb8000
;	mov ah,0x30 User defined
	mov al,' '
	mov cx,2000 ;loop initialization
	clrscr_loop:
		mov word[ebx],ax
		add ebx,2
	loop clrscr_loop
	mov bx,0
	call set_cursor_32
	popa
	ret
