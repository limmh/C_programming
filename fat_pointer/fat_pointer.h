#ifndef FAT_POINTER_H
#define FAT_POINTER_H

#include "static_assert.h"
#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* opaque fat pointer */
typedef struct fat_pointer_type_
{
	size_t do_not_access_directly[4];
} fat_pointer_type_;

/* For type annotation, 'type' refers to the type of each element being referenced */
#define fat_pointer_type(type) fat_pointer_type_

typedef enum fat_pointer_error_type
{
	fat_pointer_error_none = 0,
	fat_pointer_error_null_pointer_exception,
	fat_pointer_error_no_pointer,
	fat_pointer_error_incorrect_capacity,
	fat_pointer_error_incorrect_element_size,
	fat_pointer_error_index_out_of_range,
	fat_pointer_error_element_size_mismatch,
	fat_pointer_error_addition_overflow_detected,
	fat_pointer_error_multiplication_overflow_detected,
	fat_pointer_error_no_source_elements,
	fat_pointer_error_no_enough_capacity,
	fat_pointer_error_too_many_elements_to_remove
} fat_pointer_error_type;

typedef struct fat_pointer_debug_info_type
{
	const char *file_name;
	size_t info_1;
	size_t info_2;
	int line_number;
	fat_pointer_error_type error;
} fat_pointer_debug_info_type;

typedef void (*fat_pointer_error_reporting_handler_type)(fat_pointer_debug_info_type);

/*
Sets an error reporting handler. If no error reporting handler is set, the default report handler is used.

Parameter
error_reporting_handler: Function pointer to a custom error reporting handler

Return value: The previous error reporting handler
*/
fat_pointer_error_reporting_handler_type
fat_pointer_set_report_handler(fat_pointer_error_reporting_handler_type error_reporting_handler);

typedef void (*fat_pointer_exception_handler_type)(fat_pointer_error_type);

/*
Sets an exception handler. There is no exception handler by default.

Parameter
exception_handler: Function pointer to a custom exception handler

Return value: The previous exception handler.
*/
fat_pointer_exception_handler_type
fat_pointer_set_exception_handler(fat_pointer_exception_handler_type exception_handler);

/*
Creates an opaque fat pointer from a non-owning pointer and other parameters.

Parameters
ptr         : The non-owning pointer. Must not be a null pointer.
capacity    : The maximum number of elements allowed. Must not exceed the actual number of elements.
initial_size: The initial length. Must not exceed the capacity.
element_size: The size of each element. Must not be zero.
file_name   : The name or path of the source file which calls the function, For debugging purpose.
line_number : The line number of the source file at which the function is called. For debugging purpose.

Return value: An opaque fat pointer of type fat_pointer_type_.
*/
fat_pointer_type_
fat_pointer_create_(void *ptr, size_t capacity, size_t initial_size, size_t element_size, const char *file_name, int line_number);

#define fat_pointer_create(type, ptr, capacity, initial_length) \
	( assert(sizeof(type) == sizeof(*(ptr))), fat_pointer_create_(ptr, capacity, initial_length, sizeof(type), __FILE__, __LINE__) )

/*
Destroys a fat pointer without modifying the data it references.

Parameters
fatptr     : Opaque fat pointer. Must not be a null pointer.
file_name  : The name or path of the source file which calls the function, For debugging purpose.
line_number: The line number of the source file at which the function is called. For debugging purpose.

Return value: None
*/
void fat_pointer_destroy_(fat_pointer_type_ *fatptr, const char *file_name, int line_number);

#define fat_pointer_destroy(fatptr) fat_pointer_destroy_(&(fatptr), __FILE__, __LINE__)

/*
Zeros all the valid elements referenced by a fat pointer.

Parameters
fatptr     : Opaque fat pointer. Must not be a null pointer.
file_name  : The name or path of the source file which calls the function, For debugging purpose.
line_number: The line number of the source file at which the function is called. For debugging purpose.

Return value: None
*/
void fat_pointer_zero_(fat_pointer_type_ *fatptr, const char *file_name, int line_number);

#define fat_pointer_zero(fatptr) fat_pointer_zero_(&(fatptr), __FILE__, __LINE__)

