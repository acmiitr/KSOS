#include<stdint.h>
#include"dadio.h"
#include"hal.h"

#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

//This is really specific to out OS now, assuming ATA bus 0 master 
//Source - OsDev wiki
void read_sectors_PIO(uint32_t target_address, uint32_t LBA, uint8_t sector_count)
{

	uint8_t status = read_port(0x1F7);
	if (status & STATUS_BSY) printf("\nBusy ");
	if (status & STATUS_DRQ) printf("Drq 1");
	printhex(status);

	status = read_port(0x3F6);
	if (status & STATUS_BSY) printf("\nBusy ");
	if (status & STATUS_DRQ) printf("Drq 1");
	printhex(status);

	write_port(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	write_port(0x1F2,sector_count);
	write_port(0x1F3, (uint8_t) LBA);
	write_port(0x1F4, (uint8_t)(LBA >> 8));
	write_port(0x1F5, (uint8_t)(LBA >> 16)); 

	write_port(0x1F7,0x20); //Send the read command

	//Polling the status port
	status = read_port(0x1F7);
	printf("\nStatus byte: ");
	printhex(status);
	while(status & STATUS_BSY)
	{
		status = read_port(0x1F7);
	}

	while(!(status & STATUS_DRQ))
	{
		status = read_port(0x3F6);
	}
	printf("Success");
}
/*
static void ATA_wait_BSY()
{




}
*/
