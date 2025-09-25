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
	size_t do_not_access_this_variable; /* for memory alignment purpose */
	unsigned char do_not_access_this_array[4 * sizeof(size_t)];
} dynamic_array_type_;

/* This macro is only for annotation. */
#define dynamic_array_type(element_type) dynamic_array_type_

typedef enum dynamic_array_error_type
{
	dynamic_array_error_none = 0,
	dynamic_array_error_null_pointer_exception,
	dynamic_array_error_struct_size_mismatch,
	dynamic_array_error_no_buffer,
	dynamic_array_error_incorrect_capacity,
	dynamic_array_error_incorrect_element_size,
	dynamic_array_error_index_out_of_range,
	dynamic_array_error_element_size_mismatch,
	dynamic_array_error_addition_overflow_detected,
	dynamic_array_error_multiplication_overflow_detected,
	dynamic_array_error_no_allocator,
	dynamic_array_error_memory_allocation_failure,
	dynamic_array_error_memory_reallocation_failure,
	dynamic_array_error_no_memory_allocation_function,
	dynamic_array_error_no_memory_deallocation_function
} dynamic_array_error_type;

typedef struct dynamic_array_debug_info_type
{
	const char *file_name; /* application source file */
	const char *library_file_name; /* library source file */
	size_t line_number; /* application source file */
	size_t library_line_number; /* library source file */
	size_t struct_size;
	size_t internal_struct_size;
	size_t info_1;
	size_t info_2;
	dynamic_array_error_type error;
} dynamic_array_debug_info_type;

typedef struct dynamic_array_allocator_type
{
	void * (*allocate_funcptr)(size_t); /* pointer to a function that behaves like malloc */
	void * (*reallocate_funcptr)(void*, size_t); /* pointer to a function that behaves like realloc (optional, can be NULL) */
	void   (*deallocate_funcptr)(void*); /* pointer to a function that behaves like free */
} dynamic_array_allocator_type;

/*
Provides an exception handler callback function.

Parameter:
exception_handler_funcptr: A pointer to an exception handler function

Return value: None.
*/
void dynamic_array_set_exception_handler(
	void (*exception_handler_funcptr)(dynamic_array_error_type)
);

/*
Provides an error reporting handler callback function.
 
Parameter:
report_error_funcptr: A pointer to an error report function.

Return value: None.

Function signature of error reporting handler:
void report_error(dynamic_array_debug_info_type debug_info);

Parameters:
debug_info         : Debug information.

Return value: None.

Errors and additional debug info:
1.  dynamic_array_error_none: no additional info (info_1 == 0, info_2 == 0)
2.  dynamic_array_error_null_pointer_exception: no additional info
3.  dynamic_array_error_struct_size_mismatch: info_1 == size of external data structure, info_2 == size of internal data structure
4.  dynamic_array_error_no_buffer: no additional info
5.  dynamic_array_error_incorrect_capacity: info_1 == capacity, info_2 == number of array elements
6.  dynamic_array_error_incorrect_element_size: info_1 == element size
7.  dynamic_array_error_index_out_of_range: info_1 == index, info_2 == number of array elements
8.  dynamic_array_error_element_size_mismatch: info_1 == external element size, info_2 == internal element size
9.  dynamic_array_error_addition_overflow_detected: info_1 == operand 1, info_2 == operand 2
10. dynamic_array_error_multiplication_overflow_detected: info_1 == operand 1, info_2 == operand 2
11. dynamic_array_error_no_allocator: no additional info
12. dynamic_array_error_memory_allocation_failure: info_1 == number of bytes requested, info_2 == 0
13. dynamic_array_error_memory_reallocation_failure: info_1 == number of bytes requested, info_2 == 0
14. dynamic_array_error_no_memory_allocation_function: no additional info
15. dynamic_array_error_no_memory_deallocation_function: no additional info
 */
void dynamic_array_set_error_reporting_handler(
	void (*report_error_funcptr)(dynamic_array_debug_info_type)
);

/*
Function declarations and macros
Most functions will invoke the exception handler on error.
If no exception handler is provided, the program will be terminated when an error is detected.
*/

