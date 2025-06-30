/* Minimum C Standard: C89 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dynamic_array_type_
{
	unsigned char do_not_access_directly[5 * sizeof(size_t)];
} dynamic_array_type_;

/* This macro is only for annotation.*/
#define dynamic_array_type(element_type) dynamic_array_type_

typedef struct dynamic_array_debug_info_type
{
	const char *file_name;
	size_t line_number;
	size_t struct_size;
} dynamic_array_debug_info_type;

typedef enum dynamic_array_error_type
{
	dynamic_array_error_none = 0,
	dynamic_array_error_null_pointer_exception,
	dynamic_array_error_struct_size_is_incorrect,
	dynamic_array_error_array_does_not_contain_buffer,
	dynamic_array_error_array_capacity_is_incorrect,
	dynamic_array_error_array_element_size_is_incorrect,
	dynamic_array_error_initial_size_is_incorrect,
	dynamic_array_error_index_is_out_of_range,
	dynamic_array_error_size_mismatch_between_source_elements_and_array_elements,
	dynamic_array_error_calculation_overflow_is_detected,
	dynamic_array_error_allocator_is_not_specified,
	dynamic_array_error_memory_allocation_failure_occurred,
	dynamic_array_error_memory_reallocation_failure_occurred,
	dynamic_array_error_memory_allocation_function_is_not_available,
	dynamic_array_error_memory_reallocation_function_is_not_available,
	dynamic_array_error_memory_deallocation_function_is_not_available
} dynamic_array_error_type;

typedef struct dynamic_array_allocator_type
{
	void * (*allocate_funcptr)(size_t); /* a function that behaves like malloc */
	void * (*reallocate_funcptr)(void*, size_t); /* a function that behaves like realloc */
	void   (*deallocate_funcptr)(void*); /* a function that behaves like free */
} dynamic_array_allocator_type;

/*
Function declarations and macros
Most functions will invoke the exception handler on error.
If no exception handler is provided, the program will be terminated when an error is detected.
*/

#ifndef __cplusplus
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
static dynamic_array_debug_info_type s_debug_info = {.file_name = "", .line_number = 0U, .struct_size = 0U};
#define DYNAMIC_ARRAY_DEBUG_INFO_INIT(array) {.file_name = __FILE__, .line_number = (size_t)__LINE__, .struct_size = sizeof(array)}
#else
static dynamic_array_debug_info_type s_debug_info = {"", 0U, 0U};
#define DYNAMIC_ARRAY_DEBUG_INFO_INIT(array) {__FILE__, (size_t)__LINE__, sizeof(array)}
#endif
#else
static dynamic_array_debug_info_type s_debug_info = {"", 0U, 0U};
#define DYNAMIC_ARRAY_DEBUG_INFO_INIT(array) {__FILE__, (size_t)__LINE__, sizeof(array)}
#endif

/* Creates a dynamic array and returns a dynamic_array_type_ variable */
dynamic_array_type_
dynamic_array_create_(
	size_t initial_size,
	size_t element_size,
	dynamic_array_allocator_type *allocator,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_create(type, size) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(dynamic_array_type_), \
		dynamic_array_create_(size, sizeof(type), NULL, s_debug_info) \
	)

#define dynamic_array_create_with_allocator(type, size, allocator) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(dynamic_array_type_), \
		dynamic_array_create_(size, sizeof(type), &(allocator), s_debug_info) \
	)

