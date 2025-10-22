#ifndef SAFER_INTEGER_H
#define SAFER_INTEGER_H

#include <limits.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* runtime checks for integer operations which can cause undefined behavior */
typedef enum integer_operation_error_type
{
	integer_operation_error_none = 0,
	integer_operation_error_signed_integer_result_smaller_than_minimum,
	integer_operation_error_signed_integer_result_greater_than_maximum,
	integer_operation_error_division_of_signed_integer_by_zero,
	integer_operation_error_division_of_minimum_signed_integer_by_minus_one, /* for two's complement signed integers */
	integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller,
	integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger,
	integer_operation_error_division_of_unsigned_integer_by_zero
} integer_operation_error_type;

const char *integer_operation_error_message(integer_operation_error_type error);

/* Signed integers and safer operations */
/* Checks whether the result of (a + b) is within the range of [INT_MIN, INT_MAX] */
integer_operation_error_type safer_int_addition_check(int a, int b);
/* Checks whether the result of (a - b) is within the range of [INT_MIN, INT_MAX] */
integer_operation_error_type safer_int_subtraction_check(int a, int b);
/* Checks whether the result of (a * b) is within the range of [INT_MIN, INT_MAX] */
integer_operation_error_type safer_int_multiplication_check(int a, int b);
/* Checks whether the result of (a / b) is within the range of [INT_MIN, INT_MAX] */
integer_operation_error_type safer_int_division_check(int dividend, int divisor);

typedef struct int_result_type
{
	int value;     /* for division, value is the quotient */
	int remainder; /* the remainder of a division operation (only for division) */
	integer_operation_error_type error;
} int_result_type;

/* The result is clipped to INT_MIN if it is smaller than INT_MIN or to INT_MAX if it is larger than INT_MAX */
int_result_type safer_int_add(int a, int b);
int_result_type safer_int_minus(int a, int b);
int_result_type safer_int_multiply(int a, int b);
int_result_type safer_int_divide(int dividend, int divisor);

/* Signed long integers and safer operations */
/* Checks whether the result of (a + b) is within the range of [LONG_MIN, LONG_MAX] */
integer_operation_error_type safer_long_addition_check(long a, long b);
/* Checks whether the result of (a - b) is within the range of [LONG_MIN, LONG_MAX] */
integer_operation_error_type safer_long_subtraction_check(long a, long b);
/* Checks whether the result of (a * b) is within the range of [LONG_MIN, LONG_MAX] */
integer_operation_error_type safer_long_multiplication_check(long a, long b);
/* Checks whether the result of (a / b) is within the range of [LONG_MIN, LONG_MAX] */
integer_operation_error_type safer_long_division_check(long dividend, long divisor);

typedef struct long_result_type
{
	long value;     /* for division, value is the quotient */
	long remainder; /* the remainder of a division operation (only for division) */
	integer_operation_error_type error;
} long_result_type;

/* The result is clipped to LONG_MIN if it is smaller than LONG_MIN or to LONG_MAX if it is larger than LONG_MAX */
long_result_type safer_long_add(long a, long b);
long_result_type safer_long_minus(long a, long b);
long_result_type safer_long_multiply(long a, long b);
long_result_type safer_long_divide(long dividend, long divisor);

#if defined(LLONG_MIN) && defined(LLONG_MAX)
/* Signed long long integers and safer operations */
/* Checks whether the result of (a + b) is within the range of [LLONG_MIN, LLONG_MAX] */
integer_operation_error_type safer_llong_addition_check(long long a, long long b);
/* Checks whether the result of (a - b) is within the range of [LLONG_MIN, LLONG_MAX] */
integer_operation_error_type safer_llong_subtraction_check(long long a, long long b);
/* Checks whether the result of (a * b) is within the range of [LLONG_MIN, LLONG_MAX] */
integer_operation_error_type safer_llong_multiplication_check(long long a, long long b);
/* Checks whether the result of (a / b) is within the range of [LLONG_MIN, LLONG_MAX] */
integer_operation_error_type safer_llong_division_check(long long dividend, long long divisor);

