#ifndef UNIT_TESTING_LIBRARY_BUILD_LIBRARY
#define UNIT_TESTING_LIBRARY_BUILD_LIBRARY
#endif

#include "unit_testing.h"
#include "terminal_text_color.h"

#include <assert.h>
#include <iso646.h>
#include <string.h>

#define TEST_STATUS_PASSED "Passed"
#define TEST_STATUS_FAILED "Failed"
#define TEST_WITHOUT_ASSERTION_WARNING "No assertion"

static FILE *file_pointer = NULL;
static const char *test_status_passed = NULL;
static const char *test_status_failed = NULL;
static const char *test_without_assertion_warning = NULL;

void testing_library_set_file(FILE *pfile)
{
	file_pointer = pfile;
}

/* non-null guarantee */
FILE *testing_library_get_file(void)
{
	return (file_pointer != NULL) ? file_pointer : stdout;
}

void testing_library_set_test_status_passed_text(const char *text)
{
	test_status_passed = text;
}

static const char *test_status_passed_text(void)
{
	return (test_status_passed != NULL) ? test_status_passed : TEST_STATUS_PASSED;
}

void testing_library_set_test_status_failed_text(const char *text)
{
	test_status_failed = text;
}

static const char *test_status_failed_text(void)
{
	return (test_status_failed != NULL) ? test_status_failed : TEST_STATUS_FAILED;
}

void testing_library_set_test_without_assertion_warning_text(const char *text)
{
	test_without_assertion_warning = text;
}

static const char *test_without_assertion_warning_text(void)
{
	return (test_without_assertion_warning != NULL) ? test_without_assertion_warning : TEST_WITHOUT_ASSERTION_WARNING;
}

void testing_library_assert(int line_number, Boolean_type condition, const char *message, testing_library_data_type *pdata)
{
	FILE *file = testing_library_get_file();
	assert(message != NULL);
	assert(pdata != NULL);

	if (condition) {
		++(pdata->number_of_true_assertions);
	} else {
		++(pdata->number_of_false_assertions);
	}

	if (not condition) {
		terminal_text_color_set(terminal_color_code_red);
		fprintf(file, "Assertion failed at line %d: %s\n", line_number, message);
		terminal_text_color_set(terminal_color_code_default);
	} else if (pdata->should_print_true_assertions) {
		terminal_text_color_set(terminal_color_code_green);
		fprintf(file, "Line %d: %s\n", line_number, message);
		terminal_text_color_set(terminal_color_code_default);
	}
}

void testing_library_run_test(size_t sequence_number, testing_library_test_type *ptest, testing_library_data_type *pdata)
{	
	assert(ptest != NULL);
	assert(ptest->func_ptr != NULL);
	assert(ptest->id != NULL);
	assert(ptest->name_or_description != NULL);
	assert(pdata != NULL);

	if (ptest != NULL and ptest->func_ptr != NULL and ptest->id != NULL and ptest->name_or_description != NULL and pdata != NULL) {
		const size_t number_of_true_assertions = pdata->number_of_true_assertions;
		const size_t number_of_false_assertions = pdata->number_of_false_assertions;
		const char *status_message = "";
		terminal_color_code_type color_code = terminal_color_code_default;
		testing_library_test_result_type test_result = test_result_test_fails;
		FILE *file = testing_library_get_file();

		terminal_text_color_set(color_code);

		if (0U == ptest->sequence_number) {
			ptest->sequence_number = sequence_number;
		}

		if (sequence_number > 0U) {
			if (ptest->run_count > 0U) {
				if (ptest->sequence_number != sequence_number) {
					fprintf(file, "(%lu) is a duplicate of (%lu) %s, previously ran for %lu time%s\n",
						(unsigned long) sequence_number, (unsigned long) ptest->sequence_number,
						ptest->id, (unsigned long) (ptest->run_count), ((ptest->run_count > 1U) ? "s" : ""));
				} else {
					fprintf(file, "(%lu) %s (previously ran for %lu time%s)\n",
						(unsigned long) (ptest->sequence_number), ptest->id,
						(unsigned long) ptest->run_count, ((ptest->run_count > 1U) ? "s" : ""));
				}
			}
		} else {
			if (ptest->run_count > 0U) {
				fprintf(file, "(Previously ran for %lu time%s) %s (\"%s\")\n",
					(unsigned long) (ptest->run_count), ((ptest->run_count > 1U) ? "s" : ""),
					ptest->id, ptest->name_or_description);
			}
		}

		if (sequence_number > 0U) {
			if (ptest->name_or_description[0] != '\0') {
				fprintf(file, "(%lu) %s (%s)\n", (unsigned long) sequence_number, ptest->id, ptest->name_or_description);
			} else {
				fprintf(file, "(%lu) %s\n", (unsigned long) sequence_number, ptest->id);
			}
		} else {
			if (ptest->name_or_description[0] != '\0') {
				fprintf(file, "%s (%s)\n", ptest->id, ptest->name_or_description);
			} else {
				fprintf(file, "%s\n", ptest->id);
			}
		}
	
		(*(ptest->func_ptr))();
		++(ptest->run_count);

		if (pdata->number_of_false_assertions > number_of_false_assertions) {
			ptest->number_of_false_assertions = pdata->number_of_false_assertions - number_of_false_assertions;
		} else {
			ptest->number_of_false_assertions = 0U;
		}

		if (pdata->number_of_true_assertions > number_of_true_assertions) {
			ptest->number_of_true_assertions = pdata->number_of_true_assertions - number_of_true_assertions;
		} else {
			ptest->number_of_true_assertions = 0U;
		}

		test_result = testing_library_evaluate_test_result(ptest);
		if (test_result_test_passes == test_result) {
			status_message = test_status_passed_text();
			color_code = terminal_color_code_green;
		} else if (test_result_test_fails == test_result) {
			status_message = test_status_failed_text();
			color_code = terminal_color_code_red;
		} else if (test_result_test_has_no_assertion == test_result) {
			status_message = test_without_assertion_warning_text();
			color_code = terminal_color_code_yellow;
		} else {
			status_message = "Unknown status";
			color_code = terminal_color_code_yellow;
		}

		terminal_text_color_set(color_code);
		fprintf(file, "Status of %s: %s\n", ptest->id, status_message);
		terminal_text_color_set(terminal_color_code_default);
	}
}

