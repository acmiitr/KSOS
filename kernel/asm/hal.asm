global gen_interrupt
global install_idt
global install_gdt
global enable_interrupts
global kernel_wait
global get_pdbr
global flush_tlb_entry
global read_port
global write_port
global read_port_word
global write_port_word

read_port:
	mov edx, [esp + 4]
	in al, dx	
	ret
write_port:
	mov   edx, [esp + 4]    
	mov   eax, [esp + 4 + 4]  
	out   dx, al  
	ret

read_port_word:
	mov edx, [esp + 4]
	in ax, dx	
	ret

write_port_word:
	mov   edx, [esp + 4]    
	mov   eax, [esp + 4 + 4]  
	out   dx, ax
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

kernel_wait:
	hlt
	ret
