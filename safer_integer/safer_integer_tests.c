#include "safer_integer.h"
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

/* --- Function-based tests --- */
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

	result = simul(10, 20);
	ASSERT_INT_EQUAL(result.value, 200);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = simul(-5, 5);
	ASSERT_INT_EQUAL(result.value, -25);
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

	result = sidiv(20, 10);
	ASSERT_INT_EQUAL(result.value, 2);
	ASSERT_INT_EQUAL(result.remainder, 0);
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

/* --- Function-based tests --- */
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

	result = slmul(10, 20);
	ASSERT_LONG_EQUAL(result.value, 200);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = slmul(-5, 5);
	ASSERT_LONG_EQUAL(result.value, -25);
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

	result = sldiv(20, 10);
	ASSERT_LONG_EQUAL(result.value, 2);
	ASSERT_LONG_EQUAL(result.remainder, 0);
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
		long_division_edge_cases
	};

	PRINT_FILE_NAME();
	SHOULD_PRINT_TRUE_ASSERTIONS();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
