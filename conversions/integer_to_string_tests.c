#include "integer_to_string.h"
#include "unit_testing.h"
#include <string.h>

TEST(tests_for_int32_base_10_output, "Tests for integer-to-string conversion with base 10 output")
{
	const int base10 = 10;
	int_to_string_option_type options = int_to_string_option_default;
	i32string_type i32string = {{0}};

	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");

	options = int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");

	options = int_to_string_option_add_prefix;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "2147483647");

	options = int_to_string_option_add_plus_sign;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+2147483647");

	options = int_to_string_option_add_plus_sign | int_to_string_option_add_prefix | int_to_string_option_uppercase;
	i32string = i32_to_i32string(INT32_MIN, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-2147483648");
	i32string = i32_to_i32string(-99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-99999");
	i32string = i32_to_i32string(-1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "-1");
	i32string = i32_to_i32string(0, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "0");
	i32string = i32_to_i32string(1, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+1");
	i32string = i32_to_i32string(99999, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+99999");
	i32string = i32_to_i32string(INT32_MAX, base10, options);
	ASSERT_STRING_EQUAL(i32string.content, "+2147483647");
}

/* TODO: Add more tests in the future */

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		tests_for_int32_base_10_output
	};

	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
