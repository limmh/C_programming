#include "dynamic_array.h"
#include "Boolean_type.h"
#include "macro_alignof.h"
#include "static_assert.h"

#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Notes:
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
	size_t element_size; /* number of bytes of each element */
	void *ptr; /* points to the first element */
	dynamic_array_allocator_type *allocator; /* must have a longer lifetime than the dynamic array */
} dynamic_array_internal_type;

STATIC_ASSERT(sizeof(unsigned char) == 1U, "The size of a byte must be one.");
STATIC_ASSERT(sizeof(size_t) == sizeof(void*), "size_t and pointer type must have the same size.");
STATIC_ASSERT(sizeof(dynamic_array_type_) == sizeof(dynamic_array_internal_type), "The public data type and the internal data type must have the same size.");
STATIC_ASSERT(ALIGNOF(dynamic_array_type_) == ALIGNOF(dynamic_array_internal_type), "The public data type and the internal data type must have the same memory alignment.");

static dynamic_array_allocator_type default_allocator = {&malloc, &realloc, &free};

static void dynamic_array_report_error_default(dynamic_array_debug_info_type);
static void (*s_report_error_funcptr)(dynamic_array_debug_info_type) = &dynamic_array_report_error_default;
static void (*s_exception_handler_funcptr)(dynamic_array_error_type) = NULL;

static void dynamic_array_report_error_default(
	dynamic_array_debug_info_type debug_info
)
{
	FILE *output = stdout;
	const char *file_name = (debug_info.file_name != NULL) ? debug_info.file_name : "Unknown file name";
	const char *library_file_name = (debug_info.library_file_name != NULL) ? debug_info.library_file_name : "Unknown library file name";
	const unsigned long info_1 = (unsigned long) debug_info.info_1;
	const unsigned long info_2 = (unsigned long) debug_info.info_2;
	if (debug_info.error != dynamic_array_error_none) {
		fprintf(output, "%s (line %lu): Please refer to the code here for more details.\n",
			file_name, (unsigned long) debug_info.line_number);
	}
	fprintf(output, "%s (line %lu): ", library_file_name, (unsigned long) debug_info.library_line_number);
	switch (debug_info.error) {
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
		fprintf(output, "The capacity of the array (%lu) is incorrect. Number of elements: %lu\n", info_1, info_2);
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
	case dynamic_array_error_addition_overflow_detected:
		fprintf(output,  "Addition overflow detected: operand 1 = %lu, operand 2 = %lu\n", info_1, info_2);
		break;
	case dynamic_array_error_multiplication_overflow_detected:
		fprintf(output, "Multiplication overflow detected: operand 1 = %lu, operand 2 = %lu\n", info_1, info_2);
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
		fprintf(output, "Unknown error (%d)\n", (int) debug_info.error);
		break;
	}
}

