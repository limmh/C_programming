#include "safer_integer.h"
#include "Boolean_type.h"
#include "static_assert.h"
#include <assert.h>
#include <iso646.h>

const char *integer_operation_error_message(integer_operation_error_type error)
{
	const char *message = "Unknown error.";
	switch (error) {
	case integer_operation_error_none:
		message = "Integer operation: No error.";
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		message = "Integer operation error: The signed integer result is smaller than the minimum integer value.";
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		message = "Integer operation error: The signed integer result is larger than the maximum integer value.";
		break;
	case integer_operation_error_division_of_signed_integer_by_zero:
		message = "Integer operation error: Division of a signed integer by zero.";
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		message = "Integer operation error: The result of division of the minimum integer value by -1 is out of the range of the signed integer type.";
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		message = "Integer operation error: The result of the unsigned integer operation is larger than the maximum value and wraps around to a smaller value.";
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		message = "Integer operation error: The result of the unsigned integer operation is smaller than zero and it wraps around to a larger value.";
		break;
	case integer_operation_error_division_of_unsigned_integer_by_zero:
		message = "Integer operation error: Division of an unsigned integer by zero.";
		break;
	default:
		break;
	}
	return message;
}

/*
maximum value: the most positive value that can be represented by a fixed number of bits, e.g. 32 bits or 64 bits
minimum value: the most negative value that can be represented by a fixed number of bits, e.g. 32 bits or 64 bits
*/

STATIC_ASSERT((-INT_MAX == INT_MIN) or ((-INT_MAX - 1) == INT_MIN), "Only one's and two's complements are supported.");
STATIC_ASSERT((-LONG_MAX == LONG_MIN) or ((-LONG_MAX - 1) == LONG_MIN), "Only one's and two's complements are supported.");

integer_operation_error_type safer_int_addition_check(int a, int b)
{
	const int maximum_value = INT_MAX;
	const int minimum_value = INT_MIN;
	const int zero = 0;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a > zero and b > zero) { /* (a + b) <= maximum value, where a > 0 and b > 0 */
		if (b > (maximum_value - a)) {
			error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
		}
	} else if (a < zero and b < zero) { /* (a + b) >= minimum value, where a < 0 and b < 0 */
		if (b < (minimum_value - a)) {
			error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
		}
	}

	return error_code;
}

integer_operation_error_type safer_int_subtraction_check(int a, int b)
{
	const int maximum_value = INT_MAX;
	const int minimum_value = INT_MIN;
	const int zero = 0;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a >= zero and b < zero) { /* (a - b) <= maximum value, where a >= 0 and b < 0 */
		if (a > (maximum_value + b)) {
			error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
		}
	} else if (a < zero and b > zero) { /* (a - b) >= minimum value, where a < 0 and b > 0 */
		if (a < (minimum_value + b)) {
			error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
		}
	}

	return error_code;
}

