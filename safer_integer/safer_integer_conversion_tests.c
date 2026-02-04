#include "safer_integer_conversion.h"
#include "unit_testing.h"

/* Conversions to char */
TEST(conversion_from_char_to_char, "conversion from char to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_char_from_char(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_char_from_char(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_char(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_char_from_char(128U);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_char(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_char, "conversion from signed char to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
#if CHAR_MIN < 0
	result = safer_char_from_schar(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	result = safer_char_from_schar(-128);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_char_from_schar(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_schar(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_char, "conversion from unsigned char to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_char_from_uchar(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_uchar(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_uchar(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_uchar(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_uchar(128U);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_uchar(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_short_to_char, "conversion from signed short to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
#if CHAR_MIN < 0
	result = safer_char_from_short(-32768);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_short(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	result = safer_char_from_short(-32768);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_short(-128);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_char_from_short(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_short(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_short(128);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_short(32767);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_short(128);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_short(32767);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_ushort_to_char, "conversion from unsigned short to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_char_from_ushort(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ushort(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_ushort(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ushort(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ushort(32767U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ushort(65535U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_ushort(128U);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ushort(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ushort(32767U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ushort(65535U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_int_to_char, "conversion from signed int to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
#if CHAR_MIN < 0
	result = safer_char_from_int(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_int(-32768);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_int(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	result = safer_char_from_int(INT_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_int(-32768);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_int(-128);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_char_from_int(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_int(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_int(128);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_int(32767);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_int(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_int(128);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_int(32767);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_int(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_uint_to_char, "conversion from unsigned int to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_char_from_uint(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_uint(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_uint(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_uint(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_uint(32767U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_uint(65535U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_uint(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_uint(128U);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_uint(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_uint(32767U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_uint(65535U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_uint(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_long_to_char, "conversion from signed long to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
#if CHAR_MIN < 0
	result = safer_char_from_long(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_long(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_long(-32768L);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_long(-128L);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	result = safer_char_from_long(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_long(INT_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_long(-32768L);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_long(-128L);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_char_from_long(0L);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_long(127L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_long(128L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_long(32767L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_long(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_long(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_long(128L);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_long(32767L);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_long(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_long(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_ulong_to_char, "conversion from unsigned long to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_char_from_ulong(0UL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ulong(127UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_ulong(128UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ulong(255UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ulong(32767UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ulong(65535UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ulong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ulong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_ulong(128UL);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ulong(255UL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ulong(32767UL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ulong(65535UL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ulong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ulong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_llong_to_char, "conversion from signed long long to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
#if CHAR_MIN < 0
	result = safer_char_from_llong(LLONG_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_llong(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_llong(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_llong(-32768LL);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_char_from_llong(-128LL);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	result = safer_char_from_llong(LLONG_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_llong(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_llong(INT_MIN);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_llong(-32768LL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_char_from_llong(-128LL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_char_from_llong(0LL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_llong(127LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_llong(128LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_llong(32767LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_llong(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_llong(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_llong(LLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_llong(128LL);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_llong(32767LL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_llong(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_llong(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_llong(LLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

TEST(conversion_from_ullong_to_char, "conversion from unsigned long long to char")
{
	char_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_char_from_ullong(0ULL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ullong(127ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if CHAR_MAX < 128
	result = safer_char_from_ullong(128ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ullong(255ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ullong(32767ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ullong(65535ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ullong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ullong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_char_from_ullong(ULLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	result = safer_char_from_ullong(128ULL);
	ASSERT_INT_EQUAL(result.value, 128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ullong(255ULL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_char_from_ullong(32767ULL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ullong(65535ULL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ullong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ullong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_char_from_ullong(ULLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#endif
}

/* Conversions to signed char */
TEST(conversion_from_char_to_schar, "conversion from char to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_schar_from_char(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_schar_from_char(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_char(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_schar_from_char(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_char(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
}

TEST(conversion_from_schar_to_schar, "conversion from signed char to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_schar(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_schar(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_schar(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_schar, "conversion from unsigned char to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_uchar(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_uchar(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_uchar(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_uchar(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_short_to_schar, "conversion from signed short to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_short(-32768);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_short(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_short(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_short(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_short(128);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_short(32767);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_ushort_to_schar, "conversion from unsigned short to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_ushort(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_ushort(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_ushort(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ushort(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ushort(32767U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ushort(65535U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int_to_schar, "conversion from signed int to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_int(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_int(-32768);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_int(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_int(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_int(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_int(128);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_int(32767);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_int(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_uint_to_schar, "conversion from unsigned int to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_uint(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_uint(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_uint(128U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_uint(255U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_uint(32767U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_uint(65535U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_uint(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_long_to_schar, "conversion from signed long to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_long(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_long(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_long(-32768L);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_long(-128L);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_long(0L);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_long(127L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_long(128L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_long(32767L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_long(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_long(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_ulong_to_schar, "conversion from unsigned long to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_ulong(0UL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_ulong(127UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_ulong(128UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ulong(255UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ulong(32767UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ulong(65535UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ulong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ulong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_llong_to_schar, "conversion from signed long long to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_llong(LLONG_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_llong(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_llong(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_llong(-32768LL);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_schar_from_llong(-128LL);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_llong(0LL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_llong(127LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_llong(128LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_llong(32767LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_llong(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_llong(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_llong(LLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_ullong_to_schar, "conversion from unsigned long long to signed char")
{
	schar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_schar_from_ullong(0ULL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_ullong(127ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_schar_from_ullong(128ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ullong(255ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ullong(32767ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ullong(65535ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ullong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ullong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_schar_from_ullong(ULLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Conversions to unsigned char */
TEST(conversion_from_char_to_uchar, "conversion from char to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_uchar_from_char(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_uchar_from_char(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_char(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_uchar_from_char(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_uchar, "conversion from signed char to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_schar(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_schar(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_schar(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_uchar, "conversion from unsigned char to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_uchar(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_uchar(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_uchar(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_uchar, "conversion from signed short to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_short(-32768);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_short(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_short(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_short(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_short(255);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_short(256);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_short(32767);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_ushort_to_uchar, "conversion from unsigned short to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_ushort(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ushort(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ushort(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ushort(256U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ushort(65535U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_int_to_uchar, "conversion from signed int to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_int(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_int(-32768);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_int(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_int(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_int(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_int(255);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_int(256);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_int(32767);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_int(INT_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_uint_to_uchar, "conversion from unsigned int to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_uint(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_uint(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_uint(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_uint(256U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_uint(65535U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_uint(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_long_to_uchar, "conversion from signed long to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_long(LONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_long(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_long(-32768L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_long(-128L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_long(0L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_long(127L);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_long(255L);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_long(256L);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_long(32767L);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_long(INT_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_long(LONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_ulong_to_uchar, "conversion from unsigned long to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_ulong(0UL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ulong(127UL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ulong(255UL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ulong(256UL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ulong(65535UL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ulong(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ulong(ULONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_llong_to_uchar, "conversion from signed long long to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_llong(LLONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_llong(LONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_llong(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_llong(-32768LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_llong(-128LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uchar_from_llong(0LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_llong(127LL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_llong(255LL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_llong(256LL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_llong(32767LL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_llong(INT_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_llong(LONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_llong(LLONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_ullong_to_uchar, "conversion from unsigned long long to unsigned char")
{
	uchar_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uchar_from_ullong(0ULL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ullong(127ULL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ullong(255ULL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uchar_from_ullong(256ULL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ullong(65535ULL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ullong(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ullong(ULONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_uchar_from_ullong(ULLONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

/* Conversions to signed short */
TEST(conversion_from_char_to_short, "conversion from char to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_short_from_char(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_short_from_char(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_char(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_char(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_short, "conversion from signed char to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_schar(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_schar(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_schar(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_short, "conversion from unsigned char to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_uchar(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_uchar(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_uchar(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_short, "conversion from signed short to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_short(-32768);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_short(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_short(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_short(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_short(32767);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_short, "conversion from unsigned short to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_ushort(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ushort(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ushort(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ushort(32767U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ushort(32768U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ushort(65535U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_int_to_short, "conversion from signed int to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_int(INT_MIN);
	ASSERT_EQUAL(result.value, -32768);
#if INT_MIN < -32768
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_short_from_int(-32768);
	ASSERT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_int(-128);
	ASSERT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_int(0);
	ASSERT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_int(127);
	ASSERT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_int(32767);
	ASSERT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_int(INT_MAX);
	ASSERT_EQUAL(result.value, 32767);
#if INT_MAX > 32767
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_uint_to_short, "conversion from unsigned int to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_uint(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_uint(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_uint(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_uint(32767U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_uint(32768U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_uint(65535U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_uint(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_long_to_short, "conversion from signed long to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_long(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_short_from_long(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -32768);
#if INT_MIN < -32768
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_short_from_long(-32768L);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_long(-128L);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_long(0L);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_long(127L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_long(32767L);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_long(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
#if INT_MAX > 32767
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_short_from_long(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_ulong_to_short, "conversion from unsigned long to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_ulong(0UL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ulong(127UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ulong(255UL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ulong(32767UL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ulong(32768UL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ulong(65535UL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ulong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ulong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_llong_to_short, "conversion from signed long long to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_llong(LLONG_MIN);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_short_from_llong(LONG_MIN);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_short_from_llong(INT_MIN);
	ASSERT_INT_EQUAL(result.value, -32768);
#if INT_MIN < -32768
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_short_from_llong(-32768LL);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_llong(-128LL);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_llong(0LL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_llong(127LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_llong(32767LL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_llong(INT_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
#if INT_MAX > 32767
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_short_from_llong(LONG_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_llong(LLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_ullong_to_short, "conversion from unsigned long long to signed short")
{
	short_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_short_from_ullong(0ULL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ullong(127ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ullong(255ULL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ullong(32767ULL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_short_from_ullong(32768ULL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ullong(65535ULL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ullong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ullong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_short_from_ullong(ULLONG_MAX);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Conversions to unsigned short */
TEST(conversion_from_char_to_ushort, "conversion from char to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_ushort_from_char(-128);
	ASSERT_UINT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_ushort_from_char(0);
	ASSERT_UINT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_char(127);
	ASSERT_UINT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_ushort_from_char(255U);
	ASSERT_UINT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_ushort, "conversion from signed char to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_schar(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_schar(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_schar(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_ushort, "conversion from unsigned char to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_uchar(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_uchar(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_uchar(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_ushort, "conversion from signed short to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_short(-32768);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_short(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_short(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_short(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_short(32767);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_ushort, "conversion from unsigned short to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_ushort(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ushort(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ushort(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ushort(65535U);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int_to_ushort, "conversion from signed int to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_int(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_int(-32768);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_int(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_int(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_int(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_int(32767);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_int(INT_MAX);
#if INT_MAX > 65535
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_uint_to_ushort, "conversion from unsigned int to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_uint(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_uint(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_uint(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_uint(65535U);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_uint(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
#if UINT_MAX > 65535U
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_long_to_ushort, "conversion from signed long to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_long(LONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_long(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_long(-32768L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_long(-128L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_long(0L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_long(127L);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_long(32767L);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_long(INT_MAX);
#if INT_MAX > 65535
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_ushort_from_long(LONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_ulong_to_ushort, "conversion from unsigned long to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_ulong(0UL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ulong(127UL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ulong(65535UL);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ulong(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
#if UINT_MAX > 65535U
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_ushort_from_ulong(ULONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_llong_to_ushort, "conversion from signed long long to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_llong(LLONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_llong(LONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_llong(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_llong(-32768LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_llong(-128LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ushort_from_llong(0LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_llong(127LL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_llong(32767LL);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_llong(65535LL);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_llong(INT_MAX);
#if INT_MAX > 65535U
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_ushort_from_llong(LONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_ushort_from_llong(LLONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_ullong_to_ushort, "conversion from unsigned long long to unsigned short")
{
	ushort_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ushort_from_ullong(0ULL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ullong(255ULL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ullong(65535ULL);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ushort_from_ullong(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
#if UINT_MAX > 65535U
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_ushort_from_ullong(ULONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
	result = safer_ushort_from_ullong(ULLONG_MAX);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

/* Conversions to signed int */
TEST(conversion_from_char_to_int, "conversion from char to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_int_from_char(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_int_from_char(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_char(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_int_from_char(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_int, "conversion from signed char to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_schar(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_schar(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_schar(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_int, "conversion from unsigned char to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_uchar(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_uchar(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_uchar(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_int, "conversion from signed short to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_short(-32768);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_short(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_short(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_short(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_short(32767);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_int, "conversion from unsigned short to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_ushort(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ushort(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ushort(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ushort(32767U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ushort(32768U);
#if INT_MAX > 32767
	ASSERT_INT_EQUAL(result.value, 32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
	result = safer_int_from_ushort(65535U);
#if INT_MAX > 65535U
	ASSERT_INT_EQUAL(result.value, 65535);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
}

TEST(conversion_from_int_to_int, "conversion from signed int to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_int(INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_int(-32768);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_int(-128);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_int(0);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_int(127);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_int(32767);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_int(INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint_to_int, "conversion from unsigned int to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_uint(0U);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_uint(127U);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_uint(255U);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_uint(32767U);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_uint(32768U);
#if INT_MAX > 32767
	ASSERT_INT_EQUAL(result.value, 32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
	result = safer_int_from_uint(65535U);
#if INT_MAX > 65535U
	ASSERT_INT_EQUAL(result.value, 65535);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
	result = safer_int_from_uint(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_long_to_int, "conversion from signed long to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_long(LONG_MIN);
#if LONG_MIN < INT_MIN
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
#else
	ASSERT_INT_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_int_from_long(INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(-32768L);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(-128L);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(0L);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(127L);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(32767L);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_long(LONG_MAX);
#if LONG_MAX > INT_MAX
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_INT_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_ulong_to_int, "conversion from unsigned long to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_ulong(0UL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ulong(127UL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ulong(255UL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ulong(32767UL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ulong(65535UL);
#if INT_MAX > 65535U
	ASSERT_INT_EQUAL(result.value, 65535);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
	result = safer_int_from_ulong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_int_from_ulong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_llong_to_int, "conversion from signed long long to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_llong(LLONG_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
	result = safer_int_from_llong(LONG_MIN);
#if LONG_MIN < INT_MIN
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
#else
	ASSERT_INT_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_int_from_llong(INT_MIN);
	ASSERT_INT_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(-32768LL);
	ASSERT_INT_EQUAL(result.value, -32768);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(-128LL);
	ASSERT_INT_EQUAL(result.value, -128);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(0LL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(127LL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(32767LL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(INT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_llong(LONG_MAX);
#if LONG_MAX > INT_MAX
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_INT_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_int_from_llong(LLONG_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_ullong_to_int, "conversion from unsigned long long to signed int")
{
	int_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_int_from_ullong(0ULL);
	ASSERT_INT_EQUAL(result.value, 0);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ullong(127ULL);
	ASSERT_INT_EQUAL(result.value, 127);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ullong(255ULL);
	ASSERT_INT_EQUAL(result.value, 255);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ullong(32767ULL);
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_int_from_ullong(65535ULL);
#if INT_MAX > 65535U
	ASSERT_INT_EQUAL(result.value, 65535);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#else
	ASSERT_INT_EQUAL(result.value, 32767);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#endif
	result = safer_int_from_ullong(UINT_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_int_from_ullong(ULONG_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_int_from_ullong(ULLONG_MAX);
	ASSERT_INT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Conversions to unsigned int */
TEST(conversion_from_char_to_uint, "conversion from char to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_uint_from_char(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_uint_from_char(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_char(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_uint_from_char(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_uint, "conversion from signed char to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_schar(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_schar(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_schar(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_uint, "conversion from unsigned char to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_uchar(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_uchar(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_uchar(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_uint, "conversion from signed short to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_short(-32768);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_short(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_short(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_short(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_short(32767);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_uint, "conversion from unsigned short to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_ushort(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ushort(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ushort(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ushort(65535U);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int_to_uint, "conversion from signed int to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_int(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_int(-32768);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_int(-128);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_int(0);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_int(127);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_int(32767);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_int(INT_MAX);
	ASSERT_UINT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint_to_uint, "conversion from unsigned int to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_uint(0U);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_uint(127U);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_uint(255U);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_uint(65535U);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_uint(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_long_to_uint, "conversion from signed long to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_long(LONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_long(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_long(-32768L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_long(-128L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_long(0L);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_long(127L);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_long(32767L);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_long(INT_MAX);
	ASSERT_UINT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_long(LONG_MAX);
#if LONG_MAX > UINT_MAX
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_ulong_to_uint, "conversion from unsigned long to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_ulong(0UL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ulong(127UL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ulong(65535UL);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ulong(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ulong(ULONG_MAX);
#if ULONG_MAX > UINT_MAX
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, ULONG_MAX);
	ASSERT_UINT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_llong_to_uint, "conversion from signed long long to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_llong(LLONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_llong(LONG_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_llong(INT_MIN);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_llong(-32768LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_llong(-128LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_uint_from_llong(0LL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_llong(127LL);
	ASSERT_UINT_EQUAL(result.value, 127U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_llong(32767LL);
	ASSERT_UINT_EQUAL(result.value, 32767U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_llong(65535LL);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_llong(INT_MAX);
	ASSERT_UINT_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_llong(LONG_MAX);
#if LONG_MAX > UINT_MAX
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_uint_from_llong(LLONG_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
}

TEST(conversion_from_ullong_to_uint, "conversion from unsigned long long to unsigned int")
{
	uint_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_uint_from_ullong(0ULL);
	ASSERT_UINT_EQUAL(result.value, 0U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ullong(255ULL);
	ASSERT_UINT_EQUAL(result.value, 255U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ullong(65535ULL);
	ASSERT_UINT_EQUAL(result.value, 65535U);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ullong(UINT_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_uint_from_ullong(ULONG_MAX);
#if ULONG_MAX > UINT_MAX
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_UINT_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_uint_from_ullong(ULLONG_MAX);
	ASSERT_UINT_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
}

/* Conversions to signed long */
TEST(conversion_from_char_to_long, "conversion from char to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_long_from_char(-128);
	ASSERT_LONG_EQUAL(result.value, -128L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_long_from_char(0);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_char(127);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_long_from_char(255U);
	ASSERT_LONG_EQUAL(result.value, 255L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_long, "conversion from signed char to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_schar(-128);
	ASSERT_LONG_EQUAL(result.value, -128L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_schar(0);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_schar(127);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_long, "conversion from unsigned char to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_uchar(0U);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uchar(127U);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uchar(255U);
	ASSERT_LONG_EQUAL(result.value, 255L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_long, "conversion from signed short to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_short(-32768);
	ASSERT_LONG_EQUAL(result.value, -32768L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_short(-128);
	ASSERT_LONG_EQUAL(result.value, -128L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_short(0);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_short(127);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_short(32767);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_long, "conversion from unsigned short to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_ushort(0U);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ushort(127U);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ushort(255U);
	ASSERT_LONG_EQUAL(result.value, 255L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ushort(32767U);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ushort(32768U);
	ASSERT_LONG_EQUAL(result.value, 32768L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ushort(65535U);
	ASSERT_LONG_EQUAL(result.value, 65535L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int_to_long, "conversion from signed int to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_int(INT_MIN);
	ASSERT_LONG_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_int(-32768);
	ASSERT_LONG_EQUAL(result.value, -32768L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_int(-128);
	ASSERT_LONG_EQUAL(result.value, -128L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_int(0);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_int(127);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_int(32767);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_int(INT_MAX);
	ASSERT_LONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint_to_long, "conversion from unsigned int to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_uint(0U);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uint(127U);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uint(255U);
	ASSERT_LONG_EQUAL(result.value, 255L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uint(32767U);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uint(32768U);
	ASSERT_LONG_EQUAL(result.value, 32768L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uint(65535U);
	ASSERT_LONG_EQUAL(result.value, 65535L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_uint(UINT_MAX);
#if UINT_MAX > LONG_MAX
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_LONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_long_to_long, "conversion from signed long to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_long(LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(INT_MIN);
	ASSERT_LONG_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(-32768L);
	ASSERT_LONG_EQUAL(result.value, -32768L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(-128L);
	ASSERT_LONG_EQUAL(result.value, -128L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(0L);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(127L);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(32767L);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(INT_MAX);
	ASSERT_LONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_long(LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ulong_to_long, "conversion from unsigned long to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_ulong(0UL);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ulong(127UL);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ulong(255UL);
	ASSERT_LONG_EQUAL(result.value, 255L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ulong(32767UL);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ulong(65535UL);
	ASSERT_LONG_EQUAL(result.value, 65535L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ulong(UINT_MAX);
#if UINT_MAX > LONG_MAX
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_LONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_long_from_ulong(ULONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

TEST(conversion_from_llong_to_long, "conversion from signed long long to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_llong(LLONG_MIN);
#if LLONG_MIN < LONG_MIN
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer);
#else
	ASSERT_LONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_long_from_llong(LONG_MIN);
	ASSERT_LONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(INT_MIN);
	ASSERT_LONG_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(-32768LL);
	ASSERT_LONG_EQUAL(result.value, -32768L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(-128LL);
	ASSERT_LONG_EQUAL(result.value, -128L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(0LL);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(127LL);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(32767LL);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(INT_MAX);
	ASSERT_LONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(LONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_llong(LLONG_MAX);
#if LLONG_MAX > LONG_MAX
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_LONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_ullong_to_long, "conversion from unsigned long long to signed long")
{
	long_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_long_from_ullong(0ULL);
	ASSERT_LONG_EQUAL(result.value, 0L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ullong(127ULL);
	ASSERT_LONG_EQUAL(result.value, 127L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ullong(255ULL);
	ASSERT_LONG_EQUAL(result.value, 255L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ullong(32767ULL);
	ASSERT_LONG_EQUAL(result.value, 32767L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ullong(65535ULL);
	ASSERT_LONG_EQUAL(result.value, 65535L);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_long_from_ullong(UINT_MAX);
#if UINT_MAX > LONG_MAX
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_LONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_long_from_ullong(ULONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
	result = safer_long_from_ullong(ULLONG_MAX);
	ASSERT_LONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Conversions to unsigned long */
TEST(conversion_from_char_to_ulong, "conversion from char to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_ulong_from_char(-128);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_ulong_from_char(0);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_char(127);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_ulong_from_char(255U);
	ASSERT_ULONG_EQUAL(result.value, 255UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_ulong, "conversion from signed char to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_schar(-128);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_schar(0);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_schar(127);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_ulong, "conversion from unsigned char to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_uchar(0U);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_uchar(127U);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_uchar(255U);
	ASSERT_ULONG_EQUAL(result.value, 255UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_ulong, "conversion from signed short to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_short(-32768);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_short(-128);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_short(0);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_short(127);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_short(32767);
	ASSERT_ULONG_EQUAL(result.value, 32767UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_ulong, "conversion from unsigned short to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_ushort(0U);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ushort(127U);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ushort(255U);
	ASSERT_ULONG_EQUAL(result.value, 255UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ushort(65535U);
	ASSERT_ULONG_EQUAL(result.value, 65535UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int_to_ulong, "conversion from signed int to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_int(INT_MIN);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_int(-32768);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_int(-128);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_int(0);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_int(127);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_int(32767);
	ASSERT_ULONG_EQUAL(result.value, 32767UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_int(INT_MAX);
	ASSERT_ULONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint_to_ulong, "conversion from unsigned int to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_uint(0U);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_uint(127U);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_uint(255U);
	ASSERT_ULONG_EQUAL(result.value, 255UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_uint(65535U);
	ASSERT_ULONG_EQUAL(result.value, 65535UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_uint(UINT_MAX);
	ASSERT_ULONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_long_to_ulong, "conversion from signed long to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_long(LONG_MIN);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_long(INT_MIN);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_long(-32768L);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_long(-128L);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_long(0L);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_long(127L);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_long(32767L);
	ASSERT_ULONG_EQUAL(result.value, 32767UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_long(INT_MAX);
	ASSERT_ULONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_long(LONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ulong_to_ulong, "conversion from unsigned long to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_ulong(0UL);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ulong(127UL);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ulong(65535UL);
	ASSERT_ULONG_EQUAL(result.value, 65535UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ulong(UINT_MAX);
	ASSERT_ULONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ulong(ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_llong_to_ulong, "conversion from signed long long to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_llong(LLONG_MIN);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_llong(LONG_MIN);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_llong(INT_MIN);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_llong(-32768LL);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_llong(-128LL);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ulong_from_llong(0LL);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_llong(127LL);
	ASSERT_ULONG_EQUAL(result.value, 127UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_llong(32767LL);
	ASSERT_ULONG_EQUAL(result.value, 32767UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_llong(65535LL);
	ASSERT_ULONG_EQUAL(result.value, 65535UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_llong(INT_MAX);
	ASSERT_ULONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_llong(LONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_llong(LLONG_MAX);
#if LLONG_MAX > ULONG_MAX
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_ULONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_ullong_to_ulong, "conversion from unsigned long long to unsigned long")
{
	ulong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ulong_from_ullong(0ULL);
	ASSERT_ULONG_EQUAL(result.value, 0UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ullong(255ULL);
	ASSERT_ULONG_EQUAL(result.value, 255UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ullong(65535ULL);
	ASSERT_ULONG_EQUAL(result.value, 65535UL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ullong(UINT_MAX);
	ASSERT_ULONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ullong(ULONG_MAX);
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ulong_from_ullong(ULLONG_MAX);
#if ULLONG_MAX > ULONG_MAX
	ASSERT_ULONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer);
#else
	ASSERT_ULONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

/* Conversions to signed long long */
TEST(conversion_from_char_to_llong, "conversion from char to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_llong_from_char(-128);
	ASSERT_LLONG_EQUAL(result.value, -128LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_llong_from_char(0);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_char(127);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_llong_from_char(255U);
	ASSERT_LLONG_EQUAL(result.value, 255LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_llong, "conversion from signed char to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_schar(-128);
	ASSERT_LLONG_EQUAL(result.value, -128LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_schar(0);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_schar(127);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_llong, "conversion from unsigned char to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_uchar(0U);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uchar(127U);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uchar(255U);
	ASSERT_LLONG_EQUAL(result.value, 255LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_llong, "conversion from signed short to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_short(-32768);
	ASSERT_LLONG_EQUAL(result.value, -32768LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_short(-128);
	ASSERT_LLONG_EQUAL(result.value, -128LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_short(0);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_short(127);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_short(32767);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_llong, "conversion from unsigned short to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_ushort(0U);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ushort(127U);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ushort(255U);
	ASSERT_LLONG_EQUAL(result.value, 255LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ushort(32767U);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ushort(32768U);
	ASSERT_LLONG_EQUAL(result.value, 32768LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ushort(65535U);
	ASSERT_LLONG_EQUAL(result.value, 65535LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int_to_llong, "conversion from signed int to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_int(INT_MIN);
	ASSERT_LLONG_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_int(-32768);
	ASSERT_LLONG_EQUAL(result.value, -32768LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_int(-128);
	ASSERT_LLONG_EQUAL(result.value, -128LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_int(0);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_int(127);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_int(32767);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_int(INT_MAX);
	ASSERT_LLONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint_to_llong, "conversion from unsigned int to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_uint(0U);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uint(127U);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uint(255U);
	ASSERT_LLONG_EQUAL(result.value, 255LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uint(32767U);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uint(32768U);
	ASSERT_LLONG_EQUAL(result.value, 32768LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uint(65535U);
	ASSERT_LLONG_EQUAL(result.value, 65535LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_uint(UINT_MAX);
	ASSERT_LLONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_long_to_llong, "conversion from signed long to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_long(LONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(INT_MIN);
	ASSERT_LLONG_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(-32768L);
	ASSERT_LLONG_EQUAL(result.value, -32768LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(-128L);
	ASSERT_LLONG_EQUAL(result.value, -128LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(0L);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(127L);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(32767L);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(INT_MAX);
	ASSERT_LLONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_long(LONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ulong_to_llong, "conversion from unsigned long to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_ulong(0UL);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ulong(127UL);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ulong(255UL);
	ASSERT_LLONG_EQUAL(result.value, 255LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ulong(32767UL);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ulong(65535UL);
	ASSERT_LLONG_EQUAL(result.value, 65535LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ulong(UINT_MAX);
	ASSERT_LLONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ulong(ULONG_MAX);
#if ULONG_MAX > LLONG_MAX
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_LLONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_llong_to_llong, "conversion from signed long long to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_llong(LLONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(LONG_MIN);
	ASSERT_LLONG_EQUAL(result.value, LONG_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(INT_MIN);
	ASSERT_LLONG_EQUAL(result.value, INT_MIN);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(-32768LL);
	ASSERT_LLONG_EQUAL(result.value, -32768LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(-128LL);
	ASSERT_LLONG_EQUAL(result.value, -128LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(0LL);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(127LL);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(32767LL);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(INT_MAX);
	ASSERT_LLONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(LONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_llong(LLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ullong_to_llong, "conversion from unsigned long long to signed long long")
{
	llong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_llong_from_ullong(0ULL);
	ASSERT_LLONG_EQUAL(result.value, 0LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ullong(127ULL);
	ASSERT_LLONG_EQUAL(result.value, 127LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ullong(255ULL);
	ASSERT_LLONG_EQUAL(result.value, 255LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ullong(32767ULL);
	ASSERT_LLONG_EQUAL(result.value, 32767LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ullong(65535ULL);
	ASSERT_LLONG_EQUAL(result.value, 65535LL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ullong(UINT_MAX);
	ASSERT_LLONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_llong_from_ullong(ULONG_MAX);
#if ULONG_MAX > LLONG_MAX
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
#else
	ASSERT_LLONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
	result = safer_llong_from_ullong(ULLONG_MAX);
	ASSERT_LLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer);
}

/* Conversions to unsigned long long */
TEST(conversion_from_char_to_ullong, "conversion from char to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
#if (CHAR_MIN == -128) && (CHAR_MAX == 127)
	result = safer_ullong_from_char(-128);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
#endif
	result = safer_ullong_from_char(0);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_char(127);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#if (CHAR_MIN == 0) && (CHAR_MAX == 255)
	result = safer_ullong_from_char(255U);
	ASSERT_ULLONG_EQUAL(result.value, 255ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
#endif
}

TEST(conversion_from_schar_to_ullong, "conversion from signed char to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_schar(-128);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_schar(0);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_schar(127);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uchar_to_ullong, "conversion from unsigned char to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_uchar(0U);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_uchar(127U);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_uchar(255U);
	ASSERT_ULLONG_EQUAL(result.value, 255ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_short_to_ullong, "conversion from signed short to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_short(-32768);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_short(-128);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_short(0);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_short(127);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_short(32767);
	ASSERT_ULLONG_EQUAL(result.value, 32767ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ushort_to_ullong, "conversion from unsigned short to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_ushort(0U);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ushort(127U);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ushort(255U);
	ASSERT_ULLONG_EQUAL(result.value, 255ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ushort(65535U);
	ASSERT_ULLONG_EQUAL(result.value, 65535ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_int_to_ullong, "conversion from signed int to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_int(INT_MIN);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_int(-32768);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_int(-128);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_int(0);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_int(127);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_int(32767);
	ASSERT_ULLONG_EQUAL(result.value, 32767ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_int(INT_MAX);
	ASSERT_ULLONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_uint_to_ullong, "conversion from unsigned int to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_uint(0U);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_uint(127U);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_uint(255U);
	ASSERT_ULLONG_EQUAL(result.value, 255ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_uint(65535U);
	ASSERT_ULLONG_EQUAL(result.value, 65535ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_uint(UINT_MAX);
	ASSERT_ULLONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_long_to_ullong, "conversion from signed long to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_long(LONG_MIN);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_long(INT_MIN);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_long(-32768L);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_long(-128L);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_long(0L);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_long(127L);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_long(32767L);
	ASSERT_ULLONG_EQUAL(result.value, 32767ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_long(INT_MAX);
	ASSERT_ULLONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_long(LONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ulong_to_ullong, "conversion from unsigned long to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_ulong(0UL);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ulong(127UL);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ulong(65535UL);
	ASSERT_ULLONG_EQUAL(result.value, 65535ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ulong(UINT_MAX);
	ASSERT_ULLONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ulong(ULONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_llong_to_ullong, "conversion from signed long long to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_llong(LLONG_MIN);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_llong(LONG_MIN);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_llong(INT_MIN);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_llong(-32768LL);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_llong(-128LL);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer);
	result = safer_ullong_from_llong(0LL);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_llong(127LL);
	ASSERT_ULLONG_EQUAL(result.value, 127ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_llong(32767LL);
	ASSERT_ULLONG_EQUAL(result.value, 32767ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_llong(65535LL);
	ASSERT_ULLONG_EQUAL(result.value, 65535ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_llong(INT_MAX);
	ASSERT_ULLONG_EQUAL(result.value, INT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_llong(LONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, LONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_llong(LLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, LLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

TEST(conversion_from_ullong_to_ullong, "conversion from unsigned long long to unsigned long long")
{
	ullong_conversion_result_type result = {0, integer_conversion_error_none};
	result = safer_ullong_from_ullong(0ULL);
	ASSERT_ULLONG_EQUAL(result.value, 0ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ullong(255ULL);
	ASSERT_ULLONG_EQUAL(result.value, 255ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ullong(65535ULL);
	ASSERT_ULLONG_EQUAL(result.value, 65535ULL);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ullong(UINT_MAX);
	ASSERT_ULLONG_EQUAL(result.value, UINT_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ullong(ULONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
	result = safer_ullong_from_ullong(ULLONG_MAX);
	ASSERT_ULLONG_EQUAL(result.value, ULLONG_MAX);
	ASSERT_EQUAL(result.error, integer_conversion_error_none);
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		conversion_from_char_to_char,
		conversion_from_schar_to_char,
		conversion_from_uchar_to_char,
		conversion_from_short_to_char,
		conversion_from_ushort_to_char,
		conversion_from_int_to_char,
		conversion_from_uint_to_char,
		conversion_from_long_to_char,
		conversion_from_ulong_to_char,
		conversion_from_llong_to_char,
		conversion_from_ullong_to_char,
		conversion_from_char_to_schar,
		conversion_from_schar_to_schar,
		conversion_from_uchar_to_schar,
		conversion_from_short_to_schar,
		conversion_from_ushort_to_schar,
		conversion_from_int_to_schar,
		conversion_from_uint_to_schar,
		conversion_from_long_to_schar,
		conversion_from_ulong_to_schar,
		conversion_from_llong_to_schar,
		conversion_from_ullong_to_schar,
		conversion_from_char_to_uchar,
		conversion_from_schar_to_uchar,
		conversion_from_uchar_to_uchar,
		conversion_from_short_to_uchar,
		conversion_from_ushort_to_uchar,
		conversion_from_int_to_uchar,
		conversion_from_uint_to_uchar,
		conversion_from_long_to_uchar,
		conversion_from_ulong_to_uchar,
		conversion_from_llong_to_uchar,
		conversion_from_ullong_to_uchar,
		conversion_from_char_to_short,
		conversion_from_schar_to_short,
		conversion_from_uchar_to_short,
		conversion_from_short_to_short,
		conversion_from_ushort_to_short,
		conversion_from_int_to_short,
		conversion_from_uint_to_short,
		conversion_from_long_to_short,
		conversion_from_ulong_to_short,
		conversion_from_llong_to_short,
		conversion_from_ullong_to_short,
		conversion_from_char_to_ushort,
		conversion_from_schar_to_ushort,
		conversion_from_uchar_to_ushort,
		conversion_from_short_to_ushort,
		conversion_from_ushort_to_ushort,
		conversion_from_int_to_ushort,
		conversion_from_uint_to_ushort,
		conversion_from_long_to_ushort,
		conversion_from_ulong_to_ushort,
		conversion_from_llong_to_ushort,
		conversion_from_ullong_to_ushort,
		conversion_from_char_to_int,
		conversion_from_schar_to_int,
		conversion_from_uchar_to_int,
		conversion_from_short_to_int,
		conversion_from_ushort_to_int,
		conversion_from_int_to_int,
		conversion_from_uint_to_int,
		conversion_from_long_to_int,
		conversion_from_ulong_to_int,
		conversion_from_llong_to_int,
		conversion_from_ullong_to_int,
		conversion_from_char_to_uint,
		conversion_from_schar_to_uint,
		conversion_from_uchar_to_uint,
		conversion_from_short_to_uint,
		conversion_from_ushort_to_uint,
		conversion_from_int_to_uint,
		conversion_from_uint_to_uint,
		conversion_from_long_to_uint,
		conversion_from_ulong_to_uint,
		conversion_from_llong_to_uint,
		conversion_from_ullong_to_uint,
		conversion_from_char_to_long,
		conversion_from_schar_to_long,
		conversion_from_uchar_to_long,
		conversion_from_short_to_long,
		conversion_from_ushort_to_long,
		conversion_from_int_to_long,
		conversion_from_uint_to_long,
		conversion_from_long_to_long,
		conversion_from_ulong_to_long,
		conversion_from_llong_to_long,
		conversion_from_ullong_to_long,
		conversion_from_char_to_ulong,
		conversion_from_schar_to_ulong,
		conversion_from_uchar_to_ulong,
		conversion_from_short_to_ulong,
		conversion_from_ushort_to_ulong,
		conversion_from_int_to_ulong,
		conversion_from_uint_to_ulong,
		conversion_from_long_to_ulong,
		conversion_from_ulong_to_ulong,
		conversion_from_llong_to_ulong,
		conversion_from_ullong_to_ulong,
		conversion_from_char_to_llong,
		conversion_from_schar_to_llong,
		conversion_from_uchar_to_llong,
		conversion_from_short_to_llong,
		conversion_from_ushort_to_llong,
		conversion_from_int_to_llong,
		conversion_from_uint_to_llong,
		conversion_from_long_to_llong,
		conversion_from_ulong_to_llong,
		conversion_from_llong_to_llong,
		conversion_from_ullong_to_llong,
		conversion_from_char_to_ullong,
		conversion_from_schar_to_ullong,
		conversion_from_uchar_to_ullong,
		conversion_from_short_to_ullong,
		conversion_from_ushort_to_ullong,
		conversion_from_int_to_ullong,
		conversion_from_uint_to_ullong,
		conversion_from_long_to_ullong,
		conversion_from_ulong_to_ullong,
		conversion_from_llong_to_ullong,
		conversion_from_ullong_to_ullong
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
