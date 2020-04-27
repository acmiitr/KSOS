/**  
 * @file ATA.c
 * @brief Reading sectors from the hard disk
 * @see 
 */
#include<stdint.h>
#include"dadio.h"
#include"hal.h"

/**
 BSY: a 1 means that the controller is busy executing a command. No register should be accessed (except the digital output register) while this bit is set.
RDY: a 1 means that the controller is ready to accept a command, and the drive is spinning at correct speed..
WFT: a 1 means that the controller detected a write fault.
SKC: a 1 means that the read/write head is in position (seek completed).
DRQ: a 1 means that the controller is expecting data (for a write) or is sending data (for a read). Don't access the data register while this bit is 0.
COR: a 1 indicates that the controller had to correct data, by using the ECC bytes (error correction code: extra bytes at the end of the sector that allows to verify its integrity and, sometimes, to correct errors).
IDX: a 1 indicates the the controller retected the index mark (which is not a hole on hard-drives).
ERR: a 1 indicates that an error occured. An error code has been placed in the error register.
*/

#define STATUS_BSY 0x80 /**< Add the description here*/
#define STATUS_RDY 0x40	/**< Add the description here*/
#define STATUS_DRQ 0x08	/**< Add the description here*/
#define STATUS_DF 0x20	/**< Add the description here*/
#define STATUS_ERR 0x01	/**< Add the description here*/

/**This is really specific to out OS now, assuming ATA bus 0 master */
/** Source - OsDev wiki*/
static void ATA_wait_BSY();
static void ATA_wait_DRQ();
/** @brief A function to read data from the harddisk in sectors 
* @param target_address The address where the read data is stored in memory
* @param LBA Starting  Block number from where the is to be read in the hard disk
* @param sector_count Number of sectors to be read
* @return  
*/
void read_sectors_ATA_PIO(uint32_t target_address, uint32_t LBA, uint8_t sector_count)
{
	ATA_wait_BSY();
	write_port(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	write_port(0x1F2,sector_count);
	write_port(0x1F3, (uint8_t) LBA);
	write_port(0x1F4, (uint8_t)(LBA >> 8));
	write_port(0x1F5, (uint8_t)(LBA >> 16)); 
	write_port(0x1F7,0x20); //Send the read command

	uint16_t* target = (uint16_t*) target_address;

	for (int j =0;j<sector_count;j++)
	{
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(int i=0;i<256;i++)
			target[i] = read_port_word(0x1F0);
		target+=256;
	}
}
/** @brief Wait for bsy to be 0
*
*  Message Input the given string
* @return  
*/
static void ATA_wait_BSY()   //Wait for bsy to be 0
{
	while(read_port(0x1F7)&STATUS_BSY);
}
/** @brief //Wait fot drq to be 1
*
*  Message Input the given string
* @return  
*/
static void ATA_wait_DRQ()  //Wait fot drq to be 1
{
	while(!(read_port(0x1F7)&STATUS_RDY));
}
/*
static void ATA_wait_RDY()  //Wait fot rdy to be 1
{
	while(!read_port(0x1F7)&STATUS_RDY);
}
*/
