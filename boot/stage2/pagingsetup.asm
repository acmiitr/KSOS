bits 32

%define	PAGE_DIR	0x9C000
%define	PAGE_TABLE_0h	0x9D000
%define	PAGE_TABLE_300h	0x9E000

%define	PAGE_TABLE_ENTRIES	1024
%define	PRIV			3


EnablePaging:
	pusha
	;This makes an identity map

MakeTable0h:

	mov eax, 0x0 | PRIV				
	mov ebx, PAGE_TABLE_0h
	mov ecx, PAGE_TABLE_ENTRIES	
.loop:
	mov dword [ebx], eax
	add ebx, 4		
	add eax, 4096
	loop .loop		

MakeTable300h:
	mov eax, 0x100000 | PRIV
	mov ebx, PAGE_TABLE_300h
	mov ecx, PAGE_TABLE_ENTRIES	
.loop:
	mov dword [ebx], eax
	add eax, 4096
	add ebx, 4	
	loop .loop

MakePageDir:

	mov eax, PAGE_TABLE_0h | PRIV			; 1st table is directory entry 0
	mov dword [PAGE_DIR], eax
	mov eax, PAGE_TABLE_300h | PRIV			; 768th entry in directory table
	mov dword [PAGE_DIR+(0x300 * 4)], eax

InstallAndSwitch:

	mov eax, PAGE_DIR
	mov cr3, eax

	mov		eax, cr0
	or		eax, 0x80000000
	mov		cr0, eax

	popa
	ret
