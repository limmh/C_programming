#include "dynamic_array.h"
#include "Boolean_type.h"
#include "sizeof_array.h"
#include "static_pool.h"
#include "unit_testing.h"

#include <assert.h>
#include <iso646.h>
#include <setjmp.h>
#include <string.h>

static static_pool_type static_pool = {0U};

static void *unit_test_allocate(size_t number_of_bytes)
{
	return static_pool_allocate(&static_pool, number_of_bytes);
}

static void *unit_test_reallocate(void *ptr, size_t new_size)
{
	return static_pool_reallocate(&static_pool, ptr, new_size);
}

static void unit_test_deallocate(void *ptr)
{
	static_pool_deallocate(&static_pool, ptr);
}

static void unit_test_pool_init(void)
{
	memset(&static_pool, 0, sizeof(static_pool));
}

static void unit_test_pool_deinit(void)
{
	memset(&static_pool, 0, sizeof(static_pool));
}

static dynamic_array_allocator_type unit_test_allocator = {
	&unit_test_allocate,
	&unit_test_reallocate,
	&unit_test_deallocate
};

static jmp_buf s_execution_context;
static int s_error_code = 0;

static void exception_handler(int error_code)
{
	s_error_code = error_code;
	longjmp(s_execution_context, error_code);	
}

TEST(char_dynamic_array_with_no_buffer, "A character dynamic array with no buffer")
{
	dynamic_array_type(char) array = {0};
	const dynamic_array_error_type error = dynamic_array_check(array);
	ASSERT_INT_EQUAL(error, dynamic_array_error_array_does_not_contain_buffer);
	dynamic_array_delete(array);
}

TEST(size_test_for_char_dynamic_array_with_no_element, "A character dynamic array with no element has a size of zero.")
{
	const size_t initial_size = 0U;
	dynamic_array_type(char) array = {0};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);
	ASSERT_UINT_EQUAL(dynamic_array_size(array), 0U);
	dynamic_array_delete(array);
	unit_test_pool_deinit();
}

TEST(out_of_bounds_access_to_char_dynamic_array_with_no_element, "A character dynamic array with no element will cause an error if it is accessed.")
{
	const size_t initial_size = 0U;
	dynamic_array_type(char) array = {0};
	Boolean_type exception_has_occurred = Boolean_false;

	unit_test_pool_init();
	dynamic_array_set_exception_handler(&exception_handler);
	s_error_code = 0;

	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);
	ASSERT_UINT_EQUAL(dynamic_array_size(array), 0U);

	if (setjmp(s_execution_context) == 0) {
		dynamic_array_element(char, array, 0U) = 1;
	} else {
		exception_has_occurred = Boolean_true;
	}
	ASSERT(exception_has_occurred);
	ASSERT_INT_EQUAL(s_error_code, (int)dynamic_array_error_index_is_out_of_range);

	s_error_code = 0;
	exception_has_occurred = Boolean_false;
	if (setjmp(s_execution_context) == 0) {
		dynamic_array_element(char, array, 30U) = 1;
	} else {
		exception_has_occurred = Boolean_true;
	}
	ASSERT(exception_has_occurred);
	ASSERT_INT_EQUAL(s_error_code, (int)dynamic_array_error_index_is_out_of_range);

	dynamic_array_delete(array);
	s_error_code = 0;
	dynamic_array_set_exception_handler(NULL);
	unit_test_pool_deinit();
}

TEST(test_for_char_dynamic_array_initialized_with_one_element, "A character dynamic array initialized with a single element has only an element.")
{
	const size_t initial_size = 1U;
	dynamic_array_type(char) array = {0};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);
	ASSERT_UINT_EQUAL(dynamic_array_size(array), 1U);
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), '\0');
	dynamic_array_delete(array);
	unit_test_pool_deinit();
}

TEST(value_test_for_char_dynamic_array_with_one_element, "Changing the value of the only element of a character array with a single element.")
{
	const size_t initial_size = 1U;
	dynamic_array_type(char) array = {0};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);
	
	dynamic_array_element(char, array, 0U) = '0';
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), '0');

	dynamic_array_element(char, array, 0U) = '9';
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), '9');

	dynamic_array_element(char, array, 0U) = 'A';
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'A');

	dynamic_array_element(char, array, 0U) = 'Z';
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'Z');

	dynamic_array_element(char, array, 0U) = 'a';
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'a');

	dynamic_array_element(char, array, 0U) = 'z';
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'z');

	dynamic_array_delete(array);
	unit_test_pool_deinit();

}

