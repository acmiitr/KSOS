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
