/**  
 * @file memmove.c
 * @brief MOving data stored in memory from one location to another
 * @see 
 */
#include <string.h>

/**
 * A simple function to move data using memory address
 * @param dstptr Pointing to the destination adress 
 * @param srcptr Pointing to the source adress 
 * @param size Size to move memory
 * 
 * @return A null pointer pointing to the destination
*/
void* memmove(void* dstptr, const void* srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src) {
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	} else {
		for (size_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}
