global get_pdbr
global flush_tlb_entry

get_pdbr:
	mov eax,cr3
	ret

flush_tlb_entry:
;invlpg isn't present in i386, only from i486... Potential bug? Lol
	mov eax,[esp+ 0x04]
	invlpg [eax]
	ret
