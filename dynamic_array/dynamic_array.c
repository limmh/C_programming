#include "dynamic_array.h"
#include "Boolean_type.h"
#include "macro_alignof.h"
#include "static_assert.h"

#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Notes:
- All runtime assertions (assert) can be disabled by defining NDEBUG when compiling the source file, e.g. gcc -DNDEBUG -c dynamic_array.c
- Code for runtime checks can be disabled by defining DYNAMIC_ARRAY_NO_RUNTIME_CHECKS when compiling the source file, e.g. gcc -DDYNAMIC_ARRAY_NO_RUNTIME_CHECKS -c dynamic_array.c
- Avoid changing size variables from size_t to a signed integer type
*/

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t) -1)
#endif

typedef struct {
	size_t capacity;
	size_t number_of_elements;
	size_t element_size_in_bytes;
	void *ptr; /* points to the first element */
	dynamic_array_allocator_type *allocator; /* must have a longer lifetime than the dynamic array */
} dynamic_array_internal_type;

#if !defined(__cplusplus) && defined(__STDC_VERSION__) and (__STDC_VERSION__ >= 199901L)
#define INTERNAL_DEBUG_INFO() {.file_name = __FILE__, .line_number = (size_t)__LINE__, .struct_size = sizeof(dynamic_array_internal_type)}
#else
#define INTERNAL_DEBUG_INFO() {__FILE__, (size_t)__LINE__, sizeof(dynamic_array_internal_type)}
#endif

STATIC_ASSERT(sizeof(unsigned char) == 1U, "The size of a byte must be one.");
STATIC_ASSERT(sizeof(size_t) == sizeof(void*), "size_t and pointer type must have the same size.");
STATIC_ASSERT(sizeof(dynamic_array_type_) == sizeof(dynamic_array_internal_type), "The public data type and the internal data type must have the same size.");
STATIC_ASSERT(ALIGNOF(dynamic_array_type_) == ALIGNOF(dynamic_array_internal_type), "The public data type and the internal data type must have the same memory alignment.");

static dynamic_array_allocator_type default_allocator = {&malloc, &realloc, &free};

static void dynamic_array_report_error_default(dynamic_array_error_type, dynamic_array_debug_info_type, dynamic_array_debug_info_type, size_t, size_t);
static void (*s_report_error_funcptr)(dynamic_array_error_type, dynamic_array_debug_info_type, dynamic_array_debug_info_type, size_t, size_t) = &dynamic_array_report_error_default;
static void (*s_exception_handler_funcptr)(dynamic_array_error_type) = NULL;

static void dynamic_array_report_error_default(
	dynamic_array_error_type error,
	dynamic_array_debug_info_type debug_info,
	dynamic_array_debug_info_type internal_debug_info,
	size_t info1, size_t info2
)
{
	FILE *output = stdout;
	const unsigned long info_1 = (unsigned long) info1;
	const unsigned long info_2 = (unsigned long) info2;
	fprintf(output, "%s (line %lu): ", internal_debug_info.file_name, (unsigned long) internal_debug_info.line_number);
	switch (error) {
	case dynamic_array_error_none:
		fprintf(output, "No error.\n");
		break;
	case dynamic_array_error_null_pointer_exception:
		fprintf(output, "The pointer to the data structure is null.\n");
		break;
	case dynamic_array_error_struct_size_mismatch:
		fprintf(output, "The struct size (%lu) is not the same as the internal struct size (%lu).\n", info_1, info_2);
		break;
	case dynamic_array_error_no_buffer:
		fprintf(output, "There is no valid buffer for the internal array.\n");
		break;
	case dynamic_array_error_incorrect_capacity:
		fprintf(output, "The capacity of the array (%lu) is incorrect.\n", info_1);
		break;
	case dynamic_array_error_incorrect_element_size:
		fprintf(output, "The element size of the array (%lu) is incorrect.\n", info_1);
		break;
	case dynamic_array_error_index_out_of_range:
		fprintf(output, "The index (%lu) is out of range (number of array elements = %lu).\n", info_1, info_2);
 		break;
	case dynamic_array_error_element_size_mismatch:
		fprintf(output, "The size of a source element (%lu) is not the same as that of an array element (%lu).\n", info_1, info_2);
		break;
	case dynamic_array_error_calculation_overflow_detected:
		fprintf(output,  "The calculation overflows. Operand 1: %lu, Operand 2: %lu\n", info_1, info_2);
		break;
	case dynamic_array_error_no_allocator:
		fprintf(output, "There is no allocator.\n");
		break;
	case dynamic_array_error_memory_allocation_failure:
		fprintf(output, "Memory allocation failed. Number of bytes requested: %lu\n", info_1);
		break;
	case dynamic_array_error_memory_reallocation_failure:
		fprintf(output, "Memory reallocation failed. Number of bytes requested: %lu\n", info_1);
		break;
	case dynamic_array_error_no_memory_allocation_function:
		fprintf(output, "The memory allocation function is not available.\n");
		break;
	case dynamic_array_error_no_memory_deallocation_function:
		fprintf(output, "The memory deallocation function is not available.\n");
		break;
	default:
		fprintf(output, "Unknown error (%d)\n", (int) error);
		break;
	}
	if (error != dynamic_array_error_none) {
		fprintf(output, "%s (line %lu): Please refer to the code here for more details.\n",
			debug_info.file_name, (unsigned long) debug_info.line_number);
	}
}

