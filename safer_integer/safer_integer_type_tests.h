#ifndef SAFER_INTEGER_TYPE_TESTS_H
#define SAFER_INTEGER_TYPE_TESTS_H

#include "safer_integer_type.h"
#include "safer_integer_comparison.h"
#include "Boolean_type.h"
#include "static_assert.h"
#include "unit_testing.h"
#include <errno.h>
#include <iso646.h>
#include <stdio.h>
#include <string.h>

#define LINE __LINE__

#ifdef __cplusplus
#define TRY try
#define CATCH(EXCEPTION) catch(EXCEPTION)
#else
#define TRY if (Boolean_true)
#define CATCH(EXCEPTION) else
#endif

STATIC_ASSERT(sizeof(Boolean_type) == 1U, "Test environment assumption failure: sizeof(Boolean_type) == 1");
STATIC_ASSERT(sizeof(char) == 1U, "Test environment assumption failure: sizeof(char) == 1");
STATIC_ASSERT(sizeof(char) == sizeof(signed char), "Test environment assumption failure: sizeof(char) == sizeof(signed char)");
STATIC_ASSERT(sizeof(char) == sizeof(unsigned char), "Test environment assumption failure: sizeof(char) == sizeof(unsigned char)");
STATIC_ASSERT(sizeof(short) == 2U, "Test environment assumption failure: sizeof(short) == 2");
STATIC_ASSERT(sizeof(short) == sizeof(unsigned short), "Test environment assumption failure: sizeof(short) == sizeof(unsigned short)");
STATIC_ASSERT(sizeof(int) == 4U, "Test environment assumption failure: sizeof(int) == 4");
STATIC_ASSERT(sizeof(int) == sizeof(unsigned int), "Test environment assumption failure: sizeof(int) == sizeof(unsigned int)");
STATIC_ASSERT(sizeof(long) >= sizeof(int), "Test environment assumption failure: sizeof(long) >= sizeof(int)");
STATIC_ASSERT(sizeof(long) == sizeof(unsigned long), "Test environment assumption failure: sizeof(long) == sizeof(unsigned long)");
STATIC_ASSERT(sizeof(long long) == 8U, "Test environment assumption failure: sizeof(long long) == 8");
STATIC_ASSERT(sizeof(long long) >= sizeof(long), "Test environment assumption failure: sizeof(long long) >= sizeof(long)");
STATIC_ASSERT(sizeof(long long) == sizeof(unsigned long long), "Test environment assumption failure: sizeof(long long) == sizeof(unsigned long long)");

STATIC_ASSERT(CHAR_MIN > SHRT_MIN, "Test environment assumption failure: CHAR_MIN > SHRT_MIN");
STATIC_ASSERT(CHAR_MAX < SHRT_MAX, "Test environment assumption failure: CHAR_MAX < SHRT_MAX");
STATIC_ASSERT(SCHAR_MIN > SHRT_MIN, "Test environment assumption failure: SCHAR_MIN > SHRT_MIN");
STATIC_ASSERT(SCHAR_MAX < SHRT_MAX, "Test environment assumption failure: SCHAR_MAX < SHRT_MAX");
STATIC_ASSERT(UCHAR_MAX < USHRT_MAX, "Test environment assumption failure: UCHAR_MAX < USHRT_MAX");
STATIC_ASSERT(SHRT_MIN > INT_MIN, "Test environment assumption failure: SHRT_MIN > INT_MIN");
STATIC_ASSERT(SHRT_MAX < INT_MAX, "Test environment assumption failure: SHRT_MAX < INT_MAX");
STATIC_ASSERT(USHRT_MAX < UINT_MAX, "Test environment assumption failure: USHRT_MAX < UINT_MAX");
STATIC_ASSERT(INT_MIN >= LONG_MIN, "Test environment assumption failure: INT_MIN >= LONG_MIN");
STATIC_ASSERT(INT_MAX <= LONG_MAX, "Test environment assumption failure: INT_MAX <= LONG_MAX");
STATIC_ASSERT(UINT_MAX <= ULONG_MAX, "Test environment assumption failure: UINT_MAX <= ULONG_MAX");
STATIC_ASSERT(LONG_MIN >= LLONG_MIN, "Test environment assumption failure: LONG_MIN >= LLONG_MIN");
STATIC_ASSERT(LONG_MAX <= LLONG_MAX, "Test environment assumption failure: LONG_MAX <= LLONG_MAX");

static FILE *output_file = NULL;
static const Boolean_type safer_integer_type_exception_thrown = Boolean_true;

/* Property tests */
TEST(safer_integer_is_builtin_integer_type_tests, "Tests for safer_integer::is_builtin_integer_type<T>::value")
{
#ifdef __cplusplus
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<bool>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<char>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<signed char>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<unsigned char>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<short>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<unsigned short>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<int>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<unsigned int>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<long>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<unsigned long>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<long long>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<unsigned long long>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<ptrdiff_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<size_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<int8_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<uint8_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<int16_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<uint16_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<int32_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<uint32_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<int64_t>::value, Boolean_true);
	ASSERT_EQUAL(safer_integer::is_builtin_integer_type<uint64_t>::value, Boolean_true);
#else
	fprintf(output_file, "The tests are only for C++.\n");
#endif
}

TEST(safer_integer_type_signedness_tests, "Safer integer type signedness tests")
{
	ASSERT(not SAFER_BOOL_TYPE_IS_SIGNED);
#if (CHAR_MIN < 0)
	ASSERT(SAFER_CHAR_TYPE_IS_SIGNED);
#else
	ASSERT(not SAFER_CHAR_TYPE_IS_SIGNED);
#endif
	ASSERT(SAFER_SCHAR_TYPE_IS_SIGNED);
	ASSERT(not SAFER_UCHAR_TYPE_IS_SIGNED);
	ASSERT(SAFER_SHORT_TYPE_IS_SIGNED);
	ASSERT(not SAFER_USHORT_TYPE_IS_SIGNED);
	ASSERT(SAFER_INT_TYPE_IS_SIGNED);
	ASSERT(not SAFER_UINT_TYPE_IS_SIGNED);
	ASSERT(SAFER_LONG_TYPE_IS_SIGNED);
	ASSERT(not SAFER_ULONG_TYPE_IS_SIGNED);
	ASSERT(SAFER_LLONG_TYPE_IS_SIGNED);
	ASSERT(not SAFER_ULLONG_TYPE_IS_SIGNED);
	ASSERT(SAFER_PTRDIFF_TYPE_IS_SIGNED);
	ASSERT(not SAFER_SIZE_TYPE_IS_SIGNED);
	ASSERT(SAFER_INT8_TYPE_IS_SIGNED);
	ASSERT(not SAFER_UINT8_TYPE_IS_SIGNED);
	ASSERT(SAFER_INT16_TYPE_IS_SIGNED);
	ASSERT(not SAFER_UINT16_TYPE_IS_SIGNED);
	ASSERT(SAFER_INT32_TYPE_IS_SIGNED);
	ASSERT(not SAFER_UINT32_TYPE_IS_SIGNED);
	ASSERT(SAFER_INT64_TYPE_IS_SIGNED);
	ASSERT(not SAFER_UINT64_TYPE_IS_SIGNED);
}

TEST(safer_integer_type_min_max_tests, "Safer integer type min/max tests")
{
	ASSERT_EQUAL(SAFER_BOOL_MIN, Boolean_false);
	ASSERT_EQUAL(SAFER_BOOL_MAX, Boolean_true);
	ASSERT_EQUAL(SAFER_CHAR_MIN, CHAR_MIN);
	ASSERT_EQUAL(SAFER_CHAR_MAX, CHAR_MAX);
	ASSERT_EQUAL(SAFER_SCHAR_MIN, SCHAR_MIN);
	ASSERT_EQUAL(SAFER_SCHAR_MAX, SCHAR_MAX);
	ASSERT_EQUAL(SAFER_UCHAR_MIN, 0U);
	ASSERT_EQUAL(SAFER_UCHAR_MAX, UCHAR_MAX);
	ASSERT_EQUAL(SAFER_SHORT_MIN, SHRT_MIN);
	ASSERT_EQUAL(SAFER_SHORT_MAX, SHRT_MAX);
	ASSERT_UINT_EQUAL(SAFER_USHORT_MIN, 0U);
	ASSERT_UINT_EQUAL(SAFER_USHORT_MAX, USHRT_MAX);
	ASSERT_EQUAL(SAFER_INT_MIN, INT_MIN);
	ASSERT_EQUAL(SAFER_INT_MAX, INT_MAX);
	ASSERT_UINT_EQUAL(SAFER_UINT_MIN, 0U);
	ASSERT_UINT_EQUAL(SAFER_UINT_MAX, UINT_MAX);
	ASSERT_LONG_EQUAL(SAFER_LONG_MIN, LONG_MIN);
	ASSERT_LONG_EQUAL(SAFER_LONG_MAX, LONG_MAX);
	ASSERT_ULONG_EQUAL(SAFER_ULONG_MIN, 0UL);
	ASSERT_ULONG_EQUAL(SAFER_ULONG_MAX, ULONG_MAX);
	ASSERT_LLONG_EQUAL(SAFER_LLONG_MIN, LLONG_MIN);
	ASSERT_LLONG_EQUAL(SAFER_LLONG_MAX, LLONG_MAX);
	ASSERT_ULLONG_EQUAL(SAFER_ULLONG_MIN, 0ULL);
	ASSERT_ULLONG_EQUAL(SAFER_ULLONG_MAX, ULLONG_MAX);
	ASSERT_PTRDIFF_EQUAL(SAFER_PTRDIFF_MIN, PTRDIFF_MIN);
	ASSERT_PTRDIFF_EQUAL(SAFER_PTRDIFF_MAX, PTRDIFF_MAX);
	ASSERT_SIZE_EQUAL(SAFER_SIZE_MIN, 0U);
	ASSERT_SIZE_EQUAL(SAFER_SIZE_MAX, SIZE_MAX);
	ASSERT_EQUAL(SAFER_INT8_MIN, INT8_MIN);
	ASSERT_EQUAL(SAFER_INT8_MAX, INT8_MAX);
	ASSERT_EQUAL(SAFER_UINT8_MIN, 0U);
	ASSERT_EQUAL(SAFER_UINT8_MAX, UINT8_MAX);
	ASSERT_EQUAL(SAFER_INT16_MIN, INT16_MIN);
	ASSERT_EQUAL(SAFER_INT16_MAX, INT16_MAX);
	ASSERT_UINT_EQUAL(SAFER_UINT16_MIN, 0U);
	ASSERT_UINT_EQUAL(SAFER_UINT16_MAX, UINT16_MAX);
	ASSERT_INT32_EQUAL(SAFER_INT32_MIN, INT32_MIN);
	ASSERT_INT32_EQUAL(SAFER_INT32_MAX, INT32_MAX);
	ASSERT_UINT32_EQUAL(SAFER_UINT32_MIN, 0U);
	ASSERT_UINT32_EQUAL(SAFER_UINT32_MAX, UINT32_MAX);
	ASSERT_INT64_EQUAL(SAFER_INT64_MIN, INT64_MIN);
	ASSERT_INT64_EQUAL(SAFER_INT64_MAX, INT64_MAX);
	ASSERT_UINT64_EQUAL(SAFER_UINT64_MIN, 0ULL);
	ASSERT_UINT64_EQUAL(SAFER_UINT64_MAX, UINT64_MAX);
}

