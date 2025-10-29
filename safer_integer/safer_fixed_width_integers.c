#include "safer_fixed_width_integers.h"
#include "safer_integer_short_macros.h"
#include <assert.h>
#include <iso646.h>

/* Preconditions */
STATIC_ASSERT(sizeof(int) > sizeof(int8_t), "The size of int shall be greater than the size of int8_t");
STATIC_ASSERT(sizeof(unsigned int) > sizeof(uint8_t), "The size of unsigned int shall be greater than the size of uint8_t");
STATIC_ASSERT(sizeof(int) >= sizeof(int16_t), "The size of int shall be at least the size of int16_t");
STATIC_ASSERT(sizeof(unsigned int) >= sizeof(uint16_t), "The size of unsigned int shall be at least the size of uint16_t");
STATIC_ASSERT(sizeof(int32_t) == sizeof(int) or sizeof(int32_t) == sizeof(long), "The size of int32_t shall be the size of int or the size of long int.");
STATIC_ASSERT(sizeof(uint32_t) == sizeof(unsigned int) or sizeof(uint32_t) == sizeof(unsigned long), "The size of uint32_t shall be the size of unsigned int or the size of unsigned long int.");

i8_result_type safer_i8_add(int8_t a, int8_t b)
{
	i8_result_type i8_result = {0, 0, integer_operation_error_none};
	const int result = a + b; /* integer promotion takes place */
	if (result < INT8_MIN) {
		i8_result.value = INT8_MIN;
		i8_result.error = integer_operation_error_signed_integer_result_smaller_than_minimum;
	} else if (result > INT8_MAX) {
		i8_result.value = INT8_MAX;
		i8_result.error = integer_operation_error_signed_integer_result_greater_than_maximum;
	} else {
		i8_result.value = (int8_t) result;
	}
	return i8_result;
}

i8_result_type safer_i8_minus(int8_t a, int8_t b)
{
	i8_result_type i8_result = {0, 0, integer_operation_error_none};
	const int result = a - b; /* integer promotion takes place */
	if (result < INT8_MIN) {
		i8_result.value = INT8_MIN;
		i8_result.error = integer_operation_error_signed_integer_result_smaller_than_minimum;
	} else if (result > INT8_MAX) {
		i8_result.value = INT8_MAX;
		i8_result.error = integer_operation_error_signed_integer_result_greater_than_maximum;
	} else {
		i8_result.value = (int8_t) result;
	}
	return i8_result;
}

i8_result_type safer_i8_multiply(int8_t a, int8_t b)
{
	i8_result_type i8_result = {0, 0, integer_operation_error_none};
	const int result = a * b; /* integer promotion takes place */
	if (result < INT8_MIN) {
		i8_result.value = INT8_MIN;
		i8_result.error = integer_operation_error_signed_integer_result_smaller_than_minimum;
	} else if (result > INT8_MAX) {
		i8_result.value = INT8_MAX;
		i8_result.error = integer_operation_error_signed_integer_result_greater_than_maximum;
	} else {
		i8_result.value = (int8_t) result;
	}
	return i8_result;
}

i8_result_type safer_i8_divide(int8_t a, int8_t b)
{
	i8_result_type i8_result = {0, 0, integer_operation_error_none};
	if (b == -1 and a == INT8_MIN and INT8_MIN == (-INT8_MAX - 1)) {
		i8_result.value = INT8_MAX;
		i8_result.error = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
	} else if (b != 0) {
		i8_result.value = (int8_t) (a / b);
		i8_result.remainder = (int8_t) (a % b);
	} else {
		i8_result.error = integer_operation_error_division_of_signed_integer_by_zero;
	}
	return i8_result;
}

int16_t safe_i8_add(int8_t a, int8_t b)
{
	const int result = a + b; /* integer promotion takes place */
	return (int16_t) result;
}

int16_t safe_i8_minus(int8_t a, int8_t b)
{
	const int result = a - b; /* integer promotion takes place */
	return (int16_t) result;
}

int16_t safe_i8_multiply(int8_t a, int8_t b)
{
	const int result = a * b; /* integer promotion takes place */
	return (int16_t) result;
}

int16_t less_safe_i8_divide(int8_t a, int8_t b)
{
	int16_t result = 0;
	SAFER_INTEGER_ASSERT(b != 0);
	if (b != 0) {
		result = (int16_t) (a / b);
	}
	return result;
}

