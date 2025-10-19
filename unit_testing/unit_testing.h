#ifndef UNIT_TESTING_LIBRARY_H
#define UNIT_TESTING_LIBRARY_H

#include "Boolean_type.h"
#include "macro_stringify.h"
#include "sizeof_array.h"

#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#define UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS 0
#else
#if defined(__STDC_VERSION__) && (__STDC_VERSION__+ >= 199901L)
#define UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS 1
#else
#define UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS 0
#endif
#endif

typedef struct testing_library_data_type
{
	size_t number_of_false_assertions;
	size_t number_of_true_assertions;
	Boolean_type should_print_true_assertions;
} testing_library_data_type;

typedef struct testing_library_test_type
{
	void(*func_ptr)(void);
	const char *id;
	const char *name_or_description;
	size_t run_count;
	size_t sequence_number;
	size_t number_of_false_assertions;
	size_t number_of_true_assertions;
} testing_library_test_type;

typedef enum testing_library_test_result_type
{
	test_result_test_passes = 0,
	test_result_test_fails = 1,
	test_result_test_has_no_assertion = 2
} testing_library_test_result_type;

typedef struct testing_library_test_statistics_type {
	size_t number_of_duplicate_tests;
	size_t number_of_failed_tests;
	size_t number_of_passed_tests;
	size_t number_of_tests_without_assertion;
	size_t number_of_false_assertions;
	size_t number_of_true_assertions;
} testing_library_test_statistics_type;

void testing_library_set_file(FILE *pfile);
FILE *testing_library_get_file(void);
void testing_library_set_test_status_passed_text(const char *text);
void testing_library_set_test_status_failed_text(const char *text);
void testing_library_set_test_without_assertion_warning_text(const char *text);
void testing_library_assert(int line_number, Boolean_type condition, const char *message, testing_library_data_type *pdata);
void testing_library_run_test(size_t sequence_number, testing_library_test_type *ptest, testing_library_data_type *pdata);
void testing_library_run_tests(testing_library_test_type * const *ptests, size_t number_of_tests, testing_library_data_type *pdata);
testing_library_test_result_type testing_library_evaluate_test_result(const testing_library_test_type *ptest);
testing_library_test_statistics_type testing_library_determine_test_statistics(const testing_library_test_type * const *ptest, size_t number_of_tests);
void testing_library_print_test_statistics(const testing_library_test_statistics_type *pstat);
void testing_library_print_file_name(const char *file_name);
void testing_library_print_LHS_and_RHS_as_signed_integers(int LHS, int RHS);
void testing_library_print_LHS_and_RHS_as_unsigned_integers(unsigned int LHS, unsigned int RHS);
void testing_library_print_LHS_and_RHS_as_signed_long_integers(long LHS, long RHS);
void testing_library_print_LHS_and_RHS_as_unsigned_long_integers(unsigned long LHS, unsigned long RHS);

#ifndef UNIT_TESTING_LIBRARY_BUILD_LIBRARY

#include "static_assert.h"
#include "fixed_width_integer_types.h"
#include <limits.h>

static testing_library_data_type testing_library_data = {
#if UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS
	.number_of_false_assertions = 0U,
	.number_of_true_assertions = 0U,
	.should_print_true_assertions = Boolean_false
#else
	0U, 0U, Boolean_false
#endif
};

/* Use these macros instead of the functions above */
#if UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS
#define TEST(test, test_name_or_description) \
	static void test##_function(void); \
	static testing_library_test_type test##_data = { \
		.func_ptr = &test##_function, \
		.id = #test, \
		.name_or_description = (test_name_or_description != NULL) ? (test_name_or_description ) : "", \
		.run_count = 0U, \
		.sequence_number = 0U, \
		.number_of_false_assertions = 0U, \
		.number_of_true_assertions = 0U \
	}; \
	static testing_library_test_type * const test = &test##_data; \
	void test##_function(void)
#else
#define TEST(test, test_name_or_description) \
	static void test##_function(void); \
	static testing_library_test_type test##_data = { \
		&test##_function, \
		#test, \
		(test_name_or_description != NULL) ? (test_name_or_description) : "",\
		0U, 0U, 0U, 0U}; \
	static testing_library_test_type * const test = &test##_data; \
	void test##_function(void)
