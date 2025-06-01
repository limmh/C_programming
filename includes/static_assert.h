#ifndef STATIC_ASSERT_H
#define STATIC_ASSERT_H
/*
Compile time assertion which is applicable to C89 and C99
Note:
- When compiling using pre-C11 or pre-C++11 standards, there will be warnings about unused variables if warnings are enabled.
- Manually define STATIC_ASSERT_AVAILABLE to 1 in the compiler flags if static_assert is supported by your compiler, but
  the conditional preprocessor logic below is not applicable for your compiler.
*/

#ifndef STATIC_ASSERT_AVAILABLE
#if defined(__cplusplus) && ( __cplusplus >= 201103L)
#define STATIC_ASSERT_AVAILABLE 1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#include <assert.h>
#define STATIC_ASSERT_AVAILABLE 1
#else
#define STATIC_ASSERT_AVAILABLE 0
#endif
#endif

#if STATIC_ASSERT_AVAILABLE == 1
#define STATIC_ASSERT(condition, message) static_assert(condition, message)
#else
#include "macro_concatenate.h"
#if defined(__COUNTER__)
#define STATIC_ASSERT(condition, message) static const char * const CONCATENATE(static_assert_message_, __COUNTER__)[(condition) ? 1 : -1] = {message}
#elif defined(__LINE__)
#define STATIC_ASSERT(condition, message) static const char * const CONCATENATE(static_assert_message_, __LINE__)[(condition) ? 1 : -1] = {message}
#warning The static_assert macro cannot be implemented properly because __COUNTER__ is not defined by your compiler.
#warning Only one instance of static_assert is allowed on each line.
#else
#error The static_assert macro cannot be implemented because neither __COUNTER__ nor __LINE__ is defined by your compiler.
#endif
#endif
#endif
