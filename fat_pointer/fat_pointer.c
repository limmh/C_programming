#include "fat_pointer.h"
#include "safer_fixed_width_integers.h"
#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct fat_pointer_internal_type {
	size_t capacity;
	size_t size;
	size_t element_size;
	void *ptr;
} fat_pointer_internal_type;

STATIC_ASSERT(sizeof(fat_pointer_type_) == sizeof(fat_pointer_internal_type), "Size mismatch between public fat pointer type and internal fat pointer type.");

static void fat_pointer_default_error_reporting_handler(fat_pointer_debug_info_type debug_info)
{
	FILE *file = stdout;
	const char *file_name = (debug_info.file_name != NULL) ? debug_info.file_name : "Unknown file";
	const int line_number = debug_info.line_number;
	const unsigned long long info_1 = (unsigned long long) debug_info.info_1;
	const unsigned long long info_2 = (unsigned long long) debug_info.info_2;

	fprintf(file, "%s (line %d): ", file_name, line_number);

	switch (debug_info.error) {
	case fat_pointer_error_none:
		fprintf(file, "No error found.\n");
		break;
	case fat_pointer_error_null_pointer_exception:
		fprintf(file, "Null pointer exception.\n");
		break;
	case fat_pointer_error_no_pointer:
		fprintf(file, "No pointer internally.\n");
		break;
	case fat_pointer_error_incorrect_capacity:
		fprintf(file, "Incorrect capacity (capacity is %llu, length is %llu)\n", info_1, info_2);
		break;
	case fat_pointer_error_incorrect_element_size:
		fprintf(file, "Incorrect element size (%llu)\n", info_1);
		break;
	case fat_pointer_error_index_out_of_range:
		fprintf(file, "Index (%llu) is out of range (length: %llu)\n", info_1, info_2);
		break;
	case fat_pointer_error_element_size_mismatch:
		fprintf(file, "Element size mismatch (internal: %llu, external: %llu\n", info_1, info_2);
		break;
	case fat_pointer_error_addition_overflow_detected:
		fprintf(file, "Addition overflow detected (operand 1: %llu, operand 2: %llu)\n", info_1, info_2);
		break;
	case fat_pointer_error_multiplication_overflow_detected:
		fprintf(file, "Multiplication overflow detected (operand 1: %llu, operand 2: %llu)\n", info_1, info_2);
		break;
	case fat_pointer_error_no_source_elements:
		fprintf(file, "There are no source elements.\n");
		break;
	case fat_pointer_error_no_enough_capacity:
		fprintf(file, "The final number of elements (%llu) exceeds the actual capacity (%llu).\n", info_1, info_2);
		break;
	case fat_pointer_error_too_many_elements_to_remove:
		fprintf(file, "There are more elements to remove (%llu) than the actual number of elements present (%llu).\n", info_1, info_2);
		break;
	default:
		fprintf(file, "Unknown error (error code %d)\n", (int) debug_info.error);
		break;
	}
}

static fat_pointer_error_reporting_handler_type fat_pointer_error_reporting_handler = &fat_pointer_default_error_reporting_handler;

fat_pointer_error_reporting_handler_type
fat_pointer_set_report_handler(fat_pointer_error_reporting_handler_type error_reporting_handler)
{
	fat_pointer_error_reporting_handler_type previous_handler = fat_pointer_error_reporting_handler;
	fat_pointer_error_reporting_handler = error_reporting_handler;
	return previous_handler;
}

static void fat_pointer_report_error(fat_pointer_debug_info_type debug_info)
{
	if (fat_pointer_error_reporting_handler != NULL) {
		fat_pointer_error_reporting_handler(debug_info);
	}
}

static fat_pointer_exception_handler_type fat_pointer_exception_handler = NULL;

fat_pointer_exception_handler_type
fat_pointer_set_exception_handler(fat_pointer_exception_handler_type exception_handler)
{
	fat_pointer_exception_handler_type previous_handler = fat_pointer_exception_handler;
	fat_pointer_exception_handler = exception_handler;
	return previous_handler;
}

static void fat_pointer_handle_exception(fat_pointer_error_type error)
{
	if (fat_pointer_exception_handler != NULL) {
		fat_pointer_exception_handler(error);
	}
}

static void fat_pointer_terminate(void)
{
	exit(EXIT_FAILURE);
}

