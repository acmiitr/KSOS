#ifndef dadio_h
#define dadio_h

#include <stdint.h>

enum vga_color {
         BLACK = 0,
         BLUE = 1,
         GREEN = 2,
         CYAN = 3,
         RED = 4,
         MAGENTA = 5,
         BROWN = 6,
         LIGHT_GREY = 7,
         DARK_GREY = 8,
         LIGHT_BLUE = 9,
         LIGHT_GREEN = 10,
         LIGHT_CYAN = 11,
         LIGHT_RED = 12,
         LIGHT_MAGENTA = 13,
         LIGHT_BROWN = 14,
         WHITE = 15,
 };      



uint32_t get_cursor();
void set_cursor(uint32_t);
void printf(char* Message);
void printhex (uint32_t input);
void set_fg_color(enum vga_color);
void set_bg_color(enum vga_color);
void clear();

#endif
