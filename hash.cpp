#include "hash.h"

inline void mmix(unsigned int* h, unsigned int* k, const int r, const unsigned int m) {
    *k *= m;
    *k ^= *k >> r;
    *k *= m;
    *h *= m;
    *h ^= *k;
}

unsigned int MurmurHash2A(const void* key, int len) {
	assert(key);

	static const unsigned int seed = 236002;
    const unsigned int m = 0x5bd1e995;
	const int r = 24;
	unsigned int l = len;

	const unsigned char* data = (const unsigned char*) key;

	unsigned int h = seed;
	unsigned int k = 0;

	while(len >= 4) {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

		mmix(&h, &k, r, m);

		data += 4;
		len -= 4;
	}

	unsigned int t = 0;

	switch(len) {
        case 3: t ^= data[2] << 16; [[fallthrough]];
        case 2: t ^= data[1] << 8;  [[fallthrough]];
        case 1: t ^= data[0];       [[fallthrough]];
		case 0:
			break;
		default:
			assert(0 && "len >= 4");
	};

	mmix(&h, &t, r, m);
	mmix(&h, &l, r, m);

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}