static void dynamic_array_report_error(
	dynamic_array_error_type error,
	dynamic_array_debug_info_type debug_info,
	dynamic_array_debug_info_type internal_debug_info,
	size_t info1,
	size_t info2
)
{
	if (s_report_error_funcptr != NULL) {
		s_report_error_funcptr(error, debug_info, internal_debug_info, info1, info2);
	} else {
		dynamic_array_report_error_default(error, debug_info, internal_debug_info, info1, info2);
	}
}

static void dynamic_array_handle_exception(dynamic_array_error_type error)
{
	if (s_exception_handler_funcptr != NULL) {
		s_exception_handler_funcptr(error);
	}
}

static void dynamic_array_terminate(void)
{
	exit(EXIT_FAILURE);
}

static dynamic_array_error_type
dynamic_array_check_and_report_error(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info,
	dynamic_array_debug_info_type internal_debug_info
)
{
	const dynamic_array_internal_type *array = NULL;
	dynamic_array_error_type error = dynamic_array_error_none;
	assert(dynamic_array != NULL);
	if (dynamic_array == NULL) {
		error = dynamic_array_error_null_pointer_exception;
		dynamic_array_report_error(error, debug_info, internal_debug_info, 0U, 0U);
		return error;
	}
	if (debug_info.struct_size != sizeof(dynamic_array_internal_type)) {
		error = dynamic_array_error_struct_size_mismatch;
		dynamic_array_report_error(error, debug_info, internal_debug_info, debug_info.struct_size, sizeof(dynamic_array_internal_type));
		return error;
	}

	array = (const dynamic_array_internal_type*) dynamic_array;
	if (array->ptr == NULL) {
		error = dynamic_array_error_no_buffer;
		dynamic_array_report_error(error, debug_info, internal_debug_info, 0U, 0U);
	} else if (array->capacity < array->number_of_elements) {
		error = dynamic_array_error_incorrect_capacity;
		dynamic_array_report_error(error, debug_info, internal_debug_info, array->capacity, array->number_of_elements);
	} else if (array->element_size_in_bytes < 1U) {
		error = dynamic_array_error_incorrect_element_size;
		dynamic_array_report_error(error, debug_info, internal_debug_info, array->element_size_in_bytes, 0U);
	} else if (array->allocator == NULL) {
		error = dynamic_array_error_no_allocator;
		dynamic_array_report_error(error, debug_info, internal_debug_info, 0U, 0U);
	} else if (array->allocator != NULL) {
		if (array->allocator->allocate_funcptr == NULL) {
			error = dynamic_array_error_no_memory_allocation_function;
			dynamic_array_report_error(error, debug_info, internal_debug_info, 0U, 0U);
		} else if (array->allocator->deallocate_funcptr == NULL) {
			error = dynamic_array_error_no_memory_deallocation_function;
			dynamic_array_report_error(error, debug_info, internal_debug_info, 0U, 0U);
		}
	}
	return error;
}

void dynamic_array_set_exception_handler(
	void (*exception_handler)(dynamic_array_error_type)
)
{
	s_exception_handler_funcptr = exception_handler;
}