/* Performs cleanup and releases the memory occupied by the dynamic array */
void
dynamic_array_delete_(
	dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_delete(array) \
	do { \
		const dynamic_array_debug_info_type debug_info = \
					DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		dynamic_array_delete_(&(array), debug_info); \
	} while (0)

/* Retrieves the allocator */
const dynamic_array_allocator_type*
dynamic_array_get_allocator_(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_get_allocator(array) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(array), \
		dynamic_array_get_allocator_(&(array), debug_info) \
	)

/*
Checks the dynamic array for any error
The returned error is the first error detected
*/
dynamic_array_error_type
dynamic_array_check_(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_check(array) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(array), \
		dynamic_array_check_(&(array), s_debug_info) \
	)

/* Returns the number of elements that can be stored without reallocation */
size_t
dynamic_array_capacity_(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_capacity(array) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(array), \
		dynamic_array_capacity_(&(array), s_debug_info) \
	)

/* Returns the actual number of elements of the dynamic array */
size_t
dynamic_array_size_(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_size(array) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(array), \
		dynamic_array_size_(&(array), s_debug_info) \
	)

#define dynamic_array_length(array) \
	( \
		s_debug_info.file_name = __FILE__, \
		s_debug_info.line_number = (size_t)__LINE__, \
		s_debug_info.struct_size = sizeof(array), \
		dynamic_array_size_(&(array), s_debug_info) \
	)

/*
Returns a pointer to an element of the array based on the given index.
The pointer is a void pointer and must be cast to the proper type of each element.
NOTE: Do not call this function directly. Use the provided macro below to access an array element.
*/
void *
dynamic_array_element_ptr_(
	const dynamic_array_type_ *dynamic_array,
	size_t index,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_element(type, array, index) \
		(*((type*) dynamic_array_element_ptr_(&(array), index, sizeof(type), __FILE__, (size_t)__LINE__, sizeof(array))))

/*
Adds or inserts elements at an index
Valid index values: from 0 to one past the last index, i.e. [0, array_size]
The function will perform reallocation if there is no enough capacity.
*/
void
dynamic_array_add_elements_at_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_add_element_at_index(type, array, index, element) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		type tmp = element; \
		dynamic_array_add_elements_at_index_(&(array), index, &tmp, 1U, sizeof(tmp), debug_info); \
	} while (0)

#define dynamic_array_add_elements_at_index(type, array, index, elements, element_count) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		assert(sizeof(type) == sizeof((elements)[0])); \
		dynamic_array_add_elements_at_index_(&(array), index, elements, element_count, sizeof((elements)[0]), debug_info); \
	} while (0)

#define dynamic_array_append_element(type, array, element) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		type tmp = element; \
		dynamic_array_add_elements_at_index_(&(array), dynamic_array_size(array), &tmp, 1U, sizeof(tmp), debug_info); \
	} while (0)

#define dynamic_array_push_back(type, array, element) dynamic_array_append_element(type, array, element)

#define dynamic_array_append_elements(type, array, elements, element_count) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		assert(sizeof(type) == sizeof((elements)[0])); \
		dynamic_array_add_elements_at_index_(&(array), dynamic_array_size(array), elements, element_count, sizeof((elements)[0]), debug_info); \
	} while (0)

/*
Removes elements start from the given index
The specified number of elements to be removed can larger than the actual number of  elements that are available.
Only the available elements will be removed.
The function will not perform any reallocation.
*/
void
dynamic_array_remove_elements_starting_from_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_remove_element_at_index(type, array, index) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		dynamic_array_remove_elements_starting_from_index_(&(array), index, NULL, 1U, sizeof(type), debug_info); \
	} while (0)

#define dynamic_array_remove_elements_starting_from_index(type, array, index, number_of_elements) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		dynamic_array_remove_elements_starting_from_index_(&(array), index, NULL, number_of_elements, sizeof(type), debug_info); \
	} while (0)

#define dynamic_array_move_elements_starting_from_index_to_buffer(type, array, index, buffer, number_of_elements) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		assert(buffer != NULL); \
		assert(sizeof(type) == sizeof((buffer)[0])); \
		dynamic_array_remove_elements_starting_from_index_(&(array), index, buffer, number_of_elements, sizeof((buffer)[0]), debug_info); \
	} while (0)

#define dynamic_array_pop_back(type, array, variable) \
	do { \
		size_t last_element_index = 0U, array_length = 0U; \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		assert(sizeof(type) == sizeof(variable)); \
		array_length = dynamic_array_size(array); \
		assert(array_length >= 1U); \
		last_element_index = (array_length >= 1U) ? (array_length - 1U) : 0U; \
		dynamic_array_remove_elements_starting_from_index_(&(array), last_element_index, &(variable), 1U, sizeof(variable), debug_info); \
	} while (0)

/*
Changes the size of the array.
If the new size is larger than the old size, reallocation may be performed and all new elements are zero initialized.
If the new size is smaller than the old size, there will be no reallocation. Old elements at the end will be zeroed.
*/
void
dynamic_array_resize_(
	dynamic_array_type_ *dynamic_array,
	size_t new_size,
	size_t element_size,
	dynamic_array_debug_info_type debug_info
);

#define dynamic_array_resize(type, array, new_size) \
	do { \
		const dynamic_array_debug_info_type debug_info = DYNAMIC_ARRAY_DEBUG_INFO_INIT(array); \
		dynamic_array_resize_(&(array), new_size, sizeof(type), debug_info); \
	} while (0)

/* Provides an exception handler. */
void
dynamic_array_set_exception_handler(
	void (*exception_handler)(dynamic_array_error_type)
);

/* Provides an error reporting handler.
 TODO: More details in the future ... */
void
dynamic_array_set_error_reporting_handler(
	void (*report_error_funcptr)(dynamic_array_error_type, dynamic_array_debug_info_type, dynamic_array_debug_info_type, size_t, size_t)
);

#ifdef __cplusplus
}
#endif

#endif