static void fat_pointer_detect_first_obvious_error(const fat_pointer_type_ *fatptr, fat_pointer_debug_info_type *pdebug_info)
{
	const fat_pointer_internal_type *fatptr_ = (const fat_pointer_internal_type*) fatptr;
	assert(fatptr_ != NULL);
	assert(pdebug_info != NULL);
	if (fatptr_->ptr == NULL) {
		pdebug_info->error = fat_pointer_error_no_pointer;
		pdebug_info->info_1 = 0U;
		pdebug_info->info_2 = 0U;
	} else if (fatptr_->capacity < fatptr_->size) {
		pdebug_info->error = fat_pointer_error_incorrect_capacity;
		pdebug_info->info_1 = fatptr_->capacity;
		pdebug_info->info_2 = fatptr_->size;
	} else if (fatptr_->element_size < 1U) {
		pdebug_info->error = fat_pointer_error_incorrect_element_size;
		pdebug_info->info_1 = fatptr_->element_size;
		pdebug_info->info_2 = 0U;
	} else {
		const size_result_type result = safer_size_multiply(fatptr_->capacity, fatptr_->element_size);
		if (result.error == integer_operation_error_none) {
			pdebug_info->error = fat_pointer_error_none;
			pdebug_info->info_1 = 0U;
			pdebug_info->info_2 = 0U;
		} else {
			pdebug_info->error = fat_pointer_error_multiplication_overflow_detected;
			pdebug_info->info_1 = fatptr_->capacity;
			pdebug_info->info_2 = fatptr_->element_size;
		}
	}
}

fat_pointer_type_ fat_pointer_create_(void *ptr, size_t capacity, size_t initial_size, size_t element_size, const char *file_name, int line_number)
{
	fat_pointer_type_ fatptr = {0};
	fat_pointer_internal_type fatptr_ = {0};
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
#endif

	assert(ptr != NULL);
	fatptr_.ptr = ptr;
	assert(capacity > 0U);
	fatptr_.capacity = capacity;
	assert(initial_size <= capacity);
	fatptr_.size = initial_size;
	assert(element_size > 0U);
	fatptr_.element_size = element_size;

	memcpy(&fatptr, &fatptr_, sizeof(fatptr));

#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_detect_first_obvious_error(&fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		fat_pointer_terminate();
	}
#endif
	return fatptr;
}

void fat_pointer_destroy_(fat_pointer_type_ *fatptr, const char *file_name, int line_number)
{
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return;
	}
#endif
	if (fatptr != NULL) {
		memset(fatptr, 0, sizeof(*fatptr));
	}
}

void fat_pointer_zero_(fat_pointer_type_ *fatptr, const char *file_name, int line_number)
{
	fat_pointer_internal_type *fatptr_ = (fat_pointer_internal_type*) fatptr;
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return;
	}
#endif
	{
		const size_t number_of_bytes_to_zero = fatptr_->size * fatptr_->element_size;
		if (number_of_bytes_to_zero) {
			const int zero_byte = 0;
			memset(fatptr_->ptr, zero_byte, number_of_bytes_to_zero);
		}
	}
}

size_t fat_pointer_capacity_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number)
{
	const fat_pointer_internal_type *fatptr_ = (const fat_pointer_internal_type*) fatptr;
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return 0U;
	}
#endif
	return fatptr_->capacity;
}

size_t fat_pointer_size_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number)
{
	const fat_pointer_internal_type *fatptr_ = (const fat_pointer_internal_type*) fatptr;
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return 0U;
	}
#endif
	return fatptr_->size;
}

size_t fat_pointer_element_size_(const fat_pointer_type_ *fatptr, const char *file_name, int line_number)
{
	const fat_pointer_internal_type *fatptr_ = (const fat_pointer_internal_type*) fatptr;
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return 0U;
	}
#endif
	return fatptr_->element_size;
}

void *fat_pointer_element_ptr_(
	const fat_pointer_type_ *fatptr,
	size_t index,
	size_t element_size,
	const char *file_name,
	int line_number
)
{
	const fat_pointer_internal_type *fatptr_ = (const fat_pointer_internal_type*) fatptr;
#ifndef FAT_POINTER_NO_RUNTIME_CHECKS
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		fat_pointer_terminate();
	}
	if (index >= fatptr_->size) {
		debug_info.error = fat_pointer_error_index_out_of_range;
		debug_info.info_1 = index;
		debug_info.info_2 = fatptr_->size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		fat_pointer_terminate();
	}
	if (element_size != fatptr_->element_size) {
		debug_info.error = fat_pointer_error_element_size_mismatch;
		debug_info.info_1 = fatptr_->element_size;
		debug_info.info_2 = element_size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		fat_pointer_terminate();
	}
