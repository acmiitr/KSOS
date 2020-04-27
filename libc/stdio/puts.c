
/**  
 * @file puts.c
 * @brief This is a file which is used to print a give string on the VGA display  
 * @see 
 */
#include <stdio.h>

#ifdef __is_libk
#include <kernel/dadio.h>
#endif

int puts(const char* string) {
#ifdef __is_libk
	monitor_puts((char*)string);
	return 0;
#else
	return 0;
#endif
}
