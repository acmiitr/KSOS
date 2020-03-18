#ifndef KEYBOARD_H
#define KEYBOARD_H

#include<stdbool.h>

//Variable (semaphore-ish)
extern bool _is_keyboard_interrupt;


bool kbc_init();
char get_latest_char();
uint8_t get_latest_scan_code();

#endif
