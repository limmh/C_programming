#include "static_pool.h"
#include "macro_alignof.h"
#include "static_assert.h"
#include <assert.h>
#include <iso646.h>
#include <string.h>

STATIC_ASSERT(ALIGNOF(static_pool_type) == ALIGNOF(void*), "static_pool_type and pointer type must have the same memory alignment.");

void *static_pool_allocate(static_pool_type *pool, size_t number_of_bytes)
{
	unsigned char *ptr = NULL;

	assert(pool != NULL);
	if (pool->index_of_chunk_occupied != 1U and number_of_bytes <= sizeof(pool->chunk1)) {
		ptr = pool->chunk1;
		pool->index_of_chunk_occupied = 1U;
	} else if (pool->index_of_chunk_occupied != 2U and number_of_bytes <= sizeof(pool->chunk2)) {
		ptr = pool->chunk2;
		pool->index_of_chunk_occupied = 2U;
	} else if (pool->index_of_chunk_occupied != 3U and number_of_bytes <= sizeof(pool->chunk3)) {
		ptr = pool->chunk3;
		pool->index_of_chunk_occupied = 3U;
	} else if (pool->index_of_chunk_occupied != 4U and number_of_bytes <= sizeof(pool->chunk4)) {
		ptr = pool->chunk4;
		pool->index_of_chunk_occupied = 4U;
	} else if (pool->index_of_chunk_occupied != 5U and number_of_bytes <= sizeof(pool->chunk5)) {
		ptr = pool->chunk5;
		pool->index_of_chunk_occupied = 5U;
	} else if (pool->index_of_chunk_occupied != 6U and number_of_bytes <= sizeof(pool->chunk6)) {
		ptr = pool->chunk6;
		pool->index_of_chunk_occupied = 6U;
	} else if (pool->index_of_chunk_occupied != 7U and number_of_bytes <= sizeof(pool->chunk7)) {
		ptr = pool->chunk7;
		pool->index_of_chunk_occupied = 7U;
	} else if (pool->index_of_chunk_occupied != 8U and number_of_bytes <= sizeof(pool->chunk8)) {
		ptr = pool->chunk8;
		pool->index_of_chunk_occupied = 8U;
	} else if (pool->index_of_chunk_occupied != 9U and number_of_bytes <= sizeof(pool->chunk9)) {
		ptr = pool->chunk9;
		pool->index_of_chunk_occupied = 9U;
	} else if (pool->index_of_chunk_occupied != 10U and number_of_bytes <= sizeof(pool->chunk10)) {
		ptr = pool->chunk10;
		pool->index_of_chunk_occupied = 10U;
	} else {
		ptr = NULL;
	}

	return ptr;
}