void dynamic_array_set_error_reporting_handler(
	void (*report_error_funcptr)(dynamic_array_error_type, dynamic_array_debug_info_type, dynamic_array_debug_info_type, size_t, size_t)
)
{
	s_report_error_funcptr = report_error_funcptr;
}

dynamic_array_error_type
dynamic_array_check_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	const dynamic_array_internal_type *array = NULL;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;
	assert(dynamic_array != NULL);
	if (dynamic_array == NULL) {
		return dynamic_array_error_null_pointer_exception;
	}
	if (debug_info.struct_size != sizeof(dynamic_array_internal_type)) {
		return dynamic_array_error_struct_size_mismatch;
	}
	array = (const dynamic_array_internal_type*) dynamic_array;
	if (array->ptr == NULL) {
		return dynamic_array_error_no_buffer;
	} else if (array->capacity < array->number_of_elements) {
		return dynamic_array_error_incorrect_capacity;
	} else if (array->element_size_in_bytes < 1U) {
		return dynamic_array_error_incorrect_element_size;
	} else if (array->allocator == NULL) {
		return dynamic_array_error_no_allocator;
	} else if (array->allocator != NULL) {
		if (array->allocator->allocate_funcptr == NULL) {
			return dynamic_array_error_no_memory_allocation_function;
		} else if (array->allocator->deallocate_funcptr == NULL) {
			return dynamic_array_error_no_memory_deallocation_function;
		}
	}
	return dynamic_array_error_none;
}

dynamic_array_type_
dynamic_array_create_(
	size_t initial_size,
	size_t element_size,
	dynamic_array_allocator_type *allocator,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	size_t initial_capacity = 1U;
	size_t total_bytes = 0U;
	void *ptr = NULL;
	Boolean_type multiplication_overflow_detected = Boolean_false;
	dynamic_array_internal_type array = {0U};
	dynamic_array_type_ dyn_array = {0U};
	size_t max_allowed_element_size = 0U;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;

	assert(element_size > 0U);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size < 1U) {
		const dynamic_array_error_type error = dynamic_array_error_incorrect_element_size;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, element_size, 0U);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	if (initial_size == SIZE_MAX) {
		initial_capacity = initial_size;
	}
	while (initial_capacity < initial_size) {
		initial_capacity += initial_capacity;
	}

	max_allowed_element_size = SIZE_MAX / initial_capacity;
	multiplication_overflow_detected = not (max_allowed_element_size > element_size);
	if (multiplication_overflow_detected and initial_capacity > initial_size) {
		initial_capacity = (initial_size < 1U) ? 1U : initial_size;
		max_allowed_element_size = SIZE_MAX / initial_capacity;
		multiplication_overflow_detected = not (max_allowed_element_size > element_size);
	}
	assert(not multiplication_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (multiplication_overflow_detected) {
		const dynamic_array_error_type error = dynamic_array_error_calculation_overflow_detected;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, element_size, initial_capacity);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	if (allocator != NULL) {
		const Boolean_type use_allocator = (allocator->allocate_funcptr != NULL and allocator->deallocate_funcptr != NULL);

		assert(allocator->allocate_funcptr != NULL);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		if (allocator->allocate_funcptr == NULL) {
			const dynamic_array_error_type error = dynamic_array_error_no_memory_allocation_function;
			const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
			dynamic_array_report_error(error, debug_info, internal_debug_info, 0u, 0u);
			dynamic_array_handle_exception(error);
			dynamic_array_terminate();
		}
#endif
		assert(allocator->deallocate_funcptr != NULL);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		if (allocator->deallocate_funcptr == NULL) {
			const dynamic_array_error_type error = dynamic_array_error_no_memory_deallocation_function;
			const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
			dynamic_array_report_error(error, debug_info, internal_debug_info, 0u, 0u);
			dynamic_array_handle_exception(error);
			dynamic_array_terminate();
		}
#endif
		if (not use_allocator) {
			allocator = &default_allocator;
		}
	} else {
		allocator = &default_allocator;
	}

	assert(allocator != NULL);
	total_bytes = initial_capacity * element_size;
	ptr = allocator->allocate_funcptr(total_bytes);
	if (ptr != NULL) {
		memset(ptr, 0, total_bytes);
	} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		const dynamic_array_error_type error = dynamic_array_error_memory_allocation_failure;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, total_bytes, 0U);
		dynamic_array_handle_exception(error);
