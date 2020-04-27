/**  
 * @file memcmp.c
 * @brief Comapre data stored in memory 
 * @see 
 */
#include <string.h>
/**
 * 
 * @param aptr Pointing to the first object to compare
 * @param bptr Pointing to second object to comapre
 * @param size Size to compare in memory
 * @return an integer determing which is greater
*/
int memcmp(const void* aptr, const void* bptr, size_t size) {
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}
