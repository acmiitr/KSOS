#include <stdio.h>

#ifdef __lib_k
#include <kernel/dadio.h>
#endif

int puts(const char* string) {
#ifdef __lib_k
	monitor_puts(string);
	return 0;
#else
	return 0;
#endif
}
