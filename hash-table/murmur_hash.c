#ifndef MURMUR_HASH_C
#define MURMUR_HASH_C
// I use MINGW GCC C Compiler

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FORCE_INLINE inline __attribute__ ((always_inline)) 

static FORCE_INLINE uint64_t
fmix64(uint64_t k)
{
    k ^= k >> 33;
    k *= 0xff51afd7ed558ccd;
    k ^= k >> 33;
    k *= 0xc4ceb9fe1a85ec53;
    k ^= k >> 33;

    return k;
}

static FORCE_INLINE uint64_t
rotl64(uint64_t x, uint64_t r)
{
    return (x << r) | (x >> (64 - r));
}

static FORCE_INLINE uint64_t 
getblock64(const uint64_t * p, int i)
{
    return p[i];
}

// Modified murmur3 hash function to use it on string
// Also studying/understanding this hash function
// See https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
uint64_t
murmur_hash_string(char *val, uint32_t seed)
{
    const char *data = (const char *)val;
    const int len = strlen(val);
    const int nblocks = len / 16;

    uint64_t h1 = seed;
    uint64_t h2 = seed;

    const uint64_t c1 = 0x87c37b91114253d5ULL;
    const uint64_t c2 = 0x4cf5ad432745937fULL;

    const uint64_t *blocks = (const uint64_t *)data;

    // Hashing / Mixing ?
    for (int i = 0; i < nblocks; ++i)
    {
        uint64_t k1 = getblock64(blocks, i * 2 + 0);
        uint64_t k2 = getblock64(blocks, i * 2 + 1);

        k1 *= c1; 
        k1  = rotl64(k1, 31); 
        k1 *= c2; 
        h1 ^= k1;

        h1 = rotl64(h1, 27); 
        h1 += h2; 
        h1 = h1 * 5 + 0x52dce729;

        k2 *= c2; 
        k2 = rotl64(k2, 33); 
        k2 *= c1;
        h2 ^= k2;

        h2 = rotl64(h2, 31);
        h2 += h1;
        h2 = h2 * 5 + 0x38495ab5;
    }

    // Byte left
    const char *tail = (const char *)(data + nblocks * 16);

    uint64_t k1 = 0;
    uint64_t k2 = 0;

    switch (len & 15)
    {
        // It will fall down I think
        case 15: k2 ^= ((uint64_t)tail[14]) << 48;
        case 14: k2 ^= ((uint64_t)tail[13]) << 40;
        case 13: k2 ^= ((uint64_t)tail[12]) << 32;
        case 12: k2 ^= ((uint64_t)tail[11]) << 24;
        case 11: k2 ^= ((uint64_t)tail[10]) << 16;
        case 10: k2 ^= ((uint64_t)tail[ 9]) << 8;
        case  9: k2 ^= ((uint64_t)tail[ 8]) << 0;
                 k2 *= c2; 
                 k2 = rotl64(k2,33);
                 k2 *= c1;
                 h2 ^= k2;

        case  8: k1 ^= ((uint64_t)tail[ 7]) << 56;
        case  7: k1 ^= ((uint64_t)tail[ 6]) << 48;
        case  6: k1 ^= ((uint64_t)tail[ 5]) << 40;
        case  5: k1 ^= ((uint64_t)tail[ 4]) << 32;
        case  4: k1 ^= ((uint64_t)tail[ 3]) << 24;
        case  3: k1 ^= ((uint64_t)tail[ 2]) << 16;
        case  2: k1 ^= ((uint64_t)tail[ 1]) << 8;
        case  1: k1 ^= ((uint64_t)tail[ 0]) << 0;
                 k1 *= c1; 
                 k1 = rotl64(k1,31);
                 k1 *= c2;
                 h1 ^= k1;
    };
    
    // finalization
    h1 ^= len; 
    h2 ^= len;

    h1 += h2;
    h2 += h1;

    h1 = fmix64(h1);
    h2 = fmix64(h2);

    h1 += h2;
    h2 += h1;

    return h2;
}

#endif