#endif
		initial_capacity = initial_size = 0U;
	}

	array.capacity = initial_capacity;
	array.number_of_elements = initial_size;
	array.element_size_in_bytes = element_size;
	array.ptr = ptr;
	array.allocator = allocator;
	memcpy(&dyn_array, &array, sizeof(array));
	return dyn_array;
}

void
dynamic_array_delete_(
	dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type debug_info
)
{
	dynamic_array_internal_type *array = NULL;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	const dynamic_array_error_type error = 
		dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none and error != dynamic_array_error_no_buffer) {
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif
	array = (dynamic_array_internal_type*) dynamic_array;
	array->capacity = 0U;
	array->number_of_elements = 0U;
	array->element_size_in_bytes = 0U;
	assert(array->allocator != NULL and array->allocator->deallocate_funcptr != NULL);
	if (array->ptr != NULL and array->allocator != NULL and array->allocator->deallocate_funcptr != NULL) {
		array->allocator->deallocate_funcptr(array->ptr);
	}
	array->ptr = NULL;
	array->allocator = NULL;
}

const dynamic_array_allocator_type*
dynamic_array_get_allocator_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	dynamic_array_error_type error = dynamic_array_error_none;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;
	error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		return NULL;
	}
#endif

	return ((const dynamic_array_internal_type*) dynamic_array)->allocator;
}

size_t
dynamic_array_capacity_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	dynamic_array_error_type error = dynamic_array_error_none;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;
	error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		return 0U;
	}
#endif
	return ((const dynamic_array_internal_type*) dynamic_array)->capacity;
}

size_t
dynamic_array_size_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	dynamic_array_error_type error = dynamic_array_error_none;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;
	error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		return 0U;
	}
#endif
	return ((const dynamic_array_internal_type*) dynamic_array)->number_of_elements;
}

void *
dynamic_array_element_ptr_(
	const dynamic_array_type_ *dynamic_array,
	size_t index,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	const dynamic_array_internal_type *array = NULL;
	size_t offset = 0U;
	unsigned char *ptr = NULL;
	dynamic_array_debug_info_type debug_info = {0};
	dynamic_array_error_type error = dynamic_array_error_none;

#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;
	error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif
	array = (const dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size_in_bytes);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size_in_bytes) {
		const dynamic_array_error_type error = dynamic_array_error_element_size_mismatch;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, element_size, array->element_size_in_bytes);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	assert(index < array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index >= array->number_of_elements) {
		const dynamic_array_error_type error = dynamic_array_error_index_out_of_range;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, index, array->number_of_elements);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	offset = index * array->element_size_in_bytes;
	ptr = (unsigned char*) array->ptr;
	return &ptr[offset];
}

void
dynamic_array_add_elements_at_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	dynamic_array_debug_info_type debug_info
)
{
	size_t new_number_of_elements = 0U; 
	dynamic_array_internal_type *array = NULL;

#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	const dynamic_array_error_type error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	assert(ptr_to_first_element != NULL);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (ptr_to_first_element == NULL) {
		const dynamic_array_error_type error = dynamic_array_error_null_pointer_exception;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, 0U, 0U);
		dynamic_array_terminate();
	}
