#ifndef STATIC_POOL_H
#define STATIC_POOL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct static_pool_type {
	unsigned char chunk1[128];
	unsigned char chunk2[64];
	unsigned char chunk3[32];
	unsigned char chunk4[16];
	unsigned char chunk5[8];
	unsigned char chunk6[4];
	unsigned char chunk7[2];
	unsigned char chunk8[1];
	unsigned char padding;
};

typedef struct static_pool_type static_pool_type;

void *static_pool_allocate(static_pool_type *pool, size_t number_of_bytes);

void *static_pool_reallocate(static_pool_type *pool, void *ptr, size_t new_size);

void static_pool_deallocate(static_pool_type *pool, void *ptr);

#ifdef __cplusplus
}
#endif

#endif
