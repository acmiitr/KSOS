extern general_interrupt_handler

%macro  save 0  ;%macro `name` `param_count`
	pusha
	push ds
	push es
	push fs
	push gs
%endmacro

%macro restore 0
	pop gs
	pop fs
	pop es
	pop ds
	popa
%endmacro

%macro int_nerr 1
	global isr%1
isr%1:
	push 0   ;Dummy error
	push %1
	save
	call general_interrupt_handler
	restore
	add esp,8 ;Error code + number
	iret
%endmacro

%macro int_err 1
	global isr%1
isr%1:
	push %1
	save
	call general_interrupt_handler
	restore
	add esp,8 ;Error code + number
	iret
%endmacro


;Initiating these stubs - It is really important to know which instruction throws what

int_nerr 0
int_nerr 1
int_nerr 2
int_nerr 3
int_nerr 4
int_nerr 5
int_nerr 6
int_nerr 7
int_err 8

int_err 10
int_err 11
int_err 12
int_err 13
int_err 14

int_nerr 16
int_err 17
int_nerr 18
int_nerr 19
int_nerr 20

int_err 30


;; interrupts:

int_nerr 32
int_nerr 33
int_nerr 34
int_nerr 35
int_nerr 36
int_nerr 37
int_nerr 38
int_nerr 39
int_nerr 40
int_nerr 41
int_nerr 42
int_nerr 43
int_nerr 44
int_nerr 45
int_nerr 46
int_nerr 47

int_nerr 128  ;Syscall