void testing_library_run_tests(testing_library_test_type * const *ptests, size_t number_of_tests, testing_library_data_type *pdata)
{
	size_t i = 0U;
	assert(ptests != NULL);
	if (NULL == ptests) {
		number_of_tests = 0U;
	}
	for (; i < number_of_tests; ++i) {
		const size_t sequence_number = i + 1U;
		testing_library_run_test(sequence_number, ptests[i], pdata);
	}
}

testing_library_test_result_type testing_library_evaluate_test_result(const testing_library_test_type *ptest)
{
	testing_library_test_result_type test_result = test_result_test_has_no_assertion;
	assert(ptest != NULL);
	if (ptest != NULL) {
		if (ptest->number_of_true_assertions > 0U and ptest->number_of_false_assertions == 0U) {
			test_result = test_result_test_passes;
		} else if (ptest->number_of_false_assertions > 0U) {
			test_result = test_result_test_fails;
		}
	}
	return test_result;
}

testing_library_test_statistics_type testing_library_determine_test_statistics(const testing_library_test_type * const *ptests, size_t number_of_tests)
{
	size_t i = 0U;
	testing_library_test_statistics_type statistics = {0U};
	assert(ptests != NULL);
	if (NULL == ptests) {
		number_of_tests = 0U;
	}
	for (; i < number_of_tests; ++i) {
		const size_t sequence_number = i + 1U;
		assert(ptests[i] != NULL);
		if (sequence_number == ptests[i]->sequence_number) {
			const testing_library_test_result_type result = testing_library_evaluate_test_result(ptests[i]);
			if (result == test_result_test_passes) {
				++(statistics.number_of_passed_tests);
			} else if (result == test_result_test_fails) {
				++(statistics.number_of_failed_tests);
			} else if (result == test_result_test_has_no_assertion) {
				++(statistics.number_of_tests_without_assertion);
			}
			statistics.number_of_false_assertions += ptests[i]->number_of_false_assertions;
			statistics.number_of_true_assertions += ptests[i]->number_of_true_assertions;
			if (ptests[i]->run_count > 1U) {
				statistics.number_of_duplicate_tests += (ptests[i]->run_count - 1U);
			}
		}
	}

	return statistics;
}

