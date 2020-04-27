/**  
 * @file memcpy.c
 * @brief COpy data from one source to destination 
 * @see 
 */
#include <string.h>
/**
 * A simple function to copy data using memory address
 * @param dstptr Pointing to the destination adress 
 * @param srcptr Pointing to the source adress 
 * @param size Size to copy in memory
 * 
 * @return A null pointer pointing to the destination
*/
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}
