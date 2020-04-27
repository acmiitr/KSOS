/**  
 * @file strlen.c
 * @brief Compute length of a given string 
 * @see 
 */
#include <string.h>
/**
 * A simple function to compute the length of a given string
 * @param str String starting address 
 * 
 * @return size of string
*/
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
