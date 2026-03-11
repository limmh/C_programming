#include "string_reference.h"
#include "sizeof_array.h"
#include "unit_testing.h"

#include <iso646.h>
#include <string.h>

/* TEST: stringref_to_const_stringref */

TEST(stringref_to_const_stringref_basic, "Convert stringref to const_stringref")
{
	char buffer[] = "Hello";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));
	const_stringref_type const_ref = stringref_to_const_stringref(ref);

	ASSERT(ref.string == buffer);
	ASSERT_SIZE_EQUAL(ref.length, 5U);
	ASSERT_EQUAL(memcmp(ref.string, buffer, 5U), 0);
	ASSERT(const_ref.string == buffer);
	ASSERT_SIZE_EQUAL(const_ref.length, 5U);
	ASSERT_EQUAL(memcmp(const_ref.string, buffer, 5U), 0);
}

TEST(stringref_to_const_stringref_empty, "Convert empty stringref to const_stringref")
{
	char buffer[] = "";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));
	const_stringref_type const_ref = stringref_to_const_stringref(ref);

	ASSERT(ref.string == buffer);
	ASSERT_SIZE_EQUAL(ref.length, 0U);
	ASSERT(const_ref.string == buffer);
	ASSERT_SIZE_EQUAL(const_ref.length, 0U);
}

TEST(stringref_to_const_stringref_null, "Convert null stringref to const_stringref")
{
	stringref_type ref = string_to_stringref(NULL, 0);
	const_stringref_type const_ref = stringref_to_const_stringref(ref);

	ASSERT(ref.string == NULL);
	ASSERT_SIZE_EQUAL(ref.length, 0U);
	ASSERT(const_ref.string == NULL);
	ASSERT_SIZE_EQUAL(const_ref.length, 0U);
}

/* TEST: stringref_is_valid */

TEST(stringref_is_valid_with_valid_pointer, "stringref_is_valid returns true for valid pointer")
{
	char buffer[] = "Hello";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	ASSERT(stringref_is_valid(ref));
}

TEST(stringref_is_valid_with_null_pointer, "stringref_is_valid returns false for null pointer")
{
	stringref_type ref = string_to_stringref(NULL, 5);

	ASSERT(not stringref_is_valid(ref));
}

TEST(stringref_is_valid_with_empty_string, "stringref_is_valid returns true for empty string")
{
	char buffer[] = "";
	stringref_type ref = string_to_stringref(buffer, 0);

	ASSERT(stringref_is_valid(ref));
}

/* TEST: const_stringref_is_valid */

TEST(const_stringref_is_valid_with_valid_pointer, "const_stringref_is_valid returns true for valid pointer")
{
	const char buffer[] = "Hello";
	const_stringref_type ref = string_to_const_stringref(buffer, strlen(buffer));

	ASSERT(const_stringref_is_valid(ref));
}

TEST(const_stringref_is_valid_with_null_pointer, "const_stringref_is_valid returns false for null pointer")
{
	const_stringref_type ref = string_to_const_stringref(NULL, 5);

	ASSERT(not const_stringref_is_valid(ref));
}

TEST(const_stringref_is_valid_with_empty_string, "const_stringref_is_valid returns true for empty string")
{
	const char buffer[] = "";
	const_stringref_type ref = string_to_const_stringref(buffer, strlen(buffer));

	ASSERT(const_stringref_is_valid(ref));
}

/* TEST: stringref_string_is_empty */

TEST(stringref_string_is_empty_with_empty_string, "stringref_string_is_empty returns true for empty string")
{
	char buffer[] = "";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	ASSERT(stringref_string_is_empty(ref));
}

TEST(stringref_string_is_empty_with_nonempty_string, "stringref_string_is_empty returns false for non-empty string")
{
	char buffer[] = "Hello";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	ASSERT(not stringref_string_is_empty(ref));
}

TEST(stringref_string_is_empty_with_null_pointer, "stringref_string_is_empty returns true for null pointer")
{
	stringref_type ref = string_to_stringref(NULL, 5);

	ASSERT(stringref_string_is_empty(ref));
}

TEST(stringref_string_is_empty_with_zero_length, "stringref_string_is_empty returns true for zero length")
{
	char buffer[] = "Hello";
	stringref_type ref = string_to_stringref(buffer, 0);

	ASSERT(stringref_string_is_empty(ref));
}

TEST(stringref_string_is_empty_with_null_terminator_at_start, "stringref_string_is_empty with null terminator at start")
{
	char buffer[] = "\0Hello";
	stringref_type ref = string_to_stringref(buffer, 6);

	ASSERT(stringref_string_is_empty(ref));
}

