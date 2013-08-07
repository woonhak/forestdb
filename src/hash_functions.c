/*
 * Copyright 2013 Jung-Sang Ahn <jungsang.ahn@gmail.com>.
 * All Rights Reserved.
 */

#include <stdint.h>

#include "hash_functions.h"
#include "common.h"

// djb2 hashing using last LEN digits in VALUE
INLINE uint32_t hash_djb2(void *value, int len)
{
	unsigned hash = 5381;
	while(len--){
		hash = ((hash << 5) + hash) + *((uint8_t*)value + len);
	}
	return hash;
}

uint32_t hash_uint_modular(uint64_t value, uint64_t mod)
{
	return value % mod;
}

uint32_t hash_shuffle_2uint(uint64_t a, uint64_t b)
{
	uint32_t c;

	a ^= bitswap64(a ^ 0xffffffffffffffff);
	b ^= bitswap64(b ^ 0xffffffffffffffff);

	a = (a & 0xffff) ^ ((a & 0xffff0000) >> 16) ^ ((a & 0xffff00000000) >> 32) ^ ((a & 0xffff000000000000) >> 48);
	b = (b & 0xffff) ^ ((b & 0xffff0000) >> 16) ^ ((b & 0xffff00000000) >> 32) ^ ((b & 0xffff000000000000) >> 48);

	c = (((a & 0x0000000f) << 0) | 
		((b & 0x0000000f) << 4) |
		((a & 0x000000f0) << 4) | 
		((b & 0x000000f0) << 8) |
		((a & 0x00000f00) << 8) | 
		((b & 0x00000f00) << 12) |
		((a & 0x0000f000) << 12) | 
		((b & 0x0000f000) << 16));

	return (((c << 5) + c) << 5) + c;	
}
