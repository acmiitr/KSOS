print_si:
	pusha
	mov ah,0x0e ;This is the higher byte of the ax register
	_loop:
	;	mov al,[si]
	;	inc si
		lodsb ;Performs the function of the previous two shits
		cmp al,0
		je _end
		int 0x10
		jmp _loop
	_end:
	mov al,0x0A ;Enter
	int 0x10
	mov al,0x0D ;Carriage return
	int 0x10
	popa
	ret
	
printHex_bx:
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
_start:
	cmp cx,4
	je _finish
	mov ax,bx
	and ax,0xf000
	shr ax,12
	cmp ax,9
	jg _letter
	add ax,0x30  ;ascii encoding for numbers 
	jmp _conv_end
	_letter:
	add ax,55  ;ascii encoding for numbers 

	_conv_end:
		mov ah,0x0e  ;Printing routine
		int 0x10

	shl bx,4
	inc cx
	jmp _start
_finish:
popa
ret
	

disk_read: 
        pusha 
        mov ah,0x02 ;Read thing 
         
        mov al,1 ;This is the number of sectors to be read 
        mov ch,0 ;Cylinder no 
        mov dh,0 ;track no 
        mov cl,2 ;sector no -- starts from 1!!! 
         
        mov bx,0x7c0;We're using ES:BX addressing to get the next sector'ish' from bootsector in memory 
        mov es,bx 
        mov bx, 512 
        int 0x13 ;BIOS interrupt to read disk 
 
        jc read_error 
        popa 
        ret 
 
        read_error: ;This is an error method that is to be JUMPED to 
        mov si,Error 
        call print_si 
        jmp $
	
	Error: db 'Error reading disk',0

[bits 32]

print_pm_esi:
	pusha

	mov ah,0xf0
	mov ebx,0xb8000

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