/* TEST: const_stringref_string_is_empty */

TEST(const_stringref_string_is_empty_with_empty_string, "const_stringref_string_is_empty returns true for empty string")
{
	const char buffer[] = "";
	const_stringref_type ref = string_to_const_stringref(buffer, strlen(buffer));

	ASSERT(const_stringref_string_is_empty(ref));
}

TEST(const_stringref_string_is_empty_with_nonempty_string, "const_stringref_string_is_empty returns false for non-empty string")
{
	const char buffer[] = "Hello";
	const_stringref_type ref = string_to_const_stringref(buffer, strlen(buffer));

	ASSERT(not const_stringref_string_is_empty(ref));
}

TEST(const_stringref_string_is_empty_with_null_pointer, "const_stringref_string_is_empty returns true for null pointer")
{
	const_stringref_type ref = string_to_const_stringref(NULL, 5);

	ASSERT(const_stringref_string_is_empty(ref));
}

/* TEST: string_to_stringref */

TEST(string_to_stringref_basic, "string_to_stringref creates valid reference")
{
	char buffer[] = "Hello World";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	ASSERT(ref.string == buffer);
	ASSERT_SIZE_EQUAL(ref.length, 11U);
	ASSERT_EQUAL(memcmp(ref.string, buffer, 11U), 0);
}

TEST(string_to_stringref_null_pointer, "string_to_stringref with null pointer")
{
	stringref_type ref = string_to_stringref(NULL, 0);

	ASSERT(ref.string == NULL);
	ASSERT_SIZE_EQUAL(ref.length, 0u);
}

TEST(string_to_stringref_empty_string, "string_to_stringref with empty string")
{
	char buffer[] = "";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	ASSERT(ref.string == buffer);
	ASSERT_SIZE_EQUAL(ref.length, 0U);
}

/* TEST: string_to_const_stringref */

TEST(string_to_const_stringref_basic, "string_to_const_stringref creates valid reference")
{
	const char buffer[] = "Hello World";
	const_stringref_type ref = string_to_const_stringref(buffer, strlen(buffer));

	ASSERT(ref.string == buffer);
	ASSERT_SIZE_EQUAL(ref.length, 11U);
}

TEST(string_to_const_stringref_null_pointer, "string_to_const_stringref with null pointer")
{
	const_stringref_type ref = string_to_const_stringref(NULL, 0);

	ASSERT(ref.string == NULL);
	ASSERT_SIZE_EQUAL(ref.length, 0U);
}

TEST(string_to_const_stringref_empty_string, "string_to_const_stringref with empty string")
{
	const char buffer[] = "";
	const_stringref_type ref = string_to_const_stringref(buffer, strlen(buffer));

	ASSERT(ref.string == buffer);
	ASSERT_SIZE_EQUAL(ref.length, 0);
}

/* TEST: const_stringref_string_length */

TEST(const_stringref_string_length_basic, "const_stringref_string_length calculates correct length")
{
	const char buffer[20] = "Hello";
	const_stringref_type ref = string_to_const_stringref(buffer, 20);

	const size_t length = const_stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 5U);
}

TEST(const_stringref_string_length_empty_string, "const_stringref_string_length with empty string")
{
	const char buffer[20] = "";
	const_stringref_type ref = string_to_const_stringref(buffer, 20);

	const size_t length = const_stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 0U);
}

TEST(const_stringref_string_length_with_null_terminator_in_middle, "const_stringref_string_length stops at null terminator")
{
	const char buffer[20] = "Hello\0World";
	const_stringref_type ref = string_to_const_stringref(buffer, 20);

	const size_t length = const_stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 5U);
}

TEST(const_stringref_string_length_no_null_terminator, "const_stringref_string_length without null terminator")
{
	const char buffer[20] = "Hello World";
	const_stringref_type ref = string_to_const_stringref(buffer, 5);

	size_t length = const_stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 5U);
}

TEST(const_stringref_string_length_null_pointer, "const_stringref_string_length with null pointer")
{
	const_stringref_type ref = string_to_const_stringref(NULL, 20);

	const size_t length = const_stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 0U);
}

/* TEST: stringref_string_length */

TEST(stringref_string_length_basic, "stringref_string_length calculates correct length")
{
	char buffer[20] = "Hello";
	stringref_type ref = string_to_stringref(buffer, 20);

	const size_t length = stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 5U);
}

TEST(stringref_string_length_empty_string, "stringref_string_length with empty string")
{
	char buffer[20] = "";
	stringref_type ref = string_to_stringref(buffer, 20);

	const size_t length = stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 0U);
}