int8_t less_safe_i8_remainder(int8_t a, int8_t b)
{
	int8_t result = 0;
	SAFER_INTEGER_ASSERT(b != 0);
	if (b != 0) {
		result = (int8_t) (a % b);
	}
	return result;
}

u8_result_type safer_u8_add(uint8_t a, uint8_t b)
{
	u8_result_type u8_result = {0U, 0U, integer_operation_error_none};
	const unsigned int result = (unsigned int) a + (unsigned int) b;
	if (result <= UINT8_MAX) {
		u8_result.value = (uint8_t) result;
	} else {
		u8_result.value = UINT8_MAX;
		u8_result.error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
	}
	return u8_result;
}

u8_result_type safer_u8_minus(uint8_t a, uint8_t b)
{
	u8_result_type u8_result = {0U, 0U, integer_operation_error_none};
	if (a >= b) {
		u8_result.value = (uint8_t) ((unsigned int) a - (unsigned int) b);
	} else {
		u8_result.error = integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
	}
	return u8_result;
}

u8_result_type safer_u8_multiply(uint8_t a, uint8_t b)
{
	u8_result_type u8_result = {0U, 0U, integer_operation_error_none};
	const unsigned int result = (unsigned int) a * (unsigned int) b;
	if (result <= UINT8_MAX) {
		u8_result.value = (uint8_t) result;
	} else {
		u8_result.value = UINT8_MAX;
		u8_result.error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
	}
	return u8_result;
}

u8_result_type safer_u8_divide(uint8_t a, uint8_t b)
{
	u8_result_type u8_result = {0U, 0U, integer_operation_error_none};
	if (b != 0U) {
		u8_result.value = (uint8_t) ((unsigned int) a / (unsigned int) b);
		u8_result.remainder = (uint8_t) ((unsigned int) a % (unsigned int) b);
	} else {
		u8_result.error = integer_operation_error_division_of_unsigned_integer_by_zero;
	}
	return u8_result;
}

uint16_t safe_u8_add(uint8_t a, uint8_t b)
{
	const unsigned int result = (unsigned int) a + (unsigned int) b;
	return (uint16_t) result;
}

int16_t safe_u8_minus(uint8_t a, uint8_t b)
{
	const int result = (int) a - (int) b;
	return (int16_t) result;
}

uint16_t safe_u8_multiply(uint8_t a, uint8_t b)
{
	const unsigned int result = (unsigned int) a * (unsigned int) b;
	return (uint16_t) result;
}

uint8_t less_safe_u8_divide(uint8_t a, uint8_t b)
{
	uint8_t result = 0U;
	SAFER_INTEGER_ASSERT(b != 0U);
	if (b != 0U) {
		result = (uint8_t) ((unsigned int) a / (unsigned int) b);
	}
	return result;
}

uint8_t less_safe_u8_remainder(uint8_t a, uint8_t b)
{
	uint8_t result = 0U;
	SAFER_INTEGER_ASSERT(b != 0U);
	if (b != 0U) {
		result = (uint8_t) ((unsigned int) a % (unsigned int) b);
	}
	return result;
}

i16_result_type safer_i16_add(int16_t a, int16_t b)
{
	i16_result_type i16_result = {0, 0, integer_operation_error_none};
	const int32_t result = (int32_t) a + (int32_t) b;
	if (result < INT16_MIN) {
		i16_result.value = INT16_MIN;
		i16_result.error = integer_operation_error_signed_integer_result_smaller_than_minimum;
	} else if (result > INT16_MAX) {
		i16_result.value = INT16_MAX;
		i16_result.error = integer_operation_error_signed_integer_result_greater_than_maximum;
	} else {
		i16_result.value = (int16_t) result;
	}
	return i16_result;
}

i16_result_type safer_i16_minus(int16_t a, int16_t b)
{
	i16_result_type i16_result = {0, 0, integer_operation_error_none};
	const int32_t result = (int32_t) a - (int32_t) b;
	if (result < INT16_MIN) {
		i16_result.value = INT16_MIN;
		i16_result.error = integer_operation_error_signed_integer_result_smaller_than_minimum;
	} else if (result > INT16_MAX) {
		i16_result.value = INT16_MAX;
		i16_result.error = integer_operation_error_signed_integer_result_greater_than_maximum;
	} else {
		i16_result.value = (int16_t) result;
	}
	return i16_result;
}

