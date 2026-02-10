#include "safer_fixed_width_integer_conversion.h"
#include "unit_testing.h"

/* Tests for int8_t conversions */

TEST(conversion_from_int8_to_int8, "Conversion from int8_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_int8(-128);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int8(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int8(127);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_int8, "Conversion from uint8_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_uint8(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint8(127U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint8(128U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_uint8(255U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int16_to_int8, "Conversion from int16_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_int16(-32768);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);

	result = safer_int8_from_int16(-128);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int16(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int16(127);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int16(128);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_int16(32767);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint16_to_int8, "Conversion from uint16_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_uint16(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint16(127U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint16(128U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_uint16(65535U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int32_to_int8, "Conversion from int32_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_int32(INT32_MIN);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);

	result = safer_int8_from_int32(-128);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int32(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int32(127);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int32(128);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_int32(INT32_MAX);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint32_to_int8, "Conversion from uint32_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_uint32(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint32(127U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint32(128U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_uint32(UINT32_MAX);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int64_to_int8, "Conversion from int64_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_int64(INT64_MIN);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);

	result = safer_int8_from_int64(-128);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int64(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int64(127);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_int64(128);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_int64(INT64_MAX);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint64_to_int8, "Conversion from uint64_t to int8_t")
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int8_from_uint64(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint64(127U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int8_from_uint64(128U);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int8_from_uint64(UINT64_MAX);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Tests for uint8_t conversions */

TEST(conversion_from_int8_to_uint8, "Conversion from int8_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_int8(-128);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint8_from_int8(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int8(127);
	ASSERT_UINT32_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_uint8, "Conversion from uint8_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_uint8(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint8(255U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_uint8, "Conversion from int16_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_int16(-32768);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint8_from_int16(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int16(255);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int16(256);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint8_from_int16(32767);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint16_to_uint8, "Conversion from uint16_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_uint16(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint16(255U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint16(256U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint8_from_uint16(65535U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_int32_to_uint8, "Conversion from int32_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_int32(INT32_MIN);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint8_from_int32(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int32(255);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int32(256);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint8_from_int32(INT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint32_to_uint8, "Conversion from uint32_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_uint32(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint32(255U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint32(256U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint8_from_uint32(UINT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_int64_to_uint8, "Conversion from int64_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_int64(INT64_MIN);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint8_from_int64(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int64(255);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_int64(256);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint8_from_int64(INT64_MAX);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint64_to_uint8, "Conversion from uint64_t to uint8_t")
{
	uint8_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint8_from_uint64(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint64(255U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint8_from_uint64(256U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint8_from_uint64(UINT64_MAX);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

/* Tests for int16_t conversions */

TEST(conversion_from_int8_to_int16, "Conversion from int8_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_int8(-128);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int8(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int8(127);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_int16, "Conversion from uint8_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_uint8(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint8(255U);
	ASSERT_INT32_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_int16, "Conversion from int16_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_int16(-32768);
	ASSERT_INT32_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int16(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int16(32767);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint16_to_int16, "Conversion from uint16_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_uint16(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint16(32767U);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint16(32768U);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int16_from_uint16(65535U);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int32_to_int16, "Conversion from int32_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_int32(INT32_MIN);
	ASSERT_INT32_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);

	result = safer_int16_from_int32(-32768);
	ASSERT_INT32_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int32(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int32(32767);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int32(32768);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int16_from_int32(INT32_MAX);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint32_to_int16, "Conversion from uint32_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_uint32(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint32(32767);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint32(32768U);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int16_from_uint32(UINT32_MAX);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int64_to_int16, "Conversion from int64_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_int64(INT64_MIN);
	ASSERT_INT32_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);

	result = safer_int16_from_int64(-32768);
	ASSERT_INT32_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int64(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int64(32767);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_int64(32768);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int16_from_int64(INT64_MAX);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint64_to_int16, "Conversion from uint64_t to int16_t")
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int16_from_uint64(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint64(32767U);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int16_from_uint64(32768U);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int16_from_uint64(UINT64_MAX);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Tests for uint16_t conversions */

TEST(conversion_from_int8_to_uint16, "Conversion from int8_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_int8(-128);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint16_from_int8(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_int8(127);
	ASSERT_UINT32_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_uint16, "Conversion from uint8_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_uint8(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_uint8(255U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_uint16, "Conversion from int16_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_int16(-32768);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint16_from_int16(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_int16(32767);
	ASSERT_UINT32_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint16_to_uint16, "Conversion from uint16_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_uint16(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_uint16(65535U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int32_to_uint16, "Conversion from int32_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_int32(INT32_MIN);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint16_from_int32(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_int32(65535);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_int32(65536U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint16_from_int32(INT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint32_to_uint16, "Conversion from uint32_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_uint32(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_uint32(65535U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_uint32(65536U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint16_from_uint32(UINT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_int64_to_uint16, "Conversion from int64_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_int64(INT64_MIN);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint16_from_int64(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_int64(65535);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_int64(65536);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint16_from_int64(INT64_MAX);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint64_to_uint16, "Conversion from uint64_t to uint16_t")
{
	uint16_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint16_from_uint64(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_uint64(65535U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint16_from_uint64(65536U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint16_from_uint64(UINT64_MAX);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

/* Tests for int32_t conversions */

TEST(conversion_from_int8_to_int32, "Conversion from int8_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_int8(-128);
	ASSERT_INT32_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int8(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int8(127);
	ASSERT_INT32_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_int32, "Conversion from uint8_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_uint8(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_uint8(255U);
	ASSERT_INT32_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_int32, "Conversion from int16_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_int16(-32768);
	ASSERT_INT32_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int16(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int16(32767);
	ASSERT_INT32_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint16_to_int32, "Conversion from uint16_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_uint16(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_uint16(65535U);
	ASSERT_INT32_EQUAL(result.value, 65535);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int32_to_int32, "Conversion from int32_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_int32(INT32_MIN);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int32(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int32(INT32_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint32_to_int32, "Conversion from uint32_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_uint32(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_uint32(INT32_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_uint32((uint32_t)(INT32_MAX) + 1U);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int32_from_uint32(UINT32_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int64_to_int32, "Conversion from int64_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_int64(INT64_MIN);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);

	result = safer_int32_from_int64(INT32_MIN);
	ASSERT_INT32_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int64(0);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int64(INT32_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_int64((int64_t)(INT32_MAX) + 1);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int32_from_int64(INT64_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint64_to_int32, "Conversion from uint64_t to int32_t")
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int32_from_uint64(0U);
	ASSERT_INT32_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_uint64(INT32_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int32_from_uint64((uint64_t)(INT32_MAX) + 1U);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int32_from_uint64(UINT64_MAX);
	ASSERT_INT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Tests for uint32_t conversions */

TEST(conversion_from_int8_to_uint32, "Conversion from int8_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_int8(-128);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint32_from_int8(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_int8(127);
	ASSERT_UINT32_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_uint32, "Conversion from uint8_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_uint8(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_uint8(255U);
	ASSERT_UINT32_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_uint32, "Conversion from int16_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_int16(-32768);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint32_from_int16(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_int16(32767);
	ASSERT_UINT32_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint16_to_uint32, "Conversion from uint16_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_uint16(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_uint16(65535U);
	ASSERT_UINT32_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int32_to_uint32, "Conversion from int32_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_int32(INT32_MIN);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint32_from_int32(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_int32(INT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint32_to_uint32, "Conversion from uint32_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_uint32(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_uint32(UINT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int64_to_uint32, "Conversion from int64_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_int64(INT64_MIN);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint32_from_int64(0);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_int64(UINT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_int64((int64_t)(UINT32_MAX) + 1);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint32_from_int64(INT64_MAX);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint64_to_uint32, "Conversion from uint64_t to uint32_t")
{
	uint32_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint32_from_uint64(0U);
	ASSERT_UINT32_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_uint64(UINT32_MAX);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint32_from_uint64((uint64_t)(UINT32_MAX) + 1U);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);

	result = safer_uint32_from_uint64(UINT64_MAX);
	ASSERT_UINT32_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

/* Tests for int64_t conversions */

TEST(conversion_from_int8_to_int64, "Conversion from int8_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_int8(-128);
	ASSERT_INT64_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int8(0);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int8(127);
	ASSERT_INT64_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_int64, "Conversion from uint8_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_uint8(0U);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_uint8(255U);
	ASSERT_INT64_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_int64, "Conversion from int16_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_int16(-32768);
	ASSERT_INT64_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int16(0);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int16(32767);
	ASSERT_INT64_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint16_to_int64, "Conversion from uint16_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_uint16(0U);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_uint16(65535U);
	ASSERT_INT64_EQUAL(result.value, 65535);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int32_to_int64, "Conversion from int32_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_int32(INT32_MIN);
	ASSERT_INT64_EQUAL(result.value, INT32_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int32(0);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int32(INT32_MAX);
	ASSERT_INT64_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint32_to_int64, "Conversion from uint32_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_uint32(0U);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_uint32(UINT32_MAX);
	ASSERT_INT64_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int64_to_int64, "Conversion from int64_t to int64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_int64(INT64_MIN);
	ASSERT_INT64_EQUAL(result.value, INT64_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int64(0);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_int64(INT64_MAX);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint64_to_int64, "Conversion from uint64_t to uint64_t")
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};

	result = safer_int64_from_uint64(0U);
	ASSERT_INT64_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_uint64(INT64_MAX);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_int64_from_uint64((uint64_t)(INT64_MAX) + 1U);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);

	result = safer_int64_from_uint64(UINT64_MAX);
	ASSERT_INT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Tests for uint64_t conversions */

TEST(conversion_from_int8_to_uint64, "Conversion from int8_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_int8(-128);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint64_from_int8(0);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_int8(127);
	ASSERT_UINT64_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint8_to_uint64, "Conversion from uint8_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_uint8(0U);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_uint8(255U);
	ASSERT_UINT64_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int16_to_uint64, "Conversion from int16_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_int16(-32768);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint64_from_int16(0);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_int16(32767);
	ASSERT_UINT64_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint16_to_uint64, "Conversion from uint16_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_uint16(0U);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_uint16(65535U);
	ASSERT_UINT64_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int32_to_uint64, "Conversion from int32_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_int32(INT32_MIN);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint64_from_int32(0);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_int32(INT32_MAX);
	ASSERT_UINT64_EQUAL(result.value, INT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint32_to_uint64, "Conversion from uint32_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_uint32(0U);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_uint32(UINT32_MAX);
	ASSERT_UINT64_EQUAL(result.value, UINT32_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int64_to_uint64, "Conversion from int64_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_int64(INT64_MIN);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);

	result = safer_uint64_from_int64(0);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_int64(INT64_MAX);
	ASSERT_UINT64_EQUAL(result.value, INT64_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint64_to_uint64, "Conversion from uint64_t to uint64_t")
{
	uint64_conversion_result_type result = {0U, integer_conversion_error_none};

	result = safer_uint64_from_uint64(0U);
	ASSERT_UINT64_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);

	result = safer_uint64_from_uint64(UINT64_MAX);
	ASSERT_UINT64_EQUAL(result.value, UINT64_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		conversion_from_int8_to_int8,
		conversion_from_uint8_to_int8,
		conversion_from_int16_to_int8,
		conversion_from_uint16_to_int8,
		conversion_from_int32_to_int8,
		conversion_from_uint32_to_int8,
		conversion_from_int64_to_int8,
		conversion_from_uint64_to_int8,
		conversion_from_int8_to_uint8,
		conversion_from_uint8_to_uint8,
		conversion_from_int16_to_uint8,
		conversion_from_uint16_to_uint8,
		conversion_from_int32_to_uint8,
		conversion_from_uint32_to_uint8,
		conversion_from_int64_to_uint8,
		conversion_from_uint64_to_uint8,
		conversion_from_int8_to_int16,
		conversion_from_uint8_to_int16,
		conversion_from_int16_to_int16,
		conversion_from_uint16_to_int16,
		conversion_from_int32_to_int16,
		conversion_from_uint32_to_int16,
		conversion_from_int64_to_int16,
		conversion_from_uint64_to_int16,
		conversion_from_int8_to_uint16,
		conversion_from_uint8_to_uint16,
		conversion_from_int16_to_uint16,
		conversion_from_uint16_to_uint16,
		conversion_from_int32_to_uint16,
		conversion_from_uint32_to_uint16,
		conversion_from_int64_to_uint16,
		conversion_from_uint64_to_uint16,
		conversion_from_int8_to_int32,
		conversion_from_uint8_to_int32,
		conversion_from_int16_to_int32,
		conversion_from_uint16_to_int32,
		conversion_from_int32_to_int32,
		conversion_from_uint32_to_int32,
		conversion_from_int64_to_int32,
		conversion_from_uint64_to_int32,
		conversion_from_int8_to_uint32,
		conversion_from_uint8_to_uint32,
		conversion_from_int16_to_uint32,
		conversion_from_uint16_to_uint32,
		conversion_from_int32_to_uint32,
		conversion_from_uint32_to_uint32,
		conversion_from_int64_to_uint32,
		conversion_from_uint64_to_uint32,
		conversion_from_int8_to_int64,
		conversion_from_uint8_to_int64,
		conversion_from_int16_to_int64,
		conversion_from_uint16_to_int64,
		conversion_from_int32_to_int64,
		conversion_from_uint32_to_int64,
		conversion_from_int64_to_int64,
		conversion_from_uint64_to_int64,
		conversion_from_int8_to_uint64,
		conversion_from_uint8_to_uint64,
		conversion_from_int16_to_uint64,
		conversion_from_uint16_to_uint64,
		conversion_from_int32_to_uint64,
		conversion_from_uint32_to_uint64,
		conversion_from_int64_to_uint64,
		conversion_from_uint64_to_uint64
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
