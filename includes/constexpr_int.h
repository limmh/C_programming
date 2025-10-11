#ifndef CONSTEXPR_INT_H
#define CONSTEXPR_INT_H

#include "macro_stringify.h"

/*
Usage example:

int main(void)
{
	CONSTEXPR_INT(array_size, 10);
	int array[array_size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t i = 0U;
	for (; i < array_size; ++i) {
		printf("%d\n", array[i]);
	}
	return 0;
}

Note:
Make sure the second argument is really a constant expression.
*/

#if defined(__cplusplus)

#if __cplusplus >= 201103L
#pragma message("C++ standard: " STRINGIFY(__cplusplus) ", using constexpr int")
#define CONSTEXPR_INT(name, constant_expression) constexpr int name = (constant_expression)
#else
#pragma message("C++ standard: " STRINGIFY(__cplusplus) ", using const int")
#define CONSTEXPR_INT(name, constant_expression) const int name = (constant_expression)
#endif /* C++ standard detection */

#elif defined(__STDC_VERSION__)

#if __STDC_VERSION__ >= 202311L
#pragma message("C standard: " STRINGIFY(__STDC_VERSION__) ", using constexpr int")
#define CONSTEXPR_INT(name, constant_expression) constexpr int name = (constant_expression)
#else
#pragma message("C standard: " STRINGIFY(__STDC_VERSION__) ", using enum")
#define CONSTEXPR_INT(name, constant_expression) enum { name = (constant_expression) }
#endif /* C standard detection */

#elif defined(__STDC__)

#pragma message("C standard: probably C89/C90, using enum")
#define CONSTEXPR_INT(name, constant_expression) enum { name = (constant_expression) }

#else

#pragma message("Unknown C standard, using enum")
#define CONSTEXPR_INT(name, constant_expression) enum { name = (constant_expression) }

#endif

#endif