/*
Returns the maximum number of elements referenced by an opaque fat pointer

Parameters
fatptr     : Opaque fat pointer. Must not be a null pointer.
file_name  : The name or path of the source file which calls the function, For debugging purpose.
line_number: The line number of the source file at which the function is called. For debugging purpose.

Return value: Maximum number of elements allowed
*/
size_t fat_pointer_capacity_(const fat_pointer_type_ *p_fatptr, const char *file_name, int line_number);

#define fat_pointer_capacity(fatptr) fat_pointer_capacity_(&(fatptr), __FILE__, __LINE__)

/*
Returns the number of valid elements referenced by an opaque fat pointer
May not be the same as the maximum mumber of elements

Parameters
fatptr     : Opaque fat pointer. Must not be a null pointer.
file_name  : The name or path of the source file which calls the function, For debugging purpose.
line_number: The line number of the source file at which the function is called. For debugging purpose.

Return value: The number of valid elements, i.e. elements in use
*/
size_t fat_pointer_size_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number);

#define fat_pointer_size(fatptr) fat_pointer_size_(&(fatptr), __FILE__, __LINE__)
#define fat_pointer_length(fatptr) fat_pointer_size(fatptr)

/*
Returns the size of each element referenced by an opaque fat pointer

Parameters
fatptr     : Opaque fat pointer. Must not be a null pointer.
file_name  : The name or path of the source file which calls the function, For debugging purpose.
line_number: The line number of the source file at which the function is called. For debugging purpose.

Return value: The size of each element
*/
size_t fat_pointer_element_size_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number);

#define fat_pointer_element_size(fatptr) fat_pointer_element_size_(&(fatptr), __FILE__, __LINE__)

/*
Returns the address of an element referenced by an opaque fat pointer

Parameters
fatptr      : Opaque fat pointer. Must not be a null pointer.
index       : The index of an element. Must not exceed the number of valid elements (elements in use).
element_size: The size of each element. Must match the element size specified when the fat pointer was first initialized.
file_name   : The name or path of the source file which calls the function, For debugging purpose.
line_number : The line number of the source file at which the function is called. For debugging purpose.

Return value: A void pointer referring to an element referenced by the fat pointer

Note: DO NOT call the function directly but use the provided function macros for element access.
*/
void *fat_pointer_element_ptr_(
	const fat_pointer_type_ *fatptr,
	size_t index,
	size_t element_size,
	const char *file_name,
	int line_number
);

/* Access the element via a pointer */
#define fat_pointer_element_ptr(type, fatptr, index) \
	( (type*) fat_pointer_element_ptr_(&(fatptr), index, sizeof(type), __FILE__, __LINE__) )


/* Access the element as an l-value, the element can be modified */
#define fat_pointer_element(type, fatptr, index) \
	(*fat_pointer_element_ptr(type, fatptr, index))

/*
Adds elements to the array referenced by an opaque fat pointer

Parameters
fatptr              : Opaque fat pointer. Must not be a null pointer.
index               : The index to insert elements. (index + number of elements to be inserted) must not exceed the actual capacity.
ptr_to_first_element: A pointer to the first element in the source buffer to be copied.
number_of_elements  : The number of elements to be copied from the source buffer.
element_size        : The size of each element. Must match the element size specified when the fat pointer was first initialized.
file_name           : The name or path of the source file which calls the function, For debugging purpose.
line_number         : The line number of the source file at which the function is called. For debugging purpose.

Return value: An error code

Notes:
- DO NOT call the function directly but use the provided function macros.
- If there is an error, the insertion operation WILL NOT be performed.
*/
fat_pointer_error_type
fat_pointer_add_elements_at_index_(
	fat_pointer_type_ *fatptr,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number
);

#define fat_pointer_add_elements_at_index(type, fatptr, index, elements, element_count) \
	do { \
		STATIC_ASSERT(sizeof(type) == sizeof((elements)[0]), "Mismatch between type size and element size."); \
		fat_pointer_add_elements_at_index_(&(fatptr), index, elements, element_count, sizeof((elements)[0]), __FILE__, __LINE__); \
	} while (0)

#define fat_pointer_add_element_at_index(type, fatptr, index, element) \
	do { \
		type tmp = element; \
		fat_pointer_add_elements_at_index_(&(fatptr), index, &tmp, 1U, sizeof(tmp), __FILE__, __LINE__); \
	} while (0)