i16_result_type safer_i16_multiply(int16_t a, int16_t b)
{
	i16_result_type i16_result = {0, 0, integer_operation_error_none};
	const int32_t result = (int32_t) a * (int32_t) b;
	if (result < INT16_MIN) {
		i16_result.value = INT16_MIN;
		i16_result.error = integer_operation_error_signed_integer_result_smaller_than_minimum;
	} else if (result > INT16_MAX) {
		i16_result.value = INT16_MAX;
		i16_result.error = integer_operation_error_signed_integer_result_greater_than_maximum;
	} else {
		i16_result.value = (int16_t) result;
	}
	return i16_result;
}

i16_result_type safer_i16_divide(int16_t a, int16_t b)
{
	i16_result_type i16_result = {0, 0, integer_operation_error_none};
	if (b == -1 and a == INT16_MIN and INT16_MIN == (-INT16_MAX - 1)) {
		i16_result.value = INT16_MAX;
		i16_result.error = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
	} else if (b != 0) {
		i16_result.value = (int16_t) (a / b);
		i16_result.remainder = (int16_t) (a % b);
	} else {
		i16_result.error = integer_operation_error_division_of_signed_integer_by_zero;
	}
	return i16_result;
}

int32_t safe_i16_add(int16_t a, int16_t b)
{
	const int32_t result = (int32_t) a + (int32_t) b;
	return result;
}

int32_t safe_i16_minus(int16_t a, int16_t b)
{
	const int32_t result = (int32_t) a - (int32_t) b;
	return result;
}

int32_t safe_i16_multiply(int16_t a, int16_t b)
{
	const int32_t result = (int32_t) a * (int32_t) b;
	return result;
}

int32_t less_safe_i16_divide(int16_t a, int16_t b)
{
	int32_t result = 0;
	SAFER_INTEGER_ASSERT(b != 0);
	if (b != 0) {
		result = (int32_t) a / (int32_t) b;
	}
	return result;
}

int16_t less_safe_i16_remainder(int16_t a, int16_t b)
{
	int16_t result = 0;
	SAFER_INTEGER_ASSERT(b != 0);
	if (b != 0) {
		result = (int16_t) ((int32_t) a % (int32_t) b);
	}
	return result;
}

u16_result_type safer_u16_add(uint16_t a, uint16_t b)
{
	u16_result_type u16_result = {0U, 0U, integer_operation_error_none};
	const uint32_t result = (uint32_t) a + (uint32_t) b;
	if (result <= UINT16_MAX) {
		u16_result.value = (uint16_t) result;
	} else {
		u16_result.value = UINT16_MAX;
		u16_result.error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
	}
	return u16_result;
}

u16_result_type safer_u16_minus(uint16_t a, uint16_t b)
{
	u16_result_type u16_result = {0U, 0U, integer_operation_error_none};
	if (a >= b) {
		u16_result.value = (uint16_t) ((unsigned int) a - (unsigned int) b);
	} else {
		u16_result.error = integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
	}
	return u16_result;
}

u16_result_type safer_u16_multiply(uint16_t a, uint16_t b)
{
	u16_result_type u16_result = {0U, 0U, integer_operation_error_none};
	const uint32_t result = (uint32_t) a * (uint32_t) b;
	if (result <= UINT16_MAX) {
		u16_result.value = (uint16_t) result;
	} else {
		u16_result.value = UINT16_MAX;
		u16_result.error = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
	}
	return u16_result;
}

u16_result_type safer_u16_divide(uint16_t a, uint16_t b)
{
	u16_result_type u16_result = {0U, 0U, integer_operation_error_none};
	if (b != 0U) {
		u16_result.value = (uint16_t) ((unsigned int) a / (unsigned int) b);
		u16_result.remainder = (uint16_t) ((unsigned int) a % (unsigned int) b);
	} else {
		u16_result.error = integer_operation_error_division_of_unsigned_integer_by_zero;
	}
	return u16_result;
}

uint32_t safe_u16_add(uint16_t a, uint16_t b)
{
	const uint32_t result = (uint32_t) a + (uint32_t) b;
	return result;
}

int32_t safe_u16_minus(uint16_t a, uint16_t b)
{
	const int32_t result = (int32_t) a - (int32_t) b;
	return result;
}

