[bits 16]
BootDiskNumber: db 0
disk_read_16:  ;bx is an argument, es is argument ,cl is also an argument, al is also an argument
	pusha
		mov dl,[BootDiskNumber]
		mov ah,0x02 ;interrupt function
		int 0x13
	popa
	ret