#define fat_pointer_append_elements(type, fatptr, elements, element_count) \
	do { \
		STATIC_ASSERT(sizeof(type) == sizeof((elements)[0]), "Mismatch between type size and element size."); \
		fat_pointer_add_elements_at_index_(&(fatptr), fat_pointer_length(fatptr), elements, element_count, sizeof((elements)[0]), __FILE__, __LINE__); \
	} while (0)

#define fat_pointer_append_element(type, fatptr, element) \
	do { \
		type tmp = element; \
		fat_pointer_add_elements_at_index_(&(fatptr), fat_pointer_length(fatptr), &tmp, 1U, sizeof(tmp), __FILE__, __LINE__); \
	} while (0)

#define fat_pointer_push_back(type, fatptr, element)  fat_pointer_append_element(type, fatptr, element)

/*
Removes elements from the array referenced by an opaque fat pointer

Parameters
fatptr            : Opaque fat pointer. Must not be a null pointer.
index             : The index of the first element to be removed. Must not exceed the number of valid elements (elements in use).
output_buffer     : A pointer to the first element in the destination buffer. Optional, can be a null pointer.
number_of_elements: The number of elements to be removed. Must not exceed the number of elements between index and the final element.
                    Must not exceed the maximum number of elements of the output buffer.
element_size      : The size of each element. Must match the element size specified when the fat pointer was first initialized.
file_name         : The name or path of the source file which calls the function, For debugging purpose.
line_number       : The line number of the source file at which the function is called. For debugging purpose.

Return value: An error code

Notes:
- DO NOT call the function directly but use the provided function macros.
- If there is an error, the removal operation WILL NOT be performed.
*/
fat_pointer_error_type
fat_pointer_remove_elements_starting_from_index_(
	fat_pointer_type_ *fatptr,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number
);

#define fat_pointer_remove_elements_starting_from_index(type, fatptr, index, number_of_elements) \
	fat_pointer_remove_elements_starting_from_index_(&(fatptr), index, NULL, number_of_elements, sizeof(type), __FILE__, __LINE__)

#define fat_pointer_move_elements_starting_from_index_to_buffer(type, fatptr, index, buffer, number_of_elements) \
	do { \
		STATIC_ASSERT(sizeof(type) == sizeof((buffer)[0]), "Mismatch between type size and element size."); \
		assert(buffer != NULL); \
		fat_pointer_remove_elements_starting_from_index_(&(fatptr), index, buffer, number_of_elements, sizeof((buffer)[0])); \
	} while (0)

#define fat_pointer_remove_element_at_index(type, fatptr, index) \
	fat_pointer_remove_elements_starting_from_index_(&(fatptr), index, NULL, 1U, sizeof(type), __FILE__, __LINE__)

#define fat_pointer_pop_back(type, fatptr, variable) \
	do { \
		STATIC_ASSERT(sizeof(type) == sizeof(variable), "Mismatch between type size and variable size."); \
		size_t last_element_index = 0U, fatptr_length = 0U; \
		fatptr_length = fat_pointer_length(fatptr); \
		assert(fatptr_length >= 1U); \
		last_element_index = (fatptr_length >= 1U) ? (fatptr_length - 1U) : 0U; \
		fat_pointer_remove_elements_starting_from_index_(&(fatptr), last_element_index, &(variable), 1U, sizeof(variable), __FILE__, __LINE__); \
	} while (0)

/*
Resizes the array referenced by an opaque fat pointer

Parameters
fatptr      : Opaque fat pointer. Must not be a null pointer.
new_size    : The new number of valid elements (elements in use). Must not exceed the maximum number of elements of the output buffer.
element_size: The size of each element. Must match the element size specified when the fat pointer was first initialized.
file_name   : The name or path of the source file which calls the function, For debugging purpose.
line_number : The line number of the source file at which the function is called. For debugging purpose.

Return value: An error code

Notes:
- DO NOT call the function directly but use the provided function macro.
- If there is an error, the resize operation WILL NOT be performed.
*/
fat_pointer_error_type
fat_pointer_resize_(
	fat_pointer_type_ *fatptr,
	size_t new_size,
	size_t element_size,
	const char *file_name,
	int line_number
);

#define fat_pointer_resize(type, fatptr, new_size) \
	fat_pointer_resize_(&(fatptr), new_size, sizeof(type), __FILE__, __LINE__)

#ifdef __cplusplus
}
#endif

#endif