TEST(char_dynamic_array_with_one_element_and_a_new_element_is_added_to_the_back,
	"Another element is added to the back of a character dynamic array with an element")
{
	const size_t initial_size = 1U;
	dynamic_array_type(char) array = {0};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);

	dynamic_array_element(char, array, 0U) = 'H';
	dynamic_array_append_element(char, array, 'i');

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 2U);
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'H');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 1U), 'i');

	dynamic_array_delete(array);	
	unit_test_pool_deinit();
}

TEST(char_dynamic_array_with_one_element_and_a_new_element_is_added_to_the_front,
	"Another element is added to the front of a character dynamic array with an element")
{
	const size_t initial_size = 1U;
	dynamic_array_type(char) array = {0};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);

	dynamic_array_element(char, array, 0U) = 'i';
	dynamic_array_add_element_at_index(char, array, 0U, 'p');

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 2U);
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'p');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 1U), 'i');

	dynamic_array_delete(array);	
	unit_test_pool_deinit();
}

TEST(string_operations_on_char_dynamic_array, "String operations")
{
	const char buffer[] = "Hello World";
	const size_t initial_size = 0U;
	dynamic_array_type(char) array = {0};
	size_t index = 0U;

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(char, initial_size, unit_test_allocator);
	index = 0U;
	dynamic_array_add_elements_at_index(char, array, index, buffer, sizeof_array(buffer));

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 12U);
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'H');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 1U), 'e');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 2U), 'l');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 3U), 'l');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 4U), 'o');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 5U), ' ');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 6U), 'W');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 7U), 'o');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 8U), 'r');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 9U), 'l');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 10U), 'd');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 11U), '\0');

	index = 6U;
	dynamic_array_add_elements_at_index(char, array, index, "Sir", strlen("Sir"));
	index = 9U;
	dynamic_array_remove_elements_starting_from_index(char, array, index, 5U /*number of elements to remove*/);

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 10U);
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 0U), 'H');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 1U), 'e');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 2U), 'l');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 3U), 'l');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 4U), 'o');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 5U), ' ');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 6U), 'S');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 7U), 'i');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 8U), 'r');
	ASSERT_INT_EQUAL(dynamic_array_element(char, array, 9U), '\0');

	dynamic_array_delete(array);	
	unit_test_pool_deinit();
}

TEST(dynamic_integer_array, "Dynamic integer array")
{
	const int integer_array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	const size_t initial_size = 0U;
	dynamic_array_type(int) array = {0};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(int, initial_size, unit_test_allocator);

	dynamic_array_append_elements(int, array, integer_array, sizeof_array(integer_array));
	ASSERT_UINT_EQUAL(dynamic_array_size(array), 10U);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 0U), 0);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 1U), 1);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 2U), 2);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 3U), 3);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 4U), 4);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 5U), 5);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 6U), 6);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 7U), 7);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 8U), 8);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 9U), 9);

	/* remove all odd integers */
	dynamic_array_remove_element_at_index(int, array, 9U);
	dynamic_array_remove_element_at_index(int, array, 7U);
	dynamic_array_remove_element_at_index(int, array, 5U);
	dynamic_array_remove_element_at_index(int, array, 3U);
	dynamic_array_remove_element_at_index(int, array, 1U);

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 5U);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 0U), 0);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 1U), 2);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 2U), 4);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 3U), 6);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 4U), 8);

	/* add elements at the start and the end */
	dynamic_array_add_element_at_index(int, array, 0U, -2);
	dynamic_array_append_element(int, array, 10);

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 7U);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 0U), -2);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 1U), 0);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 2U), 2);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 3U), 4);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 4U), 6);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 5U), 8);
	ASSERT_INT_EQUAL(dynamic_array_element(int, array, 6U), 10);

	dynamic_array_delete(array);
	unit_test_pool_deinit();
}
 
