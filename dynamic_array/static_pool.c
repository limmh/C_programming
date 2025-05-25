#include "static_pool.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void *static_pool_allocate(static_pool_type *pool, size_t number_of_bytes)
{
	unsigned char *ptr = NULL;
	assert(pool != NULL);
	if (number_of_bytes <= sizeof(pool->chunk8)) {
		ptr = pool->chunk8;
	} else if (number_of_bytes <= sizeof(pool->chunk7)) {
		ptr = pool->chunk7;
	} else if (number_of_bytes <= sizeof(pool->chunk6)) {
		ptr = pool->chunk6;
	} else if (number_of_bytes <= sizeof(pool->chunk5)) {
		ptr = pool->chunk5;
	} else if (number_of_bytes <= sizeof(pool->chunk4)) {
		ptr = pool->chunk4;
	} else if (number_of_bytes <= sizeof(pool->chunk3)) {
		ptr = pool->chunk3;
	} else if (number_of_bytes <= sizeof(pool->chunk2)) {
		ptr = pool->chunk2;
	} else if (number_of_bytes <= sizeof(pool->chunk1)) {
		ptr = pool->chunk1;
	} else {
		ptr = NULL;
	}
	return ptr;
}

void *static_pool_reallocate(static_pool_type *pool, void *ptr, size_t new_size)
{
	unsigned char *new_ptr = NULL;
	assert(pool != NULL);
	if (ptr == pool->chunk8) {
		if (new_size > sizeof(pool->chunk8)) {
			memset(pool->chunk7, 0, sizeof(pool->chunk7));
			memcpy(pool->chunk7, pool->chunk8, sizeof(pool->chunk8));
			memset(pool->chunk8, 0, sizeof(pool->chunk8));
			new_ptr = pool->chunk7;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk7) {
		if (new_size > sizeof(pool->chunk7)) {
			memset(pool->chunk6, 0, sizeof(pool->chunk6));
			memcpy(pool->chunk6, pool->chunk7, sizeof(pool->chunk7));
			memset(pool->chunk7, 0, sizeof(pool->chunk7));
			new_ptr = pool->chunk6;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk6) {
		if (new_size > sizeof(pool->chunk6)) {
			memset(pool->chunk5, 0, sizeof(pool->chunk5));
			memcpy(pool->chunk5, pool->chunk6, sizeof(pool->chunk6));
			memset(pool->chunk6, 0, sizeof(pool->chunk6));
			new_ptr = pool->chunk5;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk5) {
		if (new_size > sizeof(pool->chunk5)) {
			memset(pool->chunk4, 0, sizeof(pool->chunk4));
			memcpy(pool->chunk4, pool->chunk5, sizeof(pool->chunk5));
			memset(pool->chunk5, 0, sizeof(pool->chunk5));
			new_ptr = pool->chunk4;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk4) {
		if (new_size > sizeof(pool->chunk4)) {
			memset(pool->chunk3, 0, sizeof(pool->chunk3));
			memcpy(pool->chunk3, pool->chunk4, sizeof(pool->chunk4));
			memset(pool->chunk4, 0, sizeof(pool->chunk4));
			new_ptr = pool->chunk3;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk3) {
		if (new_size > sizeof(pool->chunk3)) {
			memset(pool->chunk2, 0, sizeof(pool->chunk2));
			memcpy(pool->chunk2, pool->chunk3, sizeof(pool->chunk3));
			memset(pool->chunk3, 0, sizeof(pool->chunk3));
			new_ptr = pool->chunk2;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk2) {
		if (new_size > sizeof(pool->chunk2)) {
			memset(pool->chunk1, 0, sizeof(pool->chunk1));
			memcpy(pool->chunk1, pool->chunk2, sizeof(pool->chunk2));
			memset(pool->chunk2, 0, sizeof(pool->chunk2));
			new_ptr = pool->chunk1;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == pool->chunk1) {
		if (new_size > sizeof(pool->chunk1)) {
			new_ptr = NULL;
		} else {
			new_ptr = (unsigned char*) ptr;
		}
	} else if (ptr == NULL) {
		new_ptr = static_pool_allocate(pool, new_size);
	} else {
		new_ptr = NULL;
		fprintf(stdout, "%s (line %d): An error has occurred.\n", __FILE__, __LINE__);
	}

	return new_ptr;
}

void static_pool_deallocate(static_pool_type *pool, void *ptr)
{
	assert(pool != NULL);
	
	if (ptr == NULL) {
		return;
	} else if (ptr == pool->chunk1) {
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
	} else {
		fprintf(stdout, "%s (line %d): An error has occurred.\n", __FILE__, __LINE__);
	}
}