static void dynamic_array_report_error(
	dynamic_array_debug_info_type debug_info
)
{
	if (s_report_error_funcptr != NULL) {
		s_report_error_funcptr(debug_info);
	} else {
		dynamic_array_report_error_default(debug_info);
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

static Boolean_type dynamic_array_addition_overflow_detected(size_t a, size_t b)
{
	return (b > (SIZE_MAX - a));
}

static Boolean_type dynamic_array_multiplication_overflow_detected(size_t a, size_t b)
{
	if (a == 0U or b == 0U) {
		return Boolean_false;
	} else {
		const size_t quotient  = SIZE_MAX / a;
		const size_t remainder = SIZE_MAX % a;
		return ((b > quotient) or (b == quotient and remainder != 0U));
	}
}

static void dynamic_array_check_error_internal(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type *pdebug_info
)
{
	const dynamic_array_internal_type *array = NULL;
	assert(dynamic_array != NULL);
	assert(pdebug_info != NULL);
	pdebug_info->info_1 = 0U;
	pdebug_info->info_2 = 0U;

	if (dynamic_array == NULL) {
		pdebug_info->error = dynamic_array_error_null_pointer_exception;
	}

	if (pdebug_info->struct_size != sizeof(dynamic_array_internal_type)) {
		pdebug_info->error = dynamic_array_error_struct_size_mismatch;
		pdebug_info->info_1 = pdebug_info->struct_size;
		pdebug_info->info_2 = pdebug_info->internal_struct_size;
	}

	array = (const dynamic_array_internal_type*) dynamic_array;

	if (array->ptr == NULL) {
		pdebug_info->error = dynamic_array_error_no_buffer;
	} else if (array->capacity < array->number_of_elements) {
		pdebug_info->error = dynamic_array_error_incorrect_capacity;
		pdebug_info->info_1 = array->capacity;
		pdebug_info->info_2 = array->number_of_elements;
	} else if (array->element_size < 1U) {
		pdebug_info->error = dynamic_array_error_incorrect_element_size;
		pdebug_info->info_1 = array->element_size;
	} else if (array->allocator == NULL) {
		pdebug_info->error = dynamic_array_error_no_allocator;
	} else if (array->allocator->allocate_funcptr == NULL) {
		pdebug_info->error = dynamic_array_error_no_memory_allocation_function;
	} else if (array->allocator->deallocate_funcptr == NULL) {
		pdebug_info->error = dynamic_array_error_no_memory_deallocation_function;
	} else {
		pdebug_info->error = dynamic_array_error_none;
	}
}

static void dynamic_array_check_and_report_error(
	const dynamic_array_type_ *dynamic_array,
	dynamic_array_debug_info_type *pdebug_info
)
{
	dynamic_array_check_error_internal(dynamic_array, pdebug_info);
	if (pdebug_info->error != dynamic_array_error_none) {
		dynamic_array_report_error(*pdebug_info);
	}
}

void dynamic_array_set_exception_handler(
	void (*exception_handler_funcptr)(dynamic_array_error_type)
)
{
	s_exception_handler_funcptr = exception_handler_funcptr;
}

void dynamic_array_set_error_reporting_handler(
	void (*report_error_funcptr)(dynamic_array_debug_info_type)
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
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_error_internal(dynamic_array, &debug_info);
	return debug_info.error;
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
	size_t number_of_bytes = 0U;
	void *ptr = NULL;
	Boolean_type multiplication_overflow_detected = Boolean_false;
	dynamic_array_internal_type array = {0U};
	dynamic_array_type_ dyn_array = {0U};
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);

	assert(element_size > 0U);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size < 1U) {
		debug_info.error = dynamic_array_error_incorrect_element_size;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif

	if (initial_size == SIZE_MAX) {
		initial_capacity = initial_size;
	}

	while (initial_capacity < initial_size) {
		initial_capacity += initial_capacity;
	}

	multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(initial_capacity, element_size);
	assert(not multiplication_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (multiplication_overflow_detected) {
		debug_info.error = dynamic_array_error_multiplication_overflow_detected;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = initial_capacity;
		debug_info.info_2 = element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif

	if (allocator != NULL) {
		const Boolean_type use_custom_allocator = (allocator->allocate_funcptr != NULL and allocator->deallocate_funcptr != NULL);
		assert(allocator->allocate_funcptr != NULL);
		assert(allocator->deallocate_funcptr != NULL);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		if (allocator->allocate_funcptr == NULL) {
			debug_info.error = dynamic_array_error_no_memory_allocation_function;
			debug_info.library_line_number = (size_t)__LINE__;
			dynamic_array_report_error(debug_info);
			dynamic_array_handle_exception(debug_info.error);
			dynamic_array_terminate();
		}
		if (allocator->deallocate_funcptr == NULL) {
			debug_info.error = dynamic_array_error_no_memory_deallocation_function;
			debug_info.library_line_number = (size_t)__LINE__;
			dynamic_array_report_error(debug_info);
			dynamic_array_handle_exception(debug_info.error);
			dynamic_array_terminate();
		}
#endif
		if (not use_custom_allocator) {
			allocator = &default_allocator;
		}
	} else {
		allocator = &default_allocator;
	}

	assert(allocator != NULL);
	number_of_bytes = initial_capacity * element_size;
	ptr = allocator->allocate_funcptr(number_of_bytes);
	if (ptr != NULL) {
		memset(ptr, 0, number_of_bytes);
	} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		debug_info.error = dynamic_array_error_memory_allocation_failure;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = number_of_bytes;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
#endif
		initial_capacity = initial_size = 0U;
	}

	array.capacity = initial_capacity;
	array.number_of_elements = initial_size;
	array.element_size = element_size;
	array.ptr = ptr;
	array.allocator = allocator;
	memcpy(&dyn_array, &array, sizeof(array));
	return dyn_array;
}

void dynamic_array_delete_(
	dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	dynamic_array_internal_type *array = NULL;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none and debug_info.error != dynamic_array_error_no_buffer) {
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	array = (dynamic_array_internal_type*) dynamic_array;
	array->capacity = 0U;
	array->number_of_elements = 0U;
	array->element_size = 0U;
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
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		return NULL;
	}
#endif
	return ((const dynamic_array_internal_type*) dynamic_array)->allocator;
}

size_t dynamic_array_capacity_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		return 0U;
	}
