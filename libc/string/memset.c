/**  
 * @file memset.c
 * @brief Comapre data stored in memory 
 * @see 
 */
#include <string.h>

/**
 * A simple function to initialize data to a specific value
 * @param bufptr Pointing to the starting adress of contiguous memory 
 * @param value Default value to be assigned 
 * @param size Size in memory location
 * 
 * @return A null pointer pointing to the original starting address
*/
void* memset(void* bufptr, int value, size_t size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}
