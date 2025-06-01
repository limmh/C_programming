#include "static_pool.h"
#include <assert.h>
#include <iso646.h>
#include <string.h>

void *static_pool_allocate(static_pool_type *pool, size_t number_of_bytes)
{
	unsigned char *ptr = NULL;

	assert(pool != NULL);
	if (number_of_bytes <= sizeof(pool->chunk1)) {
		ptr = pool->chunk1;
	} else if (number_of_bytes <= sizeof(pool->chunk2)) {
		ptr = pool->chunk2;
	} else if (number_of_bytes <= sizeof(pool->chunk3)) {
		ptr = pool->chunk3;
	} else if (number_of_bytes <= sizeof(pool->chunk4)) {
		ptr = pool->chunk4;
	} else if (number_of_bytes <= sizeof(pool->chunk5)) {
		ptr = pool->chunk5;
	} else if (number_of_bytes <= sizeof(pool->chunk6)) {
		ptr = pool->chunk6;
	} else if (number_of_bytes <= sizeof(pool->chunk7)) {
		ptr = pool->chunk7;
	} else if (number_of_bytes <= sizeof(pool->chunk8)) {
		ptr = pool->chunk8;
	} else if (number_of_bytes <= sizeof(pool->chunk9)) {
		ptr = pool->chunk9;
	} else if (number_of_bytes <= sizeof(pool->chunk10)) {
		ptr = pool->chunk10;
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

	assert(pool != NULL);
	if (ptr == pool->chunk1) {
		chunk_ptr = pool->chunk1;
		chunk_size = sizeof(pool->chunk1);
	} else if (ptr == pool->chunk2) {
		chunk_ptr = pool->chunk2;
		chunk_size = sizeof(pool->chunk2);
	} else if (ptr == pool->chunk3) {
		chunk_ptr = pool->chunk3;
		chunk_size = sizeof(pool->chunk3);
	} else if (ptr == pool->chunk4) {
		chunk_ptr = pool->chunk4;
		chunk_size = sizeof(pool->chunk4);
	} else if (ptr == pool->chunk5) {
		chunk_ptr = pool->chunk5;
		chunk_size = sizeof(pool->chunk5);
	} else if (ptr == pool->chunk6) {
		chunk_ptr = pool->chunk6;
		chunk_size = sizeof(pool->chunk6);
	} else if (ptr == pool->chunk7) {
		chunk_ptr = pool->chunk7;
		chunk_size = sizeof(pool->chunk7);
	} else if (ptr == pool->chunk8) {
		chunk_ptr = pool->chunk8;
		chunk_size = sizeof(pool->chunk8);
	} else if (ptr == pool->chunk9) {
		chunk_ptr = pool->chunk9;
		chunk_size = sizeof(pool->chunk9);
	} else if (ptr == pool->chunk10) {
		chunk_ptr = pool->chunk10;
		chunk_size = sizeof(pool->chunk10);
	}

	assert(chunk_ptr != NULL);
	if (new_size > sizeof(pool->chunk10)) {
		new_ptr = NULL;
		new_chunk_size = new_size;
	} else if (new_size > sizeof(pool->chunk9)) {
		new_ptr = pool->chunk10;
		new_chunk_size = sizeof(pool->chunk10);
	} else if (new_size > sizeof(pool->chunk8)) {
		new_ptr = pool->chunk9;
		new_chunk_size = sizeof(pool->chunk9);
	} else if (new_size > sizeof(pool->chunk7)) {
		new_ptr = pool->chunk8;
		new_chunk_size = sizeof(pool->chunk8);
	} else if (new_size > sizeof(pool->chunk6)) {
		new_ptr = pool->chunk7;
		new_chunk_size = sizeof(pool->chunk7);
	} else if (new_size > sizeof(pool->chunk5)) {
		new_ptr = pool->chunk6;
		new_chunk_size = sizeof(pool->chunk6);
	} else if (new_size > sizeof(pool->chunk4)) {
		new_ptr = pool->chunk5;
		new_chunk_size = sizeof(pool->chunk5);
	} else if (new_size > sizeof(pool->chunk3)) {
		new_ptr = pool->chunk4;
		new_chunk_size = sizeof(pool->chunk4);
	} else if (new_size > sizeof(pool->chunk2)) {
		new_ptr = pool->chunk3;
		new_chunk_size = sizeof(pool->chunk3);
	} else if (new_size > sizeof(pool->chunk1)) {
		new_ptr = pool->chunk2;
		new_chunk_size = sizeof(pool->chunk2);
	} else {
		new_ptr = pool->chunk1;
		new_chunk_size = sizeof(pool->chunk1);
	}

	if (new_ptr != NULL and chunk_ptr != NULL and new_ptr != chunk_ptr) {
		assert(new_chunk_size > chunk_size);
		memset(new_ptr, 0, new_chunk_size * sizeof(*new_ptr));
		memcpy(new_ptr, chunk_ptr, chunk_size * sizeof(*chunk_ptr));
		memset(chunk_ptr, 0, chunk_size * sizeof(*chunk_ptr));
	}

	return new_ptr;
}

void static_pool_deallocate(static_pool_type *pool, void *ptr)
{
	assert(pool != NULL);

	if (ptr == pool->chunk1) {
		memset(pool->chunk1, 0, sizeof(pool->chunk1));
	} else if (ptr == pool->chunk2) {
		memset(pool->chunk2, 0, sizeof(pool->chunk2));
	} else if (ptr == pool->chunk3) {
		memset(pool->chunk3, 0, sizeof(pool->chunk3));
	} else if (ptr == pool->chunk4) {
		memset(pool->chunk4, 0, sizeof(pool->chunk4));
	} else if (ptr == pool->chunk5) {
		memset(pool->chunk5, 0, sizeof(pool->chunk5));
	} else if (ptr == pool->chunk6) {
		memset(pool->chunk6, 0, sizeof(pool->chunk6));
	} else if (ptr == pool->chunk7) {
		memset(pool->chunk7, 0, sizeof(pool->chunk7));
	} else if (ptr == pool->chunk8) {
		memset(pool->chunk8, 0, sizeof(pool->chunk8));
	} else if (ptr == pool->chunk9) {
		memset(pool->chunk9, 0, sizeof(pool->chunk9));
	} else if (ptr == pool->chunk10) {
		memset(pool->chunk10, 0, sizeof(pool->chunk10));
	}
}
