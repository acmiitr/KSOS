;This is our bootloader assembly code

Stage2Sector equ 0x7e0
TempKernelSector equ 0x3000
RootLoad equ 0x1000
FATLoad equ 0x6000
[org 0x7c00]
[bits 16]

jmp near  boot_stage_1
;---------------------------------------------------------------------------------------
;times (0x3d-0x02) db 0
bpbOEM			db "DummyBPB"
bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 	DB 2
bpbRootEntries: 	DW 512
bpbTotalSectors: 	DW 2880
bpbMedia: 		DB 0xf0  
bpbSectorsPerFAT: 	DW 6     ;We need all this
bpbSectorsPerTrack: 	DW 63
bpbHeadsPerCylinder: 	DW 16
bpbHiddenSectors: 	DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 		DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3
bsVolumeLabel: 	        DB "DUMMY DISK "
bsFileSystem: 	        DB "FAT12   "
;---------------------------------------------------------------------------------------
boot_stage_1:
cli
xor bx,bx
mov ss,bx
mov ds,bx
mov bp,0x9000
mov sp,bp
sti
mov [BootDiskNumber],dl
;---------------------------------------------------------------------------------------
	;Initialize ROOT_SECT_NO and DATA_SECT_NO
;---------------------------------------------------------------------------------------
xor ax,ax
mov al,[bpbNumberOfFATs]
mul byte[bpbSectorsPerFAT] ;we ignore dx  what?? potential bug?
add ax,[bpbReservedSectors]
mov [ROOT_SECT_NO],ax
mov bx,[bpbRootEntries]
shr bx,4
add ax,bx
mov [DATA_SECT_NO],ax

;---------------------------------------------------------------------------------------
call init_CHS   ;Initializes the disk geometry
;---------------------------------------------------------------------------------------

;---------------------------------------------------------------------------------------
	;Loads the Root directory and FAT tables into memory
;---------------------------------------------------------------------------------------
LoadRoot:
	mov ax,[ROOT_SECT_NO]
	call LBA_to_CHS
	mov bx,[bpbRootEntries]
	shr bx,4   ;9-5  Number of sectors
	mov al,bl
	xor bx,bx
	mov es,bx
	mov bx,RootLoad  ;Reading to 0x1000
	call disk_read_16
LoadFAT:
	mov ax,[bpbReservedSectors]
	call LBA_to_CHS
	mov al,[bpbSectorsPerFAT]
	mov bx,FATLoad  ;Reading to 0x6000
	call disk_read_16
;---------------------------------------------------------------------------------------
	;Finds the file with given target name
;---------------------------------------------------------------------------------------

mov bx,Stage2Name
mov word[ReadWhere],Stage2Sector
call Findfile 
xor bx,bx
mov es,bx
mov bx,KernelName
mov word[ReadWhere],TempKernelSector
call Findfile 
;---------------------------------------------------------------------------------------
END_OF_STAGE:
mov ah,0x00  ;This is a cool thing... It waits for user input before going into 32 bit mode
int 0x16
jmp (Stage2Sector << 4)
;---------------------------------------------------------------------------------------
;Functions 
%include "boot/stage1/disk_read.asm"
%include "boot/stage1/print.asm"
%include "boot/stage1/CHS.asm"

Findfile:  ;Returns cluster number in bx
	mov si,.TargetMessage
	call print_si_16
	mov si,bx
	call print_si_16
	cld  ;Clears the direction flag
	mov di,RootLoad
	mov cx,[bpbRootEntries]  ; Loop whatever number of times
	.Loop:
		push cx
		mov cx,11
		push di
		mov si,bx
		rep cmpsb
		pop di
		pop cx
		je .Found
		add di,0x20
	loop .Loop
	.NotFound 
		mov si, .Error
		call print_si_16
		jmp $

	.Error: db 0xa,0xd,'File not found!',0
	.Message: db 0xa,0xd,'Success!',0x0a,0x0d,0
	.TargetMessage: db 'Searching for file: ',0
	.Found:
		mov si,.Message
		call print_si_16
		add di,26
		mov dx,word[di]


ReadFile:
	;Read sector bx, get next sector, loop
	xor cx,cx
	mov bx,[ReadWhere]
mov es,bx
xor bx,bx
	.loop:
	mov ax,dx   ;ax current, dx next
	cmp ax,0xfff
	je .end
	sub ax,2
	add ax,[DATA_SECT_NO]
	
	push dx
	push cx
	call LBA_to_CHS
	mov al,1 ;Read on sector at a time
	call disk_read_16
	pop cx
	pop dx
	call GetNextSector
	add bx,512 ;Next sector memory location
	inc cx
	jmp .loop
	.end:
	ret

GetNextSector:  ;dx is parameter
	push bx
	mov bx,dx ;move the fat cluster value in bx
	shl bx,1
	add bx,dx ;bx = dx*3
	shr bx,1   ;bx = dx*3/2
	
	jc .odd
	.even:
	add bx,FATLoad
	mov dx,[bx]
	and dx,0x0fff
	pop bx 
	ret
	.odd:
	add bx,FATLoad
	mov dx,[bx]
	shr dx,4   ; 0040 -> 0004
	pop bx
	ret
	

;These are all hard disk addresses
ROOT_SECT_NO: dw 0
DATA_SECT_NO: dw 0   ; Corresponds to FAT table entry 2 (0,1,2..)
ReadWhere: dw 0x7e00
KernelName: db 'KERNEL  BIN',0
Stage2Name: db 'STAGE2  BIN',0
times 510 - ($-$$) db 0
dw 0xaa55
;---------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------
;Bootsector over


