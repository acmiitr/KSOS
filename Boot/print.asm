[bits 16]
print_si_16:
        pusha 
        mov ah,0x0e ;This is the higher byte of the ax register 
        print_16_loop: 
        ;       mov al,[si] 
        ;       inc si 
                lodsb ;Performs the function of the previous two shits 
                cmp al,0 
                je print_16_end 
                int 0x10 
                jmp print_16_loop 
        print_16_end: 
        mov al,0x0A ;Enter 
        int 0x10 
        mov al,0x0D ;Carriage return 
        int 0x10 
        popa 
        ret

[bits 16]
print_hex_bx:
	pusha
	mov ah,0x0e
	mov al,10
	int 0x10
	mov al,13
	int 0x10
	mov al,'0'
	int 0x10
	mov al,'x'
	int 0x10
	mov cx,0
	print_hex_start:
		cmp cx,4
		je _finish
		mov ax,bx
		and ax,0xf000
		shr ax,12
		cmp ax,9
		jg print_hex_letter
		add ax,0x30  ;ascii encoding for numbers 
		jmp print_hex_conv_end
		print_hex_letter:
		add ax,55  ;ascii encoding for numbers 

		print_hex_conv_end:
			mov ah,0x0e  ;Printing routine
			int 0x10

		shl bx,4
		inc cx
		jmp print_hex_start
	_finish:
	popa
	ret


[bits 16]
get_cursor_16:
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

[bits 32]  
print_esi_32:
	pusha

	mov ah,0x0f  ;Background on foreground
	mov ebx,0xb8000 ;Starting address

	_print_pm_loop:
		mov al,[esi]
		mov [ebx],ax
		add esi,1
		add ebx,2
		cmp al,0
		je _print_pm_end
	jmp _print_pm_loop
	_print_pm_end:

	popa
	ret
