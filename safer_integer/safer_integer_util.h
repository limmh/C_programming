#ifndef SAFER_INTEGER_UTIL_H
#define SAFER_INTEGER_UTIL_H

#include "macro_stringify.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

static void safer_integer_assert(FILE *file, int Boolean_condition, const char *file_name, int line_number, const char *message)
{
	assert(file != NULL);
	assert(file_name != NULL);
	assert(message != NULL);
	if (!Boolean_condition) {
		fprintf(file, "File: %s\nAssertion failure at line %d: %s\n", file_name, line_number, message);
	}
}

/* Macro for safer integer assertion (can be overridden by your own custom version) */
#ifndef SAFER_INTEGER_ASSERT
#define SAFER_INTEGER_ASSERT(condition) safer_integer_assert(stderr, condition, __FILE__, __LINE__, STRINGIFY(condition))
#endif

/*
Macros which check whether an integer is within a range [inclusively or exclusively].
Make sure all the macro arguments have the same signedness, i.e. all signed or all unsigned.
Make sure the minimum value [or lower bound value] is smaller than the maximum value [or upper bound value].
*/
#define INTEGER_IS_WITHIN_RANGE(integer, minimum, maximum) ((integer) >= (minimum) && (integer) <= (maximum))

#define INTEGER_IS_WITHIN_RANGE_EXCLUSIVE(integer, lower_bound, upper_bound) \
	((integer) > (lower_bound) && (integer) < (upper_bound))

#endif
