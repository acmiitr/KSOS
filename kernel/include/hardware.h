#ifndef HARDWARE_H
#define HARDWARE_H

#include<stdbool.h>

//Keyboard
extern bool _is_keyboard_interrupt;

bool kbc_init();
char get_latest_char();
uint8_t get_latest_scan_code();
void wait_for_keyboard();

//ATA
void read_sectors_ATA_PIO(uint32_t target_address, uint32_t LBA, uint8_t sector_count);


//PIC
void init_pic();
void send_EOI_master();
void send_EOI_slave();

#endif


