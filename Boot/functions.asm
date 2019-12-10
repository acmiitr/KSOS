[bits 16]
disk_read_16:  ;THis si a function that reads the next 9 sectors 1-10 and loads it at 0x1000
	pusha
		mov dl,0x80;Drive number
		mov dh,0x0;This is actually head number/platter number
		mov ch,0x0 ;This is track number
		mov cl,2 ;This is sector number ... starts from 1
		mov ah,0x02 ;interrupt function
		mov al,9 ;Number of sectors to be read
		mov bx,0x100
		mov es,bx
		xor bx,bx   ;mov bx,0
		int 0x13
	popa
	ret
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
[bits 32]  ;Need to understand the impact of this!!!
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


