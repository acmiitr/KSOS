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
;        mov al,0x0A ;Enter 
;        int 0x10 
;        mov al,0x0D ;Carriage return 
;        int 0x10 
        popa 
        ret