integer_operation_error_type safer_int_multiplication_check(int a, int b)
{
	const int maximum_value = INT_MAX;
	const int minimum_value = INT_MIN;
	const int zero = 0;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a > zero) {
		if (b > zero) { /* (a * b) <= maximum value, where a > 0 and b > 0 */
			if (b > (maximum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
			}
		} else if (b < zero) { /* (a * b) >= minimum value, where a > 0 and b < 0 */
			if (b < (minimum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
			}
		}
	} else if (a < zero) {
		if (b > zero) { /* (a * b) >=  minimum value, where a < 0 and b > 0 */
			if (a < (minimum_value / b)) {
				error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
			}
		} else if (b < zero) { /* (a * b) <= maximum value, where a < 0 and b < 0 */
			if (b < (maximum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
			}
		}
	}

	return error_code;
}

integer_operation_error_type safer_int_division_check(int dividend, int divisor)
{
	const int maximum_value = INT_MAX;
	const int minimum_value = INT_MIN;
	const int zero = 0;
	const int minus_one = -1;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (divisor == zero) {
		error_code = integer_operation_error_division_of_signed_integer_by_zero;
	} else if (divisor == minus_one) {
		if (minimum_value == (-maximum_value + minus_one) and dividend == minimum_value) {
			error_code = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
		}
	}

	return error_code;
}

/* Safer signed integer operations */
int_result_type safer_int_add(int a, int b)
{
	int_result_type result = {0, 0, integer_operation_error_none};
	result.error = safer_int_addition_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a + b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = INT_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = INT_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

int_result_type safer_int_minus(int a, int b)
{
	int_result_type result = {0, 0, integer_operation_error_none};
	result.error = safer_int_subtraction_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a - b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = INT_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = INT_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

int_result_type safer_int_multiply(int a, int b)
{
	int_result_type result = {0, 0, integer_operation_error_none};
	result.error = safer_int_multiplication_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a * b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = INT_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = INT_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

int_result_type safer_int_divide(int dividend, int divisor)
{
	int_result_type result = {0, 0, integer_operation_error_none};
	result.error = safer_int_division_check(dividend, divisor);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = dividend / divisor;
		result.remainder = dividend % divisor;
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		result.value = INT_MAX; /* clipped to the nearest value */
		break;
	default:
		break;
	}
	return result;
}

/* Signed long integers */
integer_operation_error_type safer_long_addition_check(long a, long b)
{
	const long maximum_value = LONG_MAX;
	const long minimum_value = LONG_MIN;
	const long zero = 0L;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a > zero and b > zero) { /* (a + b) <= maximum value, where a > 0 and b > 0 */
		if (b > (maximum_value - a)) {
			error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
		}
	} else if (a < zero and b < zero) { /* (a + b) >= minimum value, where a < 0 and b < 0 */
		if (b < (minimum_value - a)) {
			error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
		}
	}

	return error_code;
}

integer_operation_error_type safer_long_subtraction_check(long a, long b)
{
	const long maximum_value = LONG_MAX;
	const long minimum_value = LONG_MIN;
	const long zero = 0L;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a >= zero and b < zero) { /* (a - b) <= maximum value, where a >= 0 and b < 0 */
		if (a > (maximum_value + b)) {
			error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
		}
	} else if (a < zero and b > zero) { /* (a - b) >= minimum value, where a < 0 and b > 0 */
		if (a < (minimum_value + b)) {
			error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
		}
	}

	return error_code;
}

integer_operation_error_type safer_long_multiplication_check(long a, long b)
{
	const long maximum_value = LONG_MAX;
	const long minimum_value = LONG_MIN;
	const long zero = 0L;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a > zero) {
		if (b > zero) { /* (a * b) <= maximum value, where a > 0 and b > 0 */
			if (b > (maximum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
			}
		} else if (b < zero) { /* (a * b) >= minimum value, where a > 0 and b < 0 */
			if (b < (minimum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
			}
		}
	} else if (a < zero) {
		if (b > zero) { /* (a * b) >=  minimum value, where a < 0 and b > 0 */
			if (a < (minimum_value / b)) {
				error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
			}
		} else if (b < zero) { /* (a * b) <= maximum value, where a < 0 and b < 0 */
			if (b < (maximum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
			}
		}
	}

	return error_code;
}

integer_operation_error_type safer_long_division_check(long dividend, long divisor)
{
	const long maximum_value = LONG_MAX;
	const long minimum_value = LONG_MIN;
	const long zero = 0L;
	const long minus_one = -1L;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (divisor == zero) {
		error_code = integer_operation_error_division_of_signed_integer_by_zero;
	} else if (divisor == minus_one) {
		if (minimum_value == (-maximum_value + minus_one) and dividend == minimum_value) {
			error_code = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
		}
	}

	return error_code;
}

/* Safer signed long integer operations */
long_result_type safer_long_add(long a, long b)
{
	long_result_type result = {0L, 0L, integer_operation_error_none};
	result.error = safer_long_addition_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a + b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = LONG_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = LONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

long_result_type safer_long_minus(long a, long b)
{
	long_result_type result = {0L, 0L, integer_operation_error_none};
	result.error = safer_long_subtraction_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a - b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = LONG_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = LONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

long_result_type safer_long_multiply(long a, long b)
{
	long_result_type result = {0L, 0L, integer_operation_error_none};
	result.error = safer_long_multiplication_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a * b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = LONG_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = LONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

long_result_type safer_long_divide(long dividend, long divisor)
{
	long_result_type result = {0L, 0L, integer_operation_error_none};
	result.error = safer_long_division_check(dividend, divisor);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = dividend / divisor;
		result.remainder = dividend % divisor;
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		result.value = LONG_MAX; /* clipped to the nearest value */
		break;
	default:
		break;
	}
	return result;
}

#if LONG_LONG_INTEGER_TYPE_IS_AVAILABLE
/* Signed long long integers */
STATIC_ASSERT((-LLONG_MAX == LLONG_MIN) or ((-LLONG_MAX - 1) == LLONG_MIN), "Only one's and two's complements are supported.");

integer_operation_error_type safer_llong_addition_check(long long a, long long b)
{
	const long long maximum_value = LLONG_MAX;
	const long long minimum_value = LLONG_MIN;
	const long long zero = 0LL;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a > zero and b > zero) { /* (a + b) <= maximum value, where a > 0 and b > 0 */
		if (b > (maximum_value - a)) {
			error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
		}
	} else if (a < zero and b < zero) { /* (a + b) >= minimum value, where a < 0 and b < 0 */
		if (b < (minimum_value - a)) {
			error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
		}
	}

	return error_code;
}

integer_operation_error_type safer_llong_subtraction_check(long long a, long long b)
{
	const long long maximum_value = LLONG_MAX;
	const long long minimum_value = LLONG_MIN;
	const long long zero = 0LL;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a >= zero and b < zero) { /* (a - b) <= maximum value, where a >= 0 and b < 0 */
		if (a > (maximum_value + b)) {
			error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
		}
	} else if (a < zero and b > zero) { /* (a - b) >= minimum value, where a < 0 and b > 0 */
		if (a < (minimum_value + b)) {
			error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
		}
	}

	return error_code;
}

integer_operation_error_type safer_llong_multiplication_check(long long a, long long b)
{
	const long long maximum_value = LLONG_MAX;
	const long long minimum_value = LLONG_MIN;
	const long long zero = 0LL;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (a > zero) {
		if (b > zero) { /* (a * b) <= maximum value, where a > 0 and b > 0 */
			if (b > (maximum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
			}
		} else if (b < zero) { /* (a * b) >= minimum value, where a > 0 and b < 0 */
			if (b < (minimum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
			}
		}
	} else if (a < zero) {
		if (b > zero) { /* (a * b) >=  minimum value, where a < 0 and b > 0 */
			if (a < (minimum_value / b)) {
				error_code = integer_operation_error_signed_integer_result_smaller_than_minimum;
			}
		} else if (b < zero) { /* (a * b) <= maximum value, where a < 0 and b < 0 */
			if (b < (maximum_value / a)) {
				error_code = integer_operation_error_signed_integer_result_greater_than_maximum;
			}
		}
	}

	return error_code;
}

integer_operation_error_type safer_llong_division_check(long long dividend, long long divisor)
{
	const long long maximum_value = LLONG_MAX;
	const long long minimum_value = LLONG_MIN;
	const long long zero = 0LL;
	const long long minus_one = -1LL;
	integer_operation_error_type error_code = integer_operation_error_none;

	if (divisor == zero) {
		error_code = integer_operation_error_division_of_signed_integer_by_zero;
	} else if (divisor == minus_one) {
		if (minimum_value == (-maximum_value + minus_one) and dividend == minimum_value) {
			error_code = integer_operation_error_division_of_minimum_signed_integer_by_minus_one;
		}
	}

	return error_code;
}

/* Safer signed long long integer operations */
llong_result_type safer_llong_add(long long a, long long b)
{
	llong_result_type result = {0LL, 0LL, integer_operation_error_none};
	result.error = safer_llong_addition_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a + b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = LLONG_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = LLONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

llong_result_type safer_llong_minus(long long a, long long b)
{
	llong_result_type result = {0LL, 0LL, integer_operation_error_none};
	result.error = safer_llong_subtraction_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a - b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = LLONG_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = LLONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

llong_result_type safer_llong_multiply(long long a, long long b)
{
	llong_result_type result = {0LL, 0LL, integer_operation_error_none};
	result.error = safer_llong_multiplication_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a * b;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		result.value = LLONG_MIN;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		result.value = LLONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

llong_result_type safer_llong_divide(long long dividend, long long divisor)
{
	llong_result_type result = {0LL, 0LL, integer_operation_error_none};
	result.error = safer_llong_division_check(dividend, divisor);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = dividend / divisor;
		result.remainder = dividend % divisor;
		break;
	case integer_operation_error_division_of_minimum_signed_integer_by_minus_one:
		result.value = LLONG_MAX; /* clipped to the nearest value */
		break;
	default:
		break;
	}
	return result;
}
#endif

/* runtime checks for unsigned integer operations */
integer_operation_error_type safer_uint_addition_check(unsigned int a, unsigned int b)
{
	const unsigned int maximum_value = UINT_MAX;
	return (b <= (maximum_value - a)) ?
		integer_operation_error_none :
		integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
}

integer_operation_error_type safer_uint_subtraction_check(unsigned int a, unsigned int b)
{
	return (a >= b) ?
		integer_operation_error_none :
		integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
}

integer_operation_error_type safer_uint_multiplication_check(unsigned int a, unsigned int b)
{
	const unsigned int zero = 0U;
	integer_operation_error_type error_code = integer_operation_error_none;
	if (a != zero and b != zero) {
		const unsigned int maximum_value = UINT_MAX;
		const unsigned int quotient = maximum_value / a;
		const unsigned int remainder = maximum_value % a;
		if ((b > quotient) or (b == quotient and remainder != zero)) {
			error_code = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		}
	}
	return error_code;
}

integer_operation_error_type safer_uint_division_check(unsigned int dividend, unsigned int divisor)
{
	const unsigned int zero = 0U;
	return (divisor != zero) ?
		integer_operation_error_none :
		integer_operation_error_division_of_unsigned_integer_by_zero;
}

uint_result_type safer_uint_add(unsigned int a, unsigned int b)
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};
	result.error = safer_uint_addition_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a + b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result.value = UINT_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

uint_result_type safer_uint_minus(unsigned int a , unsigned int b)
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};
	result.error = safer_uint_subtraction_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a - b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		result.value = 0U;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

uint_result_type safer_uint_multiply(unsigned int a, unsigned int b)
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};
	result.error = safer_uint_multiplication_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a * b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result.value = 0U;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

uint_result_type safer_uint_divide(unsigned int dividend, unsigned int divisor)
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};
	result.error = safer_uint_division_check(dividend, divisor);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = dividend / divisor;
		result.remainder = dividend % divisor;
		break;
	default:
		break;
	}
	return result;
}

integer_operation_error_type safer_ulong_addition_check(unsigned long a, unsigned long b)
{
	const unsigned long maximum_value = ULONG_MAX;
	return (b <= (maximum_value - a)) ?
		integer_operation_error_none :
		integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
}

integer_operation_error_type safer_ulong_subtraction_check(unsigned long a, unsigned long b)
{
	return (a >= b) ?
		integer_operation_error_none :
		integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
}

integer_operation_error_type safer_ulong_multiplication_check(unsigned long a, unsigned long b)
{
	const unsigned long zero = 0UL;
	integer_operation_error_type error_code = integer_operation_error_none;
	if (a != zero and b != zero) {
		const unsigned long maximum_value = ULONG_MAX;
		const unsigned long quotient = maximum_value / a;
		const unsigned long remainder = maximum_value % a;
		if ((b > quotient) or (b == quotient and remainder != zero)) {
			error_code = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		}
	}
	return error_code;
}

integer_operation_error_type safer_ulong_division_check(unsigned long dividend, unsigned long divisor)
{
	const unsigned long zero = 0UL;
	return (divisor != zero) ?
		integer_operation_error_none :
		integer_operation_error_division_of_unsigned_integer_by_zero;
}

ulong_result_type safer_ulong_add(unsigned long a, unsigned long b)
{
	ulong_result_type result = {0UL, 0UL, integer_operation_error_none};
	result.error = safer_ulong_addition_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a + b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result.value = ULONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

ulong_result_type safer_ulong_minus(unsigned long a , unsigned long b)
{
	ulong_result_type result = {0UL, 0UL, integer_operation_error_none};
	result.error = safer_ulong_subtraction_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a - b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		result.value = 0UL;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

ulong_result_type safer_ulong_multiply(unsigned long a, unsigned long b)
{
	ulong_result_type result = {0UL, 0UL, integer_operation_error_none};
	result.error = safer_ulong_multiplication_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a * b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result.value = ULONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

ulong_result_type safer_ulong_divide(unsigned long dividend, unsigned long divisor)
{
	ulong_result_type result = {0UL, 0UL, integer_operation_error_none};
	result.error = safer_ulong_division_check(dividend, divisor);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = dividend / divisor;
		result.remainder = dividend % divisor;
		break;
	default:
		break;
	}
	return result;
}

#if UNSIGNED_LONG_LONG_INTEGER_TYPE_IS_AVAILABLE
integer_operation_error_type safer_ullong_addition_check(unsigned long long a, unsigned long long b)
{
	const unsigned long long maximum_value = ULLONG_MAX;
	return (b <= (maximum_value - a)) ?
		integer_operation_error_none :
		integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
}

integer_operation_error_type safer_ullong_subtraction_check(unsigned long long a, unsigned long long b)
{
	return (a >= b) ?
		integer_operation_error_none :
		integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger;
}

integer_operation_error_type safer_ullong_multiplication_check(unsigned long long a, unsigned long long b)
{
	const unsigned long long zero = 0ULL;
	integer_operation_error_type error_code = integer_operation_error_none;
	if (a != zero and b != zero) {
		const unsigned long long maximum_value = ULLONG_MAX;
		const unsigned long long quotient = maximum_value / a;
		const unsigned long long remainder = maximum_value % a;
		if ((b > quotient) or (b == quotient and remainder != zero)) {
			error_code = integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller;
		}
	}
	return error_code;
}

integer_operation_error_type safer_ullong_division_check(unsigned long long dividend, unsigned long long divisor)
{
	const unsigned long long zero = 0ULL;
	return (divisor != zero) ?
		integer_operation_error_none :
		integer_operation_error_division_of_unsigned_integer_by_zero;
}

ullong_result_type safer_ullong_add(unsigned long long a, unsigned long long b)
{
	ullong_result_type result = {0ULL, 0ULL, integer_operation_error_none};
	result.error = safer_ullong_addition_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a + b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result.value = ULLONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

ullong_result_type safer_ullong_minus(unsigned long long a , unsigned long long b)
{
	ullong_result_type result = {0ULL, 0ULL, integer_operation_error_none};
	result.error = safer_ullong_subtraction_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a - b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		result.value = 0ULL;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}
ullong_result_type safer_ullong_multiply(unsigned long long a, unsigned long long b)
{
	ullong_result_type result = {0ULL, 0ULL, integer_operation_error_none};
	result.error = safer_ullong_multiplication_check(a, b);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = a * b;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		result.value = ULLONG_MAX;
		break;
	default:
		{
			const Boolean_type integer_operation_error_is_valid = Boolean_false;
			assert(integer_operation_error_is_valid);
		}
		break;
	}
	return result;
}

ullong_result_type safer_ullong_divide(unsigned long long dividend, unsigned long long divisor)
{
	ullong_result_type result = {0ULL, 0ULL, integer_operation_error_none};
	result.error = safer_ullong_division_check(dividend, divisor);
	switch (result.error) {
	case integer_operation_error_none:
		result.value = dividend / divisor;
		result.remainder = dividend % divisor;
		break;
	default:
		break;
	}
	return result;
}
#endif