TEST(stringref_string_length_with_null_terminator_in_middle, "stringref_string_length stops at null terminator")
{
	char buffer[20] = "Hello\0World";
	stringref_type ref = string_to_stringref(buffer, 20);

	const size_t length = stringref_string_length(ref);
	ASSERT_SIZE_EQUAL(length, 5U);
}

/* TEST: const_stringref_string_is_null_terminated */

TEST(const_stringref_string_is_null_terminated_test, "const_stringref_string_is_null_terminated returns true")
{
	const char buffer[20] = "Hello";
	const_stringref_type ref = string_to_const_stringref(buffer, 20);

	ASSERT(const_stringref_string_is_null_terminated(ref));
}

TEST(const_stringref_string_is_not_null_terminated, "const_stringref_string_is_null_terminated returns false")
{
	const char buffer[20] = "Hello";
	const_stringref_type ref = string_to_const_stringref(buffer, 5);

	ASSERT(not const_stringref_string_is_null_terminated(ref));
}

TEST(const_stringref_string_is_null_terminated_empty, "const_stringref_string_is_null_terminated with empty string")
{
	const char buffer[20] = "";
	const_stringref_type ref = string_to_const_stringref(buffer, 20);

	ASSERT(const_stringref_string_is_null_terminated(ref));
}

/* TEST: stringref_string_is_null_terminated */

TEST(stringref_string_is_null_terminated_test, "stringref_string_is_null_terminated returns true")
{
	char buffer[20] = "Hello";
	stringref_type ref = string_to_stringref(buffer, 20);

	ASSERT(stringref_string_is_null_terminated(ref));
}

TEST(stringref_string_is_not_null_terminated, "stringref_string_is_null_terminated returns false")
{
	char buffer[20] = "Hello";
	stringref_type ref = string_to_stringref(buffer, 5);

	ASSERT(not stringref_string_is_null_terminated(ref));
}

/* TEST: const_stringref_to_string */

TEST(const_stringref_to_string_basic, "const_stringref_to_string copies string correctly")
{
	const char source[20] = "Hello";
	const_stringref_type ref = string_to_const_stringref(source, 5);
	char buffer[20];

	const_stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, "Hello"), 0);
}

TEST(const_stringref_to_string_with_buffer_size_limit, "const_stringref_to_string respects buffer size")
{
	const char source[20] = "Hello World";
	const_stringref_type ref = string_to_const_stringref(source, 11);
	char buffer[6];  /* Only 5 characters + null terminator */

	const_stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, "Hello"), 0);
	ASSERT_EQUAL(buffer[5], '\0');
}

TEST(const_stringref_to_string_empty_string, "const_stringref_to_string with empty string")
{
	const char source[20] = "";
	const_stringref_type ref = string_to_const_stringref(source, 0);
	char buffer[20];

	const_stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, ""), 0);
	ASSERT_EQUAL(buffer[0], '\0');
}

TEST(const_stringref_to_string_partial_copy, "const_stringref_to_string copies partial string")
{
	const char source[20] = "Hello World";
	const_stringref_type ref = string_to_const_stringref(source, 5);
	char buffer[20];

	const_stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, "Hello"), 0);
}

TEST(const_stringref_to_string_no_null_terminator, "const_stringref_to_string with non-null-terminated source")
{
	const char source[20] = "HelloWorld";
	const_stringref_type ref = string_to_const_stringref(source, 5);
	char buffer[20];

	const_stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, "Hello"), 0);
	ASSERT_EQUAL(buffer[5], '\0');
}

/* TEST: stringref_to_string */

TEST(stringref_to_string_basic, "stringref_to_string copies string correctly")
{
	char source[20] = "Hello";
	stringref_type ref = string_to_stringref(source, 5);
	char buffer[20];

	stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, "Hello"), 0);
}

TEST(stringref_to_string_empty_string, "stringref_to_string with empty string")
{
	char source[20] = "";
	stringref_type ref = string_to_stringref(source, 0);
	char buffer[20];

	stringref_to_string(ref, buffer, sizeof(buffer));

	ASSERT_EQUAL(strcmp(buffer, ""), 0);
	ASSERT_EQUAL(buffer[0], '\0');
}

/* TEST: const_stringref_strings_are_equal */

