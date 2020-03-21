#ifndef ATA_H
#define ATA_H
void read_sectors_PIO(uint32_t target_address, uint32_t LBA, uint8_t sector_count);

#endif
