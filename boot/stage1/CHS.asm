init_CHS:  ;Initializes HEADS,etc. 
pusha
	mov dl,0x80
	xor bx,bx
	mov di,bx
	mov ah , 0x08
	int 0x13  ;Reads disk geometry
	inc dh
	mov [HEADS],dh
	mov bl,cl
	and bl,0x3f
	mov [SPT],bl
	mov bl,ch
	mov ch,0
	shr cx,6
	mov bh,cl
	inc bx
	mov [CYLINDER],bx
popa
ret

HEADS: db 0	;We need 8 bits (dh)
SPT:db 0	;We need 6 bits 
CYLINDER: dw 0	;We need 10 bits  ;At the end we do not even need this

LBA_to_CHS: ;Enter the linear block address in ax, get c,d in return
push ax
push bx
	xor bx,bx
	
	xor dx,dx
	mov bl,[SPT]
	div bx   ;ax gets divided
	inc dx
	mov cl,dl
	and cl,0x3f ;Track number is set :)

	xor dx,dx
	mov bl,[HEADS]
	div bx
	shl dx,8 ;dx is shifted by 8 ( dx -> dh )
	mov ch,al   ;Not exactly right :((( But should do
pop bx
pop ax
ret

