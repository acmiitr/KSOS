;This is our bootloader assembly code
;I am trying to include a 2 stage bootloader to not worry about space issues in the future -- Maybe we might use a filesystem

STAGE_2 equ 0x7e00
[org 0x7c00]
[bits 16]

jmp near boot_stage_1
;---------------------------------------------------------------------------------------
times (0x3d-0x02) db 0

;---------------------------------------------------------------------------------------
boot_stage_1:
mov bp,0x9000
mov sp,bp

;---------------------------------------------------------------------------------------
mov cl,0x2;All these are the arguments that one passes to the disk_read function , cl is track number
mov ch,0   ; 00000000b | 01b || 15
mov al,2 ;Some heavy calculation done here in cl
xor bx,bx
mov es,bx
mov bx,STAGE_2  ;Reading to 0x7e00
call disk_read_16
;---------------------------------------------------------------------------------------

mov si,WelcomeMessage
call print_si_16
jmp STAGE_2
;---------------------------------------------------------------------------------------
;Functions and magic bytes
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/disk_read.asm"
%include "/home/suraaj/Documents/GitStuff/DaddyOs/Boot/print.asm"

WelcomeMessage: db 'Sup, Welcome to BS1',0

times 510 - ($-$$) db 0
dw 0xaa55
;---------------------------------------------------------------------------------------
;---------------------------------------------------------------------------------------
;Bootsector over
;This is sector 2 of the hard disk
;---------------------------------------------------------------------------------------