uint32_t safe_u16_multiply(uint16_t a, uint16_t b)
{
	const uint32_t result = (uint32_t) a * (uint32_t) b;
	return result;
}

uint16_t less_safe_u16_divide(uint16_t a, uint16_t b)
{
	uint16_t result = 0U;
	if (b != 0U) {
		result = (uint16_t) ((unsigned int) a / (unsigned int) b);
	}
	return result;
}

uint16_t less_safe_u16_remainder(uint16_t a, uint16_t b)
{
	uint16_t result = 0U;
	if (b != 0U) {
		result = (uint16_t) ((unsigned int) a % (unsigned int) b);
	}
	return result;
}

i32_result_type safer_i32_add(int32_t a, int32_t b)
{
	i32_result_type i32_result = {0, 0, integer_operation_error_none};
#if (INT32_MIN == INT_MIN) && (INT32_MAX == INT_MAX)
	int_result_type result = safer_int_add(a, b);
#elif (INT32_MIN == LONG_MIN) && (INT32_MAX == LONG_MAX)
	long_result_type result = safer_long_add(a, b);
#else
	#error "Error: The size of int32_t is neither the size of int nor the size of long int."
#endif
	i32_result.value = result.value;
	i32_result.remainder = result.remainder;
	i32_result.error = result.error;
	return i32_result;
}

i32_result_type safer_i32_minus(int32_t a, int32_t b)
{
	i32_result_type i32_result = {0, 0, integer_operation_error_none};
#if (INT32_MIN == INT_MIN) && (INT32_MAX == INT_MAX)
	int_result_type result = safer_int_minus(a, b);
#elif (INT32_MIN == LONG_MIN) && (INT32_MAX == LONG_MAX)
	long_result_type result = safer_long_minus(a, b);
#else
	#error "Error: The size of int32_t is neither the size of int nor the size of long int."
#endif
	i32_result.value = result.value;
	i32_result.remainder = result.remainder;
	i32_result.error = result.error;
	return i32_result;
}

i32_result_type safer_i32_multiply(int32_t a, int32_t b)
{
	i32_result_type i32_result = {0, 0, integer_operation_error_none};
#if (INT32_MIN == INT_MIN) && (INT32_MAX == INT_MAX)
	int_result_type result = safer_int_multiply(a, b);
#elif (INT32_MIN == LONG_MIN) && (INT32_MAX == LONG_MAX)
	long_result_type result = safer_long_multiply(a, b);
#else
	#error "Error: The size of int32_t is neither the size of int nor the size of long int."
#endif
	i32_result.value = result.value;
	i32_result.remainder = result.remainder;
	i32_result.error = result.error;
	return i32_result;
}

i32_result_type safer_i32_divide(int32_t a, int32_t b)
{
	i32_result_type i32_result = {0, 0, integer_operation_error_none};
#if (INT32_MIN == INT_MIN) && (INT32_MAX == INT_MAX)
	int_result_type result = safer_int_divide(a, b);
#elif (INT32_MIN == LONG_MIN) && (INT32_MAX == LONG_MAX)
	long_result_type result = safer_long_divide(a, b);
#else
	#error "Error: The size of int32_t is neither the size of int nor the size of long int."
#endif
	i32_result.value = result.value;
	i32_result.remainder = result.remainder;
	i32_result.error = result.error;
	return i32_result;
}

u32_result_type safer_u32_add(uint32_t a, uint32_t b)
{
	u32_result_type u32_result = {0U, 0U, integer_operation_error_none};
#if (UINT32_MAX == UINT_MAX)
	uint_result_type result = safer_uint_add(a, b);
#elif (UINT32_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_add(a, b);
#else
	#error "Error: The size of uint32_t is neither the size of unsigned int nor the size of unsigned long int."
#endif
	u32_result.value = result.value;
	u32_result.remainder = result.remainder;
	u32_result.error = result.error;
	return u32_result;
}

u32_result_type safer_u32_minus(uint32_t a, uint32_t b)
{
	u32_result_type u32_result = {0U, 0U, integer_operation_error_none};
#if (UINT32_MAX == UINT_MAX)
	uint_result_type result = safer_uint_minus(a, b);
#elif (UINT32_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_minus(a, b);
#else
	#error "Error: The size of uint32_t is neither the size of unsigned int nor the size of unsigned long int."
#endif
	u32_result.value = result.value;
	u32_result.remainder = result.remainder;
	u32_result.error = result.error;
	return u32_result;
}

