global set_timer
;The source of this code is BrokenThorn XD
set_timer:
	mov dx, [esp+4]	; 100hz, or 10 milliseconds
 
	; FIRST send the command word to the PIT. Sets binary counting,
	; Mode 3, Read or Load LSB first then MSB, Channel 0
 
	mov	al, 110110b
	out	0x43, al
 
	; Now we can write to channel 0. Because we set the "Load LSB first then MSB" bit, that is
	; the way we send it
 
	mov ax, dx
	out 0x40, al	;LSB
	xchg ah, al
	out 0x40, al	;MSB
	ret
