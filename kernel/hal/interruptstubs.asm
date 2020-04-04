global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39

global isr46
global isr47


;These are C handlers
extern timer_handler
extern keyboard_handler


extern send_EOI_master
extern send_EOI_slave

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


isr46:
isr47:
	pusha
	call send_EOI_master
	call send_EOI_slave
	popa
	iret