#endif

#define TEST_FUNCTION(test)                   (*((test)->func_ptr))
#define TEST_ID(test)                         (const char * const) ((test)->id)
#define TEST_NAME_OR_DESCRIPTION(test)        (const char * const) ((test)->name_or_description)
#define TEST_NUMBER_OF_FALSE_ASSERTIONS(test) (const size_t) ((test)->number_of_false_assertions)
#define TEST_NUMBER_OF_TRUE_ASSERTIONS(test)  (const size_t) ((test)->number_of_true_assertions)

#define ASSERT(condition) testing_library_assert(__LINE__, condition, STRINGIFY(condition), &testing_library_data)

#define COMPARE_USING_OPERATOR(DATA_TYPE, LHS, OPERATOR, RHS, PRINT_FUNCTION) \
	do { \
		DATA_TYPE const lhs = (DATA_TYPE) (LHS); \
		DATA_TYPE const rhs = (DATA_TYPE) (RHS); \
		const Boolean_type result = (lhs OPERATOR rhs); \
		testing_library_assert(__LINE__, result, STRINGIFY(LHS OPERATOR RHS), &testing_library_data); \
		if (!result) { \
			(void) PRINT_FUNCTION(lhs, rhs); \
		} \
	} while (Boolean_false)

#define COMPARE_USING_FUNCTION(DATA_TYPE, COMPARISON_FUNCTION, LHS, RHS, PRINT_FUNCTION) \
	do { \
		DATA_TYPE const lhs = (DATA_TYPE) (LHS); \
		DATA_TYPE const rhs = (DATA_TYPE) (RHS); \
		const Boolean_type result = (Boolean_type) COMPARISON_FUNCTION(lhs, rhs); \
		testing_library_assert(__LINE__, result, STRINGIFY(COMPARISON_FUNCTION(LHS, RHS)), &testing_library_data); \
		if (!result) { \
			(void) PRINT_FUNCTION(lhs, rhs); \
		} \
	} while (Boolean_false)

#define SET_OUTPUT_FILE(FILE_POINTER) testing_library_set_file(FILE_POINTER)

#define SET_TEST_SUCCESS_STATUS_TEXT(TEXT) testing_library_set_test_status_passed_text(TEXT)
#define SET_TEST_FAILURE_STATUS_TEXT(TEXT) testing_library_set_test_status_failed_text(TEXT)
#define SET_NO_ASSERTION_WARNING_TEXT(TEXT) testing_library_set_test_without_assertion_warning_text(TEXT)

#define SHOULD_PRINT_TRUE_ASSERTIONS() testing_library_data.should_print_true_assertions = Boolean_true
#define SHOULD_NOT_PRINT_TRUE_ASSERTIONS() testing_library_data.should_print_true_assertions = Boolean_false

#define DEFINE_LIST_OF_TESTS(TEST_LIST) testing_library_test_type * const TEST_LIST[] = 

#define RUN_TEST(test) testing_library_run_test(0U, test, &testing_library_data)
#define RUN_TESTS(list_of_tests) testing_library_run_tests(&list_of_tests[0], SIZEOF_ARRAY(list_of_tests), &testing_library_data)

#define PRINT_FILE_NAME() testing_library_print_file_name(__FILE__)

#define PRINT_TEST_STATISTICS(list_of_tests) \
	do { \
		const testing_library_test_statistics_type stats = testing_library_determine_test_statistics( \
			(const testing_library_test_type * const *)&list_of_tests[0], SIZEOF_ARRAY(list_of_tests)); \
		testing_library_print_test_statistics(&stats); \
	} while (Boolean_false)

/* for comparison of signed integers */
#define COMPARE_INT(LHS, OPERATOR, RHS) \
	COMPARE_USING_OPERATOR(int, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_signed_integers)
