#ifndef ALLOCATOR_TYPE_H
#define ALLOCATOR_TYPE_H

#include "inline_or_static.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
'allocator_type' is an allocator interface which supports user-defined allocation, reallocation and deallocation functions.
The 'allocate' function pointer has the same signature as malloc.
The 'reallocate' function pointer has the same signature as realloc.
The 'deallocate' function pointer has the same signature as free.
The standard library functions (malloc, realloc and free) are part of stdlib.h.
Hence, the behavior of user-defined functions should be as close to the behavior of the standard library functions as possible.
*/
typedef struct allocator_type
{
	/* allocate MUST NOT be a null pointer */
	void * (*allocate)(size_t /* number of bytes */);
	/* reallocate can be a null pointer */
	void * (*reallocate)(void*/* memory block allocated using 'allocate' */, size_t /* new number of bytes*/);
	/* deallocate MUST NOT be a null pointer */
	void (*deallocate)(void*/* memory block allocated by using 'allocate' or 'reallocate' */);
} allocator_type;

/*Functions and macros */

/*
Initializes the function pointers of an allocator.

Parameters:
allocator                    : a pointer to an allocator object, must not be null
allocation_function_pointer  : a pointer to a user-defined memory allocation function, must not be null
reallocation_function_pointer: a pointer to a user-defined memory reallocation function, can be null
deallocation_function_pointer: a pointer to a user-defined memory deallocation function, must not be null

Return value: none
*/
INLINE_OR_STATIC
void allocator_init_(
	allocator_type *allocator,
	void * (*allocation_function_pointer)(size_t),
	void * (*reallocation_function_pointer)(void*, size_t),
	void (*deallocation_function_pointer)(void*)
) {
	assert(allocator != NULL);
	assert(allocation_function_pointer != NULL);
	assert(deallocation_function_pointer != NULL);
	if (allocator != NULL) {
		allocator->allocate = allocation_function_pointer;
		allocator->reallocate = reallocation_function_pointer;
		allocator->deallocate = deallocation_function_pointer;
	}
}

#define allocator_init(allocator, alloc_fptr, realloc_fptr, dealloc_fptr) \
	allocator_init_(&(allocator), alloc_fptr, realloc_fptr, dealloc_fptr)

/*
Clears the function pointers of an allocator by setting each of them to null.

Parameter:
allocator: a pointer to an allocator object, must not be null

Return value: none
*/
INLINE_OR_STATIC
void allocator_deinit_(allocator_type *allocator)
{
	assert(allocator != NULL);
	if (allocator != NULL) {
		allocator->allocate = NULL;
		allocator->reallocate = NULL;
		allocator->deallocate = NULL;
	}
}

#define allocator_deinit(allocator) allocator_deinit_(&(allocator))

/*
Performs memory allocation by calling the 'allocate' function pointer.

Parameters:
allocator      : an allocator object passed by value, its 'allocate' and 'deallocate' function pointers must be valid and non-null
number_of_bytes: the number of bytes of memory to be allocated

Return value: a pointer to a memory block if allocation is successful, otherwise NULL

Notes:
- If a memory block is allocated successfully, the function will zero the memory block.
- If number_of_bytes is zero, the returned pointer is always null.
- The user-defined allocation function should return a null pointer if no memory block of the requested size
  can be allocated.
- Always check whether the returned pointer is non-null before accessing the memory block.
*/
INLINE_OR_STATIC
void *allocator_allocate(allocator_type allocator, size_t number_of_bytes)
{
	void *memory_block = NULL;
	assert(allocator.allocate != NULL);
	assert(allocator.deallocate != NULL);
	if (number_of_bytes > 0U && allocator.allocate != NULL && allocator.deallocate != NULL) {
		memory_block = allocator.allocate(number_of_bytes);
		if (memory_block != NULL) {
			(void) memset(memory_block, 0, number_of_bytes);
		}
	}
	return memory_block;
}

