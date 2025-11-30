#include "ABI_compatibility_test.h"
#include "sizeof_array.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

static void print_newline(void)
{
	printf("\n");
}

static int compare_smaller_than(const void *p1, const void *p2)
{
	const int *ip1 = (const int*) p1;
	const int *ip2 = (const int*) p2;
	int result = 0;

	assert(ip1 != NULL);
	assert(ip2 != NULL);

	if (*ip1 < *ip2) {
		result = -1;
	} else if (*ip1 == *ip2) {
		result = 0;
	} else {
		result = 1;
	}

	return result;
}

static int compare_greater_than(const void *p1, const void *p2)
{
	const int *ip1 = (const int*) p1;
	const int *ip2 = (const int*) p2;
	int result = 0;

	assert(ip1 != NULL);
	assert(ip2 != NULL);

	if (*ip1 > *ip2) {
		result = -1;
	} else if (*ip1 == *ip2) {
		result = 0;
	} else {
		result = 1;
	}

	return result;
}

int main(void)
{
	int a = INT_MIN, b = INT_MAX;
	int_array_10_type array_a = {{0}}, array_b = {{0}};
	const size_t array_size = sizeof_array(array_a.array);

	for (size_t index = 0U; index < array_size; ++index) {
		array_a.array[index] = (int) index;
		array_b.array[index] = (int) index + 1;
	}

	printf("Before swapping values: a = %d, b = %d\n", a, b);
	int_swap(REF_OF(a), REF_OF(b));
	printf("After swapping values : a = %d, b = %d\n", a, b);

	const int REF(ref_max) = int_ref_max(REF_OF(a), REF_OF(b));
	const int REF(ref_min) = int_ref_min(REF_OF(a), REF_OF(b));

	if (&DEREF(ref_max) == &a) {
		printf("a (%d) is greater than b (%d)\n", a, b);
	} else if (&DEREF(ref_max) == &b) {
		printf("b (%d) is greater than a (%d)\n", b, a);
	}

	if(&DEREF(ref_min) == &a) {
		printf("a (%d) is smaller than b (%d)\n", a, b);
	} else if (&DEREF(ref_min) == &b) {
		printf("b (%d) is smaller than a (%d)\n", b, a);
	}

	printf("Integer array a: ");
	int_array_10_print(REF_OF(array_a.array));
	print_newline();
	printf("Integer array b: ");
	int_array_10_print(REF_OF(array_b.array));
	print_newline();

	int_array_10_type REF(ref_array_max_sum) = int_array_10_ref_max_sum(REF_OF(array_a), REF_OF(array_b));
	int_array_10_type REF(ref_array_min_sum) = int_array_10_ref_min_sum(REF_OF(array_a), REF_OF(array_b));

	if (&DEREF(ref_array_max_sum) == &array_a) {
		printf("Array a has a greater sum than array b.\n");
	} else if (&DEREF(ref_array_max_sum) == &array_b) {
		printf("Array b has a greater sum than array a.\n");
	}

	if (&DEREF(ref_array_min_sum) == &array_a) {
		printf("Array a has a smaller sum than array b.\n");
	} else if (&DEREF(ref_array_min_sum) == &array_b) {
		printf("Array b has a smaller sum than array a.\n");
	}

	printf("Round 1 of sorting\n");
	int_array_10_refs_type array_refs_1 = {REF_OF(array_a.array), REF_OF(array_b.array)};
	int_array_10_refs_type array_refs_2 = int_array_10_refs_sort_v1(array_refs_1, REF_OF(compare_greater_than));
	
	printf("Integer array a: ");
	int_array_10_print(array_refs_2.ref_array_a);
	print_newline();
	printf("Integer array b: ");
	int_array_10_print(array_refs_2.ref_array_b);
	print_newline();

	printf("Round 2 of sorting\n");	
	int_array_10_refs_type REF(ref_array_refs) = int_array_10_refs_sort_v2(REF_OF(array_refs_2), REF_OF(compare_smaller_than));
	printf("Integer array a: ");
	int_array_10_print(DEREF(ref_array_refs).ref_array_a);
	print_newline();
	printf("Integer array b: ");
	int_array_10_print(DEREF(ref_array_refs).ref_array_b);
	print_newline();

	return 0;
}
