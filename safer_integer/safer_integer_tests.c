#include "safer_integer_short_macros.h"
#include "unit_testing.h"

TEST(safer_int_addition_check_tests, "Check overflow and normal cases for int addition")
{
	ASSERT_EQUAL(safer_int_addition_check(1, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_addition_check(INT_MIN, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_addition_check(INT_MAX - 1, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_addition_check(INT_MAX, 1), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_int_addition_check(INT_MIN, -1), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_int_addition_check(INT_MAX, INT_MAX), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_int_addition_check(INT_MIN, INT_MIN), integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_int_subtraction_check_tests, "Check underflow and normal cases for int subtraction")
{
	ASSERT_EQUAL(safer_int_subtraction_check(10, 5), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_subtraction_check(INT_MIN + 1, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_subtraction_check(INT_MAX, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_subtraction_check(INT_MIN, 1), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_int_subtraction_check(INT_MAX, -1), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_int_subtraction_check(INT_MIN, INT_MAX), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_int_subtraction_check(INT_MAX, INT_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
#if INT_MIN < -INT_MAX
	ASSERT_EQUAL(safer_int_subtraction_check(0, INT_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
#endif
}

TEST(safer_int_multiplication_check_tests, "Check overflow and normal cases for int multiplication")
{
	ASSERT_EQUAL(safer_int_multiplication_check(10, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MIN / 2, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MAX / 2, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MIN, 2), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MAX, 2), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MIN, INT_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MAX, INT_MAX), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MIN, INT_MAX), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MAX, INT_MIN), integer_operation_error_signed_integer_result_smaller_than_minimum);
#if INT_MIN < -INT_MAX
	ASSERT_EQUAL(safer_int_multiplication_check(INT_MIN, -1), integer_operation_error_signed_integer_result_greater_than_maximum);
#endif
}

TEST(safer_int_division_check_tests, "Check division by zero and edge cases for int division")
{
	ASSERT_EQUAL(safer_int_division_check(0, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(10, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(INT_MIN, INT_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(INT_MAX, INT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(INT_MIN, INT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(INT_MAX, INT_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(-1, INT_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(INT_MAX, -1), integer_operation_error_none);
	ASSERT_EQUAL(safer_int_division_check(0, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_int_division_check(10, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_int_division_check(INT_MIN, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_int_division_check(INT_MAX, 0), integer_operation_error_division_of_signed_integer_by_zero);
#if INT_MIN < -INT_MAX
	ASSERT_EQUAL(safer_int_division_check(INT_MIN, -1), integer_operation_error_division_of_minimum_signed_integer_by_minus_one);
#endif
}

TEST(int_addition_tests, "int addition")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = siadd(0, 0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = siadd(10, 20);
	ASSERT_INT_EQUAL(result.value, 30);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = siadd(-5, 5);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = siadd(INT_MIN, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
#if INT_MIN == (-INT_MAX - 1)
	ASSERT_INT_EQUAL(result.value, -1);
#elif INT_MIN == -INT_MAX
	ASSERT_INT_EQUAL(result.value, 0);
#else
	#error "Unsupported integer representation: neither one's complement nor two's complement."
#endif

	result = siadd(INT_MAX, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
#if INT_MIN == (-INT_MAX - 1)
	ASSERT_INT_EQUAL(result.value, -1);
#elif INT_MIN == -INT_MAX
	ASSERT_INT_EQUAL(result.value, 0);
#else
	#error "Unsupported integer representation: neither one's complement nor two's complement."
#endif
}

TEST(int_addition_edge_cases, "Edge cases for int addition")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = siadd(INT_MAX, 1);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = siadd(INT_MIN, -1);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = siadd(INT_MAX, INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = siadd(INT_MIN, INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(int_subtraction_tests, "int subtraction")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = sisub(0, 0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sisub(10, 5);
	ASSERT_INT_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sisub(-10, -5);
	ASSERT_INT_EQUAL(result.value, -5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sisub(INT_MIN, INT_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sisub(INT_MAX, INT_MAX);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(int_subtraction_edge_cases, "Edge cases for int subtraction")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = sisub(INT_MAX, -1);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sisub(INT_MIN, 1);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = sisub(INT_MAX, INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sisub(INT_MIN, INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(int_multiplication_tests, "int multiplication")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = simul(0, 0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(-1000, -1000);
	ASSERT_INT_EQUAL(result.value, 1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(-1000, 1000);
	ASSERT_INT_EQUAL(result.value, -1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(1000, -1000);
	ASSERT_INT_EQUAL(result.value, -1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(1000, 1000);
	ASSERT_INT_EQUAL(result.value, 1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(INT_MIN, 1);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(INT_MAX, 1);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(int_multiplication_edge_cases, "Edge cases for int multiplication")
{
	int_result_type result = {0, 0, integer_operation_error_none};

#if INT_MIN < -INT_MAX
	result = simul(INT_MIN, -1);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
#endif

	result = simul(INT_MAX, -2);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = simul(INT_MIN, 2);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = simul(INT_MAX, 2);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = simul(INT_MIN, -2);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = simul(INT_MAX, INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = simul(INT_MIN, INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = simul(INT_MAX, INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = simul(INT_MIN, INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(int_division_tests, "int division")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = sidiv(0, 1);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_INT_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sidiv(21, 10);
	ASSERT_INT_EQUAL(result.value, 2);
	ASSERT_INT_EQUAL(result.remainder, 1);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sidiv(-5, 5);
	ASSERT_INT_EQUAL(result.value, -1);
	ASSERT_INT_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sidiv(INT_MIN, 1);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_INT_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sidiv(INT_MAX, 1);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_INT_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sidiv(INT_MIN, INT_MIN);
	ASSERT_INT_EQUAL(result.value, 1);
	ASSERT_INT_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sidiv(INT_MAX, INT_MAX);
	ASSERT_INT_EQUAL(result.value, 1);
	ASSERT_INT_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(int_division_edge_cases, "Edge cases for int division")
{
	int_result_type result = {0, 0, integer_operation_error_none};

	result = sidiv(INT_MIN, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sidiv(-1, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sidiv(0, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sidiv(1, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sidiv(INT_MAX, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

#if INT_MIN == (-INT_MAX - 1)
	result = sidiv(INT_MIN, -1);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);
#endif
}

TEST(safer_long_addition_check_tests, "Check overflow and normal cases for long addition")
{
	ASSERT_EQUAL(safer_long_addition_check(1, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_addition_check(LONG_MIN, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_addition_check(LONG_MAX - 1, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_addition_check(LONG_MAX, 1), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_long_addition_check(LONG_MIN, -1), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_long_addition_check(LONG_MAX, LONG_MAX), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_long_addition_check(LONG_MIN, LONG_MIN), integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_long_subtraction_check_tests, "Check underflow and normal cases for long subtraction")
{
	ASSERT_EQUAL(safer_long_subtraction_check(10, 5), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_subtraction_check(LONG_MIN + 1, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_subtraction_check(LONG_MAX, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_subtraction_check(LONG_MIN, 1), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_long_subtraction_check(LONG_MAX, -1), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_long_subtraction_check(LONG_MIN, LONG_MAX), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_long_subtraction_check(LONG_MAX, LONG_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
#if LONG_MIN < -LONG_MAX
	ASSERT_EQUAL(safer_long_subtraction_check(0, LONG_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
#endif
}

TEST(safer_long_multiplication_check_tests, "Check overflow and normal cases for long multiplication")
{
	ASSERT_EQUAL(safer_long_multiplication_check(10, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MIN / 2, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MAX / 2, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MIN, 2), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MAX, 2), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MIN, LONG_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MAX, LONG_MAX), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MIN, LONG_MAX), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MAX, LONG_MIN), integer_operation_error_signed_integer_result_smaller_than_minimum);
#if LONG_MIN < -LONG_MAX
	ASSERT_EQUAL(safer_long_multiplication_check(LONG_MIN, -1), integer_operation_error_signed_integer_result_greater_than_maximum);
#endif
}

TEST(safer_long_division_check_tests, "Check division by zero and edge cases for long division")
{
	ASSERT_EQUAL(safer_long_division_check(0, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(10, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(LONG_MIN, LONG_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(LONG_MAX, LONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(LONG_MIN, LONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(LONG_MAX, LONG_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(-1, LONG_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(LONG_MAX, -1), integer_operation_error_none);
	ASSERT_EQUAL(safer_long_division_check(0, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_long_division_check(10, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_long_division_check(LONG_MIN, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_long_division_check(LONG_MAX, 0), integer_operation_error_division_of_signed_integer_by_zero);
#if LONG_MIN < -LONG_MAX
	ASSERT_EQUAL(safer_long_division_check(LONG_MIN, -1), integer_operation_error_division_of_minimum_signed_integer_by_minus_one);
#endif
}

TEST(long_addition_tests, "long addition")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = sladd(0, 0);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sladd(10, 20);
	ASSERT_LONG_EQUAL(result.value, 30);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sladd(-5, 5);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sladd(LONG_MIN, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
#if LONG_MIN == (-LONG_MAX - 1)
	ASSERT_LONG_EQUAL(result.value, -1);
#elif LONG_MIN == -LONG_MAX
	ASSERT_LONG_EQUAL(result.value, 0);
#else
	#error "Unsupported integer representation: neither one's complement nor two's complement."
#endif

	result = sladd(LONG_MAX, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
#if LONG_MIN == (-LONG_MAX - 1)
	ASSERT_LONG_EQUAL(result.value, -1);
#elif LONG_MIN == -LONG_MAX
	ASSERT_LONG_EQUAL(result.value, 0);
#else
	#error "Unsupported integer representation: neither one's complement nor two's complement."
#endif
}

TEST(long_addition_edge_cases, "Edge cases for long addition")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = sladd(LONG_MAX, 1);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sladd(LONG_MIN, -1);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = sladd(LONG_MAX, LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sladd(LONG_MIN, LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(long_subtraction_tests, "long subtraction")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = slsub(0, 0);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slsub(10, 5);
	ASSERT_LONG_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slsub(-10, -5);
	ASSERT_LONG_EQUAL(result.value, -5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slsub(LONG_MIN, LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slsub(LONG_MAX, LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(long_subtraction_edge_cases, "Edge cases for long subtraction")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = slsub(LONG_MAX, -1);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slsub(LONG_MIN, 1);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = slsub(LONG_MAX, LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slsub(LONG_MIN, LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(long_multiplication_tests, "long multiplication")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = slmul(0, 0);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(-1000, -1000);
	ASSERT_LONG_EQUAL(result.value, 1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(-1000, 1000);
	ASSERT_LONG_EQUAL(result.value, -1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(1000, -1000);
	ASSERT_LONG_EQUAL(result.value, -1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(1000, 1000);
	ASSERT_LONG_EQUAL(result.value, 1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(LONG_MIN, 1);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(LONG_MAX, 1);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(long_multiplication_edge_cases, "Edge cases for long multiplication")
{
	long_result_type result = {0, 0, integer_operation_error_none};

#if LONG_MIN < -LONG_MAX
	result = slmul(LONG_MIN, -1);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
#endif

	result = slmul(LONG_MAX, -2);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = slmul(LONG_MIN, 2);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = slmul(LONG_MAX, 2);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slmul(LONG_MIN, -2);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slmul(LONG_MAX, LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slmul(LONG_MIN, LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slmul(LONG_MAX, LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = slmul(LONG_MIN, LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(long_division_tests, "long division")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = sldiv(0, 1);
	ASSERT_LONG_EQUAL(result.value, 0);
	ASSERT_LONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sldiv(21, 10);
	ASSERT_LONG_EQUAL(result.value, 2);
	ASSERT_LONG_EQUAL(result.remainder, 1);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sldiv(-5, 5);
	ASSERT_LONG_EQUAL(result.value, -1);
	ASSERT_LONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sldiv(LONG_MIN, 1);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_LONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sldiv(LONG_MAX, 1);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_LONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sldiv(LONG_MIN, LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, 1);
	ASSERT_LONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sldiv(LONG_MAX, LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, 1);
	ASSERT_LONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(long_division_edge_cases, "Edge cases for long division")
{
	long_result_type result = {0, 0, integer_operation_error_none};

	result = sldiv(LONG_MIN, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sldiv(-1, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sldiv(0, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sldiv(1, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = sldiv(LONG_MAX, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

#if LONG_MIN == (-LONG_MAX - 1)
	result = sldiv(LONG_MIN, -1);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);
#endif
}

#if LONG_LONG_INTEGER_TYPE_IS_AVAILABLE
TEST(safer_llong_addition_check_tests, "Check overflow and normal cases for long long addition")
{
	ASSERT_EQUAL(safer_llong_addition_check(1, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_addition_check(LLONG_MIN, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_addition_check(LLONG_MAX - 1, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_addition_check(LLONG_MAX, 1), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_llong_addition_check(LLONG_MIN, -1), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_llong_addition_check(LLONG_MAX, LLONG_MAX), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_llong_addition_check(LLONG_MIN, LLONG_MIN), integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_llong_subtraction_check_tests, "Check underflow and normal cases for long long subtraction")
{
	ASSERT_EQUAL(safer_llong_subtraction_check(10, 5), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_subtraction_check(LLONG_MIN + 1, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_subtraction_check(LLONG_MAX, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_subtraction_check(LLONG_MIN, 1), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_llong_subtraction_check(LLONG_MAX, -1), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_llong_subtraction_check(LLONG_MIN, LLONG_MAX), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_llong_subtraction_check(LLONG_MAX, LLONG_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
#if LLONG_MIN < -LLONG_MAX
	ASSERT_EQUAL(safer_llong_subtraction_check(0, LLONG_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
#endif
}

TEST(safer_llong_multiplication_check_tests, "Check overflow and normal cases for long long multiplication")
{
	ASSERT_EQUAL(safer_llong_multiplication_check(10, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MIN / 2, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MAX / 2, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MIN, 2), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MAX, 2), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MIN, LLONG_MIN), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MAX, LLONG_MAX), integer_operation_error_signed_integer_result_greater_than_maximum);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MIN, LLONG_MAX), integer_operation_error_signed_integer_result_smaller_than_minimum);
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MAX, LLONG_MIN), integer_operation_error_signed_integer_result_smaller_than_minimum);
#if LLONG_MIN < -LLONG_MAX
	ASSERT_EQUAL(safer_llong_multiplication_check(LLONG_MIN, -1), integer_operation_error_signed_integer_result_greater_than_maximum);
#endif
}

TEST(safer_llong_division_check_tests, "Check division by zero and edge cases for long long division")
{
	ASSERT_EQUAL(safer_llong_division_check(0, 1), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(10, 2), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MIN, LLONG_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MAX, LLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MIN, LLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MAX, LLONG_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(-1, LLONG_MIN), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MAX, -1), integer_operation_error_none);
	ASSERT_EQUAL(safer_llong_division_check(0, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_llong_division_check(10, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MIN, 0), integer_operation_error_division_of_signed_integer_by_zero);
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MAX, 0), integer_operation_error_division_of_signed_integer_by_zero);
#if LLONG_MIN < -LLONG_MAX
	ASSERT_EQUAL(safer_llong_division_check(LLONG_MIN, -1), integer_operation_error_division_of_minimum_signed_integer_by_minus_one);
#endif
}

TEST(llong_addition_tests, "long long addition")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = slladd(0, 0);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slladd(10, 20);
	ASSERT_LLONG_EQUAL(result.value, 30);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slladd(-5, 5);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slladd(LLONG_MIN, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
#if LLONG_MIN == (-LLONG_MAX - 1)
	ASSERT_LLONG_EQUAL(result.value, -1);
#elif LLONG_MIN == -LLONG_MAX
	ASSERT_LLONG_EQUAL(result.value, 0);
#else
	#error "Unsupported integer representation: neither one's complement nor two's complement."
#endif

	result = slladd(LLONG_MAX, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
#if LLONG_MIN == (-LLONG_MAX - 1)
	ASSERT_LLONG_EQUAL(result.value, -1);
#elif LLONG_MIN == -LLONG_MAX
	ASSERT_LLONG_EQUAL(result.value, 0);
#else
	#error "Unsupported integer representation: neither one's complement nor two's complement."
#endif
}

TEST(llong_addition_edge_cases, "Edge cases for long long addition")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = slladd(LLONG_MAX, 1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slladd(LLONG_MIN, -1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = slladd(LLONG_MAX, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = slladd(LLONG_MIN, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(llong_subtraction_tests, "long long subtraction")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = sllsub(0, 0);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllsub(10, 5);
	ASSERT_LLONG_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllsub(-10, -5);
	ASSERT_LLONG_EQUAL(result.value, -5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllsub(LLONG_MIN, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllsub(LLONG_MAX, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(llong_subtraction_edge_cases, "Edge cases for long long subtraction")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = sllsub(LLONG_MAX, -1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sllsub(LLONG_MIN, 1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = sllsub(LLONG_MAX, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sllsub(LLONG_MIN, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(llong_multiplication_tests, "long long multiplication")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = sllmul(0, 0);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllmul(-1000, -1000);
	ASSERT_LLONG_EQUAL(result.value, 1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllmul(-1000, 1000);
	ASSERT_LLONG_EQUAL(result.value, -1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllmul(1000, -1000);
	ASSERT_LLONG_EQUAL(result.value, -1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllmul(1000, 1000);
	ASSERT_LLONG_EQUAL(result.value, 1000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllmul(LLONG_MIN, 1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sllmul(LLONG_MAX, 1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(llong_multiplication_edge_cases, "Edge cases for long long multiplication")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

#if LLONG_MIN < -LLONG_MAX
	result = sllmul(LLONG_MIN, -1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
#endif

	result = sllmul(LLONG_MAX, -2);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = sllmul(LLONG_MIN, 2);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = sllmul(LLONG_MAX, 2);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sllmul(LLONG_MIN, -2);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sllmul(LLONG_MAX, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sllmul(LLONG_MIN, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = sllmul(LLONG_MAX, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = sllmul(LLONG_MIN, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(llong_division_tests, "long long division")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = slldiv(0, 1);
	ASSERT_LLONG_EQUAL(result.value, 0);
	ASSERT_LLONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slldiv(21, 10);
	ASSERT_LLONG_EQUAL(result.value, 2);
	ASSERT_LLONG_EQUAL(result.remainder, 1);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slldiv(-5, 5);
	ASSERT_LLONG_EQUAL(result.value, -1);
	ASSERT_LLONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slldiv(LLONG_MIN, 1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slldiv(LLONG_MAX, 1);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slldiv(LLONG_MIN, LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, 1);
	ASSERT_LLONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slldiv(LLONG_MAX, LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, 1);
	ASSERT_LLONG_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(llong_division_edge_cases, "Edge cases for long long division")
{
	llong_result_type result = {0, 0, integer_operation_error_none};

	result = slldiv(LLONG_MIN, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = slldiv(-1, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = slldiv(0, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = slldiv(1, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

	result = slldiv(LLONG_MAX, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);

#if LLONG_MIN == (-LLONG_MAX - 1)
	result = slldiv(LLONG_MIN, -1);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);
#endif
}
#endif /* LONG_LONG_INTEGER_TYPE_IS_AVAILABLE */

TEST(safer_uint_addition_check_tests, "Check overflow and normal cases for unsigned int addition")
{
	ASSERT_EQUAL(safer_uint_addition_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_addition_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_addition_check(0U, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_addition_check(UINT_MAX, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_addition_check(UINT_MAX - 1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_addition_check(UINT_MAX, 1U), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_uint_addition_check(UINT_MAX, UINT_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_uint_subtraction_check_tests, "Check overflow and normal cases for unsigned int subtraction")
{
	ASSERT_EQUAL(safer_uint_subtraction_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_subtraction_check(1U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_subtraction_check(UINT_MAX, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_subtraction_check(UINT_MAX, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_subtraction_check(0U, 1U), integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
	ASSERT_EQUAL(safer_uint_subtraction_check(0U, UINT_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_uint_multiplication_check_tests, "Check overflow and normal cases for unsigned int multiplication")
{
	ASSERT_EQUAL(safer_uint_multiplication_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(0U, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(1U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(1U, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(UINT_MAX, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_multiplication_check(UINT_MAX, 2U), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_uint_multiplication_check(2U, UINT_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_uint_multiplication_check(UINT_MAX, UINT_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_uint_division_check_tests, "Check division by zero and edge cases for unsigned int division")
{
	ASSERT_EQUAL(safer_uint_division_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_division_check(0U, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_division_check(1U, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_division_check(1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_division_check(UINT_MAX, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_division_check(UINT_MAX, UINT_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_uint_division_check(0U, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
	ASSERT_EQUAL(safer_uint_division_check(1U, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
	ASSERT_EQUAL(safer_uint_division_check(UINT_MAX, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(uint_addition_tests, "unsigned int addition")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suiadd(0U, 0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suiadd(10U, 20U);
	ASSERT_UINT_EQUAL(result.value, 30U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suiadd(0U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suiadd(UINT_MAX, 0U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suiadd(1U, UINT_MAX - 1U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suiadd(UINT_MAX - 1U, 1U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(uint_addition_edge_cases, "Edge cases for unsigned int addition")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suiadd(1U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = suiadd(UINT_MAX, 1U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = suiadd(UINT_MAX, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(uint_subtraction_tests, "unsigned int subtraction")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suisub(0U, 0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suisub(10U, 5U);
	ASSERT_UINT_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suisub(UINT_MAX, 0U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suisub(UINT_MAX, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(uint_subtraction_edge_cases, "Edge cases for unsigned int subtraction")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suisub(0U, 1U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);

	result = suisub(0U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(uint_multiplication_tests, "unsigned int multiplication")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suimul(0U, 0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suimul(1U, 1U);
	ASSERT_UINT_EQUAL(result.value, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suimul(1U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suimul(UINT_MAX, 1U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(uint_multiplication_edge_cases, "Edge cases for unsigned int multiplication")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suimul(2U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = suimul(UINT_MAX, 2U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = suimul(UINT_MAX, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(uint_division_tests, "unsigned int division")
{
	uint_result_type result = {0U, 0U, integer_operation_error_none};

	result = suidiv(0U, 1U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_UINT_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suidiv(25U, 10U);
	ASSERT_UINT_EQUAL(result.value, 2U);
	ASSERT_UINT_EQUAL(result.remainder, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suidiv(0U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_UINT_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suidiv(1U, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_UINT_EQUAL(result.remainder, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suidiv(UINT_MAX, 1U);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_UINT_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suidiv(UINT_MAX, UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 1U);
	ASSERT_UINT_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(uint_division_edge_cases, "Edge cases for unsigned int division")
{
	uint_result_type result = {0, 0, integer_operation_error_none};

	result = suidiv(0U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

	result = suidiv(1U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

	result = suidiv(UINT_MAX, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(safer_ulong_addition_check_tests, "Check overflow and normal cases for unsigned long addition")
{
	ASSERT_EQUAL(safer_ulong_addition_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_addition_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_addition_check(0U, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_addition_check(ULONG_MAX, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_addition_check(ULONG_MAX - 1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_addition_check(ULONG_MAX, 1U), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_ulong_addition_check(ULONG_MAX, ULONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_ulong_subtraction_check_tests, "Check overflow and normal cases for unsigned long subtraction")
{
	ASSERT_EQUAL(safer_ulong_subtraction_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_subtraction_check(1U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_subtraction_check(ULONG_MAX, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_subtraction_check(ULONG_MAX, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_subtraction_check(0U, 1U), integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
	ASSERT_EQUAL(safer_ulong_subtraction_check(0U, ULONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_ulong_multiplication_check_tests, "Check overflow and normal cases for unsigned long multiplication")
{
	ASSERT_EQUAL(safer_ulong_multiplication_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(0U, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(1U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(1U, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(ULONG_MAX, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_multiplication_check(ULONG_MAX, 2U), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_ulong_multiplication_check(2U, ULONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_ulong_multiplication_check(ULONG_MAX, ULONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_ulong_division_check_tests, "Check division by zero and edge cases for unsigned long division")
{
	ASSERT_EQUAL(safer_ulong_division_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_division_check(0U, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_division_check(1U, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_division_check(1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_division_check(ULONG_MAX, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_division_check(ULONG_MAX, ULONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ulong_division_check(0U, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
	ASSERT_EQUAL(safer_ulong_division_check(1U, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
	ASSERT_EQUAL(safer_ulong_division_check(ULONG_MAX, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(ulong_addition_tests, "unsigned long addition")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = suladd(0U, 0U);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suladd(10U, 20U);
	ASSERT_ULONG_EQUAL(result.value, 30U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suladd(0U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suladd(ULONG_MAX, 0U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suladd(1U, ULONG_MAX - 1U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suladd(ULONG_MAX - 1U, 1U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ulong_addition_edge_cases, "Edge cases for unsigned long addition")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = suladd(1U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = suladd(ULONG_MAX, 1U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = suladd(ULONG_MAX, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(ulong_subtraction_tests, "unsigned long subtraction")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulsub(0U, 0U);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulsub(10U, 5U);
	ASSERT_ULONG_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulsub(ULONG_MAX, 0U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulsub(ULONG_MAX, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ulong_subtraction_edge_cases, "Edge cases for unsigned long subtraction")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulsub(0U, 1U);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);

	result = sulsub(0U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(ulong_multiplication_tests, "unsigned long multiplication")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulmul(0U, 0U);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulmul(1U, 1U);
	ASSERT_ULONG_EQUAL(result.value, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulmul(1U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulmul(ULONG_MAX, 1U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ulong_multiplication_edge_cases, "Edge cases for unsigned long multiplication")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulmul(2U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = sulmul(ULONG_MAX, 2U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = sulmul(ULONG_MAX, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(ulong_division_tests, "unsigned long division")
{
	ulong_result_type result = {0U, 0U, integer_operation_error_none};

	result = suldiv(0U, 1U);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_ULONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suldiv(25U, 10U);
	ASSERT_ULONG_EQUAL(result.value, 2U);
	ASSERT_ULONG_EQUAL(result.remainder, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suldiv(0U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_ULONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suldiv(1U, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, 0U);
	ASSERT_ULONG_EQUAL(result.remainder, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suldiv(ULONG_MAX, 1U);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = suldiv(ULONG_MAX, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, 1U);
	ASSERT_ULONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ulong_division_edge_cases, "Edge cases for unsigned long division")
{
	ulong_result_type result = {0, 0, integer_operation_error_none};

	result = suldiv(0U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

	result = suldiv(1U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

	result = suldiv(ULONG_MAX, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

}

TEST(safer_ullong_addition_check_tests, "Check overflow and normal cases for unsigned long long addition")
{
	ASSERT_EQUAL(safer_ullong_addition_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_addition_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_addition_check(0U, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_addition_check(ULLONG_MAX, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_addition_check(ULLONG_MAX - 1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_addition_check(ULLONG_MAX, 1U), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_ullong_addition_check(ULLONG_MAX, ULLONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_ullong_subtraction_check_tests, "Check overflow and normal cases for unsigned long long subtraction")
{
	ASSERT_EQUAL(safer_ullong_subtraction_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_subtraction_check(1U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_subtraction_check(ULLONG_MAX, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_subtraction_check(ULLONG_MAX, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_subtraction_check(0U, 1U), integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
	ASSERT_EQUAL(safer_ullong_subtraction_check(0U, ULLONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_ullong_multiplication_check_tests, "Check overflow and normal cases for unsigned long long multiplication")
{
	ASSERT_EQUAL(safer_ullong_multiplication_check(0U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(0U, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(1U, 0U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(1U, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(ULLONG_MAX, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_multiplication_check(ULLONG_MAX, 2U), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_ullong_multiplication_check(2U, ULLONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
	ASSERT_EQUAL(safer_ullong_multiplication_check(ULLONG_MAX, ULLONG_MAX), integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_ullong_division_check_tests, "Check division by zero and edge cases for unsigned long long division")
{
	ASSERT_EQUAL(safer_ullong_division_check(0U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_division_check(0U, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_division_check(1U, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_division_check(1U, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_division_check(ULLONG_MAX, 1U), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_division_check(ULLONG_MAX, ULLONG_MAX), integer_operation_error_none);
	ASSERT_EQUAL(safer_ullong_division_check(0U, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
	ASSERT_EQUAL(safer_ullong_division_check(1U, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
	ASSERT_EQUAL(safer_ullong_division_check(ULLONG_MAX, 0U), integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(ullong_addition_tests, "unsigned long long addition")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulladd(0U, 0U);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulladd(10U, 20U);
	ASSERT_ULLONG_EQUAL(result.value, 30U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulladd(0U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulladd(ULLONG_MAX, 0U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulladd(1U, ULLONG_MAX - 1U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulladd(ULLONG_MAX - 1U, 1U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ullong_addition_edge_cases, "Edge cases for unsigned long long addition")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulladd(1U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = sulladd(ULLONG_MAX, 1U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = sulladd(ULLONG_MAX, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(ullong_subtraction_tests, "unsigned long long subtraction")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sullsub(0U, 0U);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sullsub(10U, 5U);
	ASSERT_ULLONG_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sullsub(ULLONG_MAX, 0U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sullsub(ULLONG_MAX, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ullong_subtraction_edge_cases, "Edge cases for unsigned long long subtraction")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sullsub(0U, 1U);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);

	result = sullsub(0U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(ullong_multiplication_tests, "unsigned long long multiplication")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sullmul(0U, 0U);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sullmul(1U, 1U);
	ASSERT_ULLONG_EQUAL(result.value, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sullmul(1U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sullmul(ULLONG_MAX, 1U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ullong_multiplication_edge_cases, "Edge cases for unsigned long long multiplication")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sullmul(2U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = sullmul(ULLONG_MAX, 2U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);

	result = sullmul(ULLONG_MAX, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(ullong_division_tests, "unsigned long long division")
{
	ullong_result_type result = {0U, 0U, integer_operation_error_none};

	result = sulldiv(0U, 1U);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_ULLONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulldiv(25U, 10U);
	ASSERT_ULLONG_EQUAL(result.value, 2U);
	ASSERT_ULLONG_EQUAL(result.remainder, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulldiv(0U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_ULLONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulldiv(1U, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, 0U);
	ASSERT_ULLONG_EQUAL(result.remainder, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulldiv(ULLONG_MAX, 1U);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = sulldiv(ULLONG_MAX, ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, 1U);
	ASSERT_ULLONG_EQUAL(result.remainder, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);
}

TEST(ullong_division_edge_cases, "Edge cases for unsigned long long division")
{
	ullong_result_type result = {0, 0, integer_operation_error_none};

	result = sulldiv(0U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

	result = sulldiv(1U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

	result = sulldiv(ULLONG_MAX, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);

}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		safer_int_addition_check_tests,
		safer_int_subtraction_check_tests,
		safer_int_multiplication_check_tests,
		safer_int_division_check_tests,
		int_addition_tests,
		int_addition_edge_cases,
		int_subtraction_tests,
		int_subtraction_edge_cases,
		int_multiplication_tests,
		int_multiplication_edge_cases,
		int_division_tests,
		int_division_edge_cases,
		safer_long_addition_check_tests,
		safer_long_subtraction_check_tests,
		safer_long_multiplication_check_tests,
		safer_long_division_check_tests,
		long_addition_tests,
		long_addition_edge_cases,
		long_subtraction_tests,
		long_subtraction_edge_cases,
		long_multiplication_tests,
		long_multiplication_edge_cases,
		long_division_tests,
		long_division_edge_cases,
#if LONG_LONG_INTEGER_TYPE_IS_AVAILABLE
		safer_llong_addition_check_tests,
		safer_llong_subtraction_check_tests,
		safer_llong_multiplication_check_tests,
		safer_llong_division_check_tests,
		llong_addition_tests,
		llong_addition_edge_cases,
		llong_subtraction_tests,
		llong_subtraction_edge_cases,
		llong_multiplication_tests,
		llong_multiplication_edge_cases,
		llong_division_tests,
		llong_division_edge_cases,
#endif
		safer_uint_addition_check_tests,
		safer_uint_subtraction_check_tests,
		safer_uint_multiplication_check_tests,
		safer_uint_division_check_tests,
		uint_addition_tests,
		uint_addition_edge_cases,
		uint_subtraction_tests,
		uint_subtraction_edge_cases,
		uint_multiplication_tests,
		uint_multiplication_edge_cases,
		uint_division_tests,
		uint_division_edge_cases,
		safer_ulong_addition_check_tests,
		safer_ulong_subtraction_check_tests,
		safer_ulong_multiplication_check_tests,
		safer_ulong_division_check_tests,
		ulong_addition_tests,
		ulong_addition_edge_cases,
		ulong_subtraction_tests,
		ulong_subtraction_edge_cases,
		ulong_multiplication_tests,
		ulong_multiplication_edge_cases,
		ulong_division_tests,
		ulong_division_edge_cases
#if UNSIGNED_LONG_LONG_INTEGER_TYPE_IS_AVAILABLE
		,
		safer_ullong_addition_check_tests,
		safer_ullong_subtraction_check_tests,
		safer_ullong_multiplication_check_tests,
		safer_ullong_division_check_tests,
		ullong_addition_tests,
		ullong_addition_edge_cases,
		ullong_subtraction_tests,
		ullong_subtraction_edge_cases,
		ullong_multiplication_tests,
		ullong_multiplication_edge_cases,
		ullong_division_tests,
		ullong_division_edge_cases
#endif
	};

	PRINT_FILE_NAME();
	SHOULD_PRINT_TRUE_ASSERTIONS();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