#define ASSERT_INT_EQUAL(LHS, RHS)            COMPARE_INT(LHS, ==, RHS)
#define ASSERT_INT_NOT_EQUAL(LHS, RHS)        COMPARE_INT(LHS, !=, RHS)
#define ASSERT_INT_GREATER(LHS, RHS)          COMPARE_INT(LHS, >, RHS)
#define ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS) COMPARE_INT(LHS, >=, RHS)
#define ASSERT_INT_LESS(LHS, RHS)             COMPARE_INT(LHS, <, RHS)
#define ASSERT_INT_LESS_OR_EQUAL(LHS, RHS)    COMPARE_INT(LHS, <=, RHS)

/* for comparison of unsigned integers */
#define COMPARE_UINT(LHS, OPERATOR, RHS) \
	COMPARE_USING_OPERATOR(unsigned int, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_unsigned_integers)
#define ASSERT_UINT_EQUAL(LHS, RHS)            COMPARE_UINT(LHS, ==, RHS)
#define ASSERT_UINT_NOT_EQUAL(LHS, RHS)        COMPARE_UINT(LHS, !=, RHS)
#define ASSERT_UINT_GREATER(LHS, RHS)          COMPARE_UINT(LHS, >, RHS)
#define ASSERT_UINT_GREATER_OR_EQUAL(LHS, RHS) COMPARE_UINT(LHS, >=, RHS)
#define ASSERT_UINT_LESS(LHS, RHS)             COMPARE_UINT(LHS, <, RHS)
#define ASSERT_UINT_LESS_OR_EQUAL(LHS, RHS)    COMPARE_UINT(LHS, <=, RHS)

/* for comparison of signed long integers */
#define COMPARE_LONG(LHS, OPERATOR, RHS) \
	COMPARE_USING_OPERATOR(long, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_signed_long_integers)
#define ASSERT_LONG_EQUAL(LHS, RHS)            COMPARE_LONG(LHS, ==, RHS)
#define ASSERT_LONG_NOT_EQUAL(LHS, RHS)        COMPARE_LONG(LHS, !=, RHS)
#define ASSERT_LONG_GREATER(LHS, RHS)          COMPARE_LONG(LHS, >, RHS)
#define ASSERT_LONG_GREATER_OR_EQUAL(LHS, RHS) COMPARE_LONG(LHS, >=, RHS)
#define ASSERT_LONG_LESS(LHS, RHS)             COMPARE_LONG(LHS, <, RHS)
#define ASSERT_LONG_LESS_OR_EQUAL(LHS, RHS)    COMPARE_LONG(LHS, <=, RHS)

/* for comparison of unsigned long integers */
#define COMPARE_ULONG(LHS, OPERATOR, RHS) \
	COMPARE_USING_OPERATOR(unsigned long, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_unsigned_long_integers)
#define ASSERT_ULONG_EQUAL(LHS, RHS)            COMPARE_ULONG(LHS, ==, RHS)
#define ASSERT_ULONG_NOT_EQUAL(LHS, RHS)        COMPARE_ULONG(LHS, !=, RHS)
#define ASSERT_ULONG_GREATER(LHS, RHS)          COMPARE_ULONG(LHS, >, RHS)
#define ASSERT_ULONG_GREATER_OR_EQUAL(LHS, RHS) COMPARE_ULONG(LHS, >=, RHS)
#define ASSERT_ULONG_LESS(LHS, RHS)             COMPARE_ULONG(LHS, <, RHS)
#define ASSERT_ULONG_LESS_OR_EQUAL(LHS, RHS)    COMPARE_ULONG(LHS, <=, RHS)

/* for comparison of default integers */
#define ASSERT_EQUAL(LHS, RHS)            ASSERT_INT_EQUAL(LHS, RHS)
#define ASSERT_NOT_EQUAL(LHS, RHS)        ASSERT_INT_NOT_EQUAL(LHS, RHS)
#define ASSERT_GREATER(LHS, RHS)          ASSERT_INT_GREATER(LHS, RHS)
#define ASSERT_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_LESS(LHS, RHS)             ASSERT_INT_LESS(LHS, RHS)
#define ASSERT_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT_LESS_OR_EQUAL(LHS, RHS)