u32_result_type safer_u32_multiply(uint32_t a, uint32_t b)
{
	u32_result_type u32_result = {0U, 0U, integer_operation_error_none};
#if (UINT32_MAX == UINT_MAX)
	uint_result_type result = safer_uint_multiply(a, b);
#elif (UINT32_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_multiply(a, b);
#else
	#error "Error: The size of uint32_t is neither the size of unsigned int nor the size of unsigned long int."
#endif
	u32_result.value = result.value;
	u32_result.remainder = result.remainder;
	u32_result.error = result.error;
	return u32_result;
}

u32_result_type safer_u32_divide(uint32_t a, uint32_t b)
{
	u32_result_type u32_result = {0U, 0U, integer_operation_error_none};
#if (UINT32_MAX == UINT_MAX)
	uint_result_type result = safer_uint_divide(a, b);
#elif (UINT32_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_divide(a, b);
#else
	#error "Error: The size of uint32_t is neither the size of unsigned int nor the size of unsigned long int."
#endif
	u32_result.value = result.value;
	u32_result.remainder = result.remainder;
	u32_result.error = result.error;
	return u32_result;
}

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)

STATIC_ASSERT(sizeof(int64_t) == sizeof(long) or sizeof(int64_t) == sizeof(long long),
	"The size of int64_t shall be the size of long int or the size of unsigned long int.");
STATIC_ASSERT(sizeof(uint64_t) == sizeof(unsigned long) or sizeof(uint64_t) == sizeof(unsigned long long),
	"The size of uint64_t shall be the size of unsigned long int or the size of unsigned long long int.");

int64_t safe_i32_add(int32_t a, int32_t b)
{
	const int64_t result = (int64_t) a + (int64_t) b;
	return result;
}

int64_t safe_i32_minus(int32_t a, int32_t b)
{
	const int64_t result = (int64_t) a - (int64_t) b;
	return result;
}

int64_t safe_i32_multiply(int32_t a, int32_t b)
{
	const int64_t result = (int64_t) a * (int64_t) b;
	return result;
}

int64_t less_safe_i32_divide(int32_t a, int32_t b)
{
	int64_t result = 0;
	SAFER_INTEGER_ASSERT(b != 0);
	if (b != 0) {
		result = (int64_t) a / (int64_t) b;
	}
	return result;
}

int32_t less_safe_i32_remainder(int32_t a, int32_t b)
{
	int32_t result = 0;
	SAFER_INTEGER_ASSERT(b != 0);
	if (b != 0) {
		result = (int32_t) ((int64_t) a % (int64_t) b);
	}
	return result;
}

uint64_t safe_u32_add(uint32_t a, uint32_t b)
{
	const uint64_t result = (uint64_t) a + (uint64_t) b;
	return result;
}

int64_t safe_u32_minus(uint32_t a, uint32_t b)
{
	const int64_t result = (int64_t) a - (int64_t) b;
	return result;
}

uint64_t safe_u32_multiply(uint32_t a, uint32_t b)
{
	const uint64_t result = (uint64_t) a * (uint64_t) b;
	return result;
}

uint32_t less_safe_u32_divide(uint32_t a, uint32_t b)
{
	uint32_t result = 0U;
	if (b != 0U) {
		result = a / b;
	}
	return result;
}

uint32_t less_safe_u32_remainder(uint32_t a, uint32_t b)
{
	uint32_t result = 0U;
	if (b != 0U) {
		result = a % b;
	}
	return result;
}

i64_result_type safer_i64_add(int64_t a, int64_t b)
{
	i64_result_type i64_result = {0, 0, integer_operation_error_none};
#if (INT64_MIN == LONG_MIN) && (INT64_MAX == LONG_MAX)
	long_result_type result = safer_long_add(a, b);
#elif (INT64_MIN == LLONG_MIN) && (INT64_MAX == LLONG_MAX)
	llong_result_type result = safer_llong_add(a, b);
#else
	#error "Error: The size of int64_t is neither the size of long int nor the size of long long int."
#endif
	i64_result.value = result.value;
	i64_result.remainder = result.remainder;
	i64_result.error = result.error;
	return i64_result;
}

