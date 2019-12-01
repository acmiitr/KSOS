[org 0x7c00]
[bits 16]
mov bp,0x9000
mov sp,bp

call disk_read_16
mov si,Message1
call print_si_16
mov si,Message2
call print_si_16

jmp $


;
;functions
;

disk_read_16:  ;we can make it user input next ... al probably
	pusha
		mov dl,0x80;Drive number
		mov dh,0x0;This is actually head number/platter number
		mov ch,0x0 ;This is track number
		mov cl,2 ;This is sector number ... starts from 1
		mov ah,0x02 ;interrupt function
		mov al,1 ;Number of sectors to be read
		mov bx,0x7c0
		mov es,bx
		mov bx,512
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

	mov ah,0xf0  ;White on black
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


;
;Data
;
%include "GDT.asm"
Message1: db 'Welcome to your OS',0
times 510 - ($-$$) db 0
dw 0xaa55

;
;Next sector - sector 2
;
Message2: db 'You are outside',0

times 512 db 0