/* for comparison of long long integers */
#if defined(LLONG_MAX) && defined(LLONG_MIN)
static void testing_library_print_LHS_and_RHS_as_signed_long_long_integers(long long lhs, long long rhs)
{
	FILE *fp = testing_library_get_file();
	fprintf(fp, "LHS == %lld, RHS == %lld\n", lhs, rhs);
}
#define COMPARE_LLONG(LHS, OPERATOR, RHS) \
	COMPARE_USING_OPERATOR(long long, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_signed_long_long_integers)
#define ASSERT_LLONG_EQUAL(LHS, RHS)            COMPARE_LLONG(LHS, ==, RHS)
#define ASSERT_LLONG_NOT_EQUAL(LHS, RHS)        COMPARE_LLONG(LHS, !=, RHS)
#define ASSERT_LLONG_GREATER(LHS, RHS)          COMPARE_LLONG(LHS, >, RHS)
#define ASSERT_LLONG_GREATER_OR_EQUAL(LHS, RHS) COMPARE_LLONG(LHS, >=, RHS)
#define ASSERT_LLONG_LESS(LHS, RHS)             COMPARE_LLONG(LHS, <, RHS)
#define ASSERT_LLONG_LESS_OR_EQUAL(LHS, RHS)    COMPARE_LLONG(LHS, <=, RHS)
#else
#pragma message("unit_testing: long long type is not supported.")
#endif /* LLONG_MAX and LLONG_MIN */

/* for comparison of unsigned long long integers */
#if defined(ULLONG_MAX)
static void testing_library_print_LHS_and_RHS_as_unsigned_long_long_integers(unsigned long long lhs, unsigned long long rhs)
{
	FILE *fp = testing_library_get_file();
	fprintf(fp, "LHS == %llu, RHS == %llu\n", lhs, rhs);
}
#define COMPARE_ULLONG(LHS, OPERATOR, RHS) \
	COMPARE_USING_OPERATOR(unsigned long long, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_unsigned_long_long_integers)
#define ASSERT_ULLONG_EQUAL(LHS, RHS)            COMPARE_ULLONG(LHS, ==, RHS)
#define ASSERT_ULLONG_NOT_EQUAL(LHS, RHS)        COMPARE_ULLONG(LHS, !=, RHS)
#define ASSERT_ULLONG_GREATER(LHS, RHS)          COMPARE_ULLONG(LHS, >, RHS)
#define ASSERT_ULLONG_GREATER_OR_EQUAL(LHS, RHS) COMPARE_ULLONG(LHS, >=, RHS)
#define ASSERT_ULLONG_LESS(LHS, RHS)             COMPARE_ULLONG(LHS, <, RHS)
#define ASSERT_ULLONG_LESS_OR_EQUAL(LHS, RHS)    COMPARE_ULLONG(LHS, <=, RHS)
#else
#pragma message("unit_testing: unsigned long long type is not supported.")
#endif /* ULLONG_MAX */

#if (INT_MIN < INT8_MIN) && (INT_MAX > INT8_MAX)
STATIC_ASSERT(sizeof(int) > sizeof(int8_t), "The size of int shall be larger than the size of int8_t.");
#define ASSERT_INT8_EQUAL(LHS, RHS)            ASSERT_INT_EQUAL(LHS, RHS)
#define ASSERT_INT8_NOT_EQUAL(LHS, RHS)        ASSERT_INT_NOT_EQUAL(LHS, RHS)
#define ASSERT_INT8_GREATER(LHS, RHS)          ASSERT_INT_GREATER(LHS, RHS)
#define ASSERT_INT8_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_INT8_LESS(LHS, RHS)             ASSERT_INT_LESS(LHS, RHS)
#define ASSERT_INT8_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for int8_t.")
#endif