#endif

	array = (dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size_in_bytes);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size_in_bytes) {
		const dynamic_array_error_type error = dynamic_array_error_element_size_mismatch;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, element_size, array->element_size_in_bytes);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	assert(index <= array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index > array->number_of_elements) {
		const dynamic_array_error_type error = dynamic_array_error_index_out_of_range;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, index, array->number_of_elements);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	new_number_of_elements = array->number_of_elements + number_of_elements;
	assert(new_number_of_elements >= number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (new_number_of_elements < number_of_elements) {
		const dynamic_array_error_type error = dynamic_array_error_calculation_overflow_detected;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, array->number_of_elements, number_of_elements);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	if (new_number_of_elements > array->capacity) {
		void *ptr = NULL;
		size_t new_byte_count = 0U;
		const size_t max_allowed_capacity = SIZE_MAX / array->element_size_in_bytes;
		size_t new_capacity = array->capacity;

		while (new_capacity < new_number_of_elements) {
			Boolean_type multiplication_overflow_detected = Boolean_false;
			new_capacity += new_capacity;
			multiplication_overflow_detected = not (max_allowed_capacity > new_capacity);
			assert(not multiplication_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			if (multiplication_overflow_detected) {
				const dynamic_array_error_type error = dynamic_array_error_calculation_overflow_detected;
				const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
				dynamic_array_report_error(error, debug_info, internal_debug_info, new_capacity, array->element_size_in_bytes);
				dynamic_array_handle_exception(error);
				dynamic_array_terminate();
			}
#endif
		}

		new_byte_count = new_capacity * array->element_size_in_bytes;
		if (array->allocator->reallocate_funcptr != NULL) {
			ptr = array->allocator->reallocate_funcptr(array->ptr, new_byte_count);
		} else {
			ptr = array->allocator->allocate_funcptr(new_byte_count);
		}
		if (ptr != NULL) {
			if (array->allocator->reallocate_funcptr == NULL) {
				const size_t number_of_bytes_occupied = array->number_of_elements * array->element_size_in_bytes;
				memcpy(ptr, array->ptr, number_of_bytes_occupied);
				memset(array->ptr, 0, number_of_bytes_occupied);
				array->allocator->deallocate_funcptr(array->ptr);
			}
			array->ptr = ptr;
			array->capacity = new_capacity;
		} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			const dynamic_array_error_type error = dynamic_array_error_memory_reallocation_failure;
			const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
			dynamic_array_report_error(error, debug_info, internal_debug_info, array->capacity, new_capacity);
			dynamic_array_handle_exception(error);
#endif
			return;
		}
	}

	if (index == array->number_of_elements) {
		const size_t offset = array->number_of_elements * array->element_size_in_bytes;
		unsigned char *ptr = (unsigned char*) array->ptr;
		const size_t total_bytes_to_copy = number_of_elements * element_size;

		memcpy(&ptr[offset], ptr_to_first_element, total_bytes_to_copy);
		array->number_of_elements = new_number_of_elements;
    	} else if (index < array->number_of_elements) {
		const size_t src_offset = index * array->element_size_in_bytes;
		const size_t dst_offset = (index + number_of_elements) * array->element_size_in_bytes;
		const size_t total_elements_to_move = array->number_of_elements - index;
		const size_t total_bytes_to_move = total_elements_to_move * array->element_size_in_bytes;
		const size_t total_bytes_to_copy = number_of_elements * element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;

		memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		memcpy(&ptr[src_offset], ptr_to_first_element, total_bytes_to_copy);
		array->number_of_elements = new_number_of_elements;
	}
}

void
dynamic_array_remove_elements_starting_from_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	dynamic_array_debug_info_type debug_info
)
{
	dynamic_array_internal_type *array = NULL;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO(); 
	const dynamic_array_error_type error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	array = (dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size_in_bytes);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size_in_bytes) {
		const dynamic_array_error_type error = dynamic_array_error_element_size_mismatch;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, element_size, array->element_size_in_bytes);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	assert(index < array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index >= array->number_of_elements) {
		const dynamic_array_error_type error = dynamic_array_error_index_out_of_range;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, index, array->number_of_elements);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	if (number_of_elements > 0U) {
		unsigned char *ptr = NULL;
		size_t offset = 0U, total_bytes_to_zero = 0U;
		const size_t number_of_elements_from_index_to_last_index = array->number_of_elements - index;
		const size_t actual_number_of_elements_to_remove = (number_of_elements < number_of_elements_from_index_to_last_index) ?
									number_of_elements : number_of_elements_from_index_to_last_index;
		const size_t number_of_elements_to_move = number_of_elements_from_index_to_last_index - actual_number_of_elements_to_remove;

		if (output_buffer != NULL) {
			const size_t total_bytes_to_copy = actual_number_of_elements_to_remove * element_size;
			const size_t src_offset = index * array->element_size_in_bytes;
			unsigned char *src_ptr = ((unsigned char*) array->ptr) + src_offset;
			unsigned char *dst_ptr = (unsigned char*) output_buffer;
			memcpy(dst_ptr, src_ptr, total_bytes_to_copy);
		}

		if (number_of_elements_to_move > 0U) {
			const size_t src_offset = (index + actual_number_of_elements_to_remove) * array->element_size_in_bytes;
			const size_t dst_offset = index * array->element_size_in_bytes;
			const size_t total_bytes_to_move = number_of_elements_to_move * array->element_size_in_bytes;
			unsigned char *ptr = (unsigned char*) array->ptr;
			memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		}

		assert(array->number_of_elements >= actual_number_of_elements_to_remove);
		array->number_of_elements -= actual_number_of_elements_to_remove;
		offset = array->number_of_elements * array->element_size_in_bytes;
		total_bytes_to_zero = actual_number_of_elements_to_remove * array->element_size_in_bytes;
		ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
	}
}

