#include "debug_mode_integer.h"
#include "Boolean_type.h"
#include "static_assert.h"
#include <assert.h>
#include <iso646.h>
#include <stdio.h>

/* non-null guarantee */
static const char *debug_mode_integer_operation_name(integer_operation_type operation)
{
	const char *name = NULL;
	switch (operation) {
	case integer_operation_addition:
		name = "addition";
		break;
	case integer_operation_subtraction:
		name = "subtraction";
		break;
	case integer_operation_multiplication:
		name = "multiplication";
		break;
	case integer_operation_division:
		name = "division";
		break;
	case integer_operation_remainder:
		name = "remainder";
		break;
	default:
		name = "unknown operation";
		break;
	}
	assert(name != NULL);
	return name;
}

static const char *debug_mode_integer_result_mode_name(integer_result_mode_type mode)
{
	const char *name = NULL;
	switch (mode) {
	case integer_result_mode_wraparound:
		name = "wraparound";
		break;
	case integer_result_mode_saturation:
		name = "saturation/clipping";
		break;
	default:
		name = "default mode";
		break;
	}
	assert(name != NULL);
	return name;
}

static void debug_mode_default_int_handler(const int_debug_info_type* debug_info)
{
#define INTEGER_SPECIFIER "%d"
#define INTEGER_TYPE_NAME "int"
	const char *operation_name = NULL, *result_mode_name = NULL, *error_message = NULL;
	FILE *file = stderr;
	assert(debug_info != NULL);
	assert(debug_info->file_name != NULL);
	operation_name = debug_mode_integer_operation_name(debug_info->operation);
	result_mode_name = debug_mode_integer_result_mode_name(debug_info->result_mode);
	error_message = integer_operation_error_message(debug_info->error);
	fprintf(file, "%s (line %d)\n", debug_info->file_name, debug_info->line_number);
	fprintf(file, "%s [Error code: %d]\n", error_message, (int) debug_info->error);
	fprintf(file, "[Operand 1: " INTEGER_SPECIFIER "][Operand 2: " INTEGER_SPECIFIER
		"][Result: " INTEGER_SPECIFIER "][Operand type: " INTEGER_TYPE_NAME
		"][Minimum: " INTEGER_SPECIFIER "][Maximum: " INTEGER_SPECIFIER "][Result mode: %s][Operation: %s]\n",
		debug_info->operand1, debug_info->operand2, debug_info->result,
		debug_info->minimum_value, debug_info->maximum_value, result_mode_name, operation_name);
#undef INTEGER_TYPE_NAME
#undef INTEGER_SPECIFIER
}

static int_debug_handler_type debug_mode_int_handler = &debug_mode_default_int_handler;

int_debug_handler_type debug_mode_int_set_handler(int_debug_handler_type handler)
{
	int_debug_handler_type previous_handler = debug_mode_int_handler;
	if (handler != NULL) {
		debug_mode_int_handler = handler;
	}
	return previous_handler;
}

void debug_mode_int_reset_handler(void)
{
	debug_mode_int_handler = &debug_mode_default_int_handler;
}

#define DEBUG_MODE_HANDLER debug_mode_int_handler
#define MINIMUM INT_MIN
#define MAXIMUM INT_MAX