void testing_library_print_test_statistics(const testing_library_test_statistics_type *pstat)
{
	assert(pstat != NULL);
	if (pstat != NULL) {
		const size_t number_of_unique_tests = pstat->number_of_passed_tests + pstat->number_of_failed_tests
							+ pstat->number_of_tests_without_assertion;
		const Boolean_type all_tests_pass = (pstat->number_of_passed_tests == number_of_unique_tests);
		const Boolean_type at_least_a_test_fails = (pstat->number_of_failed_tests > 0U);
		const Boolean_type at_least_a_test_has_no_assertion = (pstat->number_of_tests_without_assertion > 0U);
		const size_t number_of_assertions = pstat->number_of_true_assertions + pstat->number_of_false_assertions;
		const Boolean_type all_assertions_are_true = (pstat->number_of_true_assertions == number_of_assertions);
		const Boolean_type at_least_an_assertion_is_false = (pstat->number_of_false_assertions > 0U);
		FILE *file = testing_library_get_file();

		fprintf(file, "Number of unique tests: %lu\n", (unsigned long) number_of_unique_tests);
		fprintf(file, "Number of duplicate tests: %lu\n", (unsigned long) pstat->number_of_duplicate_tests);

		if (all_tests_pass) {
			terminal_text_color_set(terminal_color_code_green);
		}
		fprintf(file, "Number of passed tests: %lu\n", (unsigned long) pstat->number_of_passed_tests);
		if (all_tests_pass) {
			terminal_text_color_set(terminal_color_code_default);
		}

		if (at_least_a_test_fails) {
			terminal_text_color_set(terminal_color_code_red);
		}
		fprintf(file, "Number of failed tests: %lu\n", (unsigned long) pstat->number_of_failed_tests);
		if (at_least_a_test_fails) {
			terminal_text_color_set(terminal_color_code_default);
		}

		if (at_least_a_test_has_no_assertion) {
			terminal_text_color_set(terminal_color_code_yellow);
		}
		fprintf(file, "Number of tests without assertion: %lu\n", (unsigned long) pstat->number_of_tests_without_assertion);
		if (at_least_a_test_has_no_assertion) {
			terminal_text_color_set(terminal_color_code_default);
		}

		fprintf(file, "Number of assertions: %lu\n", (unsigned long) number_of_assertions);

		if (all_assertions_are_true) {
			terminal_text_color_set(terminal_color_code_green);
		}
		fprintf(file, "Number of true assertions: %lu\n", (unsigned long) pstat->number_of_true_assertions);
		if (all_assertions_are_true) {
			terminal_text_color_set(terminal_color_code_default);
		}

		if (at_least_an_assertion_is_false) {
			terminal_text_color_set(terminal_color_code_red);
		}
		fprintf(file, "Number of false assertions: %lu\n", (unsigned long) pstat->number_of_false_assertions);
		if (at_least_an_assertion_is_false) {
			terminal_text_color_set(terminal_color_code_default);
		}
	}
}

void testing_library_print_file_name(const char *file_name)
{
	FILE *file = testing_library_get_file();
	assert(file_name != NULL);
	fprintf(file, "%s\n", file_name);
}

void testing_library_print_LHS_and_RHS_as_signed_integers(int LHS, int RHS)
{
	FILE *file = testing_library_get_file();
	fprintf(file, "LHS == %d, RHS == %d\n", LHS, RHS);
}

void testing_library_print_LHS_and_RHS_as_unsigned_integers(unsigned int LHS, unsigned int RHS)
{
	FILE *file = testing_library_get_file();
	fprintf(file, "LHS == %u, RHS == %u\n", LHS, RHS);
}

void testing_library_print_LHS_and_RHS_as_signed_long_integers(long LHS, long RHS)
{
	FILE *file = testing_library_get_file();
	fprintf(file, "LHS == %ld, RHS == %ld\n", LHS, RHS);
}

void testing_library_print_LHS_and_RHS_as_unsigned_long_integers(unsigned long LHS, unsigned long RHS)
{
	FILE *file = testing_library_get_file();
	fprintf(file, "LHS == %lu, RHS == %lu\n", LHS, RHS);
}

/* LHS and RHS must be null-terminated. */
void testing_library_print_LHS_and_RHS_as_strings(const char *LHS, const char *RHS)
{
	FILE *file = testing_library_get_file();
	assert(LHS != NULL);
	assert(RHS != NULL);
	fprintf(file, "left string == %s, right string == %s\n", LHS, RHS);
}

Boolean_type testing_library_strings_are_equal(const char *LHS, const char *RHS)
{
	return strcmp(LHS, RHS) == 0;
}

Boolean_type testing_library_strings_are_not_equal(const char *LHS, const char *RHS)
{
	return strcmp(LHS, RHS) != 0;
}
