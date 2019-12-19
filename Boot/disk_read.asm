[bits 16]
disk_read_16:  ;bx is an argument, es is argument ,cl is also an argument, al is also an argument
	pusha
		mov dl,0x80;Drive number
		mov dh,0x0;This is actually head number/platter number
;		mov ch,0x0 ;This is track number
		mov ah,0x02 ;interrupt function
		int 0x13
	popa
	ret