typedef struct llong_result_type
{
	long long value;     /* for division, value is the quotient */
	long long remainder; /* the remainder of a division operation (only for division) */
	integer_operation_error_type error;
} llong_result_type;

/* The result is clipped to LLONG_MIN if it is smaller than LLONG_MIN or to LLONG_MAX if it is larger than LLONG_MAX */
llong_result_type safer_llong_add(long long a, long long b);
llong_result_type safer_llong_minus(long long a, long long b);
llong_result_type safer_llong_multiply(long long a, long long b);
llong_result_type safer_llong_divide(long long dividend, long long divisor);
#else
#pragma message("safer integer: long long type is not supported.")
#endif

/* runtime checks for unsigned integer operations */
integer_operation_error_type safer_uint_addition_check(unsigned int a, unsigned int b);
integer_operation_error_type safer_uint_subtraction_check(unsigned int a, unsigned int b);
integer_operation_error_type safer_uint_multiplication_check(unsigned int a, unsigned int b);
integer_operation_error_type safer_uint_division_check(unsigned int dividend, unsigned int divisor);

/* Safer unsigned integer operations */
typedef struct uint_result_type
{
	unsigned int value;     /* for division, value is the quotient */
	unsigned int remainder; /* the remainder of a division operation (only for division) */
	integer_operation_error_type error;
} uint_result_type;

uint_result_type safer_uint_add(unsigned int a, unsigned int b);
uint_result_type safer_uint_minus(unsigned int a , unsigned int b);
uint_result_type safer_uint_multiply(unsigned int a, unsigned int b);
uint_result_type safer_uint_divide(unsigned int dividend, unsigned int divisor);

integer_operation_error_type safer_ulong_addition_check(unsigned long a, unsigned long b);
integer_operation_error_type safer_ulong_subtraction_check(unsigned long a, unsigned long b);
integer_operation_error_type safer_ulong_multiplication_check(unsigned long a, unsigned long b);
integer_operation_error_type safer_ulong_division_check(unsigned long dividend, unsigned long divisor);

typedef struct ulong_result_type
{
	unsigned long value;     /* for division, value is the quotient */
	unsigned long remainder; /* the remainder of a division operation (only for division) */
	integer_operation_error_type error;
} ulong_result_type;

ulong_result_type safer_ulong_add(unsigned long a, unsigned long b);
ulong_result_type safer_ulong_minus(unsigned long a , unsigned long b);
ulong_result_type safer_ulong_multiply(unsigned long a, unsigned long b);
ulong_result_type safer_ulong_divide(unsigned long dividend, unsigned long divisor);

#if defined(ULLONG_MAX)
integer_operation_error_type safer_ullong_addition_check(unsigned long long a, unsigned long long b);
integer_operation_error_type safer_ullong_subtraction_check(unsigned long long a, unsigned long long b);
integer_operation_error_type safer_ullong_multiplication_check(unsigned long long a, unsigned long long b);
integer_operation_error_type safer_ullong_division_check(unsigned long long dividend, unsigned long long divisor);

typedef struct ullong_result_type
{
	unsigned long long value;     /* for division, value is the quotient */
	unsigned long long remainder; /* the remainder of a division operation (only for division) */
	integer_operation_error_type error;
} ullong_result_type;

ullong_result_type safer_ullong_add(unsigned long long a, unsigned long long b);
ullong_result_type safer_ullong_minus(unsigned long long a , unsigned long long b);
ullong_result_type safer_ullong_multiply(unsigned long long a, unsigned long long b);
ullong_result_type safer_ullong_divide(unsigned long long dividend, unsigned long long divisor);
#else
#pragma message("safer integer: unsigned long long type is not supported.")
#endif

#ifdef __cplusplus
}
#endif

#endif