void *static_pool_reallocate(static_pool_type *pool, void *ptr, size_t new_size)
{
	unsigned char *new_ptr = NULL;
	size_t new_chunk_size = 0U;
	unsigned char *chunk_ptr = NULL;
	size_t chunk_size = 0U;
	size_t index = 0U;

	assert(pool != NULL);
	if (ptr == pool->chunk1) {
		index = 1U;
		chunk_ptr = pool->chunk1;
		chunk_size = sizeof(pool->chunk1);
	} else if (ptr == pool->chunk2) {
		index = 2U;
		chunk_ptr = pool->chunk2;
		chunk_size = sizeof(pool->chunk2);
	} else if (ptr == pool->chunk3) {
		index = 3U;
		chunk_ptr = pool->chunk3;
		chunk_size = sizeof(pool->chunk3);
	} else if (ptr == pool->chunk4) {
		index = 4U;
		chunk_ptr = pool->chunk4;
		chunk_size = sizeof(pool->chunk4);
	} else if (ptr == pool->chunk5) {
		index = 5U;
		chunk_ptr = pool->chunk5;
		chunk_size = sizeof(pool->chunk5);
	} else if (ptr == pool->chunk6) {
		index = 6U;
		chunk_ptr = pool->chunk6;
		chunk_size = sizeof(pool->chunk6);
	} else if (ptr == pool->chunk7) {
		index = 7U;
		chunk_ptr = pool->chunk7;
		chunk_size = sizeof(pool->chunk7);
	} else if (ptr == pool->chunk8) {
		index = 8U;
		chunk_ptr = pool->chunk8;
		chunk_size = sizeof(pool->chunk8);
	} else if (ptr == pool->chunk9) {
		index = 9U;
		chunk_ptr = pool->chunk9;
		chunk_size = sizeof(pool->chunk9);
	} else if (ptr == pool->chunk10) {
		index = 10U;
		chunk_ptr = pool->chunk10;
		chunk_size = sizeof(pool->chunk10);
	}

	assert(pool->index_of_chunk_occupied == index);
	assert(chunk_ptr != NULL);
	if (new_size > sizeof(pool->chunk10)) {
		new_ptr = NULL;
		new_chunk_size = new_size;
	} else if (new_size > sizeof(pool->chunk9)) {
		new_ptr = pool->chunk10;
		new_chunk_size = sizeof(pool->chunk10);
		index = 10U;
	} else if (new_size > sizeof(pool->chunk8)) {
		new_ptr = pool->chunk9;
		new_chunk_size = sizeof(pool->chunk9);
		index = 9U;
	} else if (new_size > sizeof(pool->chunk7)) {
		new_ptr = pool->chunk8;
		new_chunk_size = sizeof(pool->chunk8);
		index = 8U;
	} else if (new_size > sizeof(pool->chunk6)) {
		new_ptr = pool->chunk7;
		new_chunk_size = sizeof(pool->chunk7);
		index = 7U;
	} else if (new_size > sizeof(pool->chunk5)) {
		new_ptr = pool->chunk6;
		new_chunk_size = sizeof(pool->chunk6);
		index = 6U;
	} else if (new_size > sizeof(pool->chunk4)) {
		new_ptr = pool->chunk5;
		new_chunk_size = sizeof(pool->chunk5);
		index = 5U;
	} else if (new_size > sizeof(pool->chunk3)) {
		new_ptr = pool->chunk4;
		new_chunk_size = sizeof(pool->chunk4);
		index = 4U;
	} else if (new_size > sizeof(pool->chunk2)) {
		new_ptr = pool->chunk3;
		new_chunk_size = sizeof(pool->chunk3);
		index = 3U;
	} else if (new_size > sizeof(pool->chunk1)) {
		new_ptr = pool->chunk2;
		new_chunk_size = sizeof(pool->chunk2);
		index = 2U;
	} else {
		new_ptr = pool->chunk1;
		new_chunk_size = sizeof(pool->chunk1);
		index = 1U;
	}

	if (new_ptr != NULL and chunk_ptr != NULL and new_ptr != chunk_ptr) {
		assert(new_chunk_size > chunk_size);
		memset(new_ptr, 0, new_chunk_size * sizeof(*new_ptr));
		memcpy(new_ptr, chunk_ptr, chunk_size * sizeof(*chunk_ptr));
		memset(chunk_ptr, 0, chunk_size * sizeof(*chunk_ptr));
		pool->index_of_chunk_occupied = index;
	}

	return new_ptr;
}

void static_pool_deallocate(static_pool_type *pool, void *ptr)
{
	unsigned char index = 0U;
	assert(pool != NULL);
	if (ptr == pool->chunk1) {
		index = 1U;
		memset(pool->chunk1, 0, sizeof(pool->chunk1));
	} else if (ptr == pool->chunk2) {
		index = 2U;
		memset(pool->chunk2, 0, sizeof(pool->chunk2));
	} else if (ptr == pool->chunk3) {
		index = 3U;
		memset(pool->chunk3, 0, sizeof(pool->chunk3));
	} else if (ptr == pool->chunk4) {
		index = 4U;
		memset(pool->chunk4, 0, sizeof(pool->chunk4));
	} else if (ptr == pool->chunk5) {
		index = 5U;
		memset(pool->chunk5, 0, sizeof(pool->chunk5));
	} else if (ptr == pool->chunk6) {
		index = 6U;
		memset(pool->chunk6, 0, sizeof(pool->chunk6));
	} else if (ptr == pool->chunk7) {
		index = 7U;
		memset(pool->chunk7, 0, sizeof(pool->chunk7));
	} else if (ptr == pool->chunk8) {
		index = 8U;
		memset(pool->chunk8, 0, sizeof(pool->chunk8));
	} else if (ptr == pool->chunk9) {
		index = 9U;
		memset(pool->chunk9, 0, sizeof(pool->chunk9));
	} else if (ptr == pool->chunk10) {
		index = 10U;
		memset(pool->chunk10, 0, sizeof(pool->chunk10));
	}

	if (pool->index_of_chunk_occupied == index) {
		pool->index_of_chunk_occupied = 0U;
	}
}