TEST(user_defined_type_test, "User-defined type")
{
	typedef struct date_type {short year; unsigned char month; unsigned char day;} date_type;
	typedef struct person_type {const char *first_name; const char *last_name; date_type date_of_birth;} person_type;
	const size_t initial_size = 0U;
	dynamic_array_type(char) array = {0};
	const person_type John_Smith = {"John", "Smith", {1990, 1, 1}};
	const person_type Rebecca_Parker = {"Rebecca", "Parker", {1987, 12, 20}};
	const person_type people[] = {
		{"Peter", "Davidson", {2000, 4, 1}},
		{"Jennifer", "Ford", {2001, 1, 15}},
		{"Daniel", "Webb", {2005, 7, 4}}
	};

	unit_test_pool_init();
	array = dynamic_array_create_with_allocator(person_type, initial_size, unit_test_allocator);

	dynamic_array_append_element(person_type, array, John_Smith);
	dynamic_array_append_element(person_type, array, Rebecca_Parker);

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 2U);

	ASSERT( strcmp(dynamic_array_element(person_type, array, 0U).first_name, "John") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 0U).last_name, "Smith") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 0U).date_of_birth.year, 1990 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 0U).date_of_birth.month, 1 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 0U).date_of_birth.day, 1 );
	
	ASSERT( strcmp(dynamic_array_element(person_type, array, 1U).first_name, "Rebecca") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 1U).last_name, "Parker") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 1U).date_of_birth.year, 1987 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 1U).date_of_birth.month, 12 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 1U).date_of_birth.day, 20 );

	dynamic_array_append_elements(person_type, array, people, sizeof_array(people));

	ASSERT_UINT_EQUAL(dynamic_array_size(array), 5U);

	ASSERT( strcmp(dynamic_array_element(person_type, array, 0U).first_name, "John") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 0U).last_name, "Smith") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 0U).date_of_birth.year, 1990 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 0U).date_of_birth.month, 1 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 0U).date_of_birth.day, 1 );
	
	ASSERT( strcmp(dynamic_array_element(person_type, array, 1U).first_name, "Rebecca") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 1U).last_name, "Parker") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 1U).date_of_birth.year, 1987 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 1U).date_of_birth.month, 12 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 1U).date_of_birth.day, 20 );

	ASSERT( strcmp(dynamic_array_element(person_type, array, 2U).first_name, "Peter") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 2U).last_name, "Davidson") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 2U).date_of_birth.year, 2000 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 2U).date_of_birth.month, 4 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 2U).date_of_birth.day, 1 );

	ASSERT( strcmp(dynamic_array_element(person_type, array, 3U).first_name, "Jennifer") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 3U).last_name, "Ford") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 3U).date_of_birth.year, 2001 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 3U).date_of_birth.month, 1 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 3U).date_of_birth.day, 15 );

	ASSERT( strcmp(dynamic_array_element(person_type, array, 4U).first_name, "Daniel") == 0 );
	ASSERT( strcmp(dynamic_array_element(person_type, array, 4U).last_name, "Webb") == 0 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 4U).date_of_birth.year, 2005 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 4U).date_of_birth.month, 7 );
	ASSERT_INT_EQUAL( dynamic_array_element(person_type, array, 4U).date_of_birth.day, 4 );

	dynamic_array_delete(array);	
	unit_test_pool_deinit();
}

DEFINE_LIST_OF_TESTS(list_of_tests) {
	char_dynamic_array_with_no_buffer,
	size_test_for_char_dynamic_array_with_no_element,
	out_of_bounds_access_to_char_dynamic_array_with_no_element,
	test_for_char_dynamic_array_initialized_with_one_element,
	value_test_for_char_dynamic_array_with_one_element,
	char_dynamic_array_with_one_element_and_a_new_element_is_added_to_the_back,
	char_dynamic_array_with_one_element_and_a_new_element_is_added_to_the_front,
	string_operations_on_char_dynamic_array,
	dynamic_integer_array,
	user_defined_type_test
};

int main(void)
{	
	PRINT_FILE_NAME();
	RUN_TESTS(list_of_tests);
	PRINT_TEST_STATISTICS(list_of_tests);
	return 0;
}
