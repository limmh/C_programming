#include "safer_integer_conversion.h"
#include "static_assert.h"
#include <assert.h>
#include <iso646.h>
#include <limits.h>
#include <stddef.h> 

const char *integer_conversion_error_message(integer_conversion_error_type error)
{
	const char *message = NULL;
	switch (error) {
	case integer_conversion_error_none:
		message = "";
		break;
	case integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer:
		message = "The negative source signed value is smaller than the minimum of the target signed integer.";
		break;
	case integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer:
		message = "The positive source signed value is greater than the maximum value of the target signed integer.";
		break;
	case integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer:
		message = "The source unsigned value is greater than the maximum value of the target signed integer.";
		break;
	case integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer:
		message = "The negative source signed value cannot be represented by the target unsigned integer.";
		break;
	case integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer:
		message = "The positive source signed value is greater than the maximum value of the target unsigned integer.";
		break;
	case integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer:
		message = "The source unsigned value is greater than the maximum value of the target unsigned integer.";
		break;
	default:
		message = "Unknown error.";
		break;
	}
	assert(message != NULL);
	return message;
}

static char_conversion_result_type char_conv_result_from_schar_conv_result(schar_conversion_result_type src_result)
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (char) src_result.value;
	result.error = src_result.error;
	return result;
}

static char_conversion_result_type char_conv_result_from_uchar_conv_result(uchar_conversion_result_type src_result)
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (char) src_result.value;
	result.error = src_result.error;
	return result;
}

STATIC_ASSERT((CHAR_MIN == SCHAR_MIN and CHAR_MAX == SCHAR_MAX) or (CHAR_MIN == 0 and CHAR_MAX == UCHAR_MAX),
	"The assumption is not valid. Please check your compiler for more info.");

char_conversion_result_type safer_char_from_char(char value)
{
	if (CHAR_MIN < 0) {
		return char_conv_result_from_schar_conv_result(safer_schar_from_schar((signed char) value));
	} else {
		return char_conv_result_from_uchar_conv_result(safer_uchar_from_uchar((unsigned char) value));
	}
}

char_conversion_result_type safer_char_from_schar(signed char value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_schar(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_schar(value));
#endif
}

char_conversion_result_type safer_char_from_uchar(unsigned char value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_uchar(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_uchar(value));
#endif
}

char_conversion_result_type safer_char_from_short(short value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_short(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_short(value));
#endif
}

char_conversion_result_type safer_char_from_ushort(unsigned short value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_ushort(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_ushort(value));
#endif
}

char_conversion_result_type safer_char_from_int(int value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_int(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_int(value));
#endif
}

char_conversion_result_type safer_char_from_uint(unsigned int value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_uint(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_uint(value));
#endif
}

char_conversion_result_type safer_char_from_long(long value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_long(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_long(value));
#endif
}

char_conversion_result_type safer_char_from_ulong(unsigned long value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_ulong(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_ulong(value));
#endif
}

char_conversion_result_type safer_char_from_llong(long long value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_llong(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_llong(value));
#endif
}

char_conversion_result_type safer_char_from_ullong(unsigned long long value)
{
#if CHAR_MIN < 0
	return char_conv_result_from_schar_conv_result(safer_schar_from_ullong(value));
#else
	return char_conv_result_from_uchar_conv_result(safer_uchar_from_ullong(value));
#endif
}

schar_conversion_result_type safer_schar_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_schar_from_schar((signed char) value);
#else
	return safer_schar_from_uchar((unsigned char) value);
#endif
}

