global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39

extern timer_handler
extern keyboard_handler
extern isr34handler
extern isr35handler
extern isr36handler
extern isr37handler
extern isr38handler
extern isr39handler

extern send_EOI_master
extern printhex


isr32:
	pusha
	call timer_handler
	call send_EOI_master
	popa
	iret
isr33:
	pusha
	call keyboard_handler
	call send_EOI_master
	popa
	iret
isr34:
isr35:
isr36:
isr37:
isr38:
isr39:
	pusha
	call send_EOI_master
	popa
	iret
