;This is our bootloader assembly code
;I am trying to include a 2 stage bootloader to not worry about space issues in the future -- Maybe we might use a filesystem

KERNEL_MEM equ 0x1000
[org 0x7c00]
[bits 16]

jmp boot_stage_1
;---------------------------------------------------------------------------------------

;This is for any filesystem information that we may input later
;This is for any filesystem information that we may input later
;This is for any filesystem information that we may input later
;This is for any filesystem information that we may input later

;---------------------------------------------------------------------------------------
boot_stage_1:
mov bp,0x9000
mov sp,bp

;---------------------------------------------------------------------------------------
mov cl,2 ;All these are the arguments that one passes to the disk_read function
mov al,9
xor bx,bx
mov es,bx
mov bx,boot_stage_2
call disk_read_16
;---------------------------------------------------------------------------------------

jmp boot_stage_2
;---------------------------------------------------------------------------------------
;Functions and magic bytes
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/disk_read.asm"
times 510 - ($-$$) db 0
dw 0xaa55
;---------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------
;Bootsector over
;This is sector 2 of the hard disk
;---------------------------------------------------------------------------------------
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/stage2.asm"