schar_conversion_result_type safer_schar_from_schar(signed char value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

schar_conversion_result_type safer_schar_from_uchar(unsigned char value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if ((int) value > SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_short(short value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SCHAR_MIN) {
		result.value = SCHAR_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_ushort(unsigned short value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if ((unsigned int) value > (unsigned int) SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_int(int value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SCHAR_MIN) {
		result.value = SCHAR_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_uint(unsigned int value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned int) SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_long(long value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SCHAR_MIN) {
		result.value = SCHAR_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_ulong(unsigned long value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned long) SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_llong(long long value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SCHAR_MIN) {
		result.value = SCHAR_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

schar_conversion_result_type safer_schar_from_ullong(unsigned long long value)
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned long long) SCHAR_MAX) {
		result.value = SCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (signed char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_uchar_from_schar((signed char) value);
#else
	return safer_uchar_from_uchar((unsigned char) value);
#endif
}

uchar_conversion_result_type safer_uchar_from_schar(signed char value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_uchar(unsigned char value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uchar_conversion_result_type safer_uchar_from_short(short value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int) UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_ushort(unsigned short value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_int(int value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int) UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_uint(unsigned int value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_long(long value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (long) UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_ulong(unsigned long value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_llong(long long value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (long long) UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

uchar_conversion_result_type safer_uchar_from_ullong(unsigned long long value)
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UCHAR_MAX) {
		result.value = UCHAR_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned char) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_short_from_schar((signed char) value);
#else
	return safer_short_from_uchar((unsigned char) value);
#endif
}

short_conversion_result_type safer_short_from_schar(signed char value)
{
	STATIC_ASSERT(SHRT_MIN <= SCHAR_MIN and SHRT_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

short_conversion_result_type safer_short_from_uchar(unsigned char value)
{
	STATIC_ASSERT(SHRT_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (short) value;
	return result;
}

short_conversion_result_type safer_short_from_short(short value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

short_conversion_result_type safer_short_from_ushort(unsigned short value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if ((unsigned int) value > (unsigned int) SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_int(int value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SHRT_MIN) {
		result.value = SHRT_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_uint(unsigned int value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned int) SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_long(long value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SHRT_MIN) {
		result.value = SHRT_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_ulong(unsigned long value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned long) SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_llong(long long value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < SHRT_MIN) {
		result.value = SHRT_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

short_conversion_result_type safer_short_from_ullong(unsigned long long value)
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned long long) SHRT_MAX) {
		result.value = SHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_ushort_from_schar((signed char) value);
#else
	return safer_ushort_from_uchar((unsigned char) value);
#endif
}

ushort_conversion_result_type safer_ushort_from_schar(signed char value)
{
	STATIC_ASSERT(SCHAR_MAX <= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_uchar(unsigned char value)
{
	STATIC_ASSERT(UCHAR_MAX <= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

ushort_conversion_result_type safer_ushort_from_short(short value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_ushort(unsigned short value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

ushort_conversion_result_type safer_ushort_from_int(int value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned int) value > (unsigned int) USHRT_MAX) {
		result.value = USHRT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_uint(unsigned int value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > USHRT_MAX) {
		result.value = USHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_long(long value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned long) value > (unsigned long) USHRT_MAX) {
		result.value = USHRT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_ulong(unsigned long value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > USHRT_MAX) {
		result.value = USHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_llong(long long value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned long long) value > (unsigned long long) USHRT_MAX) {
		result.value = USHRT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

ushort_conversion_result_type safer_ushort_from_ullong(unsigned long long value)
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > USHRT_MAX) {
		result.value = USHRT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned short) value;
	}
	return result;
}

int_conversion_result_type safer_int_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_int_from_schar((signed char) value);
#else
	return safer_int_from_uchar((unsigned char) value);
#endif
}

int_conversion_result_type safer_int_from_schar(signed char value)
{
	STATIC_ASSERT(INT_MIN <= SCHAR_MIN and INT_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int_conversion_result_type safer_int_from_uchar(unsigned char value)
{
	STATIC_ASSERT(INT_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int_conversion_result_type safer_int_from_short(short value)
{
	STATIC_ASSERT(INT_MAX >= SHRT_MAX, "Update the implementation if the assumption is not valid.");
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int_conversion_result_type safer_int_from_ushort(unsigned short value)
{
	STATIC_ASSERT(UINT_MAX >= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	int_conversion_result_type result = {0, integer_conversion_error_none};
	if ((unsigned int) value > (unsigned int) INT_MAX) {
		result.value = INT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int) value;
	}
	return result;
}

int_conversion_result_type safer_int_from_int(int value)
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int_conversion_result_type safer_int_from_uint(unsigned int value)
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	if ((unsigned int) value > (unsigned int) INT_MAX) {
		result.value = INT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int) value;
	}
	return result;
}

int_conversion_result_type safer_int_from_long(long value)
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT_MIN) {
		result.value = INT_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT_MAX) {
		result.value = INT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int) value;
	}
	return result;
}

int_conversion_result_type safer_int_from_ulong(unsigned long value)
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned long) INT_MAX) {
		result.value = INT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int) value;
	}
	return result;
}

int_conversion_result_type safer_int_from_llong(long long value)
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT_MIN) {
		result.value = INT_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT_MAX) {
		result.value = INT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int) value;
	}
	return result;
}

int_conversion_result_type safer_int_from_ullong(unsigned long long value)
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (unsigned long long) INT_MAX) {
		result.value = INT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_uint_from_schar((signed char) value);
#else
	return safer_uint_from_uchar((unsigned char) value);
#endif
}

uint_conversion_result_type safer_uint_from_schar(signed char value)
{
	STATIC_ASSERT(UINT_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_uchar(unsigned char value)
{
	STATIC_ASSERT(UINT_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint_conversion_result_type safer_uint_from_short(short value)
{
	STATIC_ASSERT(UINT_MAX >= SHRT_MAX, "Update the implementation if the assumption is not valid.");
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_ushort(unsigned short value)
{
	STATIC_ASSERT(UINT_MAX >= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint_conversion_result_type safer_uint_from_int(int value)
{
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_uint(unsigned int value)
{
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint_conversion_result_type safer_uint_from_long(long value)
{
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned long) value > (unsigned long) UINT_MAX) {
		result.value = UINT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_ulong(unsigned long value)
{
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value > UINT_MAX) {
		result.value = UINT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_llong(long long value)
{
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned long long) value > (unsigned long long) UINT_MAX) {
		result.value = UINT_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

uint_conversion_result_type safer_uint_from_ullong(unsigned long long value)
{
	uint_conversion_result_type result = {0U, integer_conversion_error_none};
	if (value > UINT_MAX) {
		result.value = UINT_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned int) value;
	}
	return result;
}

long_conversion_result_type safer_long_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_long_from_schar((signed char) value);
#else
	return safer_long_from_uchar((unsigned char) value);
#endif
}

long_conversion_result_type safer_long_from_schar(signed char value)
{
	STATIC_ASSERT(LONG_MIN <= SCHAR_MIN and LONG_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	result.value = value;
	return result;
}

long_conversion_result_type safer_long_from_uchar(unsigned char value)
{
	STATIC_ASSERT(LONG_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	result.value = value;
	return result;
}

long_conversion_result_type safer_long_from_short(short value)
{
	STATIC_ASSERT(LONG_MIN <= SHRT_MIN and LONG_MAX >= SHRT_MAX, "Update the implementation if the assumption is not valid.");
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	result.value = value;
	return result;
}

long_conversion_result_type safer_long_from_ushort(unsigned short value)
{
	STATIC_ASSERT(LONG_MAX >= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	result.value = value;
	return result;
}

long_conversion_result_type safer_long_from_int(int value)
{
	STATIC_ASSERT(LONG_MIN <= INT_MIN and LONG_MAX >= INT_MAX, "Update the implementation if the assumption is not valid.");
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	result.value = value;
	return result;
}

long_conversion_result_type safer_long_from_uint(unsigned int value)
{
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	if ((unsigned long) value > (unsigned long) LONG_MAX) {
		result.value = LONG_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = value;
	}
	return result;
}

long_conversion_result_type safer_long_from_long(long value)
{
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	result.value = value;
	return result;
}

long_conversion_result_type safer_long_from_ulong(unsigned long value)
{
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	if (value > (unsigned long) LONG_MAX) {
		result.value = LONG_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (long) value;
	}
	return result;
}

long_conversion_result_type safer_long_from_llong(long long value)
{
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	if (value < LONG_MIN) {
		result.value = LONG_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > LONG_MAX) {
		result.value = LONG_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (long) value;
	}
	return result;
}

long_conversion_result_type safer_long_from_ullong(unsigned long long value)
{
	long_conversion_result_type result = {0L, integer_conversion_error_none};
	if (value > (unsigned long long) LONG_MAX) {
		result.value = LONG_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (long) value;
	}
	return result;
}

ulong_conversion_result_type safer_ulong_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_ulong_from_schar((signed char) value);
#else
	return safer_ulong_from_uchar((unsigned char) value);
#endif
}

ulong_conversion_result_type safer_ulong_from_schar(signed char value)
{
	STATIC_ASSERT(ULONG_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0UL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long) value;
	}
	return result;
}

ulong_conversion_result_type safer_ulong_from_uchar(unsigned char value)
{
	STATIC_ASSERT(ULONG_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ulong_conversion_result_type safer_ulong_from_short(short value)
{
	STATIC_ASSERT(ULONG_MAX >= SHRT_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0UL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long) value;
	}
	return result;

}

ulong_conversion_result_type safer_ulong_from_ushort(unsigned short value)
{
	STATIC_ASSERT(ULONG_MAX >= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ulong_conversion_result_type safer_ulong_from_int(int value)
{
	STATIC_ASSERT(ULONG_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0UL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long) value;
	}
	return result;

}

ulong_conversion_result_type safer_ulong_from_uint(unsigned int value)
{
	STATIC_ASSERT(ULONG_MAX >= UINT_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ulong_conversion_result_type safer_ulong_from_long(long value)
{
	STATIC_ASSERT(ULONG_MAX >= LONG_MAX, "Update the implementation if the assumption is not valid.");
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0UL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long) value;
	}
	return result;

}

ulong_conversion_result_type safer_ulong_from_ulong(unsigned long value)
{
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ulong_conversion_result_type safer_ulong_from_llong(long long value)
{
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0UL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned long long) value > (unsigned long long) ULONG_MAX) {
		result.value = ULONG_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned long) value;
	}
	return result;
}

ulong_conversion_result_type safer_ulong_from_ullong(unsigned long long value)
{
	ulong_conversion_result_type result = {0UL, integer_conversion_error_none};
	if (value > ULONG_MAX) {
		result.value = ULONG_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned long) value;
	}
	return result;
}

llong_conversion_result_type safer_llong_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_llong_from_schar((signed char) value);
#else
	return safer_llong_from_uchar((unsigned char) value);
#endif
}

llong_conversion_result_type safer_llong_from_schar(signed char value)
{
	STATIC_ASSERT(LLONG_MIN <= SCHAR_MIN and LLONG_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_uchar(unsigned char value)
{
	STATIC_ASSERT(LLONG_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_short(short value)
{
	STATIC_ASSERT(LLONG_MIN <= SHRT_MIN and LLONG_MAX >= SHRT_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_ushort(unsigned short value)
{
	STATIC_ASSERT(LLONG_MAX >= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_int(int value)
{
	STATIC_ASSERT(LLONG_MIN <= INT_MIN and LLONG_MAX >= INT_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_uint(unsigned int value)
{
	STATIC_ASSERT(LLONG_MAX >= UINT_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_long(long value)
{
	STATIC_ASSERT(LLONG_MIN <= LONG_MIN and LLONG_MAX >= LONG_MAX, "Update the implementation if the assumption is not valid.");
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_ulong(unsigned long value)
{
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	if (value > (unsigned long long) LLONG_MAX) {
		result.value = LLONG_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (long long) value;
	}
	return result;
}

llong_conversion_result_type safer_llong_from_llong(long long value)
{
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	result.value = value;
	return result;
}

llong_conversion_result_type safer_llong_from_ullong(unsigned long long value)
{
	llong_conversion_result_type result = {0LL, integer_conversion_error_none};
	if (value > (unsigned long long) LLONG_MAX) {
		result.value = LLONG_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (long long) value;
	}
	return result;
}

ullong_conversion_result_type safer_ullong_from_char(char value)
{
#if CHAR_MIN < 0
	return safer_ullong_from_schar((signed char) value);
#else
	return safer_ullong_from_uchar((unsigned char) value);
#endif
}

ullong_conversion_result_type safer_ullong_from_schar(signed char value)
{
	STATIC_ASSERT(ULLONG_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0ULL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long long) value;
	}
	return result;
}

ullong_conversion_result_type safer_ullong_from_uchar(unsigned char value)
{
	STATIC_ASSERT(ULLONG_MAX >= UCHAR_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ullong_conversion_result_type safer_ullong_from_short(short value)
{
	STATIC_ASSERT(ULLONG_MAX >= SHRT_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0ULL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long long) value;
	}
	return result;

}

ullong_conversion_result_type safer_ullong_from_ushort(unsigned short value)
{
	STATIC_ASSERT(ULLONG_MAX >= USHRT_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ullong_conversion_result_type safer_ullong_from_int(int value)
{
	STATIC_ASSERT(ULLONG_MAX >= SCHAR_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0ULL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long long) value;
	}
	return result;

}

ullong_conversion_result_type safer_ullong_from_uint(unsigned int value)
{
	STATIC_ASSERT(ULLONG_MAX >= UINT_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ullong_conversion_result_type safer_ullong_from_long(long value)
{
	STATIC_ASSERT(ULLONG_MAX >= LLONG_MAX, "Update the implementation if the assumption is not valid.");
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0ULL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (unsigned long long) value;
	}
	return result;

}

ullong_conversion_result_type safer_ullong_from_ulong(unsigned long value)
{
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	result.value = value;
	return result;
}

ullong_conversion_result_type safer_ullong_from_llong(long long value)
{
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0ULL;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if ((unsigned long long) value > (unsigned long long) ULLONG_MAX) {
		result.value = ULLONG_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (unsigned long long) value;
	}
	return result;
}

ullong_conversion_result_type safer_ullong_from_ullong(unsigned long long value)
{
	ullong_conversion_result_type result = {0ULL, integer_conversion_error_none};
	result.value = value;
	return result;
}