/*
Creates a dynamic array and returns a dynamic_array_type_ variable.

Parameters
source            : The source of data to be copied when the dynamic array is first created. 'source' points to the first element of the source array. [Optional, can be NULL]
number_of_elements: The number of elements that the dynamic array will contain when it is first created.
                    If source is not NULL, then number_of_elements shall not exceed the number of elements that the source array contains.
element_size      : The number of bytes of each element in the array.
allocator         : A pointer to an allocator. The allocator must have a longer life time than the dynamic array. If it is a null pointer, a default allocator will be used.
file_name         : The name or path of the source file which calls the function. For debugging purpose.
line_number       : The line number of the source file at which the function is called. For debugging purpose.
struct_size       : The number of bytes of a dynamic_array_type_. For debugging purpose.

Return value
A copy of dynamic_array_type_. The return value shall be assigned to a variable of compatible dynamic_array_type_ to prevent a memory leak.

Possible errors and reasons:
1. dynamic_array_error_memory_allocation_failure: No memory block can be acquired.
2. dynamic_array_error_multiplication_overflow_detected: (Element size times initial capacity) is greater than the maximum allowed number of bytes.
3. dynamic_array_error_no_memory_allocation_function: A user allocator is provided, but the pointer to memory allocation function is NULL.
4. dynamic_array_error_no_memory_deallocation_function: A user allocator is provided, but the pointer to memory deallocation function is NULL.

Depending on the implementation, only the first error detected may be reported.
*/
dynamic_array_type_
dynamic_array_create_(
	const void *source,
	size_t number_of_elements,
	size_t element_size,
	dynamic_array_allocator_type *allocator,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_create(type, initial_size) \
	dynamic_array_create_(NULL, initial_size, sizeof(type), NULL, __FILE__, (size_t)__LINE__, sizeof(dynamic_array_type_))

#define dynamic_array_create_with_allocator(type, initial_size, allocator) \
	dynamic_array_create_(NULL, initial_size, sizeof(type), &(allocator), __FILE__, (size_t)__LINE__, sizeof(dynamic_array_type_))

#define dynamic_array_create_from_source(type, source, source_size) \
	(assert(sizeof(type) == sizeof((source)[0])), \
	dynamic_array_create_(source, source_size, sizeof(type), NULL, __FILE__, (size_t)__LINE__, sizeof(dynamic_array_type_)))

#define dynamic_array_create_from_source_with_allocator(type, source, source_size, allocator) \
	(assert(sizeof(type) == sizeof((source)[0])), \
	dynamic_array_create_(source, source_size, sizeof(type), &(allocator), __FILE__, (size_t)__LINE__, sizeof(dynamic_array_type_)))

/*
Performs cleanup and releases the memory occupied by the dynamic array.

Paramters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
file_name    : The name or path of the source file which calls the function. For debugging purpose.
line_number  : The line number of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of a dynamic_array_type_. For debugging purpose.

Return value: None.
*/
void dynamic_array_delete_(
	dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_delete(array) \
	dynamic_array_delete_(&(array), __FILE__, (size_t)__LINE__, sizeof(array))

/*
Retrieves the allocator

Parameters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
file_name    : The name of path of the source file which calls the function. For debugging purpose.
line_number  : The line of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of dynamic_array_type_. For debugging purpose.

Return value:
A pointer to the allocator used by the dynamic array. DO NOT modify any function pointer member of the allocator.
*/
const dynamic_array_allocator_type*
dynamic_array_get_allocator_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_get_allocator(array) \
	dynamic_array_get_allocator_(&(array), __FILE__, (size_t)__LINE__, sizeof(array))

/*
Checks the dynamic array for any error. The returned error is the first error detected.

Parameters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
file_name    : The name of path of the source file which calls the function. For debugging purpose.
line_number  : The line of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of dynamic_array_type_. For debugging purpose.

Return value: The first error detected.
*/
dynamic_array_error_type
dynamic_array_check_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_check(array) \
	dynamic_array_check_(&(array), __FILE__, (size_t)__LINE__, sizeof(array))

/*
Returns the number of elements that can be stored without reallocation

Parameters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
file_name    : The name of path of the source file which calls the function. For debugging purpose.
line_number  : The line of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of dynamic_array_type_. For debugging purpose.

Return value:
The number of elements that can be stored without reallocation
*/
size_t dynamic_array_capacity_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_capacity(array) \
	dynamic_array_capacity_(&(array), __FILE__, (size_t)__LINE__, sizeof(array))

/*
Returns the actual number of elements of the dynamic array

Parameters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
file_name    : The name of path of the source file which calls the function. For debugging purpose.
line_number  : The line of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of dynamic_array_type_. For debugging purpose.

Return value:
The number of elements in the dynamic array
*/
size_t dynamic_array_size_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_size(array) \
	dynamic_array_size_(&(array), __FILE__, (size_t)__LINE__, sizeof(array))

#define dynamic_array_length(array) dynamic_array_size(array)

/*
Returns a pointer to an element of the array based on the given index.
The pointer is a void pointer and must be cast to the proper type of each element.
NOTE: Do not call this function directly. Use the provided macro dynamic_array_element to access an array element.

Parameters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
index        : An array index which should be less than the number of array elements.
element_size : The number of bytes of each element. The value will be compared with the element size stored internally.
file_name    : The name of path of the source file which calls the function. For debugging purpose.
line_number  : The line of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of dynamic_array_type_. For debugging purpose.

Return value:
A pointer to an element in the internal buffer.
*/
void *dynamic_array_element_ptr_(
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

Parameters
dynamic_array       : A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
index               : The index which corresponds to the position where the first new element is to be added.
ptr_to_first_element: A pointer to the first element to be added.
number_of_elements  : The number of elements to be added.
element_size        : The number of bytes of each element. The value will be compared with the element size stored internally.
file_name           : The name or path of the source file which calls the function. For debugging purpose.
line_number         : The line number of the source file at which the function is called. For debugging purpose.
struct_size         : The number of bytes of a dynamic_array_type_. For debugging purpose.

Return value: None.

Possible errors and reasons:
1. dynamic_array_error_memory_reallocation_failure: No enough memory for reallocation.
2. Other errors in the dynamic array data structure.
*/
void dynamic_array_add_elements_at_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_add_element_at_index(type, array, index, element) \
	do { \
		type tmp = element; \
		dynamic_array_add_elements_at_index_(&(array), index, &tmp, 1U, sizeof(tmp), \
			 __FILE__, (size_t)__LINE__, sizeof(array)); \
	} while (0)

#define dynamic_array_add_elements_at_index(type, array, index, elements, element_count) \
	do { \
		assert(sizeof(type) == sizeof((elements)[0])); \
		dynamic_array_add_elements_at_index_(&(array), index, elements, element_count, sizeof((elements)[0]), \
			__FILE__, (size_t)__LINE__, sizeof(array)); \
	} while (0)

#define dynamic_array_append_element(type, array, element) \
	do { \
		type tmp = element; \
		dynamic_array_add_elements_at_index_(&(array), dynamic_array_size(array), &tmp, 1U, sizeof(tmp), \
			__FILE__, (size_t)__LINE__, sizeof(array)); \
	} while (0)

#define dynamic_array_push_back(type, array, element) dynamic_array_append_element(type, array, element)

#define dynamic_array_append_elements(type, array, elements, element_count) \
	do { \
		assert(sizeof(type) == sizeof((elements)[0])); \
		dynamic_array_add_elements_at_index_(&(array), dynamic_array_size(array), elements, element_count, sizeof((elements)[0]), \
			__FILE__, (size_t)__LINE__, sizeof(array)); \
	} while (0)

/*
Removes elements start from the given index
The specified number of elements to be removed can larger than the actual number of  elements that are available.
Only the available elements will be removed.
The function will not perform any reallocation.

Parameters
dynamic_array     : A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
index             : The index which corresponds to the position of the first element to be removed.
output buffer     : A pointer to the first element of an external buffer to store the removed elements.
                    Can be NULL if the removed elements need not be stored in any external buffer.
number_of_elements: The number of elements to be removed.
element_size      : The number of bytes of each element. The value will be compared with the element size stored internally.
file_name         : The name or path of the source file which calls the function. For debugging purpose.
line_number       : The line number of the source file at which the function is called. For debugging purpose.
struct_size       : The number of bytes of a dynamic_array_type_. For debugging purpose.

Return value: None.
*/
void dynamic_array_remove_elements_starting_from_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_remove_element_at_index(type, array, index) \
	dynamic_array_remove_elements_starting_from_index_(&(array), index, NULL, 1U, sizeof(type), \
		__FILE__, (size_t)__LINE__, sizeof(array))

#define dynamic_array_remove_elements_starting_from_index(type, array, index, number_of_elements) \
	dynamic_array_remove_elements_starting_from_index_(&(array), index, NULL, number_of_elements, sizeof(type), \
		__FILE__, (size_t)__LINE__, sizeof(array))

#define dynamic_array_move_elements_starting_from_index_to_buffer(type, array, index, buffer, number_of_elements) \
	do { \
		assert(buffer != NULL); \
		assert(sizeof(type) == sizeof((buffer)[0])); \
		dynamic_array_remove_elements_starting_from_index_(&(array), index, buffer, number_of_elements, sizeof((buffer)[0]), \
			__FILE__, (size_t)__LINE__, sizeof(array)); \
	} while (0)

#define dynamic_array_pop_back(type, array, variable) \
	do { \
		size_t last_element_index = 0U, array_length = 0U; \
		assert(sizeof(type) == sizeof(variable)); \
		array_length = dynamic_array_size(array); \
		assert(array_length >= 1U); \
		last_element_index = (array_length >= 1U) ? (array_length - 1U) : 0U; \
		dynamic_array_remove_elements_starting_from_index_(&(array), last_element_index, &(variable), 1U, sizeof(variable), \
			__FILE__, (size_t)__LINE__, sizeof(array)); \
	} while (0)

/*
Changes the size of the array.
If the new size is larger than the old size, reallocation may be performed and all new elements are zero initialized.
If the new size is smaller than the old size, there will be no reallocation. Old elements which are no longer valid will be zeroed.

Parameters
dynamic_array: A pointer to a valid dynamic_array_type_ variable. Must not be a null pointer.
new size     : The new number of array elements.
element_size : The number of bytes of each element. The value will be compared with the element size stored internally.
file_name    : The name or path of the source file which calls the function. For debugging purpose.
line_number  : The line number of the source file at which the function is called. For debugging purpose.
struct_size  : The number of bytes of a dynamic_array_type_. For debugging purpose.

Return value: None.
*/
void dynamic_array_resize_(
	dynamic_array_type_ *dynamic_array,
	size_t new_size,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
);

#define dynamic_array_resize(type, array, new_size) \
	dynamic_array_resize_(&(array), new_size, sizeof(type), __FILE__, (size_t)__LINE__, sizeof(array))

#ifdef __cplusplus
}
#endif

#endif
