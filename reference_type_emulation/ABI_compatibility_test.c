#include "ABI_compatibility_test.h"
#include "sizeof_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void int_swap(int REF(a), int REF(b))
{
	const int tmp = DEREF(a);
	DEREF(a) = DEREF(b);
	DEREF(b) = tmp;
}

int REF(int_ref_max(int REF(a), int REF(b)))
{
	/* always returns the first reference if both variables being referenced have the same value */
	return (DEREF(a) >= DEREF(b)) ? a : b;
}

int REF(int_ref_min(int REF(a), int REF(b)))
{
	/* always returns the first reference if both variables being referenced have the same value */
	return (DEREF(a) <= DEREF(b)) ? a : b;
}

int_array_10_type REF(int_array_10_ref_max_sum(int_array_10_type REF(a), int_array_10_type REF(b)))
{
	const size_t array_size = sizeof_array(DEREF(a).array);
	int sum_of_a = 0, sum_of_b = 0;
	size_t index = 0U;

	for (; index < array_size; ++index) {
		sum_of_a += DEREF(a).array[index];
		sum_of_b += DEREF(b).array[index];
	}

	/* always returns the first array reference if both arrays have the same sum */
	return (sum_of_a >= sum_of_b) ? a : b;
}

int_array_10_type REF(int_array_10_ref_min_sum(int_array_10_type REF(a), int_array_10_type REF(b)))
{
	const size_t array_size = sizeof_array(DEREF(a).array);
	int sum_of_a = 0, sum_of_b = 0;
	size_t index = 0U;

	for (; index < array_size; ++index) {
		sum_of_a += DEREF(a).array[index];
		sum_of_b += DEREF(b).array[index];
	}

	/* always returns the first array reference if both arrays have the same sum */
	return (sum_of_a <= sum_of_b) ? a : b;
}

void int_array_10_print(const int REF(ref_array)[10])
{
	const size_t array_size = sizeof_array(DEREF(ref_array));
	size_t index = 0U;
	for (; index < array_size; ++index) {
		printf("%d%s", DEREF(ref_array)[index], ((index + 1U < array_size) ? ", " : ""));		
	}
}

int_array_10_refs_type int_array_10_refs_sort_v1(int_array_10_refs_type array_refs, int REF(sort_func)(const void *, const void *))
{
	const size_t array_size = sizeof_array(DEREF(array_refs.ref_array_a));
	const size_t element_size = sizeof(DEREF(array_refs.ref_array_a)[0]);
	void *ptr1 = &DEREF(array_refs.ref_array_a)[0];
	void *ptr2 = &DEREF(array_refs.ref_array_b)[0];
	qsort(ptr1, array_size, element_size, &DEREF(sort_func));
	qsort(ptr2, array_size, element_size, &DEREF(sort_func));
	return array_refs;	
}

int_array_10_refs_type REF(int_array_10_refs_sort_v2(int_array_10_refs_type REF(array_refs), int REF(sort_func)(const void *, const void *)))
{
	const size_t array_size = sizeof_array(DEREF(DEREF(array_refs).ref_array_a));
	const size_t element_size = sizeof(DEREF(DEREF(array_refs).ref_array_a)[0]);
	void *ptr1 = &DEREF(DEREF(array_refs).ref_array_a)[0];
	void *ptr2 = &DEREF(DEREF(array_refs).ref_array_b)[0];
	qsort(ptr1, array_size, element_size, &DEREF(sort_func));
	qsort(ptr2, array_size, element_size, &DEREF(sort_func));
	return array_refs;
}