void
dynamic_array_resize_(
	dynamic_array_type_ *dynamic_array,
	size_t new_size,
	size_t element_size,
	dynamic_array_debug_info_type debug_info
)
{
	const size_t new_number_of_elements = new_size;
	dynamic_array_internal_type *array = NULL;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
	const dynamic_array_error_type error = dynamic_array_check_and_report_error(dynamic_array, debug_info, internal_debug_info);
	if (error != dynamic_array_error_none) {
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	array = (dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size_in_bytes);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size_in_bytes) {
		const dynamic_array_error_type error = dynamic_array_error_element_size_mismatch;
		const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
		dynamic_array_report_error(error, debug_info, internal_debug_info, element_size, array->element_size_in_bytes);
		dynamic_array_handle_exception(error);
		dynamic_array_terminate();
	}
#endif

	if (new_number_of_elements > array->number_of_elements) {
		size_t extra_number_of_elements = 0U;
		size_t offset = 0U;
		size_t total_bytes_to_zero = 0U;
		unsigned char *ptr = NULL;

		if (new_number_of_elements > array->capacity) {
			size_t max_allowed_capacity = 0U;
			size_t new_byte_count = 0U;
			void *ptr = NULL;
			size_t new_capacity = array->capacity;

			max_allowed_capacity = SIZE_MAX / array->element_size_in_bytes;
			while (new_capacity < new_number_of_elements) {
				Boolean_type multiplication_overflow_detected = Boolean_false; 
				new_capacity += new_capacity;
				multiplication_overflow_detected = not (max_allowed_capacity > new_capacity);
				assert(not multiplication_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
				if (multiplication_overflow_detected) {
					const dynamic_array_error_type error = dynamic_array_error_calculation_overflow_detected;
					const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
					dynamic_array_report_error(error, debug_info, internal_debug_info, new_capacity, array->element_size_in_bytes);
					dynamic_array_handle_exception(error);
					dynamic_array_terminate();
				}
#endif
			}

			new_byte_count = new_capacity * array->element_size_in_bytes;
			if (array->allocator->reallocate_funcptr != NULL) {
				ptr = array->allocator->reallocate_funcptr(array->ptr, new_byte_count);
			} else {
				ptr = array->allocator->allocate_funcptr(new_byte_count);
			}
			if (ptr != NULL) {
				if (array->allocator->reallocate_funcptr == NULL) {
					const size_t number_of_bytes_occupied = array->number_of_elements * array->element_size_in_bytes;
					memcpy(ptr, array->ptr, number_of_bytes_occupied);
					memset(array->ptr, 0, number_of_bytes_occupied);
					array->allocator->deallocate_funcptr(array->ptr);
				}
				array->ptr = ptr;
				array->capacity = new_capacity;
			} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
				const dynamic_array_error_type error = dynamic_array_error_memory_reallocation_failure;
				const dynamic_array_debug_info_type internal_debug_info = INTERNAL_DEBUG_INFO();
				dynamic_array_report_error(error, debug_info, internal_debug_info, new_capacity, 0U);
				dynamic_array_handle_exception(error);
#endif
				return;
			}
		}

		extra_number_of_elements = new_number_of_elements - array->number_of_elements;
		offset = array->number_of_elements * array->element_size_in_bytes;
		total_bytes_to_zero = extra_number_of_elements * array->element_size_in_bytes;
		ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		array->number_of_elements = new_number_of_elements;
	} else if (new_number_of_elements < array->number_of_elements) {
		const size_t number_of_elements_to_remove = array->number_of_elements - new_number_of_elements;
		const size_t offset = new_number_of_elements * array->element_size_in_bytes;
		const size_t total_bytes_to_zero = number_of_elements_to_remove * array->element_size_in_bytes;
		unsigned char *ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		array->number_of_elements = new_number_of_elements;
	}
}