/* Uninitialized variables */
TEST(safer_integer_type_uninitialized_variable_tests, "Safer integer type uninitialized variable tests")
{
	TRY {
		safer_bool_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_char_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_schar_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uchar_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_short_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ushort_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %d\n", LINE, (int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %u\n", LINE, (unsigned int) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %ld\n", LINE, (long) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %lu\n", LINE, (unsigned long) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %lld\n", LINE, (long long) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %llu\n", LINE, (unsigned long long) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ptrdiff_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %lld\n", LINE, (long long) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_size_type var;
#ifdef NDEBUG
		fprintf(output_file, "Line %d: value = %llu\n", LINE, (unsigned long long) var);
#endif
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

/* Conversion tests */
TEST(safer_bool_type_conversion_tests, "Safer bool type conversion tests")
{
	TRY {
		safer_bool_type var = Boolean_false;
		ASSERT_EQUAL(var, Boolean_false);
		var = Boolean_true;
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(0);
		ASSERT_EQUAL(var, Boolean_false);
		var = INTEGER_TO_BOOLEAN(1);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(-1);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(SCHAR_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(SCHAR_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(UCHAR_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(SHRT_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(SHRT_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(USHRT_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(UINT_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(LONG_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(LONG_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(ULONG_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(LLONG_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(LLONG_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(ULLONG_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(PTRDIFF_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(PTRDIFF_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(SIZE_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT8_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT8_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(UINT8_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT16_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT16_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(UINT16_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT32_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT32_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(UINT32_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT64_MIN);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(INT64_MAX);
		ASSERT_EQUAL(var, Boolean_true);
		var = INTEGER_TO_BOOLEAN(UINT64_MAX);
		ASSERT_EQUAL(var, Boolean_true);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_char_type_conversion_error_tests, "safer_char_type conversion error tests")
{
	TRY {
		const short original_value = (short) SHRT_MIN;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned short original_value = (unsigned short) USHRT_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY{
		const unsigned int original_value = UINT_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, original_value, (int) var);
		if (SAFER_CHAR_TYPE_IS_SIGNED) {
			ASSERT(u_ne_i(original_value, var));
		} else {
			ASSERT_UINT_NOT_EQUAL(original_value, var);
		}
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MIN;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %d\n", LINE, original_value, (int) var);
		if (SAFER_CHAR_TYPE_IS_SIGNED) {
			ASSERT(ul_ne_l(original_value, var));
		} else {
			ASSERT_ULONG_NOT_EQUAL(original_value, var);
		}
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		const safer_char_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %d\n", LINE, original_value, (int) var);
		if (SAFER_CHAR_TYPE_IS_SIGNED) {
			ASSERT(ull_ne_ll(original_value, var));
		} else {
			ASSERT_ULLONG_NOT_EQUAL(original_value, var);
		}
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_char_type_conversion_tests, "safer_char_type conversion tests")
{
	TRY {
		safer_char_type var = 0;
		ASSERT_EQUAL(var, 0);
		if (SAFER_CHAR_TYPE_IS_SIGNED) {
			var = -1;
			ASSERT_EQUAL(var, -1);
		}
		var = 1;
		ASSERT_EQUAL(var, 1);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1);
		var = CHAR_MIN;
		ASSERT_EQUAL(var, CHAR_MIN);
		var = CHAR_MAX;
		ASSERT_EQUAL(var, CHAR_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_schar_type_conversion_error_tests, "safer_schar_type conversion error tests")
{
	TRY {
		const unsigned char original_value = (unsigned char) UCHAR_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MIN;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned short original_value = (unsigned short) USHRT_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY{
		const unsigned int original_value = UINT_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, original_value, (int) var);
		ASSERT(u_ne_i(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MIN;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %d\n", LINE, original_value, (int) var);
		ASSERT(ul_ne_l(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		const safer_schar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %d\n", LINE, original_value, (int) var);
		ASSERT(ull_ne_ll(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_schar_type_conversion_tests, "Safer schar type conversion tests")
{
	TRY {
		safer_schar_type var = 0;
		ASSERT_EQUAL(var, 0);
		var = -1;
		ASSERT_EQUAL(var, -1);
		var = 1;
		ASSERT_EQUAL(var, 1);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1);
		var = SCHAR_MIN;
		ASSERT_EQUAL(var, SCHAR_MIN);
		var = SCHAR_MAX;
		ASSERT_EQUAL(var, SCHAR_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_uchar_type_conversion_error_tests, "safer_uchar_type conversion error tests")
{
	TRY {
		const signed char original_value = (signed char)-1;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const signed char original_value = (signed char) SCHAR_MIN;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MIN;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MAX;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned short original_value = (unsigned short) USHRT_MAX;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_UINT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MAX;
		const safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY{
		const unsigned int original_value = UINT_MAX;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, original_value, (int) var);
		ASSERT_UINT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MIN;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MAX;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long original_value = ULONG_MAX;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %d\n", LINE, original_value, (int) var);
		ASSERT_ULONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		safer_uchar_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %d\n", LINE, original_value, (int) var);
		ASSERT_ULLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uchar_type_conversion_tests, "safer_uchar_type conversion tests")
{
	TRY {
		safer_uchar_type var = 0;
		ASSERT_EQUAL(var, 0);
		var = 1;
		ASSERT_EQUAL(var, 1);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1);
		var = (signed char) SCHAR_MAX;
		ASSERT_EQUAL(var, SCHAR_MAX);
		var = UCHAR_MAX;
		ASSERT_EQUAL(var, UCHAR_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_short_type_conversion_error_tests, "safer_short_type conversion error tests")
{
	TRY {
		const unsigned short original_value = (unsigned short) USHRT_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int original_value = UINT_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, original_value, (int) var);
		ASSERT(u_ne_i(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MIN;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %d\n", LINE, original_value, (int) var);
		ASSERT(ul_ne_l(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		const safer_short_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %d\n", LINE, original_value, (int) var);
		ASSERT(ull_ne_ll(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_short_type_conversion_tests, "safer_short_type conversion tests")
{
	TRY {
		safer_short_type var = 0;
		ASSERT_EQUAL(var, 0);
		var = -1;
		ASSERT_EQUAL(var, -1);
		var = 1;
		ASSERT_EQUAL(var, 1);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1);
		var = SHRT_MIN;
		ASSERT_EQUAL(var, SHRT_MIN);
		var = SHRT_MAX;
		ASSERT_EQUAL(var, SHRT_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_ushort_type_conversion_error_tests, "safer_ushort_type conversion error tests")
{
	TRY {
		const signed char original_value = (signed char) SCHAR_MIN;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) -1;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MIN;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, (int) original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MAX;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %d\n", LINE, original_value, (int) var);
		ASSERT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int original_value = UINT_MAX;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, original_value, (int) var);
		ASSERT_UINT_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MIN;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MAX;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %d\n", LINE, original_value, (int) var);
		ASSERT_ULONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		const safer_ushort_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %d\n", LINE, original_value, (int) var);
		ASSERT_ULLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ushort_type_conversion_tests, "safer_ushort_type conversion tests")
{
	TRY {
		safer_ushort_type var = 0;
		ASSERT_EQUAL(var, 0);
		var = 1;
		ASSERT_EQUAL(var, 1);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1);
		var = (short) SHRT_MAX;
		ASSERT_EQUAL(var, SHRT_MAX);
		var = USHRT_MAX;
		ASSERT_EQUAL(var, USHRT_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_int_type_conversion_error_tests, "safer_ushort_type conversion error tests")
{
	TRY {
		const unsigned int original_value = UINT_MAX;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %u, value = %d\n", LINE, original_value, (int) var);
		ASSERT(u_ne_i(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

#if LONG_MIN < INT_MIN
	TRY {
		const long original_value = LONG_MIN;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#endif

#if LONG_MAX > INT_MAX
	TRY {
		const long original_value = LONG_MAX;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#endif

	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %d\n", LINE, original_value, (int) var);
		ASSERT(ul_ne_l(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %d\n", LINE, original_value, (int) var);
		ASSERT_LLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		const safer_int_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %d\n", LINE, original_value, (int) var);
		ASSERT(ull_ne_ll(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_int_type_conversion_tests, "safer_int_type conversion tests")
{
	TRY {
		safer_int_type var = 0;
		ASSERT_EQUAL(var, 0);
		var = -1;
		ASSERT_EQUAL(var, -1);
		var = 1;
		ASSERT_EQUAL(var, 1);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1);
		var = (char) CHAR_MIN;
		ASSERT_EQUAL(var, CHAR_MIN);
		var = (char) CHAR_MAX;
		ASSERT_EQUAL(var, CHAR_MAX);
		var = (signed char) SCHAR_MIN;
		ASSERT_EQUAL(var, SCHAR_MIN);
		var = (signed char) SCHAR_MAX;
		ASSERT_EQUAL(var, SCHAR_MAX);
		var = (unsigned char) UCHAR_MAX;
		ASSERT_EQUAL(var, UCHAR_MAX);
		var = (short) SHRT_MIN;
		ASSERT_EQUAL(var, SHRT_MIN);
		var = (short) SHRT_MAX;
		ASSERT_EQUAL(var, SHRT_MAX);
		var = (unsigned short) USHRT_MAX;
		ASSERT_EQUAL(var, USHRT_MAX);
		var = INT_MIN;
		ASSERT_EQUAL(var, INT_MIN);
		var = INT_MAX;
		ASSERT_EQUAL(var, INT_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_uint_type_conversion_error_tests, "safer_uint_type conversion error tests")
{
	TRY {
		const signed char original_value = (signed char) SCHAR_MIN;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %u\n", LINE, (int) original_value, (unsigned int) var);
		ASSERT(i_ne_u(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = (short) SHRT_MIN;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %u\n", LINE, (int) original_value, (unsigned int) var);
		ASSERT(i_ne_u(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const signed int original_value = -1;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT(i_ne_u(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT(i_ne_u(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}


	TRY {
		const long original_value = LONG_MIN;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

#if LONG_MAX > UINT_MAX
	TRY {
		const long original_value = LONG_MAX;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#endif

#if ULONG_MAX > UINT_MAX
	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT_ULONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#endif

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT(ll_ne_ull(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MAX;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT(ll_ne_ull(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long original_value = ULLONG_MAX;
		const safer_uint_type var = original_value;
		fprintf(output_file, "Line %d: original value = %llu, value = %u\n", LINE, original_value, (unsigned int) var);
		ASSERT_ULLONG_NOT_EQUAL(original_value, var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uint_type_conversion_tests, "safer_uint_type conversion tests")
{
	TRY {
		safer_uint_type var = 0;
		ASSERT_UINT_EQUAL(var, 0U);
		var = 1;
		ASSERT_UINT_EQUAL(var, 1U);
		var = Boolean_false;
		ASSERT_EQUAL(var, 0U);
		var = Boolean_true;
		ASSERT_EQUAL(var, 1U);
		var = (char) CHAR_MAX;
		ASSERT_UINT_EQUAL(var, CHAR_MAX);
		var = (signed char) SCHAR_MAX;
		ASSERT_UINT_EQUAL(var, SCHAR_MAX);
		var = (unsigned char) UCHAR_MAX;
		ASSERT_UINT_EQUAL(var, UCHAR_MAX);
		var = (short) SHRT_MAX;
		ASSERT_UINT_EQUAL(var, SHRT_MAX);
		var = (unsigned short) USHRT_MAX;
		ASSERT_UINT_EQUAL(var, USHRT_MAX);
		var = INT_MAX;
		ASSERT_UINT_EQUAL(var, INT_MAX);
		var = UINT_MAX;
		ASSERT_UINT_EQUAL(var, UINT_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_long_type_conversion_error_tests, "safer_long_type conversion error tests")
{
	TRY {
		const unsigned long original_value = ULONG_MAX;
		const safer_long_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lu, value = %ld\n", LINE, original_value, (long) var);
		ASSERT(ul_ne_l(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_long_type_conversion_tests, "safer_long_type conversion tests")
{
	TRY {
		safer_long_type var = 0;
		ASSERT_LONG_EQUAL(var, 0L);
		var = -1;
		ASSERT_LONG_EQUAL(var, -1L);
		var = 1;
		ASSERT_LONG_EQUAL(var, 1L);
		var = Boolean_false;
		ASSERT_LONG_EQUAL(var, 0L);
		var = Boolean_true;
		ASSERT_LONG_EQUAL(var, 1L);
		var = SCHAR_MIN;
		ASSERT_LONG_EQUAL(var, SCHAR_MIN);
		var = SCHAR_MAX;
		ASSERT_LONG_EQUAL(var, SCHAR_MAX);
		var = UCHAR_MAX;
		ASSERT_LONG_EQUAL(var, UCHAR_MAX);
		var = SHRT_MIN;
		ASSERT_LONG_EQUAL(var, SHRT_MIN);
		var = SHRT_MAX;
		ASSERT_LONG_EQUAL(var, SHRT_MAX);
		var = USHRT_MAX;
		ASSERT_LONG_EQUAL(var, USHRT_MAX);
		var = INT_MIN;
		ASSERT_LONG_EQUAL(var, INT_MIN);
		var = INT_MAX;
		ASSERT_LONG_EQUAL(var, INT_MAX);
#if LONG_MAX > UINT_MAX
		var = UINT_MAX;
		ASSERT_LONG_EQUAL(var, UINT_MAX);
#endif
		var = LONG_MIN;
		ASSERT_LONG_EQUAL(var, LONG_MIN);
		var = LONG_MAX;
		ASSERT_LONG_EQUAL(var, LONG_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_ulong_type_conversion_error_tests, "safer_ulong_type conversion error tests")
{
	TRY {
		const signed char original_value = SCHAR_MIN;
		const safer_ulong_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %lu\n", LINE, (int) original_value, (unsigned long) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const short original_value = SHRT_MIN;
		const safer_ulong_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %lu\n", LINE, (int) original_value, (unsigned long) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int original_value = INT_MIN;
		const safer_ulong_type var = original_value;
		fprintf(output_file, "Line %d: original value = %d, value = %lu\n", LINE, original_value, (unsigned long) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = -1L;
		const safer_ulong_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %lu\n", LINE, original_value, (unsigned long) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long original_value = LONG_MIN;
		const safer_ulong_type var = original_value;
		fprintf(output_file, "Line %d: original value = %ld, value = %lu\n", LINE, original_value, (unsigned long) var);
		ASSERT(l_ne_ul(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long original_value = LLONG_MIN;
		const safer_ulong_type var = original_value;
		fprintf(output_file, "Line %d: original value = %lld, value = %lu\n", LINE, original_value, (unsigned long) var);
		ASSERT(ll_ne_ull(original_value, var));
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ulong_type_conversion_tests, "safer_ulong_type conversion tests")
{
	TRY {
		safer_ulong_type var = 0;
		ASSERT_ULONG_EQUAL(var, 0UL);
		var = 1;
		ASSERT_ULONG_EQUAL(var, 1UL);
		var = Boolean_false;
		ASSERT_ULONG_EQUAL(var, 0UL);
		var = Boolean_true;
		ASSERT_ULONG_EQUAL(var, 1UL);
		var = (char) CHAR_MAX;
		ASSERT_ULONG_EQUAL(var, CHAR_MAX);
		var = (signed char) SCHAR_MAX;
		ASSERT_ULONG_EQUAL(var, SCHAR_MAX);
		var = (unsigned char) UCHAR_MAX;
		ASSERT_ULONG_EQUAL(var, UCHAR_MAX);
		var = (short) SHRT_MAX;
		ASSERT_ULONG_EQUAL(var, SHRT_MAX);
		var = (unsigned short) USHRT_MAX;
		ASSERT_ULONG_EQUAL(var, USHRT_MAX);
		var = INT_MAX;
		ASSERT_ULONG_EQUAL(var, INT_MAX);
		var = UINT_MAX;
		ASSERT_ULONG_EQUAL(var, UINT_MAX);
		var = LONG_MAX;
		ASSERT_ULONG_EQUAL(var, LONG_MAX);
		var = ULONG_MAX;
		ASSERT_ULONG_EQUAL(var, ULONG_MAX);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

/* Increment operator tests */
TEST(safer_schar_type_increment_error_tests, "safer_schar_type_increment_error_tests")
{
	TRY {
		safer_schar_type value = SCHAR_MAX;
		safer_schar_type before = value++;
		fprintf(output_file, "Line %d: (%d)++ -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_schar_type value = SCHAR_MAX;
		safer_schar_type before = value;
		safer_schar_type after = ++value;
		fprintf(output_file, "Line %d: ++(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uchar_type_increment_error_tests, "safer_uchar_type_increment_error_tests")
{
	TRY {
		safer_uchar_type value = UCHAR_MAX;
		safer_uchar_type before = value++;
		fprintf(output_file, "Line %d: (%d)++ -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uchar_type value = UCHAR_MAX;
		safer_uchar_type before = value;
		safer_uchar_type after = ++value;
		fprintf(output_file, "Line %d: ++(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_short_type_increment_error_tests, "safer_short_type addition error tests")
{
	TRY {
		safer_short_type value = SHRT_MAX;
		safer_short_type before = value++;
		fprintf(output_file, "Line %d: (%d)++ -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_short_type value = SHRT_MAX;
		safer_short_type before = value;
		safer_short_type after = ++value;
		fprintf(output_file, "Line %d: ++(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ushort_type_increment_error_tests, "safer_ushort_type addition error tests")
{
	TRY {
		safer_ushort_type value = USHRT_MAX;
		safer_ushort_type before = value++;
		fprintf(output_file, "Line %d: (%d)++ -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ushort_type value = USHRT_MAX;
		safer_ushort_type before = value;
		safer_ushort_type after = ++value;
		fprintf(output_file, "Line %d: ++(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_int_type_increment_error_tests, "safer_int_type increment error tests")
{
	TRY {
		safer_int_type value = INT_MAX;
		safer_int_type before = value++;
		fprintf(output_file, "Line %d: (%d)++ -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type value = INT_MAX;
		safer_int_type before = value;
		safer_int_type after = ++value;
		fprintf(output_file, "Line %d: ++(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uint_type_increment_error_tests, "safer_uint_type increment error tests")
{
	TRY {
		safer_uint_type value = UINT_MAX;
		safer_uint_type before = value++;
		fprintf(output_file, "Line %d: (%u)++ -> %u\n", LINE, (unsigned int) before, (unsigned int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type value = UINT_MAX;
		safer_uint_type before = value;
		safer_uint_type after = ++value;
		fprintf(output_file, "Line %d: ++(%u) -> %u, new value == %u\n", LINE, (unsigned int) before, (unsigned int) after, (unsigned int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_long_type_increment_error_tests, "safer_long_type increment error tests")
{
	TRY {
		safer_long_type value = LONG_MAX;
		safer_long_type before = value++;
		fprintf(output_file, "Line %d: (%ld)++ -> %ld\n", LINE, (long) before, (long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type value = LONG_MAX;
		safer_long_type before = value;
		safer_long_type after = ++value;
		fprintf(output_file, "Line %d: ++(%ld) -> %ld, new value == %ld\n", LINE, (long) before, (long) after, (long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ulong_type_increment_error_tests, "safer_ulong_type increment error tests")
{
	TRY {
		safer_ulong_type value = ULONG_MAX;
		safer_ulong_type before = value++;
		fprintf(output_file, "Line %d: (%lu)++ -> %lu\n", LINE, (unsigned long) before, (unsigned long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type value = ULONG_MAX;
		safer_ulong_type before = value;
		safer_ulong_type after = ++value;
		fprintf(output_file, "Line %d: ++(%lu) -> %lu, new value == %lu\n", LINE, (unsigned long) before, (unsigned long) after, (unsigned long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_llong_type_increment_error_tests, "safer_llong_type increment error tests")
{
	TRY {
		safer_llong_type value = LLONG_MAX;
		safer_llong_type before = value++;
		fprintf(output_file, "Line %d: (%lld)++ -> %lld\n", LINE, (long long) before, (long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type value = LLONG_MAX;
		safer_llong_type before = value;
		safer_llong_type after = ++value;
		fprintf(output_file, "Line %d: ++(%lld) -> %lld, new value == %lld\n", LINE, (long long) before, (long long) after, (long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ullong_type_increment_error_tests, "safer_ullong_type increment error tests")
{
	TRY {
		safer_ullong_type value = ULLONG_MAX;
		safer_ullong_type before = value++;
		fprintf(output_file, "Line %d: (%llu)++ -> %llu\n", LINE, (unsigned long long) before, (unsigned long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type value = ULLONG_MAX;
		safer_ullong_type before = value;
		safer_ullong_type after = ++value;
		fprintf(output_file, "Line %d: ++(%llu) -> %llu, new value == %llu\n", LINE,
			(unsigned long long) before, (unsigned long long) after, (unsigned long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

/* Decrement operator tests */
TEST(safer_schar_type_decrement_error_tests, "safer_schar_type decrement error tests")
{
	TRY {
		safer_schar_type value = (signed char) SCHAR_MIN;
		safer_schar_type before = value--;
		fprintf(output_file, "Line %d: (%d)-- -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_schar_type value = (signed char) SCHAR_MIN;
		safer_schar_type before = value;
		safer_schar_type after = --value;
		fprintf(output_file, "Line %d: --(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uchar_type_decrement_error_tests, "safer_uchar_type decrement error tests")
{
	TRY {
		safer_uchar_type value = (unsigned char) 0U;
		safer_uchar_type before = value--;
		fprintf(output_file, "Line %d: (%d)-- -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uchar_type value = (unsigned char) 0U;
		safer_uchar_type before = value;
		safer_uchar_type after = --value;
		fprintf(output_file, "Line %d: --(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_short_type_decrement_error_tests, "safer_short_type decrement error tests")
{
	TRY {
		safer_short_type value = (short) SHRT_MIN;
		safer_short_type before = value--;
		fprintf(output_file, "Line %d: (%d)-- -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_short_type value = (short) SHRT_MIN;
		safer_short_type before = value;
		safer_short_type after = --value;
		fprintf(output_file, "Line %d: --(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ushort_type_decrement_error_tests, "safer_ushort_type decrement error tests")
{
	TRY {
		safer_ushort_type value = (unsigned short) 0U;
		safer_ushort_type before = value--;
		fprintf(output_file, "Line %d: (%d)-- -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ushort_type value = (unsigned short) 0U;
		safer_ushort_type before = value;
		safer_ushort_type after = --value;
		fprintf(output_file, "Line %d: --(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_int_type_decrement_error_tests, "safer_int_type decrement error tests")
{
	TRY {
		safer_int_type value = INT_MIN;
		safer_int_type before = value--;
		fprintf(output_file, "Line %d: (%d)-- -> %d\n", LINE, (int) before, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type value = INT_MIN;
		safer_int_type before = value;
		safer_int_type after = --value;
		fprintf(output_file, "Line %d: --(%d) -> %d, new value == %d\n", LINE, (int) before, (int) after, (int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uint_type_decrement_error_tests, "safer_uint_type decrement error tests")
{
	TRY {
		safer_uint_type value = 0U;
		safer_uint_type before = value--;
		fprintf(output_file, "Line %d: (%u)-- -> %u\n", LINE, (unsigned int) before, (unsigned int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type value = 0U;
		safer_uint_type before = value;
		safer_uint_type after = --value;
		fprintf(output_file, "Line %d: --(%u) -> %u, new value == %u\n", LINE, (unsigned int) before, (unsigned int) after, (unsigned int) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_long_type_decrement_error_tests, "safer_long_type decrement error tests")
{
	TRY {
		safer_long_type value = LONG_MIN;
		safer_long_type before = value--;
		fprintf(output_file, "Line %d: (%ld)-- -> %ld\n", LINE, (long) before, (long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type value = LONG_MIN;
		safer_long_type before = value;
		safer_long_type after = --value;
		fprintf(output_file, "Line %d: --(%ld) -> %ld, new value == %ld\n", LINE, (long) before, (long) after, (long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ulong_type_decrement_error_tests, "safer_ulong_type decrement error tests")
{
	TRY {
		safer_ulong_type value = 0UL;
		safer_ulong_type before = value--;
		fprintf(output_file, "Line %d: (%lu)-- -> %lu\n", LINE, (unsigned long) before, (unsigned long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type value = 0UL;
		safer_ulong_type before = value;
		safer_ulong_type after = --value;
		fprintf(output_file, "Line %d: --(%lu) -> %lu, new value == %lu\n", LINE, (unsigned long) before, (unsigned long) after, (unsigned long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_llong_type_decrement_error_tests, "safer_llong_type decrement error tests")
{
	TRY {
		safer_llong_type value = LLONG_MIN;
		safer_llong_type before = value--;
		fprintf(output_file, "Line %d: (%lld)-- -> %lld\n", LINE, (long long) before, (long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type value = LLONG_MIN;
		safer_llong_type before = value;
		safer_llong_type after = --value;
		fprintf(output_file, "Line %d: --(%lld) -> %lld, new value == %lld\n", LINE, (long long) before, (long long) after, (long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ullong_type_decrement_error_tests, "safer_ullong_type decrement error tests")
{
	TRY {
		safer_ullong_type value = 0ULL;
		safer_ullong_type before = value--;
		fprintf(output_file, "Line %d: (%llu)-- -> %llu\n", LINE, (unsigned long long) before, (unsigned long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type value = 0ULL;
		safer_ullong_type before = value;
		safer_ullong_type after = --value;
		fprintf(output_file, "Line %d: --(%llu) -> %llu, new value == %llu\n", LINE,
			(unsigned long long) before, (unsigned long long) after, (unsigned long long) value);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

/* Addition tests */
TEST(safer_int_type_addition_error_tests, "safer_int_type addition error tests")
{
	TRY {
		const safer_int_type var1 = INT_MIN;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 + var2;
		fprintf(output_file, "Line %d: %d + %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const int var2 = -1;
		const safer_int_type result = var1 + var2;
		fprintf(output_file, "Line %d: %d + %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MIN;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 + var2;
		fprintf(output_file, "Line %d: %d + %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MAX;
		const safer_int_type var2 = 1;
		const safer_int_type result = var1 + var2;
		fprintf(output_file, "Line %d: %d + %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MAX;
		const int var2 = 1;
		const safer_int_type result = var1 + var2;
		fprintf(output_file, "Line %d: %d + %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MAX;
		const safer_int_type var2 = 1;
		const safer_int_type result = var1 + var2;
		fprintf(output_file, "Line %d: %d + %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MAX;
		const safer_int_type offset = 1;
		const int before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%d += %d) -> %d\n", LINE, before, (int) offset, (int)var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MAX;
		const int offset = 1;
		const int before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%d += %d) -> %d\n", LINE, before, offset, (int)var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uint_type_addition_error_tests, "safer_uint_type addition error tests")
{
	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const safer_uint_type var2 = 1U;
		const safer_uint_type result = var1 + var2;
		fprintf(output_file, "Line %d: %u + %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const unsigned int var2 = 1U;
		const safer_uint_type result = var1 + var2;
		fprintf(output_file, "Line %d: %u + %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = UINT_MAX;
		const safer_uint_type var2 = 1U;
		const safer_uint_type result = var1 + var2;
		fprintf(output_file, "Line %d: %u + %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = UINT_MAX;
		const safer_uint_type offset = 1U;
		const unsigned int before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%u += %u) -> %u\n", LINE, before, (unsigned int) offset, (unsigned int)var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = UINT_MAX;
		const unsigned int offset = 1U;
		const unsigned int before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%u += %u) -> %u\n", LINE, before, offset, (unsigned int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_long_type_addition_error_tests, "safer_long_type addition error tests")
{
	TRY {
		const safer_long_type var1 = LONG_MIN;
		const safer_long_type var2 = -1L;
		const safer_long_type result = var1 + var2;
		fprintf(output_file, "Line %d: %ld + %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const long var2 = -1L;
		const safer_long_type result = var1 + var2;
		fprintf(output_file, "Line %d: %ld + %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = LONG_MIN;
		const safer_long_type var2 = -1L;
		const safer_long_type result = var1 + var2;
		fprintf(output_file, "Line %d: %ld + %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MAX;
		const safer_long_type var2 = 1L;
		const safer_long_type result = var1 + var2;
		fprintf(output_file, "Line %d: %ld + %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MAX;
		const long var2 = 1L;
		const safer_long_type result = var1 + var2;
		fprintf(output_file, "Line %d: %ld + %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = LONG_MAX;
		const safer_long_type var2 = 1L;
		const safer_long_type result = var1 + var2;
		fprintf(output_file, "Line %d: %ld + %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MAX;
		const safer_long_type offset = 1L;
		const long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%ld += %ld) -> %ld\n", LINE, before, (long) offset, (long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MAX;
		const long offset = 1L;
		const long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%ld += %ld) -> %ld\n", LINE, before, offset, (long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ulong_type_addition_error_tests, "safer_ulong_type addition error tests")
{
	TRY {
		const safer_ulong_type var1 = ULONG_MAX;
		const safer_ulong_type var2 = 1UL;
		const safer_ulong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lu + %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = ULONG_MAX;
		const unsigned long var2 = 1UL;
		const safer_ulong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lu + %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = ULONG_MAX;
		const safer_ulong_type var2 = 1UL;
		const safer_ulong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lu + %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = ULONG_MAX;
		const safer_ulong_type offset = 1UL;
		const unsigned long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%lu += %lu) -> %lu\n", LINE, before, (unsigned long) offset, (unsigned long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = ULONG_MAX;
		const unsigned long offset = 1UL;
		const unsigned long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%lu += %lu) -> %lu\n", LINE, before, offset, (unsigned long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_llong_type_addition_error_tests, "safer_llong_type addition error tests")
{
	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const safer_llong_type var2 = -1LL;
		const safer_llong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lld + %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const long long var2 = -1LL;
		const safer_llong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lld + %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MIN;
		const safer_llong_type var2 = -1LL;
		const safer_llong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lld + %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MAX;
		const safer_llong_type var2 = 1LL;
		const safer_llong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lld + %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MAX;
		const long long var2 = 1LL;
		const safer_llong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lld + %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MAX;
		const safer_llong_type var2 = 1LL;
		const safer_llong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %lld + %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MAX;
		const safer_llong_type offset = 1LL;
		const long long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%lld += %lld) -> %lld\n", LINE, before, (long long) offset, (long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MAX;
		const long long offset = 1LL;
		const long long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%lld += %lld) -> %lld\n", LINE, before, offset, (long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ullong_type_addition_error_tests, "safer_ullong_type addition error tests")
{
	TRY {
		const safer_ullong_type var1 = ULLONG_MAX;
		const safer_ullong_type var2 = 1ULL;
		const safer_ullong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %llu + %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = ULLONG_MAX;
		const unsigned long long var2 = 1ULL;
		const safer_ullong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %llu + %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = ULLONG_MAX;
		const safer_ullong_type var2 = 1ULL;
		const safer_ullong_type result = var1 + var2;
		fprintf(output_file, "Line %d: %llu + %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = ULLONG_MAX;
		const safer_ullong_type offset = 1ULL;
		const unsigned long long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%llu += %llu) -> %llu\n", LINE, before, (unsigned long long) offset, (unsigned long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = ULLONG_MAX;
		const unsigned long long offset = 1ULL;
		const unsigned long long before = var;
		var += offset;
		fprintf(output_file, "Line %d: (%llu += %llu) -> %llu\n", LINE, before, offset, (unsigned long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_addition_tests, "safer integer type addition tests")
{
	TRY {
		const safer_schar_type scvar = -128;
		const safer_uchar_type ucvar = 255U;
		const safer_short_type svar = -32768;
		const safer_ushort_type usvar = 65535U;
		const safer_int_type ivar = -2147483647 - 1;
		const safer_uint_type uvar = 4294967295U;
		safer_int_type iresult = 0;
		iresult = scvar + (-1);
		ASSERT_EQUAL(iresult, -129);
		iresult += -1;
		ASSERT_EQUAL(iresult, -130);
		iresult = ucvar + 1;
		ASSERT_EQUAL(iresult, 256);
		iresult += 1;
		ASSERT_EQUAL(iresult, 257);
		iresult = svar + (-1);
		ASSERT_EQUAL(iresult, -32769);
		iresult += -1;
		ASSERT_EQUAL(iresult, -32770);
		iresult = usvar + 1;
		ASSERT_EQUAL(iresult, 65536);
		iresult += 1;
		ASSERT_EQUAL(iresult, 65537);
#if (LONG_MIN < INT_MIN) && (LONG_MAX > INT_MAX)
		safer_long_type lresult = 0L;
		lresult = ivar + (-1L);
		ASSERT_LONG_EQUAL(lresult, -2147483649L);
		lresult += -1L;
		ASSERT_LONG_EQUAL(lresult, -2147483650L);
		lresult = uvar + 1L;
		ASSERT_LONG_EQUAL(lresult, 4294967296L);
		lresult += 1L;
		ASSERT_LONG_EQUAL(lresult, 4294967297L);
		lresult = (safer_long_type) ivar + (-1);
		ASSERT_LONG_EQUAL(lresult, -2147483649L);
		lresult = (safer_long_type)uvar + 1;
		ASSERT_LONG_EQUAL(lresult, 4294967296L);
#endif
		safer_llong_type llresult = 0LL;
		llresult = ivar + (-1LL);
		ASSERT_LLONG_EQUAL(llresult, -2147483649LL);
		llresult += -1LL;
		ASSERT_LLONG_EQUAL(llresult, -2147483650LL);
		llresult = uvar + 1LL;
		ASSERT_LLONG_EQUAL(llresult, 4294967296LL);
		llresult += 1LL;
		ASSERT_LLONG_EQUAL(llresult, 4294967297LL);
		llresult = (safer_llong_type) ivar + (-1);
		ASSERT_LLONG_EQUAL(llresult, -2147483649LL);
		llresult = (safer_llong_type) uvar + 1;
		ASSERT_LLONG_EQUAL(llresult, 4294967296LL);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

/* Subtraction tests */
TEST(safer_int_type_subtraction_error_tests, "safer_int_type subtraction error tests")
{
	TRY {
		const safer_int_type var1 = INT_MIN;
		const safer_int_type var2 = 1;
		const safer_int_type result = var1 - var2;
		fprintf(output_file, "Line %d: %d - %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const int var2 = 1;
		const safer_int_type result = var1 - var2;
		fprintf(output_file, "Line %d: %d - %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MIN;
		const safer_int_type var2 = 1;
		const safer_int_type result = var1 - var2;
		fprintf(output_file, "Line %d: %d - %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 0;
		const safer_int_type var2 = INT_MIN;
		const safer_int_type result = var1 - var2;
		fprintf(output_file, "Line %d: %d - %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 0;
		const int var2 = INT_MIN;
		const safer_int_type result = var1 - var2;
		fprintf(output_file, "Line %d: %d - %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = 0;
		const safer_int_type var2 = INT_MIN;
		const safer_int_type result = var1 - var2;
		fprintf(output_file, "Line %d: %d - %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MIN;
		const safer_int_type offset = 1;
		const int before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%d -= %d) -> %d\n", LINE, before, (int) offset, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MIN;
		const int offset = 1;
		const int before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%d -= %d) -> %d\n", LINE, before, offset, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uint_type_subtraction_error_tests, "safer_uint_type addition error tests")
{
	TRY {
		const safer_uint_type var1 = 0U;
		const safer_uint_type var2 = 1U;
		const safer_uint_type result = var1 - var2;
		fprintf(output_file, "Line %d: %u - %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 0U;
		const unsigned int var2 = 1U;
		const safer_uint_type result = var1 - var2;
		fprintf(output_file, "Line %d: %u - %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 0U;
		const safer_uint_type var2 = 1U;
		const safer_uint_type result = var1 - var2;
		fprintf(output_file, "Line %d: %u - %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = 0U;
		const safer_uint_type offset = 1U;
		const unsigned int before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%u -= %u) -> %u\n", LINE, before, (unsigned int) offset, (unsigned int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = 0U;
		const unsigned int offset = 1U;
		const unsigned int before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%u -= %u) -> %u\n", LINE, before, offset, (unsigned int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_long_type_subtraction_error_tests, "safer_long_type subtraction error tests")
{
	TRY {
		const safer_long_type var1 = LONG_MIN;
		const safer_long_type var2 = 1L;
		const safer_long_type result = var1 - var2;
		fprintf(output_file, "Line %d: %ld - %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const long var2 = 1L;
		const safer_long_type result = var1 - var2;
		fprintf(output_file, "Line %d: %ld - %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = LONG_MIN;
		const safer_long_type var2 = 1L;
		const safer_long_type result = var1 - var2;
		fprintf(output_file, "Line %d: %ld - %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MIN;
		const safer_long_type offset = 1L;
		const long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: %ld -= %ld -> %ld\n", LINE, before, (long) offset, (long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MIN;
		const long offset = 1L;
		const long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: %ld -= %ld -> %ld\n", LINE, before, offset, (long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ulong_type_subtraction_error_tests, "safer_ulong_type subtraction error tests")
{
	TRY {
		const safer_ulong_type var1 = 0UL;
		const safer_ulong_type var2 = 1UL;
		const safer_ulong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %lu - %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 0UL;
		const unsigned long var2 = 1UL;
		const safer_ulong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %lu - %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = 0UL;
		const safer_ulong_type var2 = 1UL;
		const safer_ulong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %lu - %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = 0UL;
		const safer_ulong_type offset = 1UL;
		const unsigned long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%lu -= %lu) -> %lu\n", LINE, before, (unsigned long) offset, (unsigned long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = 0UL;
		const unsigned long offset = 1UL;
		const unsigned long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%lu -= %lu) -> %lu\n", LINE, before, offset, (unsigned long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_llong_type_subtraction_error_tests, "safer_llong_type subtraction error tests")
{
	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const safer_llong_type var2 = 1LL;
		const safer_llong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %lld - %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const long long var2 = 1LL;
		const safer_llong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %lld - %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MIN;
		const safer_llong_type var2 = 1LL;
		const safer_llong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %lld - %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MIN;
		const safer_llong_type offset = 1LL;
		const long long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%lld -= %lld) -> %lld\n", LINE, before, (long long) offset, (long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MIN;
		const long long offset = 1LL;
		const long long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%lld -= %lld) -> %lld\n", LINE, before, offset, (long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ullong_type_subtraction_error_tests, "safer_ullong_type subtraction error tests")
{
	TRY {
		const safer_ullong_type var1 = 0ULL;
		const safer_ullong_type var2 = 1ULL;
		const safer_ullong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %llu - %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 0ULL;
		const unsigned long long var2 = 1ULL;
		const safer_ullong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %llu - %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = 0ULL;
		const safer_ullong_type var2 = 1ULL;
		const safer_ullong_type result = var1 - var2;
		fprintf(output_file, "Line %d: %llu - %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = 0ULL;
		const safer_ullong_type offset = 1ULL;
		const unsigned long long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%llu -= %llu) -> %llu\n", LINE, before, (unsigned long long) offset, (unsigned long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = 0ULL;
		const unsigned long long offset = 1ULL;
		const unsigned long long before = var;
		var -= offset;
		fprintf(output_file, "Line %d: (%llu -= %llu) -> %llu\n", LINE, before, offset, (unsigned long long) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_subtraction_tests, "safer integer type subtraction tests")
{
	TRY {
		const safer_schar_type scvar = -128;
		const safer_uchar_type ucvar = 255U;
		const safer_short_type svar = -32768;
		const safer_ushort_type usvar = 65535U;
		const safer_int_type ivar = -2147483647 - 1;
		const safer_uint_type uvar = 4294967295U;
		safer_int_type iresult = 0;
		iresult = scvar - 1;
		ASSERT_EQUAL(iresult, -129);
		iresult -= 1;
		ASSERT_EQUAL(iresult, -130);
		iresult = 0 - ucvar;
		ASSERT_EQUAL(iresult, -255);
		iresult -= 1;
		ASSERT_EQUAL(iresult, -256);
		iresult = svar - 1;
		ASSERT_EQUAL(iresult, -32769);
		iresult = 0 - usvar;
		ASSERT_EQUAL(iresult, -65535);
#if (LONG_MIN < INT_MIN) && (LONG_MAX > INT_MAX)
		safer_long_type lresult = 0L;
		lresult = ivar - 1L;
		ASSERT_LONG_EQUAL(lresult, -2147483649L);
		lresult -= 1L;
		ASSERT_LONG_EQUAL(lresult, -2147483650L);
		lresult = 0L - uvar;
		ASSERT_LONG_EQUAL(lresult, -4294967295L);
		lresult -= 1L;
		ASSERT_LONG_EQUAL(lresult, -4294967296L);
		lresult = (safer_long_type) ivar - 1;
		ASSERT_LONG_EQUAL(lresult, -2147483649L);
		lresult = 0 - (safer_long_type) uvar;
		ASSERT_LONG_EQUAL(lresult, -4294967295L);
#endif
		safer_llong_type llresult = 0LL;
		llresult = ivar - 1LL;
		ASSERT_LLONG_EQUAL(llresult, -2147483649LL);
		llresult -= 1LL;
		ASSERT_LLONG_EQUAL(llresult, -2147483650LL);
		llresult = 0LL - uvar;
		ASSERT_LLONG_EQUAL(llresult, -4294967295LL);
		llresult -= 1LL;
		ASSERT_LLONG_EQUAL(llresult, -4294967296LL);
		llresult = (safer_llong_type) ivar - 1;
		ASSERT_LLONG_EQUAL(llresult, -2147483649LL);
		llresult = 0 - (safer_llong_type) uvar;
		ASSERT_LLONG_EQUAL(llresult, -4294967295LL);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

/* Multiplication tests */
TEST(safer_int_type_multiplication_error_tests, "safer_int_type multiplication error tests")
{
	TRY {
		const safer_int_type var1 = INT_MIN;
		const safer_int_type var2 = 2;
		const safer_int_type result = var1 * var2;
		fprintf(output_file, "Line %d: %d * %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const int var2 = 2;
		const safer_int_type result = var1 * var2;
		fprintf(output_file, "Line %d: %d * %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MIN;
		const safer_int_type var2 = 2;
		const safer_int_type result = var1 * var2;
		fprintf(output_file, "Line %d: %d * %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MAX;
		const safer_int_type var2 = 2;
		const safer_int_type result = var1 * var2;
		fprintf(output_file, "Line %d: %d * %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MAX;
		const int var2 = 2;
		const safer_int_type result = var1 * var2;
		fprintf(output_file, "Line %d: %d * %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MAX;
		const safer_int_type var2 = 2;
		const safer_int_type result = var1 * var2;
		fprintf(output_file, "Line %d: %d * %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MAX;
		const safer_int_type factor = 2;
		const int before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%d *= %d) -> %d\n", LINE, before, (int) factor, (int) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MAX;
		const int factor = 2;
		const int before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%d *= %d) -> %d\n", LINE, before, factor, (int) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_uint_type_multiplication_error_tests, "safer_uint_type multiplication error tests")
{
	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const safer_uint_type var2 = 2U;
		const safer_uint_type result = var1 * var2;
		fprintf(output_file, "Line %d: %u * %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const unsigned int var2 = 2U;
		const safer_uint_type result = var1 * var2;
		fprintf(output_file, "Line %d: %u * %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = UINT_MAX;
		const safer_uint_type var2 = 2U;
		const safer_uint_type result = var1 * var2;
		fprintf(output_file, "Line %d: %u * %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = UINT_MAX;
		const safer_uint_type factor = 2U;
		const unsigned int before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%u *= %u) -> %u\n", LINE, before, (unsigned int) factor, (unsigned int) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = UINT_MAX;
		const unsigned int factor = 2U;
		const unsigned int before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%u *= %u) -> %u\n", LINE, before, factor, (unsigned int) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_long_type_multiplication_error_tests, "safer_long_type multiplication error tests")
{
	TRY {
		const safer_long_type var1 = LONG_MIN;
		const safer_long_type var2 = 2L;
		const safer_long_type result = var1 * var2;
		fprintf(output_file, "Line %d: %ld * %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const long var2 = 2L;
		const safer_long_type result = var1 * var2;
		fprintf(output_file, "Line %d: %ld * %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = LONG_MIN;
		const safer_long_type var2 = 2L;
		const safer_long_type result = var1 * var2;
		fprintf(output_file, "Line %d: %ld * %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MAX;
		const safer_long_type var2 = 2L;
		const safer_long_type result = var1 * var2;
		fprintf(output_file, "Line %d: %ld * %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MAX;
		const safer_long_type factor = 2L;
		const long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%ld *= %ld) -> %ld\n", LINE, before, (long) factor, (long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MAX;
		const long factor = 2L;
		const long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%ld *= %ld) -> %ld\n", LINE, before, factor, (long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ulong_type_multiplication_error_tests, "safer_ulong_type multiplication error tests")
{
	TRY {
		const safer_ulong_type var1 = ULONG_MAX;
		const safer_ulong_type var2 = 2UL;
		const safer_ulong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lu * %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = ULONG_MAX;
		const unsigned long var2 = 2UL;
		const safer_ulong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lu * %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = ULONG_MAX;
		const safer_ulong_type var2 = 2UL;
		const safer_ulong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lu * %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = ULONG_MAX;
		const safer_ulong_type factor = 2UL;
		const unsigned long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%lu *= %lu) -> %lu\n", LINE, before, (unsigned long) factor, (unsigned long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = ULONG_MAX;
		const unsigned long factor = 2UL;
		const unsigned long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%lu *= %lu) -> %lu\n", LINE, before, factor, (unsigned long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_llong_type_multiplication_error_tests, "safer_llong_type multiplication error tests")
{
	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const safer_llong_type var2 = 2LL;
		const safer_llong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lld * %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const long long var2 = 2LL;
		const safer_llong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lld * %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MIN;
		const safer_llong_type var2 = 2LL;
		const safer_llong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lld * %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MAX;
		const safer_llong_type var2 = 2LL;
		const safer_llong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lld * %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MAX;
		const long long var2 = 2LL;
		const safer_llong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lld * %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MAX;
		const safer_llong_type var2 = 2LL;
		const safer_llong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %lld * %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MAX;
		const safer_llong_type factor = 2LL;
		const long long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%lld *= %lld) -> %lld\n", LINE, before, (long long) factor, (long long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MAX;
		const long long factor = 2LL;
		const long long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%lld *= %lld) -> %lld\n", LINE, before, factor, (long long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_ullong_type_multiplication_error_tests, "safer_ullong_type multiplication error tests")
{
	TRY {
		const safer_ullong_type var1 = ULLONG_MAX;
		const safer_ullong_type var2 = 2ULL;
		const safer_ullong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %llu * %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = ULLONG_MAX;
		const unsigned long long var2 = 2ULL;
		const safer_ullong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %llu * %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = ULLONG_MAX;
		const safer_ullong_type var2 = 2ULL;
		const safer_ullong_type result = var1 * var2;
		fprintf(output_file, "Line %d: %llu * %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = ULLONG_MAX;
		const safer_ullong_type factor = 2ULL;
		const unsigned long long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%llu *= %llu) -> %llu\n", LINE, before, (unsigned long long) factor, (unsigned long long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = ULLONG_MAX;
		const unsigned long long factor = 2ULL;
		const unsigned long long before = var;
		var *= factor;
		fprintf(output_file, "Line %d: (%llu *= %llu) -> %llu\n", LINE, before, factor, (unsigned long long) var);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_multiplication_tests, "safer integer type multiplication tests")
{
	TRY {
		const safer_schar_type scvar = -128;
		const safer_uchar_type ucvar = 255U;
		const safer_short_type svar = -32768;
		const safer_ushort_type usvar = 65535U;
		const safer_int_type ivar = -2147483647 - 1;
		const safer_uint_type uvar = 4294967295U;
		safer_int_type iresult = 0;
		iresult = scvar * 2;
		ASSERT_EQUAL(iresult, -256);
		iresult *= 2;
		ASSERT_EQUAL(iresult, -512);
		iresult = 2 * ucvar;
		ASSERT_EQUAL(iresult, 510);
		iresult *= 2;
		ASSERT_EQUAL(iresult, 1020);
		iresult = svar * 2;
		ASSERT_EQUAL(iresult, -65536);
		iresult *= 2;
		ASSERT_EQUAL(iresult, -131072);
		iresult = 2 * usvar;
		ASSERT_EQUAL(iresult, 131070);
		iresult *= 2;
		ASSERT_EQUAL(iresult, 262140);
#if (LONG_MIN < INT_MIN) && (LONG_MAX > INT_MAX)
		safer_long_type lresult = 0L;
		lresult = ivar * 2L;
		ASSERT_LONG_EQUAL(lresult, -4294967296L);
		lresult *= 2L;
		ASSERT_LONG_EQUAL(lresult, -8589934592L);
		lresult = uvar * 2L;
		ASSERT_LONG_EQUAL(lresult, 8589934590L);
		lresult *= 2L;
		ASSERT_LONG_EQUAL(lresult, 17179869180L);
		lresult = (safer_long_type) ivar * 2;
		ASSERT_LONG_EQUAL(lresult, -4294967296L);
		lresult = (safer_long_type) uvar * 2;
		ASSERT_LONG_EQUAL(lresult, 8589934590L);
#endif
		safer_llong_type llresult = 0LL;
		llresult = ivar * 2LL;
		ASSERT_LLONG_EQUAL(llresult, -4294967296LL);
		llresult *= 2L;
		ASSERT_LLONG_EQUAL(llresult, -8589934592LL);
		llresult = uvar * 2LL;
		ASSERT_LLONG_EQUAL(llresult, 8589934590LL);
		llresult *= 2L;
		ASSERT_LLONG_EQUAL(llresult, 17179869180LL);
		llresult = (safer_llong_type) ivar * 2;
		ASSERT_LLONG_EQUAL(llresult, -4294967296LL);
		llresult = (safer_llong_type) uvar * 2;
		ASSERT_LLONG_EQUAL(llresult, 8589934590LL);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

/* Division tests */
TEST(safer_int_type_division_error_tests, "safer_int_type division error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const int var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = -1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 0;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 0;
		const int var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = 0;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 1;
		const int var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = 1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const int var2 = -1;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MIN;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 / var2;
		fprintf(output_file, "Line %d: %d / %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MIN;
		const safer_int_type divisor = -1;
		const int before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%d /= %d) -> %d\n", LINE, before, (int) divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MIN;
		const int divisor = -1;
		const int before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%d /= %d) -> %d\n", LINE, before, divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const safer_int_type divisor = 0;
		const int before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%d /= %d) -> %d\n", LINE, before, (int) divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const int divisor = 0;
		const int before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%d /= %d) -> %d\n", LINE, before, divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_int_type division error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_uint_type_division_error_tests, "safer_uint_type division error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_uint_type var1 = 0U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 / var2;
		fprintf(output_file, "Line %d: %u / %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 0U;
		const unsigned int var2 = 0U;
		const safer_uint_type result = var1 / var2;
		fprintf(output_file, "Line %d: %u / %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 0U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 / var2;
		fprintf(output_file, "Line %d: %u / %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 1U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 / var2;
		fprintf(output_file, "Line %d: %u / %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 1U;
		const unsigned int var2 = 0U;
		const safer_uint_type result = var1 / var2;
		fprintf(output_file, "Line %d: %u / %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 1U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 / var2;
		fprintf(output_file, "Line %d: %u / %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = 1U;
		const safer_uint_type divisor = 0U;
		const unsigned int before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%u /= %u) -> %u\n", LINE, before, (unsigned int) divisor, (unsigned int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = 1U;
		const unsigned int divisor = 0U;
		const unsigned int before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%u /= %u) -> %u\n", LINE, before, divisor, (unsigned int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_uint_type division error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_long_type_division_error_tests, "safer_long_type division error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_long_type var1 = -1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = -1L;
		const long var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = -1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 0L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 0L;
		const long var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = 0L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 1L;
		const long var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = 1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const safer_long_type var2 = -1L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const long var2 = -1L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = LONG_MIN;
		const safer_long_type var2 = -1L;
		const safer_long_type result = var1 / var2;
		fprintf(output_file, "Line %d: %ld / %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MIN;
		const safer_long_type divisor = -1L;
		const long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%ld /= %ld) -> %ld\n", LINE, before, (long) divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MIN;
		const long divisor = -1L;
		const long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%ld /= %ld) -> %ld\n", LINE, before, divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = 1L;
		const safer_long_type divisor = 0L;
		const long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%ld /= %ld) -> %ld\n", LINE, before, (long) divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = 1L;
		const long divisor = 0L;
		const long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%ld /= %ld) -> %ld\n", LINE, before, divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_long_type division error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_ulong_type_division_error_tests, "safer_ulong_type division error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_ulong_type var1 = 0UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lu / %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 0UL;
		const unsigned long var2 = 0UL;
		const safer_ulong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lu / %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = 0UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lu / %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 1UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lu / %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 1UL;
		const unsigned long var2 = 0UL;
		const safer_ulong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lu / %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = 1UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lu / %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = 1UL;
		const safer_ulong_type divisor = 0UL;
		const unsigned long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%lu /= %lu) -> %lu\n", LINE, before, (unsigned long) divisor, (unsigned long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = 1UL;
		const unsigned long divisor = 0UL;
		const unsigned long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%lu /= %lu) -> %lu\n", LINE, before, divisor, (unsigned long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_ulong_type division error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_llong_type_division_error_tests, "safer_llong_type division error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_llong_type var1 = -1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = -1LL;
		const long long var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = -1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 0LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 0LL;
		const long long var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = 0LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 1LL;
		const long long var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = 1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const safer_llong_type var2 = -1LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const long long var2 = -1LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MIN;
		const safer_llong_type var2 = -1LL;
		const safer_llong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %lld / %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MIN;
		const safer_llong_type divisor = -1LL;
		const long long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%lld /= %lld) -> %lld\n", LINE, before, (long long) divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MIN;
		const long long divisor = -1LL;
		const long long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%lld /= %lld) -> %lld\n", LINE, before, divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = 1LL;
		const safer_llong_type divisor = 0LL;
		const long long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%lld /= %lld) -> %lld\n", LINE, before, (long long) divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = 1LL;
		const long long divisor = 0LL;
		const long long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%lld /= %lld) -> %lld\n", LINE, before, divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_llong_type division error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_ullong_type_division_error_tests, "safer_ullong_type division error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_ullong_type var1 = 0ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %llu / %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 0ULL;
		const unsigned long long var2 = 0ULL;
		const safer_ullong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %llu / %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = 0ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %llu / %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 1ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %llu / %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 1ULL;
		const unsigned long long var2 = 0ULL;
		const safer_ullong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %llu / %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = 1ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 / var2;
		fprintf(output_file, "Line %d: %llu / %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = 1ULL;
		const safer_ullong_type divisor = 0ULL;
		const unsigned long long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%llu /= %llu) -> %llu\n", LINE, before, (unsigned long long) divisor, (unsigned long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = 1ULL;
		const unsigned long long divisor = 0ULL;
		const unsigned long long before = var;
		var /= divisor;
		fprintf(output_file, "Line %d: (%llu /= %llu) -> %llu\n", LINE, before, divisor, (unsigned long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_ullong_type division error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_integer_type_division_tests, "safer integer type division tests")
{
	TRY {
		const safer_schar_type scvar = -128;
		const safer_uchar_type ucvar = 255U;
		const safer_short_type svar = -32768;
		const safer_ushort_type usvar = 65535U;
		const safer_int_type ivar = -2147483647 - 1;
		const safer_uint_type uvar = 4294967295U;
		safer_int_type iresult = 0;
		iresult = scvar / 2;
		ASSERT_EQUAL(iresult, -64);
		iresult /= 2;
		ASSERT_EQUAL(iresult, -32);
		iresult = ucvar / 2;
		ASSERT_EQUAL(iresult, 127);
		iresult /= 2;
		ASSERT_EQUAL(iresult, 63);
		iresult = svar / 2;
		ASSERT_EQUAL(iresult, -16384);
		iresult /= 2;
		ASSERT_EQUAL(iresult, -8192);
		iresult = usvar / 2;
		ASSERT_EQUAL(iresult, 32767);
		iresult /= 2;
		ASSERT_EQUAL(iresult, 16383);
		iresult = ivar / 2;
		ASSERT_EQUAL(iresult, -1073741824);
		iresult /= 2;
		ASSERT_EQUAL(iresult, -536870912);
		safer_uint_type uresult = uvar / 2U;
		ASSERT_UINT_EQUAL(uresult, 2147483647U);
		uresult /= 2U;
		ASSERT_UINT_EQUAL(uresult, 1073741823U);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

/* Remainder tests */
TEST(safer_int_type_remainder_error_tests, "safer_int_type remainder error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const int var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = -1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 0;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 0;
		const int var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = 0;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = 1;
		const int var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = 1;
		const safer_int_type var2 = 0;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = INT_MIN;
		const int var2 = -1;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, (int) var1, var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = INT_MIN;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 % var2;
		fprintf(output_file, "Line %d: %d %% %d == %d\n", LINE, var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MIN;
		const safer_int_type divisor = -1;
		const int before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%d %%= %d) -> %d\n", LINE, before, (int) divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = INT_MIN;
		const int divisor = -1;
		const int before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%d %%= %d) -> %d\n", LINE, before, divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const safer_int_type divisor = 0;
		const int before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%d %%= %d) -> %d\n", LINE, before, (int) divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const int divisor = 0;
		const int before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%d %%= %d) -> %d\n", LINE, before, divisor, (int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_int_type remainder error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_uint_type_remainder_error_tests, "safer_uint_type remainder error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_uint_type var1 = 0U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 % var2;
		fprintf(output_file, "Line %d: %u %% %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 0U;
		const unsigned int var2 = 0U;
		const safer_uint_type result = var1 % var2;
		fprintf(output_file, "Line %d: %u %% %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 0U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 % var2;
		fprintf(output_file, "Line %d: %u %% %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 1U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 % var2;
		fprintf(output_file, "Line %d: %u %% %u == %u\n", LINE, (unsigned int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 1U;
		const unsigned int var2 = 0U;
		const safer_uint_type result = var1 % var2;
		fprintf(output_file, "Line %d: %u %% %u == %u\n", LINE, (unsigned int) var1, var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 1U;
		const safer_uint_type var2 = 0U;
		const safer_uint_type result = var1 % var2;
		fprintf(output_file, "Line %d: %u %% %u == %u\n", LINE, var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = 1U;
		const safer_uint_type divisor = 0U;
		const unsigned int before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: %u %%= %u == %u\n", LINE, before, (unsigned int) divisor, (unsigned int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_uint_type var = 1U;
		const unsigned int divisor = 0U;
		const unsigned int before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: %u %%= %u == %u\n", LINE, before, divisor, (unsigned int) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_uint_type remainder error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_long_type_remainder_error_tests, "safer_long_type remainder error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_long_type var1 = -1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = -1L;
		const long var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = -1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 0L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 0L;
		const long var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = 0L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = 1L;
		const long var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = 1L;
		const safer_long_type var2 = 0L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const safer_long_type var2 = -1L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_long_type var1 = LONG_MIN;
		const long var2 = -1L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, (long) var1, var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long var1 = LONG_MIN;
		const safer_long_type var2 = -1L;
		const safer_long_type result = var1 % var2;
		fprintf(output_file, "Line %d: %ld %% %ld == %ld\n", LINE, var1, (long) var2, (long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MIN;
		const safer_long_type divisor = -1L;
		const long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%ld %%= %ld) -> %ld\n", LINE, before, (long) divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = LONG_MIN;
		const long divisor = -1L;
		const long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%ld %%= %ld) -> %ld\n", LINE, before, divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = 1L;
		const safer_long_type divisor = 0L;
		const long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%ld %%= %ld) -> %ld\n", LINE, before, (long) divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_long_type var = 1L;
		const long divisor = 0L;
		const long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%ld %%= %ld) -> %ld\n", LINE, before, divisor, (long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_long_type remainder error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_ulong_type_remainder_error_tests, "safer_ulong_type remainder error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_ulong_type var1 = 0UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lu %% %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 0UL;
		const unsigned long var2 = 0UL;
		const safer_ulong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lu %% %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = 0UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lu %% %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 1UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lu %% %lu == %lu\n", LINE, (unsigned long) var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ulong_type var1 = 1UL;
		const unsigned long var2 = 0UL;
		const safer_ulong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lu %% %lu == %lu\n", LINE, (unsigned long) var1, var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long var1 = 1UL;
		const safer_ulong_type var2 = 0UL;
		const safer_ulong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lu %% %lu == %lu\n", LINE, var1, (unsigned long) var2, (unsigned long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = 1UL;
		const safer_ulong_type divisor = 0UL;
		const unsigned long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%lu %%= %lu) -> %lu\n", LINE, before, (unsigned long) divisor, (unsigned long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ulong_type var = 1UL;
		const unsigned long divisor = 0UL;
		const unsigned long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%lu %%= %lu) -> %lu\n", LINE, before, divisor, (unsigned long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_ulong_type remainder error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_llong_type_remainder_error_tests, "safer_llong_type remainder error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_llong_type var1 = -1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = -1LL;
		const long long var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = -1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 0LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 0LL;
		const long long var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = 0LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = 1LL;
		const long long var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = 1LL;
		const safer_llong_type var2 = 0LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const safer_llong_type var2 = -1LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_llong_type var1 = LLONG_MIN;
		const long long var2 = -1LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, (long long) var1, var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const long long var1 = LLONG_MIN;
		const safer_llong_type var2 = -1LL;
		const safer_llong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %lld %% %lld == %lld\n", LINE, var1, (long long) var2, (long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MIN;
		const safer_llong_type divisor = -1LL;
		const long long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%lld %%= %lld) -> %lld\n", LINE, before, (long long) divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = LLONG_MIN;
		const long long divisor = -1LL;
		const long long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%lld %%= %lld) -> %lld\n", LINE, before, divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = 1LL;
		const safer_llong_type divisor = 0LL;
		const long long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%lld %%= %lld) -> %lld\n", LINE, before, (long long) divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_llong_type var = 1LL;
		const long long divisor = 0LL;
		const long long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%lld %%= %lld) -> %lld\n", LINE, before, divisor, (long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_llong_type remainder error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_ullong_type_remainder_error_tests, "safer_ullong_type remainder error tests")
{
#if defined(__cplusplus) &&  !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)
	TRY {
		const safer_ullong_type var1 = 0ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %llu %% %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 0ULL;
		const unsigned long long var2 = 0ULL;
		const safer_ullong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %llu %% %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = 0ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %llu %% %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 1ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %llu %% %llu == %llu\n", LINE, (unsigned long long) var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_ullong_type var1 = 1ULL;
		const unsigned long long var2 = 0ULL;
		const safer_ullong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %llu %% %llu == %llu\n", LINE, (unsigned long long) var1, var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned long long var1 = 1ULL;
		const safer_ullong_type var2 = 0ULL;
		const safer_ullong_type result = var1 % var2;
		fprintf(output_file, "Line %d: %llu %% %llu == %llu\n", LINE, var1, (unsigned long long) var2, (unsigned long long) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = 1ULL;
		const safer_ullong_type divisor = 0ULL;
		const unsigned long long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%llu %%= %llu) -> %llu\n", LINE, before, (unsigned long long) divisor, (unsigned long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_ullong_type var = 1ULL;
		const unsigned long long divisor = 0ULL;
		const unsigned long long before = var;
		var %= divisor;
		fprintf(output_file, "Line %d: (%llu %%= %llu) -> %llu\n", LINE, before, divisor, (unsigned long long) var);
	} CATCH (std::exception& ) {
		ASSERT(safer_integer_type_exception_thrown);
	}
#else
	fprintf(output_file, "Line %d: Skipping safer_ullong_type remainder error tests when built-in integer types are used.\n", LINE);
#endif
}

TEST(safer_integer_type_remainder_tests, "safer integer type remainder tests")
{
	TRY {
		const safer_schar_type scvar = -128;
		const safer_uchar_type ucvar = 255U;
		const safer_short_type svar = -32768;
		const safer_ushort_type usvar = 65535U;
		const safer_int_type ivar = -2147483647 - 1;
		const safer_uint_type uvar = 4294967295U;
		safer_int_type iresult = 0;
		iresult = scvar % 2;
		ASSERT_EQUAL(iresult, 0);
		iresult %= 2;
		ASSERT_EQUAL(iresult, 0);
		iresult = ucvar % 2;
		ASSERT_EQUAL(iresult, 1);
		iresult %= 2;
		ASSERT_EQUAL(iresult, 1);
		iresult = svar % 2;
		ASSERT_EQUAL(iresult, 0);
		iresult %= 2;
		ASSERT_EQUAL(iresult, 0);
		iresult = usvar % 2;
		ASSERT_EQUAL(iresult, 1);
		iresult %= 2;
		ASSERT_EQUAL(iresult, 1);
		iresult = ivar % 2;
		ASSERT_EQUAL(iresult, 0);
		iresult %= 2;
		ASSERT_EQUAL(iresult, 0);
		safer_uint_type uresult = uvar % 2U;
		ASSERT_UINT_EQUAL(uresult, 1U);
		uresult %= 2U;
		ASSERT_UINT_EQUAL(uresult, 1U);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

/* Comparison tests */
TEST(safer_integer_type_comparison_error_tests, "safer_integer_type comparison error tests")
{
	/* equality comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const Boolean_type result = (var1 == var2);
		fprintf(output_file, "Line %d: (%d == %u) == %s\n", LINE, (int) var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const unsigned int var2 = UINT_MAX;
		const Boolean_type result = (var1 == var2);
		fprintf(output_file, "Line %d: (%d == %u) == %s\n", LINE, (int) var1, var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const Boolean_type result = (var1 == var2);
		fprintf(output_file, "Line %d: (%d == %u) == %s\n", LINE, var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	/* inequality comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const Boolean_type result = (var1 != var2);
		fprintf(output_file, "Line %d: (%d != %u) == %s\n", LINE, (int) var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const unsigned int var2 = UINT_MAX;
		const Boolean_type result = (var1 != var2);
		fprintf(output_file, "Line %d: (%d != %u) == %s\n", LINE, (int) var1, var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const Boolean_type result = (var1 != var2);
		fprintf(output_file, "Line %d: (%d != %u) == %s\n", LINE, var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	/* less than comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = 1U;
		const Boolean_type result = (var1 < var2);
		fprintf(output_file, "Line %d: (%d < %u) == %s\n", LINE, (int) var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const unsigned int var2 = 1U;
		const Boolean_type result = (var1 < var2);
		fprintf(output_file, "Line %d: (%d < %u) == %s\n", LINE, (int) var1, var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = -1;
		const safer_uint_type var2 = 1U;
		const Boolean_type result = (var1 < var2);
		fprintf(output_file, "Line %d: (%d < %u) == %s\n", LINE, var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	/* greater than or equal to comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = 1U;
		const Boolean_type result = (var1 <= var2);
		fprintf(output_file, "Line %d: (%d <= %u) == %s\n", LINE, (int) var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const unsigned int var2 = 1U;
		const Boolean_type result = (var1 <= var2);
		fprintf(output_file, "Line %d: (%d <= %u) == %s\n", LINE, (int) var1, var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const int var1 = -1;
		const safer_uint_type var2 = 1U;
		const Boolean_type result = (var1 <= var2);
		fprintf(output_file, "Line %d: (%d <= %u) == %s\n", LINE, var1, (unsigned int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	/* greater than comparison */
	TRY {
		const safer_uint_type var1 = 1U;
		const safer_int_type var2 = -1;
		const Boolean_type result = (var1 > var2);
		fprintf(output_file, "Line %d: (%u > %d) == %s\n", LINE, (unsigned int) var1, (int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 1U;
		const int var2 = -1;
		const Boolean_type result = (var1 > var2);
		fprintf(output_file, "Line %d: (%u > %d) == %s\n", LINE, (unsigned int) var1, var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 1U;
		const safer_int_type var2 = -1;
		const Boolean_type result = (var1 > var2);
		fprintf(output_file, "Line %d: (%u > %d) == %s\n", LINE, var1, (int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	/* greater than comparison */
	TRY {
		const safer_uint_type var1 = 1U;
		const safer_int_type var2 = -1;
		const Boolean_type result = (var1 >= var2);
		fprintf(output_file, "Line %d: (%u >= %d) == %s\n", LINE, (unsigned int) var1, (int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = 1U;
		const int var2 = -1;
		const Boolean_type result = (var1 >= var2);
		fprintf(output_file, "Line %d: (%u >= %d) == %s\n", LINE, (unsigned int) var1, var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const unsigned int var1 = 1U;
		const safer_int_type var2 = -1;
		const Boolean_type result = (var1 >= var2);
		fprintf(output_file, "Line %d: (%u >= %d) == %s\n", LINE, var1, (int) var2, (result ? "true" : "false"));
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_comparison_tests, "safer_integer_type comparison tests")
{
	/* equality comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = -1;
		ASSERT(var1 == var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const safer_int_type var1 = 0;
		const int var2 = 0;
		ASSERT(var1 == var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const int var1 = 1;
		const safer_int_type var2 = 1;
		ASSERT(var1 == var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	/* inequality comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = 1;
		ASSERT(var1 != var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const safer_int_type var1 = -1;
		const int var2 = 1;
		ASSERT(var1 != var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const int var1 = -1;
		const safer_int_type var2 = 1;
		ASSERT(var1 != var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	/* less than comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = 1;
		ASSERT(var1 < var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const safer_int_type var1 = -1;
		const int var2 = 1;
		ASSERT(var1 < var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const int var1 = -1;
		const safer_int_type var2 = 1;
		ASSERT(var1 < var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	/* greater than or equal to comparison */
	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = 1;
		ASSERT(var1 <= var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const safer_int_type var1 = -1;
		const int var2 = 1;
		ASSERT(var1 <= var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const int var1 = -1;
		const safer_int_type var2 = 1;
		ASSERT(var1 <= var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	/* greater than comparison */
	TRY {
		const safer_int_type var1 = 1;
		const safer_int_type var2 = -1;
		ASSERT(var1 > var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const safer_int_type var1 = 1;
		const int var2 = -1;
		ASSERT(var1 > var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const int var1 = 1;
		const safer_int_type var2 = -1;
		ASSERT(var1 > var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	/* greater than comparison */
	TRY {
		const safer_int_type var1 = 1;
		const safer_int_type var2 = -1;
		ASSERT(var1 >= var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const safer_int_type var1 = 1;
		const int var2 = -1;
		ASSERT(var1 >= var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		const int var1 = 1;
		const safer_int_type var2 = -1;
		ASSERT(var1 >= var2);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_integer_type_bitwise_and_error_tests, "safer integer type bitwise AND error tests")
{
	TRY {
		const safer_short_type var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const safer_uint_type result = var1 & var2;
		fprintf(output_file, "Line %d: %d & %u == %u\n", LINE, (int) var1, (unsigned int) var2, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const safer_int_type result = var1 & var2;
		fprintf(output_file, "Line %d: %d & %u == %d\n", LINE, (int) var1, (unsigned int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 & var2;
		fprintf(output_file, "Line %d: %u & %d == %d\n", LINE, (unsigned int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 & var2;
		fprintf(output_file, "Line %d: %d & %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_bitwise_and_tests, "safer integer type bitwise AND tests")
{
	TRY {
		safer_int_type var1 = 5;
		safer_int_type var2 = 3;
		safer_int_type result = var1 & var2;
		ASSERT_EQUAL(result, 1);
		var1 = 0;
		var2 = 0;
		result = var1 & var2;
		ASSERT_EQUAL(result, 0);
		var1 = 0;
		var2 = INT_MAX;
		result = var1 & var2;
		ASSERT_EQUAL(result, 0);
		var1 = INT_MAX;
		var2 = 0;
		result = var1 & var2;
		ASSERT_EQUAL(result, 0);
		var1 = INT_MAX;
		var2 = INT_MAX;
		result = var1 & var2;
		ASSERT_EQUAL(result, INT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uint_type var1 = 5U;
		safer_uint_type var2 = 3U;
		safer_uint_type result = var1 & var2;
		ASSERT_UINT_EQUAL(result, 1U);
		var1 = 0U;
		var2 = 0U;
		result = var1 & var2;
		ASSERT_UINT_EQUAL(result, 0U);
		var1 = 0U;
		var2 = UINT_MAX;
		result = var1 & var2;
		ASSERT_UINT_EQUAL(result, 0U);
		var1 = UINT_MAX;
		var2 = 0U;
		result = var1 & var2;
		ASSERT_UINT_EQUAL(result, 0U);
		var1 = UINT_MAX;
		var2 = UINT_MAX;
		result = var1 & var2;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_short_type var1 = 5;
		safer_int_type var2 = 3;
		safer_int_type result = var1 & var2;
		ASSERT_EQUAL(result, 1);
		var1 = SHRT_MAX;
		var2 = INT_MAX;
		result = var1 & var2;
		ASSERT_EQUAL(result, SHRT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ushort_type var1 = 5U;
		safer_int_type var2 = 3;
		safer_int_type result = var1 & var2;
		ASSERT_EQUAL(result, 1);
		var1 = USHRT_MAX;
		var2 = INT_MAX;
		result = var1 & var2;
		ASSERT_EQUAL(result, USHRT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_integer_type_bitwise_or_error_tests, "safer integer type bitwise OR error tests")
{
	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const safer_int_type result = var1 | var2;
		fprintf(output_file, "Line %d: %d | %u == %d\n", LINE, (int) var1, (unsigned int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 | var2;
		fprintf(output_file, "Line %d: %u | %d == %d\n", LINE, (unsigned int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 | var2;
		fprintf(output_file, "Line %d: %d | %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_bitwise_or_tests, "safer integer type bitwise OR tests")
{
	TRY {
		safer_int_type var1 = 5;
		safer_int_type var2 = 3;
		safer_int_type result = var1 | var2;
		ASSERT_EQUAL(result, 7);
		var1 = 0;
		var2 = 0;
		result = var1 | var2;
		ASSERT_EQUAL(result, 0);
		var1 = 0;
		var2 = INT_MAX;
		result = var1 | var2;
		ASSERT_EQUAL(result, INT_MAX);
		var1 = INT_MAX;
		var2 = 0;
		result = var1 | var2;
		ASSERT_EQUAL(result, INT_MAX);
		var1 = INT_MAX;
		var2 = INT_MAX;
		result = var1 | var2;
		ASSERT_EQUAL(result, INT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uint_type var1 = 5U;
		safer_uint_type var2 = 3U;
		safer_uint_type result = var1 | var2;
		ASSERT_UINT_EQUAL(result, 7U);
		var1 = 0U;
		var2 = 0U;
		result = var1 | var2;
		ASSERT_UINT_EQUAL(result, 0U);
		var1 = 0U;
		var2 = UINT_MAX;
		result = var1 | var2;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
		var1 = UINT_MAX;
		var2 = 0U;
		result = var1 | var2;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
		var1 = UINT_MAX;
		var2 = UINT_MAX;
		result = var1 | var2;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_short_type var1 = 5;
		safer_int_type var2 = 3;
		safer_int_type result = var1 | var2;
		ASSERT_EQUAL(result, 7);
		var1 = SHRT_MAX;
		var2 = INT_MAX;
		result = var1 | var2;
		ASSERT_EQUAL(result, INT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ushort_type var1 = 5U;
		safer_int_type var2 = 3;
		safer_int_type result = var1 | var2;
		ASSERT_EQUAL(result, 7);
		var1 = USHRT_MAX;
		var2 = INT_MAX;
		result = var1 | var2;
		ASSERT_EQUAL(result, INT_MAX);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_integer_type_bitwise_xor_error_tests, "safer integer type bitwise XOR error tests")
{
	TRY {
		const safer_int_type var1 = -1;
		const safer_uint_type var2 = UINT_MAX;
		const safer_int_type result = var1 ^ var2;
		fprintf(output_file, "Line %d: %d ^ %u == %d\n", LINE, (int) var1, (unsigned int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var1 = UINT_MAX;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 ^ var2;
		fprintf(output_file, "Line %d: %u ^ %d == %d\n", LINE, (unsigned int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var1 = -1;
		const safer_int_type var2 = -1;
		const safer_int_type result = var1 ^ var2;
		fprintf(output_file, "Line %d: %d ^ %d == %d\n", LINE, (int) var1, (int) var2, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_bitwise_xor_tests, "safer integer type bitwise XOR tests")
{
	TRY {
		safer_int_type var1 = 5;
		safer_int_type var2 = 3;
		safer_int_type result = var1 ^ var2;
		ASSERT_EQUAL(result, 6);
		var1 = 0;
		var2 = 0;
		result = var1 ^ var2;
		ASSERT_EQUAL(result, 0);
		var1 = 0;
		var2 = INT_MAX;
		result = var1 ^ var2;
		ASSERT_EQUAL(result, INT_MAX);
		var1 = INT_MAX;
		var2 = 0;
		result = var1 ^ var2;
		ASSERT_EQUAL(result, INT_MAX);
		var1 = INT_MAX;
		var2 = INT_MAX;
		result = var1 ^ var2;
		ASSERT_EQUAL(result, 0);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uint_type var1 = 5U;
		safer_uint_type var2 = 3U;
		safer_uint_type result = var1 ^ var2;
		ASSERT_UINT_EQUAL(result, 6U);
		var1 = 0U;
		var2 = 0U;
		result = var1 ^ var2;
		ASSERT_UINT_EQUAL(result, 0U);
		var1 = 0U;
		var2 = UINT_MAX;
		result = var1 ^ var2;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
		var1 = UINT_MAX;
		var2 = 0U;
		result = var1 ^ var2;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
		var1 = UINT_MAX;
		var2 = UINT_MAX;
		result = var1 ^ var2;
		ASSERT_UINT_EQUAL(result, 0U);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_short_type var1 = 5;
		safer_int_type var2 = 3;
		safer_int_type result = var1 ^ var2;
		ASSERT_EQUAL(result, 6);
		var1 = SHRT_MAX;
		var2 = INT_MAX;
		result = var1 ^ var2;
		ASSERT_EQUAL(result, 0x7FFF8000);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ushort_type var1 = 5U;
		safer_int_type var2 = 3;
		safer_int_type result = var1 ^ var2;
		ASSERT_EQUAL(result, 6);
		var1 = USHRT_MAX;
		var2 = INT_MAX;
		result = var1 ^ var2;
		ASSERT_EQUAL(result, 0x7FFF0000);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_integer_type_bitwise_not_error_tests, "safer integer type bitwise NOT error tests")
{
	TRY {
		const safer_int_type var = -1;
		const safer_int_type result = ~var;
		fprintf(output_file, "Line %d: ~%d == %d\n", LINE, (int) var, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var = INT_MIN;
		const safer_int_type result = ~var;
		fprintf(output_file, "Line %d: ~%d == %d\n", LINE, (int) var, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_bitwise_not_tests, "safer integer type bitwise NOT tests")
{
	TRY {
		safer_int_type var = 0;
		safer_int_type result = ~var;
		ASSERT_EQUAL(result, -1);
		var = INT_MAX;
		result = ~var;
		ASSERT_EQUAL(result, INT_MIN);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uint_type var = 0U;
		safer_uint_type result = ~var;
		ASSERT_UINT_EQUAL(result, UINT_MAX);
		var = UINT_MAX;
		result = ~var;
		ASSERT_UINT_EQUAL(result, 0U);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_integer_type_bitwise_shift_error_tests, "safer integer type bitwise shift error tests")
{
	TRY {
		const safer_int_type var = -1;
		const safer_int_type result = var << -1;
		fprintf(output_file, "Line %d: %d << -1 == %d\n", LINE, (int) var, (int) result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var = 1;
		const safer_int_type result = var << -1;
		fprintf(output_file, "Line %d: %d << -1 == %d\n", LINE, (int) var, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var = 1;
		const safer_int_type result = var << 32;
		fprintf(output_file, "Line %d: %d << 32 == %d\n", LINE, (int) var, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var = -1;
		const safer_int_type result = var >> -1;
		fprintf(output_file, "Line %d: %d >> -1 == %d\n", LINE, (int)var, (int)result);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var = 1;
		const safer_int_type result = var >> -1;
		fprintf(output_file, "Line %d: %d >> -1 == %d\n", LINE, (int) var, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_int_type var = 1;
		const safer_int_type result = var >> 32;
		fprintf(output_file, "Line %d: %d >> 32 == %d\n", LINE, (int) var, (int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var = 1U;
		const safer_uint_type result = var << -1;
		fprintf(output_file, "Line %d: %u << -1 == %u\n", LINE, (unsigned int) var, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var = 1U;
		const safer_uint_type result = var << 32U;
		fprintf(output_file, "Line %d: %u << 32 == %u\n", LINE, (unsigned int) var, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var = 1U;
		const safer_uint_type result = var >> -1;
		fprintf(output_file, "Line %d: %u >> -1 == %u\n", LINE, (unsigned int) var, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		const safer_uint_type var = 1U;
		const safer_uint_type result = var >> 32U;
		fprintf(output_file, "Line %d: %u >> 32 == %u\n", LINE, (unsigned int) var, (unsigned int) result);
	} CATCH(std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = -1;
		const int before = var;
		var <<= -1;
		fprintf(output_file, "Line %d: (%d <<= -1) -> %d\n", LINE, before, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const int before = var;
		var <<= -1;
		fprintf(output_file, "Line %d: (%d <<= -1) -> %d\n", LINE, before, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const int before = var;
		var <<= 32;
		fprintf(output_file, "Line %d: (%d <<= 32) -> %d\n", LINE, before, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = -1;
		const int before = var;
		var >>= -1;
		fprintf(output_file, "Line %d: (%d >>= -1) -> %d\n", LINE, before, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const int before = var;
		var >>= -1;
		fprintf(output_file, "Line %d: (%d >>= -1) -> %d\n", LINE, before, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}

	TRY {
		safer_int_type var = 1;
		const int before = var;
		var >>= 32;
		fprintf(output_file, "Line %d: (%d >>= -1) -> %d\n", LINE, before, (int) var);
	} CATCH (std::exception&) {
		ASSERT(safer_integer_type_exception_thrown);
	}
}

TEST(safer_integer_type_bitwise_shift_tests, "safer integer type bitwise shift tests")
{
	TRY {
		safer_int_type var = 1;
		safer_int_type result = var << 0;
		ASSERT_EQUAL(result, 1);
		var = 1;
		result = var << 1;
		ASSERT_EQUAL(result, 2);
		var = 1;
		result = var << 31;
		ASSERT_EQUAL(result, INT_MIN);
		var = INT_MAX;
		result = var >> 0;
		ASSERT_EQUAL(result, INT_MAX);
		var = INT_MAX;
		result = var >> 30;
		ASSERT_EQUAL(result, 1);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uint_type var = 1U;
		safer_uint_type result = var << 0U;
		ASSERT_UINT_EQUAL(result, 1U);
		var = 1U;
		result = var << 1U;
		ASSERT_UINT_EQUAL(result, 2U);
		result <<= 1U;
		ASSERT_UINT_EQUAL(result, 4U);
		var = 1U;
		result = var << 31U;
		ASSERT_UINT_EQUAL(result, 0x80000000U);
		result <<= 1U;
		ASSERT_UINT_EQUAL(result, 0U);
		var = UINT_MAX;
		result = var >> 1U;
		ASSERT_UINT_EQUAL(result, 0x7FFFFFFFU);
		result >>= 1U;
		ASSERT_UINT_EQUAL(result, 0x3FFFFFFFU);
		var = UINT_MAX;
		result = var >> 31U;
		ASSERT_UINT_EQUAL(result, 1U);
		result >>= 1U;
		ASSERT_UINT_EQUAL(result, 0U);
	} CATCH(std::exception&) {
		ASSERT(Boolean_false);
	}
}

TEST(safer_integer_type_logical_not_tests, "safer integer type logical NOT tests")
{
	TRY {
		safer_bool_type var = Boolean_false;
		ASSERT_EQUAL(!var, Boolean_true);
		var = Boolean_true;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_char_type var = 0;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1;
		ASSERT_EQUAL(!var, Boolean_false);
#if (CHAR_MIN != 0)
		var = SAFER_CHAR_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
#endif
		var = SAFER_CHAR_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_schar_type var = 0;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_SCHAR_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_SCHAR_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uchar_type var = 0U;
		ASSERT_EQUAL(!var, Boolean_true);
		var = 1U;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_UCHAR_MIN;
		ASSERT_EQUAL(!var, Boolean_true);
		var = SAFER_UCHAR_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_short_type var = 0;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_SHORT_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_SHORT_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ushort_type var = 0U;
		ASSERT_EQUAL(!var, Boolean_true);
		var = 1U;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_USHORT_MIN;
		ASSERT_EQUAL(!var, Boolean_true);
		var = SAFER_USHORT_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_int_type var = 0;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_INT_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_INT_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_uint_type var = 0U;
		ASSERT_EQUAL(!var, Boolean_true);
		var = 1U;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_UINT_MIN;
		ASSERT_EQUAL(!var, Boolean_true);
		var = SAFER_INT_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_long_type var = 0L;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1L;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1L;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_LONG_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_LONG_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ulong_type var = 0UL;
		ASSERT_EQUAL(!var, Boolean_true);
		var = 1UL;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_ULONG_MIN;
		ASSERT_EQUAL(!var, Boolean_true);
		var = SAFER_ULONG_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_llong_type var = 0LL;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1LL;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1LL;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_LLONG_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_LLONG_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ullong_type var = 0ULL;
		ASSERT_EQUAL(!var, Boolean_true);
		var = 1ULL;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_ULLONG_MIN;
		ASSERT_EQUAL(!var, Boolean_true);
		var = SAFER_ULLONG_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_ptrdiff_type var = 0;
		ASSERT_EQUAL(!var, Boolean_true);
		var = -1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = 1;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_PTRDIFF_MIN;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_PTRDIFF_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}

	TRY {
		safer_size_type var = 0U;
		ASSERT_EQUAL(!var, Boolean_true);
		var = 1U;
		ASSERT_EQUAL(!var, Boolean_false);
		var = SAFER_SIZE_MIN;
		ASSERT_EQUAL(!var, Boolean_true);
		var = SAFER_SIZE_MAX;
		ASSERT_EQUAL(!var, Boolean_false);
	} CATCH (std::exception&) {
		ASSERT(Boolean_false);
	}
}

static void run_safer_integer_type_tests(int argc, const char **argv)
{
	const char *language = 
#ifdef __cplusplus
		"C++"
#else
		"C"
#endif
		;
	DEFINE_LIST_OF_TESTS(tests) {
		safer_integer_is_builtin_integer_type_tests,
		safer_integer_type_signedness_tests,
		safer_integer_type_min_max_tests,
		safer_integer_type_uninitialized_variable_tests,
		safer_bool_type_conversion_tests,
		safer_char_type_conversion_error_tests,
		safer_char_type_conversion_tests,
		safer_schar_type_conversion_error_tests,
		safer_schar_type_conversion_tests,
		safer_uchar_type_conversion_error_tests,
		safer_uchar_type_conversion_tests,
		safer_short_type_conversion_error_tests,
		safer_short_type_conversion_tests,
		safer_ushort_type_conversion_error_tests,
		safer_ushort_type_conversion_tests,
		safer_int_type_conversion_error_tests,
		safer_int_type_conversion_tests,
		safer_uint_type_conversion_error_tests,
		safer_uint_type_conversion_tests,
		safer_long_type_conversion_error_tests,
		safer_long_type_conversion_tests,
		safer_ulong_type_conversion_error_tests,
		safer_ulong_type_conversion_tests,
		safer_schar_type_increment_error_tests,
		safer_uchar_type_increment_error_tests,
		safer_short_type_increment_error_tests,
		safer_ushort_type_increment_error_tests,
		safer_int_type_increment_error_tests,
		safer_uint_type_increment_error_tests,
		safer_long_type_increment_error_tests,
		safer_ulong_type_increment_error_tests,
		safer_llong_type_increment_error_tests,
		safer_ullong_type_increment_error_tests,
		safer_schar_type_decrement_error_tests,
		safer_uchar_type_decrement_error_tests,
		safer_short_type_decrement_error_tests,
		safer_ushort_type_decrement_error_tests,
		safer_int_type_decrement_error_tests,
		safer_uint_type_decrement_error_tests,
		safer_long_type_decrement_error_tests,
		safer_ulong_type_decrement_error_tests,
		safer_llong_type_decrement_error_tests,
		safer_ullong_type_decrement_error_tests,
		safer_int_type_addition_error_tests,
		safer_uint_type_addition_error_tests,
		safer_long_type_addition_error_tests,
		safer_ulong_type_addition_error_tests,
		safer_llong_type_addition_error_tests,
		safer_ullong_type_addition_error_tests,
		safer_integer_type_addition_tests,
		safer_int_type_subtraction_error_tests,
		safer_uint_type_subtraction_error_tests,
		safer_long_type_subtraction_error_tests,
		safer_ulong_type_subtraction_error_tests,
		safer_llong_type_subtraction_error_tests,
		safer_ullong_type_subtraction_error_tests,
		safer_integer_type_subtraction_tests,
		safer_int_type_multiplication_error_tests,
		safer_uint_type_multiplication_error_tests,
		safer_long_type_multiplication_error_tests,
		safer_ulong_type_multiplication_error_tests,
		safer_llong_type_multiplication_error_tests,
		safer_ullong_type_multiplication_error_tests,
		safer_integer_type_multiplication_tests,
		safer_int_type_division_error_tests,
		safer_uint_type_division_error_tests,
		safer_long_type_division_error_tests,
		safer_ulong_type_division_error_tests,
		safer_llong_type_division_error_tests,
		safer_ullong_type_division_error_tests,
		safer_integer_type_division_tests,
		safer_int_type_remainder_error_tests,
		safer_uint_type_remainder_error_tests,
		safer_long_type_remainder_error_tests,
		safer_ulong_type_remainder_error_tests,
		safer_llong_type_remainder_error_tests,
		safer_ullong_type_remainder_error_tests,
		safer_integer_type_remainder_tests,
		safer_integer_type_comparison_error_tests,
		safer_integer_type_comparison_tests,
		safer_integer_type_bitwise_and_error_tests,
		safer_integer_type_bitwise_and_tests,
		safer_integer_type_bitwise_or_error_tests,
		safer_integer_type_bitwise_or_tests,
		safer_integer_type_bitwise_xor_error_tests,
		safer_integer_type_bitwise_xor_tests,
		safer_integer_type_bitwise_not_error_tests,
		safer_integer_type_bitwise_not_tests,
		safer_integer_type_bitwise_shift_error_tests,
		safer_integer_type_bitwise_shift_tests,
		safer_integer_type_logical_not_tests
	};

	if (argc >= 2 && argv != NULL && argv[1] != NULL) {
		output_file = fopen(argv[1], "w");
	} else {
		output_file = stdout;
	}

	if (output_file != NULL) {
		SET_OUTPUT_FILE(output_file);
#ifdef __cplusplus
		safer_integer::set_output_file_pointer(output_file);
#endif
		fprintf(output_file, "%s\n", __FILE__);
		fprintf(output_file, "The tests were compiled as %s code.\n", language);
		RUN_TESTS(tests);
		PRINT_TEST_STATISTICS(tests);
	} else {
		printf("%s\n", strerror(errno));
	}
}

#undef LINE

#endif /* include guard */