TEST(const_stringref_strings_are_equal_identical, "const_stringref_strings_are_equal with identical strings")
{
	const char str1[] = "Hello";
	const char str2[] = "Hello";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_different, "const_stringref_strings_are_equal with different strings")
{
	const char str1[] = "Hello";
	const char str2[] = "World";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(not const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_empty_strings, "const_stringref_strings_are_equal with empty strings")
{
	const char str1[] = "";
	const char str2[] = "";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_one_empty, "const_stringref_strings_are_equal with one empty string")
{
	const char str1[] = "";
	const char str2[] = "Hello";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(not const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_both_null, "const_stringref_strings_are_equal with both null pointers")
{
	const_stringref_type ref1 = string_to_const_stringref(NULL, 0);
	const_stringref_type ref2 = string_to_const_stringref(NULL, 0);

	ASSERT(const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_one_null, "const_stringref_strings_are_equal with one null pointer")
{
	const char str[] = "Hello";
	const_stringref_type ref1 = string_to_const_stringref(NULL, 0);
	const_stringref_type ref2 = string_to_const_stringref(str, strlen(str));

	ASSERT(not const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_case_sensitive, "const_stringref_strings_are_equal is case-sensitive")
{
	const char str1[] = "Hello";
	const char str2[] = "hello";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(not const_stringref_strings_are_equal(ref1, ref2));
}

TEST(const_stringref_strings_are_equal_special, "const_stringref_strings_are_equal with a special case")
{
	const char str1[] = "Hello\0World";
	const char str2[] = "Hello";
	const_stringref_type ref1 = string_to_const_stringref(str1, sizeof_array(str1) - 1U);
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(const_stringref_strings_are_equal(ref1, ref2));
}

/* TEST: const_stringref_contents_are_equal */

TEST(const_stringref_contents_are_equal_identical, "const_stringref_contents_are_equal with identical strings")
{
	const char str1[] = "Hello";
	const char str2[] = "Hello";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(const_stringref_contents_are_equal(ref1, ref2));
}

TEST(const_stringref_contents_are_equal_different, "const_stringref_contents_are_equal with different strings")
{
	const char str1[] = "Hello";
	const char str2[] = "World";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(not const_stringref_contents_are_equal(ref1, ref2));
}

TEST(const_stringref_contents_are_equal_with_null_terminators_ignored, "const_stringref_contents_are_equal compares exact content")
{
	const char str1[] = "Hello\0World";
	const char str2[] = "Hello\0World";
	const_stringref_type ref1 = string_to_const_stringref(str1, sizeof_array(str1) - 1U);
	const_stringref_type ref2 = string_to_const_stringref(str2, sizeof_array(str2) - 1U);

	ASSERT(const_stringref_contents_are_equal(ref1, ref2));
}

TEST(const_stringref_contents_are_equal_different_lengths, "const_stringref_contents_are_equal with different lengths")
{
	const char str1[] = "Hello";
	const char str2[] = "Hello World";
	const_stringref_type ref1 = string_to_const_stringref(str1, strlen(str1));
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(not const_stringref_contents_are_equal(ref1, ref2));
}

TEST(const_stringref_contents_are_equal_empty_strings, "const_stringref_contents_are_equal with empty strings")
{
	const_stringref_type ref1 = string_to_const_stringref("", 0);
	const_stringref_type ref2 = string_to_const_stringref("", 0);

	ASSERT(const_stringref_contents_are_equal(ref1, ref2));
}

TEST(const_stringref_contents_are_equal_special, "const_stringref_contents_are_equal with a special case")
{
	const char str1[] = "Hello\0World";
	const char str2[] = "Hello";
	const_stringref_type ref1 = string_to_const_stringref(str1, sizeof(str1) - 1U);
	const_stringref_type ref2 = string_to_const_stringref(str2, strlen(str2));

	ASSERT(not const_stringref_contents_are_equal(ref1, ref2));
}

/* TEST: stringref_reverse_string */

TEST(stringref_reverse_string_basic, "stringref_reverse_string reverses string")
{
	char buffer[] = "Hello";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "olleH"), 0);
}

TEST(stringref_reverse_string_single_char, "stringref_reverse_string with single character")
{
	char buffer[] = "A";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "A"), 0);
}

TEST(stringref_reverse_string_two_chars, "stringref_reverse_string with two characters")
{
	char buffer[] = "AB";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "BA"), 0);
}

TEST(stringref_reverse_string_empty_string, "stringref_reverse_string with empty string")
{
	char buffer[] = "";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, ""), 0);
}

TEST(stringref_reverse_string_even_length, "stringref_reverse_string with even length")
{
	char buffer[] = "abcd";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "dcba"), 0);
}

TEST(stringref_reverse_string_odd_length, "stringref_reverse_string with odd length")
{
	char buffer[] = "abcde";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "edcba"), 0);
}