/*
Performs memory reallocation by calling the 'reallocate' function pointer.

Parameters:
allocator          : an allocator object passed by value, its 'allocate' functions and 'deallocate' functions must be valid and non-null
old_block          : MUST point to a memory block previously allocated by the 'allocate' function
old_number_of_bytes: the number of bytes previously passed to 'allocate' to obtain old_block
new_number_of_bytes: the number of bytes of memory to reallocate, can be smaller than, the same as or greater than old_number_of_bytes

Return value: a pointer to a new memory block if reallocation is successful, otherwise NULL

Notes:
- If the 'reallocate' function pointer is not null, the function will call 'reallocate' to perform memory reallocation.
  Hence, memory reallocation will fully depend on the behavior of the user-defined reallocation function.
- The 'old_block' pointer MUST point to a memory block allocated by the 'allocate' or 'reallocate' function pointer.
- If the 'reallocate' function pointer is null, 'allocate' and 'deallocate' will be used to perform memory reallocation.
- When 'allocate' and 'deallocate' are used to perform memory reallocation, the function applies the following behavior conditionally.
  - Assumption: old_number_of_bytes MUST NOT be zero.
  - If old_block is null, 'allocate' will perform memory allocation. If new_number_of_bytes is zero, the returned pointer is null.
  - If old_block is valid and if old_number_of_bytes is smaller than new_number_of_bytes, a new block will be allocated.
    If the allocation is successful, the content of old_block will be copied to new_block. Then, old_block will be deallocated.
    Hence, new_block will be valid, while old_block will be invalid. DO NOT dereference old_block.
    If the allocation is not successful, new_block will be null, and old_block will not be deallocated and will remain valid.
  - If old_block is valid and if old_number_of_bytes is the same as new_number_of_bytes, no reallocation will be performed, so
    new_block will point to old_block.
  - If old_block is valid and if old_number_of_bytes is larger than new_number_of_bytes, memory allocation will be performed.
    If the allocation is successful, only the content of old_block which fits into new_block will be copied to new_block.
    Then, old_block will be deallocated. Hence, new_block will be valid, while old_block will be invalid. DO NOT dereference old_block.
    If the allocation is not successful, old_block will not be deallocated.
  - If old_block is valid and new_number_of_bytes is zero, the old block will be deallocated and the returned pointer is NULL.
    DO NOT dereference old_block.
  - If new_block is larger, the content of old_block will not fully occupy it. Additional bytes will be zeroed.
*/
INLINE_OR_STATIC
void *allocator_reallocate(allocator_type allocator, void *old_block, size_t old_number_of_bytes, size_t new_number_of_bytes)
{
	void *new_block = NULL;
	assert(allocator.allocate != NULL);
	assert(allocator.deallocate != NULL);

	if (allocator.allocate == NULL || allocator.deallocate == NULL) {
		return new_block;
	}

	if (allocator.reallocate != NULL) {
		new_block = allocator.reallocate(old_block, new_number_of_bytes);
	} else if (old_block != NULL) {
		assert(old_number_of_bytes > 0U);
		if (new_number_of_bytes == 0U) {
			new_block = NULL;
			allocator.deallocate(old_block);
		} else if (old_number_of_bytes < new_number_of_bytes) {
			new_block = allocator.allocate(new_number_of_bytes);
			if (new_block != NULL && new_block != old_block) {
				(void) memcpy(new_block, old_block, old_number_of_bytes);
				allocator.deallocate(old_block);
			}
		} else if (old_number_of_bytes == new_number_of_bytes) {
			new_block = old_block;
		} else { /* old_number_of_bytes > new_number_of_bytes */
			new_block = allocator.allocate(new_number_of_bytes);
			if (new_block != NULL && new_block != old_block) {
				(void) memcpy(new_block, old_block, new_number_of_bytes);
				allocator.deallocate(old_block);
			}
		}
	} else { /* old_block == NULL */
		new_block = (new_number_of_bytes > 0U) ? allocator.allocate(new_number_of_bytes) : NULL;
	}

	if (new_block != NULL && old_number_of_bytes < new_number_of_bytes) {
		const size_t number_of_bytes_to_zero = new_number_of_bytes - old_number_of_bytes;
		unsigned char *ptr = (unsigned char*) new_block + old_number_of_bytes;
		(void) memset(ptr, 0, number_of_bytes_to_zero);
	}

	return new_block;
}

/*
Deallocates an allocated memory block by calling the 'deallocate' function pointer.

Parameters:
allocator   : an allocator object passed by value, its 'allocate' and 'deallocate' function pointers must be valid and non-null
memory_block: MUST point to a memory block previously allocated by the 'allocate' or 'reallocate' function,
              no action is taken if memory_block is null

Return value: none
*/
INLINE_OR_STATIC
void allocator_deallocate(allocator_type allocator, void *memory_block)
{
	assert(allocator.allocate != NULL);
	assert(allocator.deallocate != NULL);
	if (memory_block != NULL && allocator.allocate != NULL && allocator.deallocate != NULL) {
		allocator.deallocate(memory_block);
	}
}

#ifdef __cplusplus
}
#endif

#endif