#endif
	{
		const size_t byte_offset = index * fatptr_->element_size;
		unsigned char *ptr = (unsigned char*) fatptr_->ptr;
		return (ptr + byte_offset);
	}
}

fat_pointer_error_type
fat_pointer_add_elements_at_index_(
	fat_pointer_type_ *fatptr,
	size_t index,
	const void *ptr_to_first_element,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number
)
{
	fat_pointer_internal_type *fatptr_ = (fat_pointer_internal_type*) fatptr;
	fat_pointer_debug_info_type debug_info = {0};
	assert(ptr_to_first_element != NULL);

	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (ptr_to_first_element == NULL) {
		debug_info.error = fat_pointer_error_no_source_elements;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (element_size != fatptr_->element_size) {
		debug_info.error = fat_pointer_error_element_size_mismatch;
		debug_info.info_1 = fatptr_->element_size;
		debug_info.info_2 = element_size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (index > fatptr_->size) {
		debug_info.error = fat_pointer_error_index_out_of_range;
		debug_info.info_1 = index;
		debug_info.info_2 = fatptr_->size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	{
		const size_t capacity = fatptr_->capacity;
		size_t new_size = 0U;
		size_result_type result = safer_size_add(fatptr_->size, number_of_elements);
		if (result.error != integer_operation_error_none) {
			debug_info.error = fat_pointer_error_addition_overflow_detected;
			debug_info.info_1 = fatptr_->size;
			debug_info.info_2 = number_of_elements;
			fat_pointer_report_error(debug_info);
			fat_pointer_handle_exception(debug_info.error);
			return debug_info.error;
		} else if (result.value > fatptr_->capacity) {
			debug_info.error = fat_pointer_error_no_enough_capacity;
			debug_info.info_1 = result.value;
			debug_info.info_2 = fatptr_->capacity;
			fat_pointer_report_error(debug_info);
			fat_pointer_handle_exception(debug_info.error);
			return debug_info.error;
		}

		new_size = result.value;
		result = safer_size_multiply(new_size, fatptr_->element_size);
		if (result.error != integer_operation_error_none) {
			debug_info.error = fat_pointer_error_multiplication_overflow_detected;
			debug_info.info_1 = new_size;
			debug_info.info_2 = fatptr_->element_size;
			fat_pointer_report_error(debug_info);
			fat_pointer_handle_exception(debug_info.error);
			return debug_info.error;
		}

		if (index == fatptr_->size) {
			const size_t offset = fatptr_->size * fatptr_->element_size;
			unsigned char *ptr = (unsigned char*) fatptr_->ptr;
			const size_t total_bytes_to_copy = number_of_elements * fatptr_->element_size;
			memcpy(&ptr[offset], ptr_to_first_element, total_bytes_to_copy);
			fatptr_->size = new_size;
		} else if (index < fatptr_->size) {
			const size_t src_offset = index * fatptr_->element_size;
			const size_t dst_offset = (index + number_of_elements) * fatptr_->element_size;
			const size_t total_elements_to_move = fatptr_->size - index;
			const size_t total_bytes_to_move = total_elements_to_move * fatptr_->element_size;
			const size_t total_bytes_to_copy = number_of_elements * fatptr_->element_size;
			unsigned char *ptr = (unsigned char*) fatptr_->ptr;
			memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
			memcpy(&ptr[src_offset], ptr_to_first_element, total_bytes_to_copy);
			fatptr_->size = new_size;
		}

		assert(capacity == fatptr_->capacity);
		assert(fatptr_->size <= fatptr_->capacity);
	}

	assert(debug_info.error == fat_pointer_error_none);
	return debug_info.error;
}

fat_pointer_error_type
fat_pointer_remove_elements_starting_from_index_(
	fat_pointer_type_ *fatptr,
	size_t index,
	void *output_buffer,
	size_t number_of_elements,
	size_t element_size,
	const char *file_name,
	int line_number
)
{
	fat_pointer_internal_type *fatptr_ = (fat_pointer_internal_type*) fatptr;
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (element_size != fatptr_->element_size) {
		debug_info.error = fat_pointer_error_element_size_mismatch;
		debug_info.info_1 = fatptr_->element_size;
		debug_info.info_2 = element_size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (index >= fatptr_->size) {
		debug_info.error = fat_pointer_error_index_out_of_range;
		debug_info.info_1 = index;
		debug_info.info_2 = fatptr_->size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (number_of_elements > 0U) {
		unsigned char *ptr = NULL;
		size_t offset = 0U, total_bytes_to_zero = 0U;
		const size_t capacity = fatptr_->capacity;
		const size_t number_of_elements_from_index_to_last_index = fatptr_->size - index;
		const size_t number_of_elements_to_remove = (number_of_elements < number_of_elements_from_index_to_last_index) ?
			number_of_elements : number_of_elements_from_index_to_last_index;
		const size_t number_of_elements_to_move = number_of_elements_from_index_to_last_index - number_of_elements_to_remove;

		if (number_of_elements > number_of_elements_from_index_to_last_index) {
			debug_info.error = fat_pointer_error_too_many_elements_to_remove;
			debug_info.info_1 = number_of_elements;
			debug_info.info_2 = number_of_elements_from_index_to_last_index;
			fat_pointer_report_error(debug_info);
			fat_pointer_handle_exception(debug_info.error);
			return debug_info.error;
		}

		if (output_buffer != NULL) {
			const size_t total_bytes_to_copy = number_of_elements_to_remove * element_size;
			const size_t src_offset = index * fatptr_->element_size;
			unsigned char *src_ptr = ((unsigned char*) fatptr_->ptr) + src_offset;
			unsigned char *dst_ptr = (unsigned char*) output_buffer;
			memcpy(dst_ptr, src_ptr, total_bytes_to_copy);
		}

		if (number_of_elements_to_move > 0U) {
			const size_t src_offset = (index  + number_of_elements_to_remove) * fatptr_->element_size;
			const size_t dst_offset = index * fatptr_->element_size;
			const size_t total_bytes_to_move = number_of_elements_to_move * fatptr_->element_size;
			ptr = (unsigned char*) fatptr_->ptr;
			memmove(&ptr[dst_offset], &ptr[src_offset], total_bytes_to_move);
		}

		fatptr_->size -= number_of_elements_to_remove;
		offset = fatptr_->size * fatptr_->element_size;
		total_bytes_to_zero = number_of_elements_to_remove * fatptr_->element_size;
		ptr = (unsigned char*) fatptr_->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		assert(capacity == fatptr_->capacity);
		assert(fatptr_->size <= fatptr_->capacity);
	}

	assert(debug_info.error == fat_pointer_error_none);
	return debug_info.error;
}

fat_pointer_error_type
fat_pointer_resize_(
	fat_pointer_type_ *fatptr,
	size_t new_size,
	size_t element_size,
	const char *file_name,
	int line_number
)
{
	size_t capacity = 0U;
	fat_pointer_internal_type *fatptr_ = (fat_pointer_internal_type*) fatptr;
	fat_pointer_debug_info_type debug_info = {0};
	debug_info.file_name = file_name;
	debug_info.line_number = line_number;
	fat_pointer_detect_first_obvious_error(fatptr, &debug_info);
	if (debug_info.error != fat_pointer_error_none) {
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	capacity = fatptr_->capacity;

	if (element_size != fatptr_->element_size) {
		debug_info.error = fat_pointer_error_element_size_mismatch;
		debug_info.info_1 = fatptr_->element_size;
		debug_info.info_2 = element_size;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (new_size > fatptr_->capacity) {
		debug_info.error = fat_pointer_error_no_enough_capacity;
		debug_info.info_1 = new_size;
		debug_info.info_2 = fatptr_->capacity;
		fat_pointer_report_error(debug_info);
		fat_pointer_handle_exception(debug_info.error);
		return debug_info.error;
	}

	if (new_size < fatptr_->size) {
		unsigned char *ptr = NULL;
		const size_t number_of_elements_to_remove = fatptr_->size - new_size;
		const size_t offset = new_size * fatptr_->element_size;
		const size_t total_bytes_to_zero = number_of_elements_to_remove * fatptr_->element_size;
		ptr = (unsigned char*) fatptr_->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		fatptr_->size = new_size;
	} else if (new_size > fatptr_->size) {
		unsigned char *ptr = NULL;
		const size_t number_of_elements_to_zero = new_size - fatptr_->size;
		const size_t offset = new_size * fatptr_->element_size;
		const size_t total_bytes_to_zero = number_of_elements_to_zero * fatptr_->element_size;
		ptr = (unsigned char*) fatptr_->ptr;
		memset(&ptr[offset], 0, total_bytes_to_zero);
		fatptr_->size = new_size;
	}

	assert(capacity == fatptr_->capacity);
	assert(fatptr_->size <= fatptr_->capacity);
	assert(debug_info.error == fat_pointer_error_none);
	return debug_info.error;
}
