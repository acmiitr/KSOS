global gen_interrupt
global install_idt
global install_gdt

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
