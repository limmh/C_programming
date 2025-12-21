#include "fat_pointer.h"
#include "unit_testing.h"
#include "sizeof_array.h"
#include <stddef.h>
#include <string.h>

TEST(fat_pointer_referencing_a_char_buffer, "Fat pointer referencing a char buffer")
{
	const char *read_only_string = "Hello, World";
	char buffer[13] = {0};
	char *ptr = NULL;
	fat_pointer_type(char) cfatptr = fat_pointer_create(char, buffer, sizeof_array(buffer), 0U);

	/* before modification */
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));

	/* adding elements */
	fat_pointer_add_elements_at_index(char, cfatptr, 0U, read_only_string, strlen(read_only_string) + 1U);
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
	fat_pointer_remove_elements_starting_from_index(char, cfatptr, 0U, 7U);
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
	fat_pointer_remove_element_at_index(char, cfatptr, 3U);
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

	/* resizing the 'virtual' array */
	fat_pointer_resize(char, cfatptr, 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_capacity(cfatptr), 13U);
	ASSERT_SIZE_EQUAL(fat_pointer_length(cfatptr), 0U);
	ASSERT_SIZE_EQUAL(fat_pointer_element_size(cfatptr), sizeof(char));

	fat_pointer_destroy(cfatptr);
}

/* More tests will be added in the future */

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		fat_pointer_referencing_a_char_buffer
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
