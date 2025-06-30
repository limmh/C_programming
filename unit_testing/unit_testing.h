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
#if defined(_STDC_VERSION_) && (_STDC_VERSION_ >= 199901L)
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

/* Use these macros instead of the functions above */
#if UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS != 0
#define TEST(test, test_name_or_description) \
	static void test##_function(void); \
	static testing_library_test_type test##_data = { \
		.func_ptr = &test##_function, \
		.id = #test, \
		.name_or_description = test_name_or_description, \
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
	static testing_library_test_type test##_data = {&test##_function, #test, test_name_or_description, 0U, 0U, 0U, 0U}; \
	static testing_library_test_type * const test = &test##_data; \
	void test##_function(void)
#endif

#define TEST_FUNCTION(test)                   (*((test)->func_ptr))
#define TEST_ID(test)                         (const char * const) ((test)->id)
#define TEST_NAME_OR_DESCRIPTION(test)        (const char * const) ((test)->name_or_description)
#define TEST_NUMBER_OF_FALSE_ASSERTIONS(test) (const size_t) ((test)->number_of_false_assertions)
#define TEST_NUMBER_OF_TRUE_ASSERTIONS(test)  (const size_t) ((test)->number_of_true_assertions)

#ifndef UNIT_TESTING_LIBRARY_BUILD_LIBRARY
static testing_library_data_type testing_library_data = {
#if UNIT_TESTING_LIBRARY_USE_C99_DESIGNATED_INITIALIZERS != 0
	.number_of_false_assertions = 0U,
	.number_of_true_assertions = 0U,
	.should_print_true_assertions = Boolean_false
#else
	0U, 0U, Boolean_false
#endif
};

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

/* for comparison of signed integers */
#define COMPARE_INT(LHS, OPERATOR, RHS) COMPARE_USING_OPERATOR(int, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_signed_integers)
#define ASSERT_INT_EQUAL(LHS, RHS) COMPARE_INT(LHS, ==, RHS)
#define ASSERT_INT_NOT_EQUAL(LHS, RHS) COMPARE_INT(LHS, !=, RHS)
#define ASSERT_INT_GREATER(LHS, RHS) COMPARE_INT(LHS, >, RHS)
#define ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS) COMPARE_INT(LHS, >=, RHS)
#define ASSERT_INT_LESS(LHS, RHS) COMPARE_INT(LHS, <, RHS)
#define ASSERT_INT_LESS_OR_EQUAL(LHS, RHS) COMPARE_INT(LHS, <=, RHS)

/* for comparison of unsigned integers */
#define COMPARE_UINT(LHS, OPERATOR, RHS) COMPARE_USING_OPERATOR(unsigned int, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_unsigned_integers)
#define ASSERT_UINT_EQUAL(LHS, RHS) COMPARE_UINT(LHS, ==, RHS)
#define ASSERT_UINT_NOT_EQUAL(LHS, RHS) COMPARE_UINT(LHS, !=, RHS)
#define ASSERT_UINT_GREATER(LHS, RHS) COMPARE_UINT(LHS, >, RHS)
#define ASSERT_UINT_GREATER_OR_EQUAL(LHS, RHS) COMPARE_UINT(LHS, >=, RHS)
#define ASSERT_UINT_LESS(LHS, RHS) COMPARE_UINT(LHS, <, RHS)
#define ASSERT_UINT_LESS_OR_EQUAL(LHS, RHS) COMPARE_UINT(LHS, <=, RHS)

/* for comparison of signed long integers */
#define COMPARE_LONG(LHS, OPERATOR, RHS) COMPARE_USING_OPERATOR(long, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_signed_long_integers)
#define ASSERT_LONG_EQUAL(LHS, RHS) COMPARE_LONG(LHS, ==, RHS)
#define ASSERT_LONG_NOT_EQUAL(LHS, RHS) COMPARE_LONG(LHS, !=, RHS)
#define ASSERT_LONG_GREATER(LHS, RHS) COMPARE_LONG(LHS, >, RHS)
#define ASSERT_LONG_GREATER_OR_EQUAL(LHS, RHS) COMPARE_LONG(LHS, >=, RHS)
#define ASSERT_LONG_LESS(LHS, RHS) COMPARE_LONG(LHS, <, RHS)
#define ASSERT_LONG_LESS_OR_EQUAL(LHS, RHS) COMPARE_LONG(LHS, <=, RHS)

/* for comparison of unsigned long integers */
#define COMPARE_ULONG(LHS, OPERATOR, RHS) COMPARE_USING_OPERATOR(unsigned long, LHS, OPERATOR, RHS, testing_library_print_LHS_and_RHS_as_unsigned_long_integers)
#define ASSERT_ULONG_EQUAL(LHS, RHS) COMPARE_ULONG(LHS, ==, RHS)
#define ASSERT_ULONG_NOT_EQUAL(LHS, RHS) COMPARE_ULONG(LHS, !=, RHS)
#define ASSERT_ULONG_GREATER(LHS, RHS) COMPARE_ULONG(LHS, >, RHS)
#define ASSERT_ULONG_GREATER_OR_EQUAL(LHS, RHS) COMPARE_ULONG(LHS, >=, RHS)
#define ASSERT_ULONG_LESS(LHS, RHS) COMPARE_ULONG(LHS, <, RHS)
#define ASSERT_ULONG_LESS_OR_EQUAL(LHS, RHS) COMPARE_ULONG(LHS, <=, RHS)

/* for comparison of default integers */
#define ASSERT_EQUAL(LHS, RHS) ASSERT_INT_EQUAL(LHS, RHS)
#define ASSERT_NOT_EQUAL(LHS, RHS) ASSERT_INT_NOT_EQUAL(LHS, RHS)
#define ASSERT_GREATER(LHS, RHS) ASSERT_INT_GREATER(LHS, RHS)
#define ASSERT_GREATER_OR_EQUAL(LHS, RHS) ASSERT_INT_GREATER_OR_EQUAL(LHS, RHS)
#define ASSERT_LESS(LHS, RHS) ASSERT_INT_LESS(LHS, RHS)
#define ASSERT_LESS_OR_EQUAL(LHS, RHS) ASSERT_INT_LESS_OR_EQUAL(LHS, RHS)

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
#endif /* UNIT_TESTING_LIBRARY_BUILD_LIBRARY */

#ifdef __cplusplus
}
#endif

#endif