TEST(stringref_reverse_string_with_special_chars, "stringref_reverse_string with special characters")
{
	char buffer[] = "!@#$%";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "%$#@!"), 0);
}

TEST(stringref_reverse_string_with_spaces, "stringref_reverse_string with spaces")
{
	char buffer[] = "a b c";
	stringref_type ref = string_to_stringref(buffer, strlen(buffer));

	stringref_reverse_string(ref);

	ASSERT_EQUAL(strcmp(buffer, "c b a"), 0);
}

/* MAIN TEST RUNNER */

int main(void)
{
	DEFINE_LIST_OF_TESTS(list_of_tests) {
		/* stringref_to_const_stringref */
		stringref_to_const_stringref_basic,
		stringref_to_const_stringref_empty,
		stringref_to_const_stringref_null,

		/* stringref_is_valid */
		stringref_is_valid_with_valid_pointer,
		stringref_is_valid_with_null_pointer,
		stringref_is_valid_with_empty_string,

		/* const_stringref_is_valid */
		const_stringref_is_valid_with_valid_pointer,
		const_stringref_is_valid_with_null_pointer,
		const_stringref_is_valid_with_empty_string,

		/* stringref_string_is_empty */
		stringref_string_is_empty_with_empty_string,
		stringref_string_is_empty_with_nonempty_string,
		stringref_string_is_empty_with_null_pointer,
		stringref_string_is_empty_with_zero_length,
		stringref_string_is_empty_with_null_terminator_at_start,

		/* const_stringref_string_is_empty */
		const_stringref_string_is_empty_with_empty_string,
		const_stringref_string_is_empty_with_nonempty_string,
		const_stringref_string_is_empty_with_null_pointer,

		/* string_to_stringref */
		string_to_stringref_basic,
		string_to_stringref_null_pointer,
		string_to_stringref_empty_string,

		/* string_to_const_stringref */
		string_to_const_stringref_basic,
		string_to_const_stringref_null_pointer,
		string_to_const_stringref_empty_string,

		/* const_stringref_string_length */
		const_stringref_string_length_basic,
		const_stringref_string_length_empty_string,
		const_stringref_string_length_with_null_terminator_in_middle,
		const_stringref_string_length_no_null_terminator,
		const_stringref_string_length_null_pointer,

		/* stringref_string_length */
		stringref_string_length_basic,
		stringref_string_length_empty_string,
		stringref_string_length_with_null_terminator_in_middle,

		/* const_stringref_string_is_null_terminated */
		const_stringref_string_is_null_terminated_test,
		const_stringref_string_is_not_null_terminated,
		const_stringref_string_is_null_terminated_empty,

		/* stringref_string_is_null_terminated */
		stringref_string_is_null_terminated_test,
		stringref_string_is_not_null_terminated,

		/* const_stringref_to_string */
		const_stringref_to_string_basic,
		const_stringref_to_string_with_buffer_size_limit,
		const_stringref_to_string_empty_string,
		const_stringref_to_string_partial_copy,
		const_stringref_to_string_no_null_terminator,

		/* stringref_to_string */
		stringref_to_string_basic,
		stringref_to_string_empty_string,

		/* const_stringref_strings_are_equal */
		const_stringref_strings_are_equal_identical,
		const_stringref_strings_are_equal_different,
		const_stringref_strings_are_equal_empty_strings,
		const_stringref_strings_are_equal_one_empty,
		const_stringref_strings_are_equal_both_null,
		const_stringref_strings_are_equal_one_null,
		const_stringref_strings_are_equal_case_sensitive,
		const_stringref_strings_are_equal_special,

		/* const_stringref_contents_are_equal */
		const_stringref_contents_are_equal_identical,
		const_stringref_contents_are_equal_different,
		const_stringref_contents_are_equal_with_null_terminators_ignored,
		const_stringref_contents_are_equal_different_lengths,
		const_stringref_contents_are_equal_empty_strings,
		const_stringref_contents_are_equal_special,

		/* stringref_reverse_string */
		stringref_reverse_string_basic,
		stringref_reverse_string_single_char,
		stringref_reverse_string_two_chars,
		stringref_reverse_string_empty_string,
		stringref_reverse_string_even_length,
		stringref_reverse_string_odd_length,
		stringref_reverse_string_with_special_chars,
		stringref_reverse_string_with_spaces
	};

	PRINT_FILE_NAME();
	RUN_TESTS(list_of_tests);
	PRINT_TEST_STATISTICS(list_of_tests);
	return 0;
}
