[bits 32] 
[global set_cursor]
[global get_cursor]

set_cursor:   ;bx is the location

	mov ecx,[esp+0x4]
	mov al, 0x0f ;Refer to the index register table port mapping for CRT (low byte)
	mov dx, 0x3d4 ; port number CRT index
	out dx,al   ;Write 0x0f in port 0x3D4  --- note that the port registers are 1 byte in size
	mov dx,0x3d5 ;port number CRT data
	mov al,cl 
	out dx,al

	mov al, 0x0e ;Refer to the index register table port mapping for CRT (high byte)
	mov dx, 0x3d4 ; port number CRT index
	out dx,al
	mov dx,0x3d5 ;port number CRT data
	mov al,ch
	out dx,al

	ret

get_cursor:
;	push dx

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

	movzx eax,bx
	
	
;	pop dx
	ret