#if (UINT_MAX > UINT8_MAX)
STATIC_ASSERT(sizeof(unsigned int) > sizeof(uint8_t), "The size of unsigned int shall be larger the size of uint8_t.");
#define ASSERT_UINT8_EQUAL(LHS, RHS)            ASSERT_UINT_EQUAL(LHS, RHS)
#define ASSERT_UINT8_NOT_EQUAL(LHS, RHS)        ASSERT_UINT_NOT_EQUAL(LHS, RHS)
#define ASSERT_UINT8_GREATER(LHS, RHS)          ASSERT_UINT_GREATER(LHS, RHS)
#define ASSERT_UINT8_GREATER_OR_EQUAL(LHS, RHS) ASSERT_UINT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_UINT8_LESS(LHS, RHS)             ASSERT_UINT_LESS(LHS, RHS)
#define ASSERT_UINT8_LESS_OR_EQUAL(LHS, RHS)    ASSERT_UINT_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for uint8_t.")
#endif

#if (INT_MIN <= INT16_MIN) && (INT_MAX >= INT16_MAX)
STATIC_ASSERT(sizeof(int) >= sizeof(int16_t), "The size of int shall b greater than or equal to the size of int16_t.");
#define ASSERT_INT16_EQUAL(LHS, RHS)            ASSERT_INT_EQUAL(LHS, RHS)
#define ASSERT_INT16_NOT_EQUAL(LHS, RHS)        ASSERT_INT_NOT_EQUAL(LHS, RHS)
#define ASSERT_INT16_GREATER(LHS, RHS)          ASSERT_INT_GREATER(LHS, RHS)
#define ASSERT_INT16_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_INT16_LESS(LHS, RHS)             ASSERT_INT_LESS(LHS, RHS)
#define ASSERT_INT16_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for int16_t.")
#endif

#if (UINT_MAX >= UINT16_MAX)
STATIC_ASSERT(sizeof(unsigned int) >= sizeof(uint16_t), "The size of unsigned int shall b greater than or equal to the size of uint16_t.");
#define ASSERT_UINT16_EQUAL(LHS, RHS)            ASSERT_UINT_EQUAL(LHS, RHS)
#define ASSERT_UINT16_NOT_EQUAL(LHS, RHS)        ASSERT_UINT_NOT_EQUAL(LHS, RHS)
#define ASSERT_UINT16_GREATER(LHS, RHS)          ASSERT_UINT_GREATER(LHS, RHS)
#define ASSERT_UINT16_GREATER_OR_EQUAL(LHS, RHS) ASSERT_UINT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_UINT16_LESS(LHS, RHS)             ASSERT_UINT_LESS(LHS, RHS)
#define ASSERT_UINT16_LESS_OR_EQUAL(LHS, RHS)    ASSERT_UINT_LESS_OR_EQUAL(LHS, RHS)
#else 
#pragma message("unit_testing: Test assertions are not supported for uint16_t.")
#endif

#if (INT_MIN <= INT32_MIN) && (INT_MAX >= INT32_MAX)
STATIC_ASSERT(sizeof(int) >= sizeof(int32_t), "The size of int shall be larger than or equal to the size of int32_t.");
#define ASSERT_INT32_EQUAL(LHS, RHS)            ASSERT_INT_EQUAL(LHS, RHS)
#define ASSERT_INT32_NOT_EQUAL(LHS, RHS)        ASSERT_INT_NOT_EQUAL(LHS, RHS)
#define ASSERT_INT32_GREATER(LHS, RHS)          ASSERT_INT_GREATER(LHS, RHS)
#define ASSERT_INT32_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_INT32_LESS(LHS, RHS)             ASSERT_INT_LESS(LHS, RHS)
#define ASSERT_INT32_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT_LESS_OR_EQUAL(LHS, RHS)
#elif (LONG_MIN <= INT32_MIN) && (LONG_MAX >= INT32_MAX)
STATIC_ASSERT(sizeof(long) >= sizeof(int32_t), "The size of long int shall be larger than or equal to the size of int32_t.");
#define ASSERT_INT32_EQUAL(LHS, RHS)            ASSERT_LONG_EQUAL(LHS, RHS)
#define ASSERT_INT32_NOT_EQUAL(LHS, RHS)        ASSERT_LONG_NOT_EQUAL(LHS, RHS)
#define ASSERT_INT32_GREATER(LHS, RHS)          ASSERT_LONG_GREATER(LHS, RHS)
#define ASSERT_INT32_GREATER_OR_EQUAL(LHS, RHS) ASSERT_LONG_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_INT32_LESS(LHS, RHS)             ASSERT_LONG_LESS(LHS, RHS)
#define ASSERT_INT32_LESS_OR_EQUAL(LHS, RHS)    ASSERT_LONG_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for int32_t.")
#endif