i64_result_type safer_i64_minus(int64_t a, int64_t b)
{
	i64_result_type i64_result = {0, 0, integer_operation_error_none};
#if (INT64_MIN == LONG_MIN) && (INT64_MAX == LONG_MAX)
	long_result_type result = safer_long_minus(a, b);
#elif (INT64_MIN == LLONG_MIN) && (INT64_MAX == LLONG_MAX)
	llong_result_type result = safer_llong_minus(a, b);
#else
	#error "Error: The size of int64_t is neither the size of long int nor the size of long long int."
#endif
	i64_result.value = result.value;
	i64_result.remainder = result.remainder;
	i64_result.error = result.error;
	return i64_result;
}

i64_result_type safer_i64_multiply(int64_t a, int64_t b)
{
	i64_result_type i64_result = {0, 0, integer_operation_error_none};
#if (INT64_MIN == LONG_MIN) && (INT64_MAX == LONG_MAX)
	long_result_type result = safer_long_multiply(a, b);
#elif (INT64_MIN == LLONG_MIN) && (INT64_MAX == LLONG_MAX)
	llong_result_type result = safer_llong_multiply(a, b);
#else
	#error "Error: The size of int64_t is neither the size of long int nor the size of long long int."
#endif
	i64_result.value = result.value;
	i64_result.remainder = result.remainder;
	i64_result.error = result.error;
	return i64_result;
}

i64_result_type safer_i64_divide(int64_t a, int64_t b)
{
	i64_result_type i64_result = {0, 0, integer_operation_error_none};
#if (INT64_MIN == LONG_MIN) && (INT64_MAX == LONG_MAX)
	long_result_type result = safer_long_divide(a, b);
#elif (INT64_MIN == LLONG_MIN) && (INT64_MAX == LLONG_MAX)
	llong_result_type result = safer_llong_divide(a, b);
#else
	#error "Error: The size of int64_t is neither the size of long int nor the size of long long int."
#endif
	i64_result.value = result.value;
	i64_result.remainder = result.remainder;
	i64_result.error = result.error;
	return i64_result;
}

u64_result_type safer_u64_add(uint64_t a, uint64_t b)
{
	u64_result_type u64_result = {0U, 0U, integer_operation_error_none};
#if (UINT64_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_add(a, b);
#elif (UINT64_MAX == ULLONG_MAX)
	ullong_result_type result = safer_ullong_add(a, b);
#else
	#error "Error: The size of uint64_t is neither the size of unsigned long int nor the size of unsigned long long int."
#endif
	u64_result.value = result.value;
	u64_result.remainder = result.remainder;
	u64_result.error = result.error;
	return u64_result;
}

u64_result_type safer_u64_minus(uint64_t a, uint64_t b)
{
	u64_result_type u64_result = {0U, 0U, integer_operation_error_none};
#if (UINT64_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_minus(a, b);
#elif (UINT64_MAX == ULLONG_MAX)
	ullong_result_type result = safer_ullong_minus(a, b);
#else
	#error "Error: The size of uint64_t is neither the size of unsigned long int nor the size of unsigned long long int."
#endif
	u64_result.value = result.value;
	u64_result.remainder = result.remainder;
	u64_result.error = result.error;
	return u64_result;
}

u64_result_type safer_u64_multiply(uint64_t a, uint64_t b)
{
	u64_result_type u64_result = {0U, 0U, integer_operation_error_none};
#if (UINT64_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_multiply(a, b);
#elif (UINT64_MAX == ULLONG_MAX)
	ullong_result_type result = safer_ullong_multiply(a, b);
#else
	#error "Error: The size of uint64_t is neither the size of unsigned long int nor the size of unsigned long long int."
#endif
	u64_result.value = result.value;
	u64_result.remainder = result.remainder;
	u64_result.error = result.error;
	return u64_result;
}

u64_result_type safer_u64_divide(uint64_t a, uint64_t b)
{
	u64_result_type u64_result = {0U, 0U, integer_operation_error_none};
#if (UINT64_MAX == ULONG_MAX)
	ulong_result_type result = safer_ulong_divide(a, b);
#elif (UINT64_MAX == ULLONG_MAX)
	ullong_result_type result = safer_ullong_divide(a, b);
#else
	#error "Error: The size of uint64_t is neither the size of unsigned long int nor the size of unsigned long long int."
#endif
	u64_result.value = result.value;
	u64_result.remainder = result.remainder;
	u64_result.error = result.error;
	return u64_result;
}

#endif /* INT64_MIN, INT64_MAX, UINT64_MAX */