#endif
	return ((const dynamic_array_internal_type*) dynamic_array)->capacity;
}

size_t dynamic_array_size_(
	const dynamic_array_type_ *dynamic_array,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		return 0U;
	}
#endif
	return ((const dynamic_array_internal_type*) dynamic_array)->number_of_elements;
}

void *dynamic_array_element_ptr_(
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
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	Boolean_type multiplication_overflow_detected = Boolean_false;
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	array = (const dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size);
	assert(index < array->number_of_elements);
	assert(not dynamic_array_multiplication_overflow_detected(index, array->number_of_elements));
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}

	if (index >= array->number_of_elements) {
		debug_info.error = dynamic_array_error_index_out_of_range;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->number_of_elements;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}

	multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(index, array->element_size);
	if (multiplication_overflow_detected) {
		debug_info.error = dynamic_array_error_multiplication_overflow_detected;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	offset = index * array->element_size;
	ptr = (unsigned char*) array->ptr;
	return &ptr[offset];
}

void dynamic_array_add_elements_at_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	size_t new_number_of_elements = 0U; 
	dynamic_array_internal_type *array = NULL;
	Boolean_type addition_overflow_detected = Boolean_false;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	assert(ptr_to_first_element != NULL);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (ptr_to_first_element == NULL) {
		debug_info.error = dynamic_array_error_null_pointer_exception;
		debug_info.library_line_number = (size_t)__LINE__;
		dynamic_array_report_error(debug_info);
		dynamic_array_terminate();
	}