#if (UINT_MAX >= UINT32_MAX)
STATIC_ASSERT(sizeof(unsigned int) >= sizeof(uint32_t), "The size of unsigned int shall be larger than or equal to the size of uint32_t.");
#define ASSERT_UINT32_EQUAL(LHS, RHS)            ASSERT_UINT_EQUAL(LHS, RHS)
#define ASSERT_UINT32_NOT_EQUAL(LHS, RHS)        ASSERT_UINT_NOT_EQUAL(LHS, RHS)
#define ASSERT_UINT32_GREATER(LHS, RHS)          ASSERT_UINT_GREATER(LHS, RHS)
#define ASSERT_UINT32_GREATER_OR_EQUAL(LHS, RHS) ASSERT_UINT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_UINT32_LESS(LHS, RHS)             ASSERT_UINT_LESS(LHS, RHS)
#define ASSERT_UINT32_LESS_OR_EQUAL(LHS, RHS)    ASSERT_UINT_LESS_OR_EQUAL(LHS, RHS)
#elif (ULONG_MAX >= UINT32_MAX)
STATIC_ASSERT(sizeof(unsigned long) >= sizeof(uint32_t), "The size of unsigned long int shall be larger than or equal to the size of uint32_t.");
#define ASSERT_UINT32_EQUAL(LHS, RHS)            ASSERT_ULONG_EQUAL(LHS, RHS)
#define ASSERT_UINT32_NOT_EQUAL(LHS, RHS)        ASSERT_ULONG_NOT_EQUAL(LHS, RHS)
#define ASSERT_UINT32_GREATER(LHS, RHS)          ASSERT_ULONG_GREATER(LHS, RHS)
#define ASSERT_UINT32_GREATER_OR_EQUAL(LHS, RHS) ASSERT_ULONG_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_UINT32_LESS(LHS, RHS)             ASSERT_ULONG_LESS(LHS, RHS)
#define ASSERT_UINT32_LESS_OR_EQUAL(LHS, RHS)    ASSERT_ULONG_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for uint32_t.")
#endif

#if defined(INT64_MIN) && defined(INT64_MAX)
#if (LONG_MIN <= INT64_MIN) && (LONG_MAX >= INT64_MAX)
STATIC_ASSERT(sizeof(long) >= sizeof(int64_t), "The size of long int shall be larger than or equal to the sizeof int64_t.");
#define ASSERT_INT64_EQUAL(LHS, RHS)            ASSERT_LONG_EQUAL(LHS, RHS)
#define ASSERT_INT64_NOT_EQUAL(LHS, RHS)        ASSERT_LONG_NOT_EQUAL(LHS, RHS)
#define ASSERT_INT64_GREATER(LHS, RHS)          ASSERT_LONG_GREATER(LHS, RHS)
#define ASSERT_INT64_GREATER_OR_EQUAL(LHS, RHS) ASSERT_LONG_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_INT64_LESS(LHS, RHS)             ASSERT_LONG_LESS(LHS, RHS)
#define ASSERT_INT64_LESS_OR_EQUAL(LHS, RHS)    ASSERT_LONG_LESS_OR_EQUAL(LHS, RHS)
#elif defined(LLONG_MIN) && (LLONG_MIN <= INT64_MIN) && defined(LLONG_MAX) && (LLONG_MAX >= INT64_MAX)
STATIC_ASSERT(sizeof(long long) >= sizeof(int64_t), "The size of long long int shall be larger than or equal to the sizeof int64_t.");
#define ASSERT_INT64_EQUAL(LHS, RHS)            ASSERT_LLONG_EQUAL(LHS, RHS)
#define ASSERT_INT64_NOT_EQUAL(LHS, RHS)        ASSERT_LLONG_NOT_EQUAL(LHS, RHS)
#define ASSERT_INT64_GREATER(LHS, RHS)          ASSERT_LLONG_GREATER(LHS, RHS)
#define ASSERT_INT64_GREATER_OR_EQUAL(LHS, RHS) ASSERT_LLONG_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_INT64_LESS(LHS, RHS)             ASSERT_LLONG_LESS(LHS, RHS)
#define ASSERT_INT64_LESS_OR_EQUAL(LHS, RHS)    ASSERT_LLONG_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for int64_t.")
#endif
#endif /* INT64_MIN and INT64_MAX defined */

