#include "safer_integer_short_macros.h"
#include "unit_testing.h"

TEST(safer_i8_add_tests, "int8_t addition")
{
	i8_result_type result = {0, 0, integer_operation_error_none};
	result = si8add(0, 0);
	ASSERT_INT8_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8add(10, 20);
	ASSERT_INT8_EQUAL(result.value, 30);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8add(INT8_MAX, 1);
	ASSERT_INT8_EQUAL(result.value, INT8_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si8add(INT8_MIN, -1);
	ASSERT_INT8_EQUAL(result.value, INT8_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i8_minus_tests, "int8_t subtraction")
{
	i8_result_type result = {0, 0, integer_operation_error_none};
	result = si8sub(0, 0);
	ASSERT_INT8_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8sub(10, 5);
	ASSERT_INT8_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8sub(INT8_MIN, 1);
	ASSERT_INT8_EQUAL(result.value, INT8_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = si8sub(INT8_MAX, -1);
	ASSERT_INT8_EQUAL(result.value, INT8_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
}

TEST(safer_i8_multiply_tests, "int8_t multiplication")
{
	i8_result_type result = {0, 0, integer_operation_error_none};
	result = si8mul(0, 0);
	ASSERT_INT8_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8mul(10, 2);
	ASSERT_INT8_EQUAL(result.value, 20);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8mul(INT8_MAX, 2);
	ASSERT_INT8_EQUAL(result.value, INT8_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si8mul(INT8_MIN, 2);
	ASSERT_INT8_EQUAL(result.value, INT8_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i8_divide_tests, "int8_t division")
{
	i8_result_type result = {0, 0, integer_operation_error_none};
	result = si8div(0, 1);
	ASSERT_INT8_EQUAL(result.value, 0);
	ASSERT_INT8_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8div(21, 10);
	ASSERT_INT8_EQUAL(result.value, 2);
	ASSERT_INT8_EQUAL(result.remainder, 1);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si8div(INT8_MIN, -1);
	ASSERT_INT8_EQUAL(result.value, INT8_MAX);
	ASSERT_INT8_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);

	result = si8div(10, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);
}

TEST(safer_u8_add_tests, "uint8_t addition")
{
	u8_result_type result = {0U, 0U, integer_operation_error_none};
	result = su8add(0U, 0U);
	ASSERT_UINT8_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su8add(UINT8_MAX, 1U);
	ASSERT_UINT8_EQUAL(result.value, UINT8_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u8_minus_tests, "uint8_t subtraction")
{
	u8_result_type result = {0U, 0U, integer_operation_error_none};
	result = su8sub(10U, 5U);
	ASSERT_UINT8_EQUAL(result.value, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su8sub(0U, 1U);
	ASSERT_UINT8_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_u8_multiply_tests, "uint8_t multiplication")
{
	u8_result_type result = {0U, 0U, integer_operation_error_none};
	result = su8mul(10U, 20U);
	ASSERT_UINT8_EQUAL(result.value, 200U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su8mul(20U, 20U);
	ASSERT_UINT8_EQUAL(result.value, UINT8_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u8_divide_tests, "uint8_t division")
{
	u8_result_type result = {0U, 0U, integer_operation_error_none};
	result = su8div(201U, 10U);
	ASSERT_UINT8_EQUAL(result.value, 20U);
	ASSERT_UINT8_EQUAL(result.remainder, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su8div(10U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(safer_i16_add_tests, "int16_t addition")
{
	i16_result_type result = {0, 0, integer_operation_error_none};
	result = si16add(0, 0);
	ASSERT_INT16_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16add(1000, 500);
	ASSERT_INT16_EQUAL(result.value, 1500);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16add(INT16_MAX, 1);
	ASSERT_INT16_EQUAL(result.value, INT16_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si16add(INT16_MIN, -1);
	ASSERT_INT16_EQUAL(result.value, INT16_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i16_minus_tests, "int16_t subtraction")
{
	i16_result_type result = {0, 0, integer_operation_error_none};
	result = si16sub(0, 0);
	ASSERT_INT16_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16sub(5, 10);
	ASSERT_INT16_EQUAL(result.value, -5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16sub(INT16_MIN, 1);
	ASSERT_INT16_EQUAL(result.value, INT16_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = safer_i16_minus(INT16_MAX, -1);
	ASSERT_INT16_EQUAL(result.value, INT16_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
}

TEST(safer_i16_multiply_tests, "int16_t multiplication")
{
	i16_result_type result = {0, 0, integer_operation_error_none};
	result = si16mul(0, 0);
	ASSERT_INT16_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16mul(1000, 20);
	ASSERT_INT16_EQUAL(result.value, 20000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16mul(INT16_MAX, 2);
	ASSERT_INT16_EQUAL(result.value, INT16_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si16mul(INT16_MIN, 2);
	ASSERT_INT16_EQUAL(result.value, INT16_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i16_divide_tests, "int16_t division")
{
	i16_result_type result = {0, 0, integer_operation_error_none};
	result = si16div(0, 1);
	ASSERT_INT16_EQUAL(result.value, 0);
	ASSERT_INT16_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16div(20001, 1000);
	ASSERT_INT16_EQUAL(result.value, 20);
	ASSERT_INT16_EQUAL(result.remainder, 1);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si16div(INT16_MIN, -1);
	ASSERT_INT16_EQUAL(result.value, INT16_MAX);
	ASSERT_INT16_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);

	result = si16div(10, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);
}

TEST(safer_u16_add_tests, "uint16_t addition")
{
	u16_result_type result = {0U, 0U, integer_operation_error_none};
	result = su16add(0U, 0U);
	ASSERT_UINT16_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su16add(UINT16_MAX, 1U);
	ASSERT_UINT16_EQUAL(result.value, UINT16_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u16_minus_tests, "uint16_t subtraction")
{
	u16_result_type result = {0U, 0U, integer_operation_error_none};
	result = su16sub(10U, 5U);
	ASSERT_UINT16_EQUAL(result.value, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su16sub(0U, 1U);
	ASSERT_UINT16_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_u16_multiply_tests, "uint16_t multiplication")
{
	u16_result_type result = {0U, 0U, integer_operation_error_none};
	result = su16mul(1000U, 10U);
	ASSERT_UINT16_EQUAL(result.value, 10000U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su16mul(UINT16_MAX, 2U);
	ASSERT_UINT16_EQUAL(result.value, UINT16_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u16_divide_tests, "uint16_t division")
{
	u16_result_type result = {0U, 0U, integer_operation_error_none};
	result = su16div(10001U, 100U);
	ASSERT_UINT16_EQUAL(result.value, 100U);
	ASSERT_UINT16_EQUAL(result.remainder, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su16div(10U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(safer_i32_add_tests, "int32_t addition")
{
	i32_result_type result = {0, 0, integer_operation_error_none};
	result = si32add(0, 0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32add(1, 1000);
	ASSERT_INT32_EQUAL(result.value, 1001);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32add(INT32_MAX, 1);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si32add(INT32_MIN, -1);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i32_minus_tests, "int32_t subtraction")
{
	i32_result_type result = {0, 0, integer_operation_error_none};
	result = si32sub(0, 0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32sub(500, 1000);
	ASSERT_INT32_EQUAL(result.value, -500);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32sub(INT32_MIN, 1);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = si32sub(INT32_MAX, -1);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
}

TEST(safer_i32_multiply_tests, "int32_t multiplication")
{
	i32_result_type result = {0, 0, integer_operation_error_none};
	result = si32mul(0, 0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32mul(100000, 20);
	ASSERT_INT32_EQUAL(result.value, 2000000);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32mul(INT32_MAX, 2);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si32mul(INT32_MIN, 2);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i32_divide_tests, "int32_t division")
{
	i32_result_type result = {0, 0, integer_operation_error_none};
	result = si32div(0, 1);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_INT32_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32div(2000001, 100000);
	ASSERT_INT32_EQUAL(result.value, 20);
	ASSERT_INT32_EQUAL(result.remainder, 1);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si32div(INT32_MIN, -1);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_INT32_EQUAL(result.remainder, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);

	result = si32div(10, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);
}

TEST(safer_u32_add_tests, "uint32_t addition")
{
	u32_result_type result = {0U, 0U, integer_operation_error_none};
	result = su32add(0U, 0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su32add(UINT32_MAX, 1U);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u32_minus_tests, "uint32_t subtraction")
{
	u32_result_type result = {0U, 0U, integer_operation_error_none};
	result = su32sub(10U, 5U);
	ASSERT_UINT32_EQUAL(result.value, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su32sub(0U, 1U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_u32_multiply_tests, "uint32_t multiplication")
{
	u32_result_type result = {0U, 0U, integer_operation_error_none};
	result = su32mul(100000U, 10000U);
	ASSERT_UINT32_EQUAL(result.value, 1000000000U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su32mul(UINT32_MAX, 2U);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u32_divide_tests, "uint32_t division")
{
	u32_result_type result = {0, 0, integer_operation_error_none};
	result = su32div(1000000001U, 100000U);
	ASSERT_UINT32_EQUAL(result.value, 10000U);
	ASSERT_UINT32_EQUAL(result.remainder, 1U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su32div(10U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);
}

TEST(i8add_tests, "i8add tests")
{
	ASSERT_INT_EQUAL(i8add(-128, -128), -256);
	ASSERT_INT_EQUAL(i8add(-128, -1), -129);
	ASSERT_INT_EQUAL(i8add(0, 0), 0);
	ASSERT_INT_EQUAL(i8add(127, 1), 128);
	ASSERT_INT_EQUAL(i8add(127, 127), 254);
}

TEST(i8sub_tests, "i8sub tests")
{
	ASSERT_INT_EQUAL(i8sub(-128, 127), -255);
	ASSERT_INT_EQUAL(i8sub(-128, 1), -129);
	ASSERT_INT_EQUAL(i8sub(0, 0), 0);
	ASSERT_INT_EQUAL(i8sub(127, -1), 128);
	ASSERT_INT_EQUAL(i8sub(127, -128), 255);
}

TEST(i8mul_tests, "i8mul tests")
{
	ASSERT_INT_EQUAL(i8mul(-128, -128), 16384);
	ASSERT_INT_EQUAL(i8mul(-128, 127), -16256);
	ASSERT_INT_EQUAL(i8mul(0, 0), 0);
	ASSERT_INT_EQUAL(i8mul(127, -128), -16256);
	ASSERT_INT_EQUAL(i8mul(127, 127), 16129);
}

TEST(i8div_tests, "i8div tests")
{
	ASSERT_INT_EQUAL(i8div(-128, -128), 1);
	ASSERT_INT_EQUAL(i8rem(-128, -128), 0);
	ASSERT_INT_EQUAL(i8div(-128, 127), -1);
	ASSERT_INT_EQUAL(i8rem(-128, 127), -1);
	ASSERT_INT_EQUAL(i8div(0, 1), 0);
	ASSERT_INT_EQUAL(i8rem(0, 1), 0);
	ASSERT_INT_EQUAL(i8div(127, -128), 0);
	ASSERT_INT_EQUAL(i8rem(127, -128), 127);
	ASSERT_INT_EQUAL(i8div(127, 127), 1);
	ASSERT_INT_EQUAL(i8rem(127, 127), 0);
}

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
TEST(safer_i64_add_tests, "int64_t addition")
{
	i64_result_type result = {0, 0, integer_operation_error_none};
	result = si64add(0, 0);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si64add(INT64_MAX, 1);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si64add(INT64_MIN, -1);
	ASSERT_INT64_EQUAL(result.value, INT64_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i64_minus_tests, "int64_t subtraction")
{
	i64_result_type result = {0, 0, integer_operation_error_none};
	result = si64sub(10, 5);
	ASSERT_INT64_EQUAL(result.value, 5);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si64sub(INT64_MIN, 1);
	ASSERT_INT64_EQUAL(result.value, INT64_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);

	result = si64sub(INT64_MAX, -1);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);
}

TEST(safer_i64_multiply_tests, "int64_t multiplication")
{
	i64_result_type result = {0, 0, integer_operation_error_none};
	result = si64mul(1000000000LL, 2000000LL);
	ASSERT_INT64_EQUAL(result.value, 2000000000000000LL);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si64mul(INT64_MAX, 2);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_greater_than_maximum);

	result = si64mul(INT64_MIN, 2);
	ASSERT_INT64_EQUAL(result.value, INT64_MIN);
	ASSERT_EQUAL(result.error, integer_operation_error_signed_integer_result_smaller_than_minimum);
}

TEST(safer_i64_divide_tests, "int64_t division")
{
	i64_result_type result = {0, 0, integer_operation_error_none};
	result = si64div(2000000000000000LL, 1000000000LL);
	ASSERT_INT64_EQUAL(result.value, 2000000LL);
	ASSERT_INT64_EQUAL(result.remainder, 0LL);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = si64div(INT64_MIN, -1);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_minimum_signed_integer_by_minus_one);

	result = si64div(10, 0);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_signed_integer_by_zero);
}

TEST(safer_u64_add_tests, "uint64_t addition")
{
	u64_result_type result = {0U, 0U, integer_operation_error_none};
	result = su64add(0U, 0U);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su64add(UINT64_MAX, 1U);
	ASSERT_UINT64_EQUAL(result.value, UINT64_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u64_minus_tests, "uint64_t subtraction")
{
	u64_result_type result = {0U, 0U, integer_operation_error_none};
	result = su64sub(10U, 5U);
	ASSERT_UINT64_EQUAL(result.value, 5U);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su64sub(0U, 1U);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger);
}

TEST(safer_u64_multiply_tests, "uint64_t multiplication")
{
	u64_result_type result = {0U, 0U, integer_operation_error_none};
	result = su64mul(1000000000ULL, 1000000000ULL);
	ASSERT_UINT64_EQUAL(result.value, 1000000000000000000ULL);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su64mul(UINT64_MAX, 2U);
	ASSERT_UINT64_EQUAL(result.value, UINT64_MAX);
	ASSERT_EQUAL(result.error, integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller);
}

TEST(safer_u64_divide_tests, "uint64_t division")
{
	u64_result_type result = {0U, 0U, integer_operation_error_none};
	result = su64div(1000000000000000000ULL, 1000000000ULL);
	ASSERT_UINT64_EQUAL(result.value, 1000000000ULL);
	ASSERT_UINT64_EQUAL(result.remainder, 0ULL);
	ASSERT_EQUAL(result.error, integer_operation_error_none);

	result = su64div(10U, 0U);
	ASSERT_EQUAL(result.error, integer_operation_error_division_of_unsigned_integer_by_zero);
}
#endif

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		safer_i8_add_tests,
		safer_i8_minus_tests,
		safer_i8_multiply_tests,
		safer_i8_divide_tests,
		safer_u8_add_tests,
		safer_u8_minus_tests,
		safer_u8_multiply_tests,
		safer_u8_divide_tests,
		safer_i16_add_tests,
		safer_i16_minus_tests,
		safer_i16_multiply_tests,
		safer_i16_divide_tests,
		safer_u16_add_tests,
		safer_u16_minus_tests,
		safer_u16_multiply_tests,
		safer_u16_divide_tests,
		safer_i32_add_tests,
		safer_i32_minus_tests,
		safer_i32_multiply_tests,
		safer_i32_divide_tests,
		safer_u32_add_tests,
		safer_u32_minus_tests,
		safer_u32_multiply_tests,
		safer_u32_divide_tests,
		i8add_tests,
		i8sub_tests,
		i8mul_tests,
		i8div_tests
#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
		,
		safer_i64_add_tests,
		safer_i64_minus_tests,
		safer_i64_multiply_tests,
		safer_i64_divide_tests,
		safer_u64_add_tests,
		safer_u64_minus_tests,
		safer_u64_multiply_tests,
		safer_u64_divide_tests,
#endif
	};

	PRINT_FILE_NAME();
	SHOULD_PRINT_TRUE_ASSERTIONS();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
