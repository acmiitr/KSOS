[org 0x7c00]
[bits 16]
mov bp,0x9000
mov sp,bp

call disk_read_16

mov si,Message1
call print_si_16

cli
lgdt [gdt_descriptor]

mov eax, cr0
or eax,1
mov cr0,eax ;This makes it protected

jmp 0x08:pm_32_start ;This jumps to 32 bit segment
[bits 32] ;why 32 here???? This is the answer to life love and everything in between
pm_32_start:
jmp kernel


;
;functions
;

[bits 16]
disk_read_16:  ;we can make it user input next ... al probably
	pusha
		mov dl,0x80;Drive number
		mov dh,0x0;This is actually head number/platter number
		mov ch,0x0 ;This is track number
		mov cl,2 ;This is sector number ... starts from 1
		mov ah,0x02 ;interrupt function
		mov al,9 ;Number of sectors to be read
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


;
;Data
;
%include "GDT.asm"
Message1: db 'Welcome to your OS',0
Message2: db 'Rishi is one gay boi',0
times 510 - ($-$$) db 0
dw 0xaa55
;Bootsector over
kernel:
mov esi,Message2
call print_esi_32
jmp $