int debug_mode_int_add(int a, int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR +
	typedef int integer_type;
	typedef unsigned int unsigned_integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	const integer_operation_type operation = integer_operation_addition;
	const integer_operation_error_type error = safer_int_addition_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

int debug_mode_int_minus(int a, int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR -
	typedef int integer_type;
	typedef unsigned int unsigned_integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	const integer_operation_type operation = integer_operation_subtraction;
	const integer_operation_error_type error = safer_int_subtraction_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

int debug_mode_int_multiply(int a, int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR *
	typedef int integer_type;
	typedef unsigned int unsigned_integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	const integer_operation_type operation = integer_operation_multiplication;
	const integer_operation_error_type error = safer_int_multiplication_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

int debug_mode_int_divide(int a, int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR /
	typedef int integer_type;
	typedef int_debug_info_type debug_info_type;
	const integer_type zero = 0;
	integer_type result = zero;
	const integer_operation_type operation = integer_operation_division;
	const integer_operation_error_type error = safer_int_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		if (result_mode == integer_result_mode_saturation) {
			if (a < zero) {
				result = MINIMUM;
			} else if (a > zero) {
				result = MAXIMUM;
			}
		}
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else {
			result = MINIMUM;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

int debug_mode_int_remainder(int a, int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR %
	typedef int integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	const integer_operation_type operation = integer_operation_remainder;
	const integer_operation_error_type error = safer_int_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER

/* unsigned int */
static void debug_mode_default_uint_handler(const uint_debug_info_type* debug_info)
{
#define INTEGER_SPECIFIER "%u"
#define INTEGER_TYPE_NAME "unsigned int"
	const char *operation_name = NULL, *result_mode_name = NULL, *error_message = NULL;
	FILE *file = stderr;
	assert(debug_info != NULL);
	assert(debug_info->file_name != NULL);
	operation_name = debug_mode_integer_operation_name(debug_info->operation);
	result_mode_name = debug_mode_integer_result_mode_name(debug_info->result_mode);
	error_message = integer_operation_error_message(debug_info->error);
	fprintf(file, "%s (line %d)\n", debug_info->file_name, debug_info->line_number);
	fprintf(file, "%s [Error code: %d]\n", error_message, (int) debug_info->error);
	fprintf(file, "[Operand 1: " INTEGER_SPECIFIER "][Operand 2: " INTEGER_SPECIFIER
		"][Result: " INTEGER_SPECIFIER "][Operand type: " INTEGER_TYPE_NAME
		"][Minimum: " INTEGER_SPECIFIER "][Maximum: " INTEGER_SPECIFIER "][Result mode: %s][Operation: %s]\n",
		debug_info->operand1, debug_info->operand2, debug_info->result,
		debug_info->minimum_value, debug_info->maximum_value, result_mode_name, operation_name);
#undef INTEGER_TYPE_NAME
#undef INTEGER_SPECIFIER
}

static uint_debug_handler_type debug_mode_uint_handler = &debug_mode_default_uint_handler;

uint_debug_handler_type debug_mode_uint_set_handler(uint_debug_handler_type handler)
{
	uint_debug_handler_type previous_handler = debug_mode_uint_handler;
	if (handler != NULL) {
		debug_mode_uint_handler = handler;
	}
	return previous_handler;
}

void debug_mode_uint_reset_handler(void)
{
	debug_mode_uint_handler = &debug_mode_default_uint_handler;
}

#define DEBUG_MODE_HANDLER debug_mode_uint_handler
#define MINIMUM 0U
#define MAXIMUM UINT_MAX

unsigned int debug_mode_uint_add(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR +
	typedef unsigned int unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	const integer_operation_type operation = integer_operation_addition;
	const integer_operation_error_type error = safer_uint_addition_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result = (result_mode == integer_result_mode_saturation) ? MAXIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned int debug_mode_uint_minus(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR -
	typedef unsigned int unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	const integer_operation_type operation = integer_operation_subtraction;
	const integer_operation_error_type error = safer_uint_subtraction_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		result = (result_mode == integer_result_mode_saturation) ? MINIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}
unsigned int debug_mode_uint_multiply(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR *
	typedef unsigned int unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	const integer_operation_type operation = integer_operation_multiplication;
	const integer_operation_error_type error = safer_uint_multiplication_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result = (result_mode == integer_result_mode_saturation) ? MAXIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned int debug_mode_uint_divide(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR /
	typedef unsigned int unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	const integer_operation_type operation = integer_operation_division;
	const integer_operation_error_type error = safer_uint_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		if (result_mode == integer_result_mode_saturation) {
			if (a != 0U) {
				result = MAXIMUM;
			}
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned int debug_mode_uint_remainder(unsigned int a, unsigned int b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR %
	typedef unsigned int unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	const integer_operation_type operation = integer_operation_remainder;
	const integer_operation_error_type error = safer_uint_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER

/* long */
static void debug_mode_default_long_handler(const long_debug_info_type* debug_info)
{
#define INTEGER_SPECIFIER "%ld"
#define INTEGER_TYPE_NAME "long"
	const char *operation_name = NULL, *result_mode_name = NULL, *error_message = NULL;
	FILE *file = stderr;
	assert(debug_info != NULL);
	assert(debug_info->file_name != NULL);
	operation_name = debug_mode_integer_operation_name(debug_info->operation);
	result_mode_name = debug_mode_integer_result_mode_name(debug_info->result_mode);
	error_message = integer_operation_error_message(debug_info->error);
	fprintf(file, "%s (line %d)\n", debug_info->file_name, debug_info->line_number);
	fprintf(file, "%s [Error code: %d]\n", error_message, (int) debug_info->error);
	fprintf(file, "[Operand 1: " INTEGER_SPECIFIER "][Operand 2: " INTEGER_SPECIFIER
		"][Result: " INTEGER_SPECIFIER "][Operand type: " INTEGER_TYPE_NAME
		"][Minimum: " INTEGER_SPECIFIER "][Maximum: " INTEGER_SPECIFIER "][Result mode: %s][Operation: %s]\n",
		debug_info->operand1, debug_info->operand2, debug_info->result,
		debug_info->minimum_value, debug_info->maximum_value, result_mode_name, operation_name);
#undef INTEGER_TYPE_NAME
#undef INTEGER_SPECIFIER
}

static long_debug_handler_type debug_mode_long_handler = &debug_mode_default_long_handler;

long_debug_handler_type debug_mode_long_set_handler(long_debug_handler_type handler)
{
	long_debug_handler_type previous_handler = debug_mode_long_handler;
	if (handler != NULL) {
		debug_mode_long_handler = handler;
	}
	return previous_handler;
}

void debug_mode_long_reset_handler(void)
{
	debug_mode_long_handler = &debug_mode_default_long_handler;
}

#define DEBUG_MODE_HANDLER debug_mode_long_handler
#define MINIMUM LONG_MIN
#define MAXIMUM LONG_MAX

long debug_mode_long_add(long a, long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR +
	typedef long integer_type;
	typedef unsigned long unsigned_integer_type;
	typedef long_debug_info_type debug_info_type;
	integer_type result = 0L;
	const integer_operation_type operation = integer_operation_addition;
	const integer_operation_error_type error = safer_long_addition_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long debug_mode_long_minus(long a, long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR -
	typedef long integer_type;
	typedef unsigned long unsigned_integer_type;
	typedef long_debug_info_type debug_info_type;
	integer_type result = 0L;
	const integer_operation_type operation = integer_operation_subtraction;
	const integer_operation_error_type error = safer_long_subtraction_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long debug_mode_long_multiply(long a, long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR *
	typedef long integer_type;
	typedef unsigned long unsigned_integer_type;
	typedef long_debug_info_type debug_info_type;
	integer_type result = 0L;
	const integer_operation_type operation = integer_operation_multiplication;
	const integer_operation_error_type error = safer_long_multiplication_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long debug_mode_long_divide(long a, long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR /
	typedef long integer_type;
	typedef long_debug_info_type debug_info_type;
	const integer_type zero = 0L;
	integer_type result = zero;
	const integer_operation_type operation = integer_operation_division;
	const integer_operation_error_type error = safer_long_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		if (result_mode == integer_result_mode_saturation) {
			if (a < zero) {
				result = MINIMUM;
			} else if (a > zero) {
				result = MAXIMUM;
			}
		}
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else {
			result = MINIMUM;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long debug_mode_long_remainder(long a, long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR %
	typedef long integer_type;
	typedef long_debug_info_type debug_info_type;
	integer_type result = 0L;
	const integer_operation_type operation = integer_operation_remainder;
	const integer_operation_error_type error = safer_long_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER

/* unsigned long */
static void debug_mode_default_ulong_handler(const ulong_debug_info_type* debug_info)
{
#define INTEGER_SPECIFIER "%lu"
#define INTEGER_TYPE_NAME "unsigned long"
	const char *operation_name = NULL, *result_mode_name = NULL, *error_message = NULL;
	FILE *file = stderr;
	assert(debug_info != NULL);
	assert(debug_info->file_name != NULL);
	operation_name = debug_mode_integer_operation_name(debug_info->operation);
	result_mode_name = debug_mode_integer_result_mode_name(debug_info->result_mode);
	error_message = integer_operation_error_message(debug_info->error);
	fprintf(file, "%s (line %d)\n", debug_info->file_name, debug_info->line_number);
	fprintf(file, "%s [Error code: %d]\n", error_message, (int) debug_info->error);
	fprintf(file, "[Operand 1: " INTEGER_SPECIFIER "][Operand 2: " INTEGER_SPECIFIER
		"][Result: " INTEGER_SPECIFIER "][Operand type: " INTEGER_TYPE_NAME
		"][Minimum: " INTEGER_SPECIFIER "][Maximum: " INTEGER_SPECIFIER "][Result mode: %s][Operation: %s]\n",
		debug_info->operand1, debug_info->operand2, debug_info->result,
		debug_info->minimum_value, debug_info->maximum_value, result_mode_name, operation_name);
#undef INTEGER_TYPE_NAME
#undef INTEGER_SPECIFIER
}

static ulong_debug_handler_type debug_mode_ulong_handler = &debug_mode_default_ulong_handler;

ulong_debug_handler_type debug_mode_ulong_set_handler(ulong_debug_handler_type handler)
{
	ulong_debug_handler_type previous_handler = debug_mode_ulong_handler;
	if (handler != NULL) {
		debug_mode_ulong_handler = handler;
	}
	return previous_handler;
}

void debug_mode_ulong_reset_handler(void)
{
	debug_mode_ulong_handler = &debug_mode_default_ulong_handler;
}

#define DEBUG_MODE_HANDLER debug_mode_ulong_handler
#define MINIMUM 0UL
#define MAXIMUM ULONG_MAX

unsigned long debug_mode_ulong_add(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR +
	typedef unsigned long unsigned_integer_type;
	typedef ulong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0UL;
	const integer_operation_type operation = integer_operation_addition;
	const integer_operation_error_type error = safer_ulong_addition_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result = (result_mode == integer_result_mode_saturation) ? MAXIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long debug_mode_ulong_minus(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR -
	typedef unsigned long unsigned_integer_type;
	typedef ulong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0UL;
	const integer_operation_type operation = integer_operation_subtraction;
	const integer_operation_error_type error = safer_ulong_subtraction_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		result = (result_mode == integer_result_mode_saturation) ? MINIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}
unsigned long debug_mode_ulong_multiply(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR *
	typedef unsigned long unsigned_integer_type;
	typedef ulong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0UL;
	const integer_operation_type operation = integer_operation_multiplication;
	const integer_operation_error_type error = safer_ulong_multiplication_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result = (result_mode == integer_result_mode_saturation) ? MAXIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long debug_mode_ulong_divide(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR /
	typedef unsigned long unsigned_integer_type;
	typedef ulong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0UL;
	const integer_operation_type operation = integer_operation_division;
	const integer_operation_error_type error = safer_ulong_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		if (result_mode == integer_result_mode_saturation) {
			if (a != 0UL) {
				result = MAXIMUM;
			}
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long debug_mode_ulong_remainder(unsigned long a, unsigned long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR %
	typedef unsigned long unsigned_integer_type;
	typedef ulong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0UL;
	const integer_operation_type operation = integer_operation_remainder;
	const integer_operation_error_type error = safer_ulong_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER

/* long long */
#if defined(LLONG_MIN) && defined(LLONG_MAX)
static void debug_mode_default_llong_handler(const llong_debug_info_type* debug_info)
{
#define INTEGER_SPECIFIER "%lld"
#define INTEGER_TYPE_NAME "long long"
	const char *operation_name = NULL, *result_mode_name = NULL, *error_message = NULL;
	FILE *file = stderr;
	assert(debug_info != NULL);
	assert(debug_info->file_name != NULL);
	operation_name = debug_mode_integer_operation_name(debug_info->operation);
	result_mode_name = debug_mode_integer_result_mode_name(debug_info->result_mode);
	error_message = integer_operation_error_message(debug_info->error);
	fprintf(file, "%s (line %d)\n", debug_info->file_name, debug_info->line_number);
	fprintf(file, "%s [Error code: %d]\n", error_message, (int) debug_info->error);
	fprintf(file, "[Operand 1: " INTEGER_SPECIFIER "][Operand 2: " INTEGER_SPECIFIER
		"][Result: " INTEGER_SPECIFIER "][Operand type: " INTEGER_TYPE_NAME
		"][Minimum: " INTEGER_SPECIFIER "][Maximum: " INTEGER_SPECIFIER "][Result mode: %s][Operation: %s]\n",
		debug_info->operand1, debug_info->operand2, debug_info->result,
		debug_info->minimum_value, debug_info->maximum_value, result_mode_name, operation_name);
#undef INTEGER_TYPE_NAME
#undef INTEGER_SPECIFIER
}

static llong_debug_handler_type debug_mode_llong_handler = &debug_mode_default_llong_handler;

llong_debug_handler_type debug_mode_llong_set_handler(llong_debug_handler_type handler)
{
	llong_debug_handler_type previous_handler = debug_mode_llong_handler;
	if (handler != NULL) {
		debug_mode_llong_handler = handler;
	}
	return previous_handler;
}

void debug_mode_llong_reset_handler(void)
{
	debug_mode_llong_handler = &debug_mode_default_llong_handler;
}

#define DEBUG_MODE_HANDLER debug_mode_llong_handler
#define MINIMUM LLONG_MIN
#define MAXIMUM LLONG_MAX

long long debug_mode_llong_add(long long a, long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR +
	typedef long long integer_type;
	typedef unsigned long long unsigned_integer_type;
	typedef llong_debug_info_type debug_info_type;
	integer_type result = 0LL;
	const integer_operation_type operation = integer_operation_addition;
	const integer_operation_error_type error = safer_llong_addition_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long long debug_mode_llong_minus(long long a, long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR -
	typedef long long integer_type;
	typedef unsigned long long unsigned_integer_type;
	typedef llong_debug_info_type debug_info_type;
	integer_type result = 0LL;
	const integer_operation_type operation = integer_operation_subtraction;
	const integer_operation_error_type error = safer_llong_subtraction_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long long debug_mode_llong_multiply(long long a, long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR *
	typedef long long integer_type;
	typedef unsigned long long unsigned_integer_type;
	typedef llong_debug_info_type debug_info_type;
	integer_type result = 0LL;
	const integer_operation_type operation = integer_operation_multiplication;
	const integer_operation_error_type error = safer_llong_multiplication_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned_integer_type) a INTEGER_OPERATOR (unsigned_integer_type) b);
		} else {
			result = a INTEGER_OPERATOR b;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long long debug_mode_llong_divide(long long a, long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR /
	typedef long long integer_type;
	typedef llong_debug_info_type debug_info_type;
	const integer_type zero = 0LL;
	integer_type result = zero;
	const integer_operation_type operation = integer_operation_division;
	const integer_operation_error_type error = safer_llong_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		if (result_mode == integer_result_mode_saturation) {
			if (a < zero) {
				result = MINIMUM;
			} else if (a > zero) {
				result = MAXIMUM;
			}
		}
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else {
			result = MINIMUM;
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

long long debug_mode_llong_remainder(long long a, long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR %
	typedef long long integer_type;
	typedef llong_debug_info_type debug_info_type;
	integer_type result = 0LL;
	const integer_operation_type operation = integer_operation_remainder;
	const integer_operation_error_type error = safer_llong_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER
#endif /* LLONG_MIN and LLONG_MAX */

/* unsigned long long */
#if defined(ULLONG_MAX)
static void debug_mode_default_ullong_handler(const ullong_debug_info_type* debug_info)
{
#define INTEGER_SPECIFIER "%llu"
#define INTEGER_TYPE_NAME "unsigned long long"
	const char *operation_name = NULL, *result_mode_name = NULL, *error_message = NULL;
	FILE *file = stderr;
	assert(debug_info != NULL);
	assert(debug_info->file_name != NULL);
	operation_name = debug_mode_integer_operation_name(debug_info->operation);
	result_mode_name = debug_mode_integer_result_mode_name(debug_info->result_mode);
	error_message = integer_operation_error_message(debug_info->error);
	fprintf(file, "%s (line %d)\n", debug_info->file_name, debug_info->line_number);
	fprintf(file, "%s [Error code: %d]\n", error_message, (int) debug_info->error);
	fprintf(file, "[Operand 1: " INTEGER_SPECIFIER "][Operand 2: " INTEGER_SPECIFIER
		"][Result: " INTEGER_SPECIFIER "][Operand type: " INTEGER_TYPE_NAME
		"][Minimum: " INTEGER_SPECIFIER "][Maximum: " INTEGER_SPECIFIER "][Result mode: %s][Operation: %s]\n",
		debug_info->operand1, debug_info->operand2, debug_info->result,
		debug_info->minimum_value, debug_info->maximum_value, result_mode_name, operation_name);
#undef INTEGER_SPECIFIER
}

static ullong_debug_handler_type debug_mode_ullong_handler = &debug_mode_default_ullong_handler;

ullong_debug_handler_type debug_mode_ullong_set_handler(ullong_debug_handler_type handler)
{
	ullong_debug_handler_type previous_handler = debug_mode_ullong_handler;
	if (handler != NULL) {
		debug_mode_ullong_handler = handler;
	}
	return previous_handler;
}

void debug_mode_ullong_reset_handler(void)
{
	debug_mode_ullong_handler = &debug_mode_default_ullong_handler;
}

#define DEBUG_MODE_HANDLER debug_mode_ullong_handler
#define MINIMUM 0ULL
#define MAXIMUM ULLONG_MAX

unsigned long long debug_mode_ullong_add(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR +
	typedef unsigned long long unsigned_integer_type;
	typedef ullong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0ULL;
	const integer_operation_type operation = integer_operation_addition;
	const integer_operation_error_type error = safer_ullong_addition_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result = (result_mode == integer_result_mode_saturation) ? MAXIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long long debug_mode_ullong_minus(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR -
	typedef unsigned long long unsigned_integer_type;
	typedef ullong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0UL;
	const integer_operation_type operation = integer_operation_subtraction;
	const integer_operation_error_type error = safer_ullong_subtraction_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		result = (result_mode == integer_result_mode_saturation) ? MINIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long long debug_mode_ullong_multiply(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR *
	typedef unsigned long long unsigned_integer_type;
	typedef ullong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0ULL;
	const integer_operation_type operation = integer_operation_multiplication;
	const integer_operation_error_type error = safer_ullong_multiplication_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result = (result_mode == integer_result_mode_saturation) ? MAXIMUM : (a INTEGER_OPERATOR b);
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long long debug_mode_ullong_divide(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR /
	typedef unsigned long long unsigned_integer_type;
	typedef ullong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0ULL;
	const integer_operation_type operation = integer_operation_division;
	const integer_operation_error_type error = safer_ullong_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		if (result_mode == integer_result_mode_saturation) {
			if (a != 0ULL) {
				result = MAXIMUM;
			}
		}
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

unsigned long long debug_mode_ullong_remainder(unsigned long long a, unsigned long long b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#define INTEGER_OPERATOR %
	typedef unsigned long long unsigned_integer_type;
	typedef ullong_debug_info_type debug_info_type;
	unsigned_integer_type result = 0ULL;
	const integer_operation_type operation = integer_operation_remainder;
	const integer_operation_error_type error = safer_ullong_division_check(a, b);
	switch (error) {
	case integer_operation_error_none:
		result = a INTEGER_OPERATOR b;
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		break;
	default:
		assert(Boolean_false);
		break;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
#undef INTEGER_OPERATOR
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER
#endif /* ULLONG_MAX */

STATIC_ASSERT(sizeof(int) > sizeof(int8_t), "The size of int shall be greater than the size of int8_t");
STATIC_ASSERT(sizeof(unsigned int) > sizeof(uint8_t), "The size of unsigned int shall be greater than the size of uint8_t");
STATIC_ASSERT(sizeof(int) >= sizeof(int16_t), "The size of int shall be at least the size of int16_t");
STATIC_ASSERT(sizeof(unsigned int) >= sizeof(uint16_t), "The size of unsigned int shall be at least the size of uint16_t");
STATIC_ASSERT(sizeof(int32_t) == sizeof(int) or sizeof(int32_t) == sizeof(long), "The size of int32_t shall be the size of int or the size of long int.");
STATIC_ASSERT(sizeof(uint32_t) == sizeof(unsigned int) or sizeof(uint32_t) == sizeof(unsigned long), "The size of uint32_t shall be the size of unsigned int or the size of unsigned long int.");

#define DEBUG_MODE_HANDLER debug_mode_int_handler
#define MINIMUM INT8_MIN
#define MAXIMUM INT8_MAX

int8_t debug_mode_i8_add(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int8_t integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_addition;
	const unsigned int maximum_unsigned_value = UINT8_MAX;
	const int iresult = a + b;
	if (iresult < MINIMUM) {
		error = integer_operation_error_signed_integer_result_smaller_than_minimum;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else if (iresult > MAXIMUM) {
		error = integer_operation_error_signed_integer_result_greater_than_maximum;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else {
		result = (integer_type) iresult;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

int8_t debug_mode_i8_minus(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int8_t integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_subtraction;
	const unsigned int maximum_unsigned_value = UINT8_MAX;
	const int iresult = a - b;
	if (iresult < MINIMUM) {
		error = integer_operation_error_signed_integer_result_smaller_than_minimum;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else if (iresult > MAXIMUM) {
		error = integer_operation_error_signed_integer_result_greater_than_maximum;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else {
		result = (integer_type) iresult;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

int8_t debug_mode_i8_multiply(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int8_t integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_multiplication;
	const unsigned int maximum_unsigned_value = UINT8_MAX;
	const int iresult = a * b;
	if (iresult < MINIMUM) {
		error = integer_operation_error_signed_integer_result_smaller_than_minimum;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else if (iresult > MAXIMUM) {
		error = integer_operation_error_signed_integer_result_greater_than_maximum;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else {
		result = (integer_type) iresult;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

int8_t debug_mode_i8_divide(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int8_t integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_division;
	if (b == 0) {
		error = integer_operation_error_division_of_signed_integer_by_zero;
		if (result_mode == integer_result_mode_saturation) {
			if (a < 0) {
				result = MINIMUM;
			} else if (a > 0) {
				result = MAXIMUM;
			}
		}
	} else if (a == MINIMUM and b == -1) {
		error = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else {
			result = MINIMUM;
		}
	} else {
		result = (integer_type) (a / b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

int8_t debug_mode_i8_remainder(int8_t a, int8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int8_t integer_type;
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_remainder;
	if (b == 0) {
		error = integer_operation_error_division_of_signed_integer_by_zero;
	} else if (a == MINIMUM and b == -1) {
		error = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
	} else {
		result = (integer_type) (a % b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER
#define DEBUG_MODE_HANDLER debug_mode_uint_handler
#define MINIMUM 0U
#define MAXIMUM UINT8_MAX

uint8_t debug_mode_u8_add(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint8_t unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_addition;
	const unsigned int maximum_unsigned_value = UINT8_MAX;
	if (b <= ((unsigned int) MAXIMUM - a)) {
		result = (unsigned_integer_type) ((unsigned int) a + (unsigned int) b);
	} else {
		error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (unsigned_integer_type) (((unsigned int) a + (unsigned int) b) % (maximum_unsigned_value + 1U)); 
		} else {
			result = (unsigned_integer_type) ((unsigned int) a + (unsigned int) b);
		}
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

uint8_t debug_mode_u8_minus(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint8_t unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_subtraction;
	const unsigned int maximum_unsigned_value = UINT8_MAX;
	if (a >= b) {
		result = (unsigned_integer_type) ((unsigned int) a - (unsigned int) b);
	} else {
		error = integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (unsigned_integer_type) (((unsigned int) a - (unsigned int) b) % (maximum_unsigned_value + 1U)); 
		} else {
			result = (unsigned_integer_type) ((unsigned int) a - (unsigned int) b);
		}
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

uint8_t debug_mode_u8_multiply(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint8_t unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_multiplication;
	const unsigned int maximum_unsigned_value = UINT8_MAX;
	const unsigned int uresult = (unsigned int) a * (unsigned int) b;
	if (uresult <= MAXIMUM) {
		result = (unsigned_integer_type) uresult;
	} else {
		error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (unsigned_integer_type) (uresult % (maximum_unsigned_value + 1U)); 
		} else {
			result = (unsigned_integer_type) uresult;
		}
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

uint8_t debug_mode_u8_divide(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint8_t unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_division;
	if (b == 0U) {
		error = integer_operation_error_division_of_unsigned_integer_by_zero;
		if (result_mode == integer_result_mode_saturation) {
			if (a != 0U) {
				result = MAXIMUM;
			}
		}
	} else {
		result = (unsigned_integer_type) ((unsigned int) a / (unsigned int) b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

uint8_t debug_mode_u8_remainder(uint8_t a, uint8_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint8_t unsigned_integer_type;
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_remainder;
	if (b == 0U) {
		error = integer_operation_error_division_of_unsigned_integer_by_zero;
	} else {
		result = (unsigned_integer_type) ((unsigned int) a % (unsigned int) b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
	return result;
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER
#define DEBUG_MODE_HANDLER debug_mode_int_handler
#define MINIMUM INT16_MIN
#define MAXIMUM INT16_MAX

int16_t debug_mode_i16_add(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int16_t integer_type;
#if (INT_MIN < MINIMUM) && (INT_MAX > MAXIMUM)
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_addition;
	const unsigned int maximum_unsigned_value = UINT16_MAX;
	const int iresult = a + b;
	if (iresult < MINIMUM) {
		error = integer_operation_error_signed_integer_result_smaller_than_minimum;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else if (iresult > MAXIMUM) {
		error = integer_operation_error_signed_integer_result_greater_than_maximum;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else {
		result = (integer_type) iresult;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	integer_type result = (integer_type) debug_mode_int_add(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

int16_t debug_mode_i16_minus(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int16_t integer_type;
#if (INT_MIN < MINIMUM) && (INT_MAX > MAXIMUM)
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_subtraction;
	const unsigned int maximum_unsigned_value = UINT16_MAX;
	const int iresult = a - b;
	if (iresult < MINIMUM) {
		error = integer_operation_error_signed_integer_result_smaller_than_minimum;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else if (iresult > MAXIMUM) {
		error = integer_operation_error_signed_integer_result_greater_than_maximum;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else {
		result = (integer_type) iresult;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	integer_type result = (integer_type) debug_mode_int_minus(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

int16_t debug_mode_i16_multiply(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int16_t integer_type;
#if (INT_MIN < MINIMUM) && (INT_MAX > MAXIMUM)
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_multiplication;
	const unsigned int maximum_unsigned_value = UINT16_MAX;
	const int iresult = a * b;
	if (iresult < MINIMUM) {
		error = integer_operation_error_signed_integer_result_smaller_than_minimum;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else if (iresult > MAXIMUM) {
		error = integer_operation_error_signed_integer_result_greater_than_maximum;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (integer_type) ((unsigned int) iresult % (maximum_unsigned_value + 1U));
		} else {
			result = (integer_type) iresult;
		}
	} else {
		result = (integer_type) iresult;
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	integer_type result = (integer_type) debug_mode_int_multiply(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

int16_t debug_mode_i16_divide(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int16_t integer_type;
#if (INT_MIN < MINIMUM) && (INT_MAX > MAXIMUM)
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_division;
	if (b == 0) {
		error = integer_operation_error_division_of_signed_integer_by_zero;
		if (result_mode == integer_result_mode_saturation) {
			if (a < 0) {
				result = MINIMUM;
			} else if (a > 0) {
				result = MAXIMUM;
			}
		}
	} else if (a == MINIMUM and b == -1) {
		error = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else {
			result = MINIMUM;
		}
	} else {
		result = (integer_type) (a / b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	integer_type result = (integer_type) debug_mode_int_divide(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

int16_t debug_mode_i16_remainder(int16_t a, int16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef int16_t integer_type;
#if (INT_MIN < MINIMUM) && (INT_MAX > MAXIMUM)
	typedef int_debug_info_type debug_info_type;
	integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_division;
	if (b == 0) {
		error = integer_operation_error_division_of_signed_integer_by_zero;
	} else if (a == MINIMUM and b == -1) {
		error = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
	} else {
		result = (integer_type) (a % b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	integer_type result = (integer_type) debug_mode_int_remainder(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER
#define DEBUG_MODE_HANDLER debug_mode_uint_handler
#define MINIMUM 0U
#define MAXIMUM UINT16_MAX

uint16_t debug_mode_u16_add(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint16_t unsigned_integer_type;
#if UINT_MAX > UINT16_MAX
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_addition;
	const unsigned int maximum_unsigned_value = UINT16_MAX;
	if (b <= ((unsigned int) MAXIMUM - a)) {
		result = (unsigned_integer_type) ((unsigned int) a + (unsigned int) b);
	} else {
		error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (unsigned_integer_type) (((unsigned int) a + (unsigned int) b) % (maximum_unsigned_value + 1U)); 
		} else {
			result = (unsigned_integer_type) ((unsigned int) a + (unsigned int) b);
		}
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	unsigned_integer_type result = (unsigned_integer_type) debug_mode_uint_add(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

uint16_t debug_mode_u16_minus(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint16_t unsigned_integer_type;
#if UINT_MAX > UINT16_MAX
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_subtraction;
	const unsigned int maximum_unsigned_value = UINT16_MAX;
	if (a >= b) {
		result = (unsigned_integer_type) ((unsigned int) a - (unsigned int) b);
	} else {
		error = integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
		if (result_mode == integer_result_mode_saturation) {
			result = MINIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (unsigned_integer_type) (((unsigned int) a - (unsigned int) b) % (maximum_unsigned_value + 1U)); 
		} else {
			result = (unsigned_integer_type) ((unsigned int) a - (unsigned int) b);
		}
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	unsigned_integer_type result = (unsigned_integer_type) debug_mode_uint_minus(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

uint16_t debug_mode_u16_multiply(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint16_t unsigned_integer_type;
#if UINT_MAX > UINT16_MAX
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_multiplication;
	const unsigned int maximum_unsigned_value = UINT16_MAX;
	const unsigned int uresult = (unsigned int) a * (unsigned int) b;
	if (uresult <= MAXIMUM) {
		result = (unsigned_integer_type) uresult;
	} else {
		error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		if (result_mode == integer_result_mode_saturation) {
			result = MAXIMUM;
		} else if (result_mode == integer_result_mode_wraparound) {
			result = (unsigned_integer_type) (uresult % (maximum_unsigned_value + 1U)); 
		} else {
			result = (unsigned_integer_type) uresult;
		}
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	unsigned_integer_type result = (unsigned_integer_type) debug_mode_uint_multiply(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

uint16_t debug_mode_u16_divide(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint16_t unsigned_integer_type;
#if UINT_MAX > UINT16_MAX
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_division;
	if (b == 0U) {
		error = integer_operation_error_division_of_unsigned_integer_by_zero;
		if (result_mode == integer_result_mode_saturation) {
			if (a != 0U) {
				result = MAXIMUM;
			}
		}
	} else {
		result = (unsigned_integer_type) ((unsigned int) a / (unsigned int) b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	unsigned_integer_type result = (unsigned_integer_type) debug_mode_uint_divide(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

uint16_t debug_mode_u16_remainder(uint16_t a, uint16_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
	typedef uint16_t unsigned_integer_type;
#if UINT_MAX > UINT16_MAX
	typedef uint_debug_info_type debug_info_type;
	unsigned_integer_type result = 0U;
	integer_operation_error_type error = integer_operation_error_none;
	const integer_operation_type operation = integer_operation_remainder;
	if (b == 0U) {
		error = integer_operation_error_division_of_unsigned_integer_by_zero;
	} else {
		result = (unsigned_integer_type) ((unsigned int) a % (unsigned int) b);
	}
	if (error != integer_operation_error_none) {
		debug_info_type debug_info = {0};
		debug_info.file_name = file_name;
		debug_info.line_number = line_number;
		debug_info.operand1 = a;
		debug_info.operand2 = b;
		debug_info.result = result;
		debug_info.minimum_value = MINIMUM;
		debug_info.maximum_value = MAXIMUM;
		debug_info.operation = operation;
		debug_info.result_mode = result_mode;
		debug_info.error = error;
		assert(DEBUG_MODE_HANDLER != NULL);
		DEBUG_MODE_HANDLER(&debug_info);
	}
#else
	unsigned_integer_type result = (unsigned_integer_type) debug_mode_uint_remainder(a, b, result_mode, file_name, line_number);
#endif
	return result;
}

#undef MAXIMUM
#undef MINIMUM
#undef DEBUG_MODE_HANDLER
#define MINIMUM INT32_MIN
#define MAXIMUM INT32_MAX

int32_t debug_mode_i32_add(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (INT_MIN == MINIMUM) && (INT_MAX == MAXIMUM)
	STATIC_ASSERT(sizeof(int) == sizeof(int32_t), "The size of int must be the same as the size of int32_t.");
	return debug_mode_int_add(a, b, result_mode, file_name, line_number);
#elif (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	STATIC_ASSERT(sizeof(long) == sizeof(int32_t), "The size of long int must be the same as the size of int32_t.");
	return debug_mode_long_add(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int32_t debug_mode_i32_minus(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (INT_MIN == MINIMUM) && (INT_MAX == MAXIMUM)
	return debug_mode_int_minus(a, b, result_mode, file_name, line_number);
#elif (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_minus(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int32_t debug_mode_i32_multiply(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (INT_MIN == MINIMUM) && (INT_MAX == MAXIMUM)
	return debug_mode_int_multiply(a, b, result_mode, file_name, line_number);
#elif (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_multiply(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int32_t debug_mode_i32_divide(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (INT_MIN == MINIMUM) && (INT_MAX == MAXIMUM)
	return debug_mode_int_divide(a, b, result_mode, file_name, line_number);
#elif (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_divide(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int32_t debug_mode_i32_remainder(int32_t a, int32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (INT_MIN == MINIMUM) && (INT_MAX == MAXIMUM)
	return debug_mode_int_remainder(a, b, result_mode, file_name, line_number);
#elif (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_remainder(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

#undef MAXIMUM
#undef MINIMUM
#define MAXIMUM UINT32_MAX

uint32_t debug_mode_u32_add(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if UINT_MAX == MAXIMUM
	STATIC_ASSERT(sizeof(unsigned int) == sizeof(uint32_t), "The size of unsigned int must be the same as the size of uint32_t.");
	return debug_mode_uint_add(a, b, result_mode, file_name, line_number);
#elif ULONG_MAX == MAXIMUM
	STATIC_ASSERT(sizeof(unsigned long) == sizeof(uint32_t), "The size of unsigned long int must be the same as the size of uint32_t.");
	return debug_mode_ulong_add(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint32_t debug_mode_u32_minus(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if UINT_MAX == MAXIMUM
	return debug_mode_uint_minus(a, b, result_mode, file_name, line_number);
#elif ULONG_MAX == MAXIMUM
	return debug_mode_ulong_minus(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint32_t debug_mode_u32_multiply(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if UINT_MAX == MAXIMUM
	return debug_mode_uint_multiply(a, b, result_mode, file_name, line_number);
#elif ULONG_MAX == MAXIMUM
	return debug_mode_ulong_multiply(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint32_t debug_mode_u32_divide(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if UINT_MAX == MAXIMUM
	return debug_mode_uint_divide(a, b, result_mode, file_name, line_number);
#elif ULONG_MAX == MAXIMUM
	return debug_mode_ulong_divide(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint32_t debug_mode_u32_remainder(uint32_t a, uint32_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if UINT_MAX == MAXIMUM
	return debug_mode_uint_remainder(a, b, result_mode, file_name, line_number);
#elif ULONG_MAX == MAXIMUM
	return debug_mode_ulong_remainder(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

#undef MAXIMUM

#if defined(INT64_MIN) && defined(INT64_MAX)
#define MINIMUM INT64_MIN
#define MAXIMUM INT64_MAX
int64_t debug_mode_i64_add(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	STATIC_ASSERT(sizeof(long) == sizeof(int64_t), "The size of long int must be the same as the size of int64_t.");
	return debug_mode_long_add(a, b, result_mode, file_name, line_number);
#elif (LLONG_MIN == MINIMUM) && (LLONG_MAX == MAXIMUM)
	STATIC_ASSERT(sizeof(long long) == sizeof(int64_t), "The size of long long int must be the same as the size of int64_t.");
	return debug_mode_llong_add(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int64_t debug_mode_i64_minus(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_minus(a, b, result_mode, file_name, line_number);
#elif (LLONG_MIN == MINIMUM) && (LLONG_MAX == MAXIMUM)
	return debug_mode_llong_minus(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int64_t debug_mode_i64_multiply(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_multiply(a, b, result_mode, file_name, line_number);
#elif (LLONG_MIN == MINIMUM) && (LLONG_MAX == MAXIMUM)
	return debug_mode_llong_multiply(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int64_t debug_mode_i64_divide(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_divide(a, b, result_mode, file_name, line_number);
#elif (LLONG_MIN == MINIMUM) && (LLONG_MAX == MAXIMUM)
	return debug_mode_llong_divide(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

int64_t debug_mode_i64_remainder(int64_t a, int64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (LONG_MIN == MINIMUM) && (LONG_MAX == MAXIMUM)
	return debug_mode_long_remainder(a, b, result_mode, file_name, line_number);
#elif (LLONG_MIN == MINIMUM) && (LLONG_MAX == MAXIMUM)
	return debug_mode_llong_remainder(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}
#undef MAXIMUM
#undef MINIMUM
#endif /* INT64_MIN and INT64_MAX */

#if defined(UINT64_MAX)
#define MAXIMUM UINT64_MAX
uint64_t debug_mode_u64_add(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if ULONG_MAX == MAXIMUM
	STATIC_ASSERT(sizeof(unsigned long) == sizeof(uint64_t), "The size of unsigned long must be the same as the size of uint64_t.");
	return debug_mode_ulong_add(a, b, result_mode, file_name, line_number);
#elif ULLONG_MAX == MAXIMUM
	STATIC_ASSERT(sizeof(unsigned long long) == sizeof(uint64_t), "The size of unsigned long long must be the same as the size of uint64_t.");
	return debug_mode_ullong_add(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint64_t debug_mode_u64_minus(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if ULONG_MAX == MAXIMUM
	return debug_mode_ulong_minus(a, b, result_mode, file_name, line_number);
#elif ULLONG_MAX == MAXIMUM
	return debug_mode_ullong_minus(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint64_t debug_mode_u64_multiply(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if ULONG_MAX == MAXIMUM
	return debug_mode_ulong_multiply(a, b, result_mode, file_name, line_number);
#elif ULLONG_MAX == MAXIMUM
	return debug_mode_ullong_multiply(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint64_t debug_mode_u64_divide(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if ULONG_MAX == MAXIMUM
	return debug_mode_ulong_divide(a, b, result_mode, file_name, line_number);
#elif ULLONG_MAX == MAXIMUM
	return debug_mode_ullong_divide(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

uint64_t debug_mode_u64_remainder(uint64_t a, uint64_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if ULONG_MAX == MAXIMUM
	return debug_mode_ulong_remainder(a, b, result_mode, file_name, line_number);
#elif ULLONG_MAX == MAXIMUM
	return debug_mode_ullong_remainder(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}
#undef MAXIMUM
#endif /* UINT64_MAX */

ptrdiff_t debug_mode_ptrdiff_add(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
	STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int16_t), "The size of ptrdiff_t must be the same as the size of int16_t.");
	return debug_mode_i16_add(a, b, result_mode, file_name, line_number);
#elif (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
	STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int32_t), "The size of ptrdiff_t must be the same as the size of int32_t.");
	return debug_mode_i32_add(a, b, result_mode, file_name, line_number);
#elif defined(INT64_MIN) && (PTRDIFF_MIN == INT64_MIN) && defined(INT64_MAX) && (PTRDIFF_MAX == INT64_MAX)
	STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int64_t), "The size of ptrdiff_t must be the same as the size of int64_t.");
	return debug_mode_i64_add(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

ptrdiff_t debug_mode_ptrdiff_minus(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
	return debug_mode_i16_minus(a, b, result_mode, file_name, line_number);
#elif (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
	return debug_mode_i32_minus(a, b, result_mode, file_name, line_number);
#elif defined(INT64_MIN) && (PTRDIFF_MIN == INT64_MIN) && defined(INT64_MAX) && (PTRDIFF_MAX == INT64_MAX)
	return debug_mode_i64_minus(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

ptrdiff_t debug_mode_ptrdiff_multiply(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
	return debug_mode_i16_multiply(a, b, result_mode, file_name, line_number);
#elif (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
	return debug_mode_i32_multiply(a, b, result_mode, file_name, line_number);
#elif defined(INT64_MIN) && (PTRDIFF_MIN == INT64_MIN) && defined(INT64_MAX) && (PTRDIFF_MAX == INT64_MAX)
	return debug_mode_i64_multiply(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

ptrdiff_t debug_mode_ptrdiff_divide(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
	return debug_mode_i16_divide(a, b, result_mode, file_name, line_number);
#elif (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
	return debug_mode_i32_divide(a, b, result_mode, file_name, line_number);
#elif defined(INT64_MIN) && (PTRDIFF_MIN == INT64_MIN) && defined(INT64_MAX) && (PTRDIFF_MAX == INT64_MAX)
	return debug_mode_i64_divide(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

ptrdiff_t debug_mode_ptrdiff_remainder(ptrdiff_t a, ptrdiff_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
	return debug_mode_i16_remainder(a, b, result_mode, file_name, line_number);
#elif (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
	return debug_mode_i32_remainder(a, b, result_mode, file_name, line_number);
#elif defined(INT64_MIN) && (PTRDIFF_MIN == INT64_MIN) && defined(INT64_MAX) && (PTRDIFF_MAX == INT64_MAX)
	return debug_mode_i64_remainder(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

size_t debug_mode_size_add(size_t a, size_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if SIZE_MAX == UINT16_MAX
	STATIC_ASSERT(sizeof(size_t) == sizeof(uint16_t), "The size of size_t must be the same as the size of uint16_t.");
	return debug_mode_u16_add(a, b, result_mode, file_name, line_number);
#elif SIZE_MAX == UINT32_MAX
	STATIC_ASSERT(sizeof(size_t) == sizeof(uint32_t), "The size of size_t must be the same as the size of uint32_t.");
	return debug_mode_u32_add(a, b, result_mode, file_name, line_number);
#elif defined(UINT64_MAX) && (SIZE_MAX == UINT64_MAX)
	STATIC_ASSERT(sizeof(size_t) == sizeof(uint64_t), "The size of size_t must be the same as the size of uint64_t.");
	return debug_mode_u64_add(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

size_t debug_mode_size_minus(size_t a, size_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if SIZE_MAX == UINT16_MAX
	return debug_mode_u16_minus(a, b, result_mode, file_name, line_number);
#elif SIZE_MAX == UINT32_MAX
	return debug_mode_u32_minus(a, b, result_mode, file_name, line_number);
#elif defined(UINT64_MAX) && (SIZE_MAX == UINT64_MAX)
	return debug_mode_u64_minus(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

size_t debug_mode_size_multiply(size_t a, size_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if SIZE_MAX == UINT16_MAX
	return debug_mode_u16_multiply(a, b, result_mode, file_name, line_number);
#elif SIZE_MAX == UINT32_MAX
	return debug_mode_u32_multiply(a, b, result_mode, file_name, line_number);
#elif defined(UINT64_MAX) && (SIZE_MAX == UINT64_MAX)
	return debug_mode_u64_multiply(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}

size_t debug_mode_size_divide(size_t a, size_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
{
#if SIZE_MAX == UINT16_MAX
	return debug_mode_u16_divide(a, b, result_mode, file_name, line_number);
#elif SIZE_MAX == UINT32_MAX
	return debug_mode_u32_divide(a, b, result_mode, file_name, line_number);
#elif defined(UINT64_MAX) && (SIZE_MAX == UINT64_MAX)
	return debug_mode_u64_divide(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}
}

size_t debug_mode_size_remainder(size_t a, size_t b, integer_result_mode_type result_mode, const char *file_name, int line_number)
{
#if SIZE_MAX == UINT16_MAX
	return debug_mode_u16_remainder(a, b, result_mode, file_name, line_number);
#elif SIZE_MAX == UINT32_MAX
	return debug_mode_u32_remainder(a, b, result_mode, file_name, line_number);
#elif defined(UINT64_MAX) && (SIZE_MAX == UINT64_MAX)
	return debug_mode_u64_remainder(a, b, result_mode, file_name, line_number);
#else
#error "Error: The debug mode operation cannot be implemented properly."
#endif
}
