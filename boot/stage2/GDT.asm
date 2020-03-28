;GDT part
;global gdt_descriptor
null_segment:
	dd 0
	dd 0

code_segment:
	dw 0xffff  ;limit
	dw 0       ;starting address
	db 0
	db 10011010b ;present|privilage 0|S=codedata or traps|1=code|0=not conforming|Readable|Accessed (some debug)
	db 11001111b ;Granularity|32 bit code|is64?|Userbit|segment limit 4 more bits
	db 0
data_segment:
	dw 0xffff  ;limit
	dw 0       ;starting address
	db 0
	db 10010010b ;present|privilage 00|S=codedata or traps|1=code|0=not conforming|Readable|Accessed (some debug)
	db 11001111b ;Granularity|32 bit code|is64?|Userbit|segment limit 4 more bits
	db 0
code_segment_u:
	dw 0xffff  ;limit
	dw 0       ;starting address
	db 0
	db 11111010b ;present|privilage 0|S=codedata or traps|1=code|0=not conforming|Readable|Accessed (some debug)
	db 11001111b ;Granularity|32 bit code|is64?|Userbit|segment limit 4 more bits
	db 0
data_segment_u:
	dw 0xffff  ;limit
	dw 0       ;starting address
	db 0
	db 11110010b ;present|privilage 00|S=codedata or traps|1=code|0=not conforming|Readable|Accessed (some debug)
	db 11001111b ;Granularity|32 bit code|is64?|Userbit|segment limit 4 more bits
	db 0


GDT_end:

gdt_descriptor: ;16 bit size | 32 bit starting address
dw null_segment - GDT_end -1
dd null_segment; + 0x7c00 I did this when I was doing bakchodi
