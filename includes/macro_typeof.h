#ifndef MACRO_TYPEOF_H
#define MACRO_TYPEOF_H

#include "macro_stringify.h"

/*
Usage example:

int main(void)
{
	int a = 0;
	TYPEOF(a) b = a;
	return b;
}

Notes:
- If MSVC does not support decltype for C++, the TYPEOF macro will not work.
- If your compiler does not support the __typeof__ operator, then the TYPEOF macro will not work.
*/

#if defined(__cplusplus)

#if __cplusplus >= 201103L
#pragma message("C++ standard: " STRINGIFY(__cplusplus) ", defining TYPEOF as decltype")
#include <type_traits>
#define TYPEOF(expression) typename std::remove_reference<decltype(expression)>::type
#elif defined(_MSC_VER)
#pragma message("MSVC C++ standard: " STRINGIFY(__cplusplus) ", trying luck by defining TYPEOF as decltype")
#include <type_traits>
#define TYPEOF(expression) typename std::remove_reference<decltype(expression)>::type
#else
#pragma message("C++ standard: " STRINGIFY(__cplusplus) ", trying luck by defining TYPEOF as __typeof__")
#define TYPEOF(expression) __typeof__(expression)
#endif /* C++ standard detection */

#elif defined(__STDC_VERSION__)

#if __STDC_VERSION__ >= 202311L
#pragma message("C standard: " STRINGIFY(__STDC_VERSION__) ", defining TYPEOF as typeof")
#define TYPEOF(expression) typeof(expression)
#else
#pragma message("C standard: " STRINGIFY(__STDC_VERSION__) ", trying luck by defining TYPEOF as __typeof__")
#define TYPEOF(expression) __typeof__(expression)
#endif /* C standard detection */

#elif defined(__STDC__)

#pragma message("C standard: Probably C89/C90, trying luck by defining TYPEOF as __typeof__")
#define TYPEOF(expression) __typeof__(expression)

#else
	
#pragma message("Unknown C standard, trying luck by defining TYPEOF as __typeof__")
#define TYPEOF(expression) __typeof__(expression)

#endif

#endif
