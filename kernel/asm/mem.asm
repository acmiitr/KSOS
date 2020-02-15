global get_pdbr
global flush_tlb_entry

get_pdbr:
	mov eax,cr3
	ret

flush_tlb_entry:
	mov eax,[esp+ 0x04]
	invlpg [eax]
	ret
