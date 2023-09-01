#ifndef HASH_H_
#define HASH_H_

#include <assert.h>

/**
 * @brief Generates MurMur hash2A
 *
 * @param key data
 * @param len data len
 * @return unsigned int
 */
unsigned int MurmurHash2A(const void* key, int len);

#endif // #ifndef HASH_H_