#if defined(UINT64_MAX)
#if (ULONG_MAX >= UINT64_MAX)
STATIC_ASSERT(sizeof(unsigned long) >= sizeof(uint64_t), "The size of unsigned long int shall be larger than or equal to the sizeof uint64_t.");
#define ASSERT_UINT64_EQUAL(LHS, RHS)            ASSERT_ULONG_EQUAL(LHS, RHS)
#define ASSERT_UINT64_NOT_EQUAL(LHS, RHS)        ASSERT_ULONG_NOT_EQUAL(LHS, RHS)
#define ASSERT_UINT64_GREATER(LHS, RHS)          ASSERT_ULONG_GREATER(LHS, RHS)
#define ASSERT_UINT64_GREATER_OR_EQUAL(LHS, RHS) ASSERT_ULONG_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_UINT64_LESS(LHS, RHS)             ASSERT_ULONG_LESS(LHS, RHS)
#define ASSERT_UINT64_LESS_OR_EQUAL(LHS, RHS)    ASSERT_ULONG_LESS_OR_EQUAL(LHS, RHS)
#elif defined(ULLONG_MAX) && (ULLONG_MAX >= INT64_MAX)
STATIC_ASSERT(sizeof(unsigned long long) >= sizeof(uint64_t), "The size of unsigned long long int shall be larger than or equal to the sizeof uint64_t.");
#define ASSERT_UINT64_EQUAL(LHS, RHS)            ASSERT_ULLONG_EQUAL(LHS, RHS)
#define ASSERT_UINT64_NOT_EQUAL(LHS, RHS)        ASSERT_ULLONG_NOT_EQUAL(LHS, RHS)
#define ASSERT_UINT64_GREATER(LHS, RHS)          ASSERT_ULLONG_GREATER(LHS, RHS)
#define ASSERT_UINT64_GREATER_OR_EQUAL(LHS, RHS) ASSERT_ULLONG_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_UINT64_LESS(LHS, RHS)             ASSERT_ULLONG_LESS(LHS, RHS)
#define ASSERT_UINT64_LESS_OR_EQUAL(LHS, RHS)    ASSERT_ULLONG_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for uint64_t.")
#endif
#endif /* UINT64_MAX defined */

#if (PTRDIFF_MIN == INT64_MIN) && (PTRDIFF_MAX == INT64_MAX)
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int64_t), "The size of ptrdiff_t shall be equal to the sizeof int64_t.");
#define ASSERT_PTRDIFF_EQUAL(LHS, RHS)            ASSERT_INT64_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_NOT_EQUAL(LHS, RHS)        ASSERT_INT64_NOT_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_GREATER(LHS, RHS)          ASSERT_INT64_GREATER(LHS, RHS)
#define ASSERT_PTRDIFF_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT64_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_LESS(LHS, RHS)             ASSERT_INT64_LESS(LHS, RHS)
#define ASSERT_PTRDIFF_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT64_LESS_OR_EQUAL(LHS, RHS)
#elif (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int32_t), "The size of ptrdiff_t shall be equal to the sizeof int32_t.");
#define ASSERT_PTRDIFF_EQUAL(LHS, RHS)            ASSERT_INT32_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_NOT_EQUAL(LHS, RHS)        ASSERT_INT32_NOT_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_GREATER(LHS, RHS)          ASSERT_INT32_GREATER(LHS, RHS)
#define ASSERT_PTRDIFF_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT32_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_LESS(LHS, RHS)             ASSERT_INT32_LESS(LHS, RHS)
#define ASSERT_PTRDIFF_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT32_LESS_OR_EQUAL(LHS, RHS)
#elif (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int16_t), "The size of ptrdiff_t shall be equal to the sizeof int16_t.");
#define ASSERT_PTRDIFF_EQUAL(LHS, RHS)            ASSERT_INT16_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_NOT_EQUAL(LHS, RHS)        ASSERT_INT16_NOT_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_GREATER(LHS, RHS)          ASSERT_INT16_GREATER(LHS, RHS)
#define ASSERT_PTRDIFF_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT16_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_PTRDIFF_LESS(LHS, RHS)             ASSERT_INT16_LESS(LHS, RHS)
#define ASSERT_PTRDIFF_LESS_OR_EQUAL(LHS, RHS)    ASSERT_INT16_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for ptrdiff_t.")
#endif

