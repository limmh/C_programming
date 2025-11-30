#ifndef ABI_COMPATIBILITY_TEST_H
#define ABI_COMPATIBILITY_TEST_H

#include "reference_type_emulation.h"

#ifdef __cplusplus
extern "C" {
#endif

void int_swap(int REF(a), int REF(b));

int REF( int_ref_max(int REF(a), int REF(b)) );

int REF( int_ref_min(int REF(a), int REF(b)) );

typedef struct int_array_10_type
{
	int array[10];
} int_array_10_type;

int_array_10_type REF( int_array_10_ref_max_sum(int_array_10_type REF(a), int_array_10_type REF(b)) );

int_array_10_type REF( int_array_10_ref_min_sum(int_array_10_type REF(a), int_array_10_type REF(b)) );

void int_array_10_print(const int REF(ref_array)[10]);

typedef struct int_array_10_refs_type
{
	int REF(ref_array_a)[10];
	int REF(ref_array_b)[10];
} int_array_10_refs_type;

int_array_10_refs_type int_array_10_refs_sort_v1(int_array_10_refs_type array_refs, int REF(sort_func)(const void *, const void *));

int_array_10_refs_type REF( int_array_10_refs_sort_v2(int_array_10_refs_type REF(array_refs), int REF(sort_func)(const void *, const void *)) );

#ifdef __cplusplus
}
#endif

#endif
