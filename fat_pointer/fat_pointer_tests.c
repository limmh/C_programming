#include "fat_pointer.h"
#include "unit_testing.h"
#include "sizeof_array.h"
#include <stddef.h>
#include <string.h>

TEST(fat_pointer_referencing_a_char_buffer, "Fat pointer referencing a char buffer")
{
	fat_pointer_error_type error = fat_pointer_error_none;
	const char *read_only_string = "Hello, World";
	char buffer[13] = {0};
	char *ptr = NULL;
	fat_pointer_type(char) cfatptr = fat_pointer_create(char, buffer, sizeof_array(buffer), 0U);

	/* before modification */
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));

	/* adding elements */
	error = fat_pointer_add_elements_at_index(char, cfatptr, 0U, read_only_string, strlen(read_only_string) + 1U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ptr = fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == &buffer[0]);
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), 'H');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), 'e');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 5U), ',');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 6U), ' ');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 7U), 'W');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 8U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 9U), 'r');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 10U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 11U), 'd');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 12U), '\0');
	ASSERT_SIZE_EQUAL(strlen(fat_pointer_element_ptr(char, cfatptr, 0U)), 12U);
	ASSERT_EQUAL(buffer[0], 'H');
	ASSERT_EQUAL(buffer[1], 'e');
	ASSERT_EQUAL(buffer[2], 'l');
	ASSERT_EQUAL(buffer[3], 'l');
	ASSERT_EQUAL(buffer[4], 'o');
	ASSERT_EQUAL(buffer[5], ',');
	ASSERT_EQUAL(buffer[6], ' ');
	ASSERT_EQUAL(buffer[7], 'W');
	ASSERT_EQUAL(buffer[8], 'o');
	ASSERT_EQUAL(buffer[9], 'r');
	ASSERT_EQUAL(buffer[10], 'l');
	ASSERT_EQUAL(buffer[11], 'd');
	ASSERT_EQUAL(buffer[12], '\0');
	ASSERT_SIZE_EQUAL(strlen(buffer), 12U);

	/* removing elements */
	error = fat_pointer_remove_elements_starting_from_index(char, cfatptr, 0U, 7U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 6U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ptr = fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == &buffer[0]);
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), 'W');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), 'r');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), 'l');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), 'd');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 5U), '\0');
	ASSERT_SIZE_EQUAL(strlen(fat_pointer_element_ptr(char, cfatptr, 0U)), 5U);
	ASSERT_EQUAL(buffer[0], 'W');
	ASSERT_EQUAL(buffer[1], 'o');
	ASSERT_EQUAL(buffer[2], 'r');
	ASSERT_EQUAL(buffer[3], 'l');
	ASSERT_EQUAL(buffer[4], 'd');
	ASSERT_EQUAL(buffer[5], '\0');
	ASSERT_SIZE_EQUAL(strlen(buffer), 5U);

	/* removing a single element at a time */
	error = fat_pointer_remove_element_at_index(char, cfatptr, 3U);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 5U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));
	ptr = fat_pointer_element_ptr(char, cfatptr, 0U);
	ASSERT(ptr == &buffer[0]);
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 0U), 'W');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 1U), 'o');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 2U), 'r');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 3U), 'd');
	ASSERT_EQUAL(fat_pointer_element(char, cfatptr, 4U), '\0');
	ASSERT_SIZE_EQUAL(strlen(fat_pointer_element_ptr(char, cfatptr, 0U)), 4U);
	ASSERT_EQUAL(buffer[0], 'W');
	ASSERT_EQUAL(buffer[1], 'o');
	ASSERT_EQUAL(buffer[2], 'r');
	ASSERT_EQUAL(buffer[3], 'd');
	ASSERT_EQUAL(buffer[4], '\0');
	ASSERT_SIZE_EQUAL(strlen(buffer), 4U);

	fat_pointer_resize(char, cfatptr, 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));

	fat_pointer_destroy(cfatptr);
}

TEST(fat_pointer_referencing_an_integer_buffer, "Fat pointer referencing an integer array")
{
	fat_pointer_error_type error = fat_pointer_error_none;
	size_t index = 0U;
	int var = 0, var2 = 0;
	int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int dest_array[sizeof_array(array) / 2U] = {0};
	fat_pointer_type(int) fatptr = fat_pointer_create(int, array, sizeof_array(array), sizeof_array(array));

	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 0);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 1);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 2);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 3);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 4);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 5);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 6U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 7U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 8U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 9U), 9);

	for (index = 0U; index < fat_pointer_length(fatptr); ++index) {
		++fat_pointer_element(int, fatptr, index);
	}

	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 1);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 2);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 3);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 4);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 5);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 6U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 7U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 8U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 9U), 10);
	ASSERT_EQUAL(array[0], 1);
	ASSERT_EQUAL(array[1], 2);
	ASSERT_EQUAL(array[2], 3);
	ASSERT_EQUAL(array[3], 4);
	ASSERT_EQUAL(array[4], 5);
	ASSERT_EQUAL(array[5], 6);
	ASSERT_EQUAL(array[6], 7);
	ASSERT_EQUAL(array[7], 8);
	ASSERT_EQUAL(array[8], 9);
	ASSERT_EQUAL(array[9], 10);

	index = 0U;
	error = fat_pointer_move_elements_starting_from_index_to_buffer(int, fatptr, index, dest_array, sizeof_array(dest_array)); 
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 5U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(array[0], 6);
	ASSERT_EQUAL(array[1], 7);
	ASSERT_EQUAL(array[2], 8);
	ASSERT_EQUAL(array[3], 9);
	ASSERT_EQUAL(array[4], 10);
	ASSERT_EQUAL(dest_array[0], 1);
	ASSERT_EQUAL(dest_array[1], 2);
	ASSERT_EQUAL(dest_array[2], 3);
	ASSERT_EQUAL(dest_array[3], 4);
	ASSERT_EQUAL(dest_array[4], 5);

	var = 11;
	error = fat_pointer_push_back(int, fatptr, var);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 6U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 5U), 11);
	ASSERT_EQUAL(array[0], 6);
	ASSERT_EQUAL(array[1], 7);
	ASSERT_EQUAL(array[2], 8);
	ASSERT_EQUAL(array[3], 9);
	ASSERT_EQUAL(array[4], 10);
	ASSERT_EQUAL(array[5], 11);

	error = fat_pointer_pop_back(int, fatptr, var2);
	ASSERT_EQUAL(error, fat_pointer_error_none);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(fatptr), 10U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(fatptr), 5U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(fatptr), sizeof(int));
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 0U), 6);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 1U), 7);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 2U), 8);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 3U), 9);
	ASSERT_EQUAL(fat_pointer_element(int, fatptr, 4U), 10);
	ASSERT_EQUAL(array[0], 6);
	ASSERT_EQUAL(array[1], 7);
	ASSERT_EQUAL(array[2], 8);
	ASSERT_EQUAL(array[3], 9);
	ASSERT_EQUAL(array[4], 10);
	ASSERT_EQUAL(var2, 11);

	fat_pointer_destroy(fatptr);
}

/* More tests will be added in the future */

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		fat_pointer_referencing_a_char_buffer,
		fat_pointer_referencing_an_integer_buffer
	};

	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
