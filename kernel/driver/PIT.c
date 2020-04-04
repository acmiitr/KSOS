#include "hal.h"

#define PIC1_COMMAND 0x20
#define PIC2_COMMAND 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1

void init_pic()
{
	
	//ICW 1  Expect IC4|single?|0|level?|init?|000
	write_port(PIC1_COMMAND,0x11);
	write_port(PIC2_COMMAND,0x11);
	
	//ICW 2  Remapping the IRQs
	write_port(PIC1_DATA,0x20);
	write_port(PIC2_DATA,0x28);

	// Send ICW 3 to primary PIC
	// 0x4 = 0100 Second bit (IR Line 2)
	write_port(PIC1_DATA,0x04);

	// Send ICW 3 to secondary PIC
	// 010=> IR line 2
	// write to data register of secondary PIC
	write_port(PIC2_DATA,0x02);

	// Send ICW 4 - Set x86 mode --------------------------------
	// bit 0 enables 80x86 mode
	write_port(PIC1_DATA,0x01);
	write_port(PIC2_DATA,0x01);
 
	
	// Setting the IMR - All interrupts enabled
	write_port(PIC1_DATA,0);
	write_port(PIC2_DATA,0);
}

void send_EOI_master()
{
	write_port(PIC1_COMMAND,0x20);
}

void send_EOI_slave()
{
	write_port(PIC2_COMMAND,0x20);
}