#if SIZE_MAX == UINT64_MAX
STATIC_ASSERT(sizeof(size_t) == sizeof(uint64_t), "The size of size_t shall be equal to the sizeof uint64_t.");
#define ASSERT_SIZE_EQUAL(LHS, RHS)            ASSERT_UINT64_EQUAL(LHS, RHS)
#define ASSERT_SIZE_NOT_EQUAL(LHS, RHS)        ASSERT_UINT64_NOT_EQUAL(LHS, RHS)
#define ASSERT_SIZE_GREATER(LHS, RHS)          ASSERT_UINT64_GREATER(LHS, RHS)
#define ASSERT_SIZE_GREATER_OR_EQUAL(LHS, RHS) ASSERT_UINT64_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_SIZE_LESS(LHS, RHS)             ASSERT_UINT64_LESS(LHS, RHS)
#define ASSERT_SIZE_LESS_OR_EQUAL(LHS, RHS)    ASSERT_UINT64_LESS_OR_EQUAL(LHS, RHS)
#elif SIZE_MAX == UINT32_MAX
STATIC_ASSERT(sizeof(size_t) == sizeof(uint32_t), "The size of size_t shall be equal to the sizeof uint32_t.");
#define ASSERT_SIZE_EQUAL(LHS, RHS)            ASSERT_UINT32_EQUAL(LHS, RHS)
#define ASSERT_SIZE_NOT_EQUAL(LHS, RHS)        ASSERT_UINT32_NOT_EQUAL(LHS, RHS)
#define ASSERT_SIZE_GREATER(LHS, RHS)          ASSERT_UINT32_GREATER(LHS, RHS)
#define ASSERT_SIZE_GREATER_OR_EQUAL(LHS, RHS) ASSERT_UINT32_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_SIZE_LESS(LHS, RHS)             ASSERT_UINT32_LESS(LHS, RHS)
#define ASSERT_SIZE_LESS_OR_EQUAL(LHS, RHS)    ASSERT_UINT32_LESS_OR_EQUAL(LHS, RHS)
#elif SIZE_MAX == UINT16_MAX
STATIC_ASSERT(sizeof(size_t) == sizeof(uint16_t), "The size of size_t shall be equal to the sizeof uint16_t.");
#define ASSERT_SIZE_EQUAL(LHS, RHS)            ASSERT_UINT16_EQUAL(LHS, RHS)
#define ASSERT_SIZE_NOT_EQUAL(LHS, RHS)        ASSERT_UINT16_NOT_EQUAL(LHS, RHS)
#define ASSERT_SIZE_GREATER(LHS, RHS)          ASSERT_UINT16_GREATER(LHS, RHS)
#define ASSERT_SIZE_GREATER_OR_EQUAL(LHS, RHS) ASSERT_UINT16_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_SIZE_LESS(LHS, RHS)             ASSERT_UINT16_LESS(LHS, RHS)
#define ASSERT_SIZE_LESS_OR_EQUAL(LHS, RHS)    ASSERT_UINT16_LESS_OR_EQUAL(LHS, RHS)
#else
#pragma message("unit_testing: Test assertions are not supported for size_t.")
#endif

#endif /* UNIT_TESTING_LIBRARY_BUILD_LIBRARY */

#ifdef __cplusplus
}
#endif

#endif