#endif
	array = (dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	assert(index <= array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index > array->number_of_elements) {
		debug_info.error = dynamic_array_error_index_out_of_range;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->number_of_elements;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	addition_overflow_detected = dynamic_array_addition_overflow_detected(array->number_of_elements, number_of_elements);
	assert(not addition_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (addition_overflow_detected) {
		debug_info.error = dynamic_array_error_addition_overflow_detected;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = array->number_of_elements;
		debug_info.info_2 = number_of_elements;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	new_number_of_elements = array->number_of_elements + number_of_elements;
	if (new_number_of_elements > array->capacity) {
		void *ptr = NULL;
		size_t new_byte_count = 0U;
		size_t new_capacity = array->capacity;
		Boolean_type multiplication_overflow_detected = Boolean_false;

		while (new_capacity < new_number_of_elements) {
			new_capacity += new_capacity;
		}

		multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(new_capacity, array->element_size);
		assert(not multiplication_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
		if (multiplication_overflow_detected) {
			debug_info.error = dynamic_array_error_multiplication_overflow_detected;
			debug_info.library_line_number = (size_t)__LINE__;
			debug_info.info_1 = new_capacity;
			debug_info.info_2 = array->element_size;
			dynamic_array_report_error(debug_info);
			dynamic_array_handle_exception(debug_info.error);
			dynamic_array_terminate();
		}
#endif
		new_byte_count = new_capacity * array->element_size;
		if (array->allocator->reallocate_funcptr != NULL) {
			ptr = array->allocator->reallocate_funcptr(array->ptr, new_byte_count);
		} else {
			ptr = array->allocator->allocate_funcptr(new_byte_count);
		}
		if (ptr != NULL) {
			if (array->allocator->reallocate_funcptr == NULL) {
				const size_t number_of_bytes_occupied = array->number_of_elements * array->element_size;
				memcpy(ptr, array->ptr, number_of_bytes_occupied);
				memset(array->ptr, 0, number_of_bytes_occupied);
				array->allocator->deallocate_funcptr(array->ptr);
			}
			array->ptr = ptr;
			array->capacity = new_capacity;
		} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			debug_info.error = dynamic_array_error_memory_reallocation_failure;
			debug_info.library_line_number = (size_t)__LINE__;
			debug_info.info_1 = new_byte_count;
			dynamic_array_report_error(debug_info);
			dynamic_array_handle_exception(debug_info.error);
#endif
			return;
		}
	}

	if (index == array->number_of_elements) {
		const size_t offset = array->number_of_elements * array->element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;
		const size_t total_bytes_to_copy = number_of_elements * element_size;
		memcpy(&ptr[offset], ptr_to_first_element, total_bytes_to_copy);
		array->number_of_elements = new_number_of_elements;
	} else if (index < array->number_of_elements) {
		const size_t src_offset = index * array->element_size;
		const size_t dst_offset = (index + number_of_elements) * array->element_size;
		const size_t total_elements_to_move = array->number_of_elements - index;
		const size_t total_bytes_to_move = total_elements_to_move * array->element_size;
		const size_t total_bytes_to_copy = number_of_elements * element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;
		memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		memcpy(&ptr[src_offset], ptr_to_first_element, total_bytes_to_copy);
		array->number_of_elements = new_number_of_elements;
	}
}

void dynamic_array_remove_elements_starting_from_index_(
	dynamic_array_type_ *dynamic_array,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	dynamic_array_internal_type *array = NULL;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	array = (dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	assert(index < array->number_of_elements);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (index >= array->number_of_elements) {
		debug_info.error = dynamic_array_error_index_out_of_range;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = index;
		debug_info.info_2 = array->number_of_elements;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	if (number_of_elements > 0U) {
		unsigned char *ptr = NULL;
		size_t offset = 0U, total_bytes_to_zero = 0U;
		const size_t number_of_elements_from_index_to_last_index = array->number_of_elements - index;
		const size_t number_of_elements_to_remove = (number_of_elements < number_of_elements_from_index_to_last_index) ?
			number_of_elements : number_of_elements_from_index_to_last_index;
		const size_t number_of_elements_to_move = number_of_elements_from_index_to_last_index - number_of_elements_to_remove;

		if (output_buffer != NULL) {
			const size_t total_bytes_to_copy = number_of_elements_to_remove * element_size;
			const size_t src_offset = index * array->element_size;
			unsigned char *src_ptr = ((unsigned char*) array->ptr) + src_offset;
			unsigned char *dst_ptr = (unsigned char*) output_buffer;
			memcpy(dst_ptr, src_ptr, total_bytes_to_copy);
		}

		if (number_of_elements_to_move > 0U) {
			const size_t src_offset = (index + number_of_elements_to_remove) * array->element_size;
			const size_t dst_offset = index * array->element_size;
			const size_t total_bytes_to_move = number_of_elements_to_move * array->element_size;
			unsigned char *ptr = (unsigned char*) array->ptr;
			memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		}

		assert(array->number_of_elements >= number_of_elements_to_remove);
		array->number_of_elements -= number_of_elements_to_remove;
		offset = array->number_of_elements * array->element_size;
		total_bytes_to_zero = number_of_elements_to_remove * array->element_size;
		ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
	}
}

void dynamic_array_resize_(
	dynamic_array_type_ *dynamic_array,
	size_t new_size,
	size_t element_size,
	const char *file_name,
	size_t line_number,
	size_t struct_size
)
{
	const size_t new_number_of_elements = new_size;
	dynamic_array_internal_type *array = NULL;
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	dynamic_array_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.library_file_name = __FILE__;
	debug_info.line_number = line_number;
	debug_info.library_line_number = (size_t)__LINE__;
	debug_info.struct_size = struct_size;
	debug_info.internal_struct_size = sizeof(dynamic_array_internal_type);
	dynamic_array_check_and_report_error(dynamic_array, &debug_info);
	if (debug_info.error != dynamic_array_error_none) {
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	array = (dynamic_array_internal_type*) dynamic_array;
	assert(element_size == array->element_size);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
	if (element_size != array->element_size) {
		debug_info.error = dynamic_array_error_element_size_mismatch;
		debug_info.library_line_number = (size_t)__LINE__;
		debug_info.info_1 = element_size;
		debug_info.info_2 = array->element_size;
		dynamic_array_report_error(debug_info);
		dynamic_array_handle_exception(debug_info.error);
		dynamic_array_terminate();
	}
#endif
	if (new_number_of_elements > array->number_of_elements) {
		size_t extra_number_of_elements = 0U;
		size_t offset = 0U;
		size_t total_bytes_to_zero = 0U;
		unsigned char *ptr = NULL;

		if (new_number_of_elements > array->capacity) {
			size_t new_byte_count = 0U;
			void *ptr = NULL;
			size_t new_capacity = array->capacity;
			Boolean_type multiplication_overflow_detected = Boolean_false;

			while (new_capacity < new_number_of_elements) {
				new_capacity += new_capacity;
			}

			multiplication_overflow_detected = dynamic_array_multiplication_overflow_detected(new_capacity, array->element_size);
			assert(not multiplication_overflow_detected);
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
			if (multiplication_overflow_detected) {
				debug_info.error = dynamic_array_error_multiplication_overflow_detected;
				debug_info.library_line_number = (size_t)__LINE__;
				debug_info.info_1 = new_capacity;
				debug_info.info_2 = array->element_size;
				dynamic_array_report_error(debug_info);
				dynamic_array_handle_exception(debug_info.error);
				dynamic_array_terminate();
			}
#endif
			new_byte_count = new_capacity * array->element_size;
			if (array->allocator->reallocate_funcptr != NULL) {
				ptr = array->allocator->reallocate_funcptr(array->ptr, new_byte_count);
			} else {
				ptr = array->allocator->allocate_funcptr(new_byte_count);
			}
			if (ptr != NULL) {
				if (array->allocator->reallocate_funcptr == NULL) {
					const size_t number_of_bytes_occupied = array->number_of_elements * array->element_size;
					memcpy(ptr, array->ptr, number_of_bytes_occupied);
					memset(array->ptr, 0, number_of_bytes_occupied);
					array->allocator->deallocate_funcptr(array->ptr);
				}
				array->ptr = ptr;
				array->capacity = new_capacity;
			} else {
#ifndef DYNAMIC_ARRAY_NO_RUNTIME_CHECKS
				debug_info.error = dynamic_array_error_memory_reallocation_failure;
				debug_info.library_line_number = (size_t)__LINE__;
				debug_info.info_1 = new_byte_count;
				dynamic_array_report_error(debug_info);
				dynamic_array_handle_exception(debug_info.error);
#endif
				return;
			}
		}

		extra_number_of_elements = new_number_of_elements - array->number_of_elements;
		offset = array->number_of_elements * array->element_size;
		total_bytes_to_zero = extra_number_of_elements * array->element_size;
		ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		array->number_of_elements = new_number_of_elements;
	} else if (new_number_of_elements < array->number_of_elements) {
		const size_t number_of_elements_to_remove = array->number_of_elements - new_number_of_elements;
		const size_t offset = new_number_of_elements * array->element_size;
		const size_t total_bytes_to_zero = number_of_elements_to_remove * array->element_size;
		unsigned char *ptr = (unsigned char*) array->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		array->number_of_elements = new_number_of_elements;
	}
}
