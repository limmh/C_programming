#ifndef STATIC_POOL_H
#define STATIC_POOL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct static_pool_type {
	size_t index_of_chunk_occupied;
	unsigned char chunk10[512];
	unsigned char chunk9[256];
	unsigned char chunk8[128];
	unsigned char chunk7[64];
	unsigned char chunk6[32];
	unsigned char chunk5[16];
	unsigned char chunk4[8];
	unsigned char chunk3[4];
	unsigned char chunk2[2];
	unsigned char chunk1[1];
	unsigned char zero_padding;
};

typedef struct static_pool_type static_pool_type;

void *static_pool_allocate(static_pool_type *pool, size_t number_of_bytes);

void *static_pool_reallocate(static_pool_type *pool, void *ptr, size_t new_size);

void static_pool_deallocate(static_pool_type *pool, void *ptr);

#ifdef __cplusplus
}
#endif

#endif
