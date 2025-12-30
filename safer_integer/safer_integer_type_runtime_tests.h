#ifndef SAFER_INTEGER_TYPE_RUNTIME_TESTS_H
#define SAFER_INTEGER_TYPE_RUNTIME_TESTS_H

#define SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#define SAFER_INTEGER_TYPE_APPLY_SATURATED_RESULTS

#include "safer_integer_type.h"

#include <iso646.h>
#include <stdio.h>

static void test_sum_of_series(int n)
{
	DEFINE_SAFER_INTEGER(safer_int_type, sum, 0);
	DEFINE_SAFER_INTEGER(safer_int_type, i, 0);
	for (i = 1; i <= n; ++i) {
		sum += i;
	}
	printf("Sum of 1..%d = %d\n", n, (int)sum);
}

static void test_factorial(int n)
{
	DEFINE_SAFER_INTEGER(safer_int_type, result, 1);
	DEFINE_SAFER_INTEGER(safer_int_type, i, 0);
	for (i = 2; i <= n; ++i) {
		result *= i;
	}
	printf("Factorial of %d = %d\n", n, (int)result);
}

static int test_power(int base, int exponent)
{
	DEFINE_SAFER_INTEGER(safer_int_type, result, 1);
	DEFINE_SAFER_INTEGER(safer_int_type, i, 0);
	for (i = 0; i < exponent; ++i) {
		result *= base;
	}
	printf("%d ^ %d = %d\n", base, exponent, (int)result);
	return result;
}

static int test_binary_search(const int *arr, int size, int target)
{
	DEFINE_SAFER_INTEGER(safer_int_type, left, 0);
	DEFINE_SAFER_INTEGER(safer_int_type, right, (safer_int_type)size - 1);
	DEFINE_SAFER_INTEGER(safer_int_type, mid, -1);
	while (left <= right) {
		mid = (left + right) / 2;
		if (arr[mid] == target) {
			return mid;
		} else if (arr[mid] < target) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return mid;
}

static void test_integer_overflow_1(void)
{
	DEFINE_SAFER_INTEGER(const safer_int_type, a, INT_MAX);
	DEFINE_SAFER_INTEGER(const safer_int_type, b, 1);
	safer_int_type result = a + b;
	printf("Overflow test: INT_MAX + 1 = %d\n", (int)result);
}

static void test_integer_overflow_2(void)
{
	DEFINE_SAFER_INTEGER(const safer_int_type, a, INT_MIN);
	DEFINE_SAFER_INTEGER(const safer_int_type, b, 1);
	safer_int_type result = a - b;
	printf("Underflow test: INT_MIN - 1 = %d\n", (int)result);
}

static void test_integer_division_by_zero(void)
{
#ifdef __cplusplus
	DEFINE_SAFER_INTEGER(const safer_int_type, a, 1);
	DEFINE_SAFER_INTEGER(const safer_int_type, b, 0);
	safer_int_type result = a / b;
	printf("The result of division by zero is undefined. The result (%d) shall not be used.\n", (int)result);
#else
	printf("Division by zero test skipped because runtime checks are disabled.\n");
#endif
}

static void test_division_of_minimum_integer_value_by_minus_one(void)
{
#ifdef __cplusplus
	DEFINE_SAFER_INTEGER(const safer_int_type, a, INT_MIN);
	DEFINE_SAFER_INTEGER(const safer_int_type, b, -1);
	safer_int_type result = a / b;
	printf("The result of division %d by %d is %d.\n", (int)a, (int)b, (int)result);
#else
	printf("Division of minimum integer value by -1 test skipped because runtime checks are disabled.\n");
#endif
}

static void test_Boolean_comparisons(void)
{
	DEFINE_SAFER_INTEGER(const safer_short_type, a, -1);
	DEFINE_SAFER_INTEGER(const safer_int_type, b, 0);
	safer_bool_type result = (a and b);
	printf("Boolean comparison: %d AND %d = %s\n", (int)a, (int)b, (result ? "true" : "false"));
	result = (a or b);
	printf("Boolean comparison: %d OR %d = %s\n", (int)a, (int)b, (result ? "true" : "false"));
	result = not a;
	printf("Boolean comparison: NOT %d = %s\n", (int)a, (result ? "true" : "false"));
	result = not b;
	printf("Boolean comparison: NOT %d = %s\n", (int)b, (result ? "true" : "false"));
	if (a) {
		printf("This will be printed.\n");
	}
	if (b) {
		printf("This will NOT be printed.\n");
	}
}

static void test_conversions(void)
{
	safer_short_type s = SHRT_MAX;
	safer_int_type i = s += 1;
	signed char native_sc = s;
	safer_long_type l = i;

	printf("Misc test: SHRT_MAX + 1 = %d\n", (int)i);
	printf("Misc test: signed char from short_type = %d\n", (int)native_sc);
	printf("Misc test: long_type from int_type = %ld\n", (long)l);
}

static void run_tests(void)
{
	int i = 0;
	int arr[10] = {0};

	printf("Testing sum of series...\n");
	test_sum_of_series(100);

	printf("Testing factorial...\n");
	test_factorial(13); /* 13! overflows 32-bit int */

	printf("Testing integer power...\n");
	test_power(2, 31); /* 2^31 overflows 32-bit int */

	printf("Testing binary search...\n");
	for (i = 0; i < 10; ++i) {
		arr[i] = i * 3;
	}
	int idx = test_binary_search(arr, 10, 9);
	printf("Binary search for 9 in arr: %s (index %d)\n", (idx >= 0 ? "found" : "not found"), idx);

	printf("Testing integer overflow...\n");
	test_integer_overflow_1();

	printf("Testing integer underflow...\n");
	test_integer_overflow_2();

	printf("Testing division by zero...\n");
	test_integer_division_by_zero();

	printf("Testing division of minimum integer value (%d) by -1...\n", INT_MIN);
	test_division_of_minimum_integer_value_by_minus_one();

	printf("Testing Boolean comparisons\n");
	test_Boolean_comparisons();

	printf("Testing conversions\n");
	test_conversions();
}

#endif /* include guard */
