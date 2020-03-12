global gen_interrupt
global install_idt
global install_gdt
global init_pic
global enable_interrupts
global send_EOI_master
global kernel_wait
global get_pdbr
global flush_tlb_entry
global read_port
global write_port

read_port:
	mov edx, [esp + 4]
	in al, dx	
	ret

write_port:
	mov   edx, [esp + 4]    
	mov   al, [esp + 4 + 4]  
	out   dx, al  
	ret

get_pdbr:
	mov eax,cr3
	ret

flush_tlb_entry:
;invlpg isn't present in i386, only from i486... Potential bug? Lol
	mov eax,[esp+ 0x04]
	invlpg [eax]
	ret


gen_interrupt:
	mov al,[esp+4]
	mov byte [.placeholder + 1] ,al
	.placeholder:
		int 0
	ret


install_idt:
	mov eax,[esp+4]
	lidt [eax]
	ret

install_gdt:
	mov eax,[esp+4]
	lgdt [eax]
	ret

enable_interrupts:
	sti
	ret


init_pic:
	mov al, 0x11  ;ICW 1  ;Expect IC4|single?|0|level?|init?|000
	out 0x20,al
	out 0xA0,al
	
	mov al,0x20  ;Remapping the IRQs
	out 0x21,al
	mov al,0x28
	out 0xA1,al

	; Send ICW 3 to primary PIC
	mov al, 0x4	 ; 0x4 = 0100 Second bit (IR Line 2)
	out 0x21, al ; write to data register of primary PIC

	; Send ICW 3 to secondary PIC
	mov al, 0x2	; 010=> IR line 2
	out 0xA1, al ; write to data register of secondary PIC

	; Send ICW 4 - Set x86 mode --------------------------------
 
	mov al, 1	; bit 0 enables 80x86 mode
 
	out 0x21, al
	out 0xA1, al
	
	; Unmaskig all the registers 
 
	mov al, 0
	out 0x21, al
	out 0xA1, al
	
	ret


send_EOI_master:
	mov al,0x20  ;Set bit 4 of OCW2
	out 0x20,al
	ret
send_EOI_slave:
	mov al,0x20  ;Set bit 4 of OCW2
	out 0xA0,al
	ret

kernel_wait:
	hlt
	ret
