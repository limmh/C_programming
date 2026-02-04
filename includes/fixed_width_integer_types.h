#ifndef FIXED_WIDTH_INTEGER_TYPES_H
#define FIXED_WIDTH_INTEGER_TYPES_H

#include <limits.h>
#include <stddef.h>

#if (defined(__cplusplus) && (__cplusplus >= 201103L)) || (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))

#include <stdint.h>

#if defined(INT64_MIN) && defined(INT64_MAX)
#define FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED 1
#else
#define FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED 0
#endif

#if defined(UINT64_MAX)
#define FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED 1
#else
#define FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED 0
#endif

#pragma message("The standard header file <stdint.h> has been included.")

#else /* C++ or C version detection */

#include "static_assert.h"

#pragma message("Using a custom implementation for fixed-width integer types.")
#define INT8_MAX   (0x7F)
#define INT8_MIN   (-INT8_MAX - 1)
#define UINT8_MAX  (0xFFU)
#define INT16_MAX  (0x7FFF)
#define INT16_MIN  (-INT16_MAX - 1)
#define UINT16_MAX (0xFFFFU)
#define INT32_MAX  (0x7FFFFFFF)
#define INT32_MIN  (-INT32_MAX - 1)
#define UINT32_MAX (0xFFFFFFFFU)

#if (LONG_MIN < INT32_MIN) && (LONG_MAX > INT32_MAX)
STATIC_ASSERT((sizeof(long) * CHAR_BIT) == 64U, "The size of long must be 64-bit.");
#define INT64_MAX (0x7FFFFFFFFFFFFFFFL)
#define INT64_MIN (-INT64_MAX - 1L)
#define FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED 1
#elif defined(LLONG_MIN) && (LLONG_MIN < INT32_MIN) && defined(LLONG_MAX) && (LLONG_MAX > INT32_MAX)
STATIC_ASSERT((sizeof(long long) * CHAR_BIT) == 64U, "The size of long long must be 64-bit.");
#define INT64_MAX (0x7FFFFFFFFFFFFFFFLL)
#define INT64_MIN (-INT64_MAX - 1LL)
#define FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED 1
#else
#define FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED 0
#endif

#if (ULONG_MAX > UINT32_MAX)
STATIC_ASSERT((sizeof(unsigned long) * CHAR_BIT) == 64U, "The size of unsigned long must be 64-bit.");
#define UINT64_MAX (0xFFFFFFFFFFFFFFFFUL)
#define FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED 1
#elif defined(ULLONG_MAX) && (ULLONG_MAX > UINT32_MAX)
STATIC_ASSERT((sizeof(unsigned long long) * CHAR_BIT) == 64U, "The size of unsigned long long must be 64-bit.");
#define UINT64_MAX (0xFFFFFFFFFFFFFFFFULL)
#define FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED 1
#else
#define FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED 0
#endif

#if (SCHAR_MIN == INT8_MIN) && (SCHAR_MAX == INT8_MAX)
STATIC_ASSERT((sizeof(signed char) * CHAR_BIT) == 8U, "The size of signed char must be 8-bit.");
#pragma message("The size of signed char is 8-bit.")
typedef signed char int8_t;
typedef int8_t int_least8_t;
typedef int8_t int_fast8_t;
#define INT_FAST8_MIN INT8_MIN
#define INT_FAST8_MAX INT8_MAX
#else
#error "int8_t cannot be implemented properly."
#endif

#if (UCHAR_MAX == UINT8_MAX)
STATIC_ASSERT((sizeof(unsigned char) * CHAR_BIT) == 8U, "The size of unsigned char must be 8-bit.");
#pragma message("The size of unsigned char is 8-bit.")
typedef unsigned char uint8_t;
typedef uint8_t uint_least8_t;
typedef uint8_t uint_fast8_t;
#define UINT_FAST8_MAX UINT8_MAX
#else
#error "uint8_t cannot be implemented properly."
#endif

#if (SHRT_MIN == INT16_MIN) && (SHRT_MAX == INT16_MAX)
STATIC_ASSERT((sizeof(short) * CHAR_BIT) == 16U, "The size of short must be 16-bit.");
#pragma message("The sizeof short is 16-bit.")
typedef short int16_t;
typedef int16_t int_least16_t;
#elif (INT_MIN == INT16_MIN) && (INT_MAX == INT16_MAX)
STATIC_ASSERT((sizeof(int) * CHAR_BIT) == 16U, "The size of int must be 16-bit.");
#pragma message("The size of int is 16-bit.")
typedef int int16_t;
typedef int16_t int_least16_t;
typedef int16_t int_fast16_t;
#define INT_FAST16_MIN INT_MIN
#define INT_FAST16_MAX INT_MAX
#else
#error "int16_t cannot be implemented properly."
#endif

#if (USHRT_MAX == UINT16_MAX)
STATIC_ASSERT((sizeof(unsigned short) * CHAR_BIT) == 16U, "The size of unsigned short must be 16-bit.");
#pragma message("The size of unsigned short is 16-bit.")
typedef unsigned short uint16_t;
typedef uint16_t uint_least16_t;
#elif (UINT_MAX == UINT16_MAX)
STATIC_ASSERT((sizeof(unsigned int) * CHAR_BIT) == 16U, "The size of unsigned int must be 16-bit.");
#pragma message("The size of unsigned int is 16-bit.")
typedef unsigned int uint16_t;
typedef uint16_t uint_least16_t;
typedef uint16_t uint_fast16_t;
#define UINT_FAST16_MAX UINT_MAX
#else
#error "uint16_t cannot be implemented properly."
#endif

#if (INT_MIN == INT32_MIN) && (INT_MAX == INT32_MAX)
STATIC_ASSERT((sizeof(int) * CHAR_BIT) == 32U, "The size of int must be 32-bit.");
#pragma message("The size of int is 32-bit.")
typedef int int32_t;
typedef int32_t int_least32_t;
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
#define INT_FAST16_MIN   INT_MIN
#define INT_FAST16_MAX   INT_MAX
#define INT_FAST32_MIN   INT_MIN
#define INT_FAST32_MAX   INT_MAX
#elif (LONG_MIN == INT32_MIN) && (LONG_MAX == INT32_MAX)
STATIC_ASSERT((sizeof(long) * CHAR_BIT) == 32U, "The size of long must be 32-bit.");
#pragma message("The size of long is 32-bit.")
typedef long int32_t;
typedef int32_t int_least32_t;
typedef int32_t int_fast32_t;
#define INT_FAST32_MIN   LONG_MIN
#define INT_FAST32_MAX   LONG_MAX
#else
#error "int32_t cannot be implemented properly."
#endif

#if (UINT_MAX == UINT32_MAX)
STATIC_ASSERT((sizeof(unsigned int) * CHAR_BIT) == 32U, "The size of unsigned int must be 32-bit.");
#pragma message("The size of unsigned int is 32-bit.")
typedef unsigned int uint32_t;
typedef uint32_t uint_least32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
#define UINT_FAST16_MAX  UINT_MAX
#define UINT_FAST32_MAX  UINT_MAX
#elif (ULONG_MAX == UINT32_MAX)
STATIC_ASSERT((sizeof(unsigned long) * CHAR_BIT) == 32U, "The size of unsigned long must be 32-bit.");
#pragma message("The size of unsigned long is 32-bit.")
typedef unsigned long uint32_t;
typedef uint32_t uint_least32_t;
typedef uint32_t uint_fast32_t;
#define UINT_FAST32_MAX  ULONG_MAX
#else
#error "uint32_t cannot be implemented properly."
#endif

#define INT_LEAST8_MIN    INT8_MIN
#define INT_LEAST8_MAX    INT8_MAX
#define INT_LEAST16_MIN   INT16_MIN
#define INT_LEAST16_MAX   INT16_MAX
#define INT_LEAST32_MIN   INT32_MIN
#define INT_LEAST32_MAX   INT32_MAX
#define UINT_LEAST8_MAX   UINT8_MAX
#define UINT_LEAST16_MAX  UINT16_MAX
#define UINT_LEAST32_MAX  UINT32_MAX

#if FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED
#if defined(_MSC_VER)
STATIC_ASSERT((sizeof(__int64) * CHAR_BIT) == 64U, "The size of __int64 must be 64-bit.");
#pragma message("The size of __int64 is 64-bit.")
typedef __int64 int64_t;
#elif (LONG_MIN == INT64_MIN) && (LONG_MAX == INT64_MAX)
STATIC_ASSERT((sizeof(long) * CHAR_BIT) == 64U, "The size of long must be 64-bit.");
#pragma message("The size of long is 64-bit.")
typedef long int64_t;
#else
STATIC_ASSERT((sizeof(long long) * CHAR_BIT) == 64U, "The size of long long must be 64-bit.");
#pragma message("The size of long long is 64-bit.")
typedef long long int64_t;
#endif
typedef int64_t int_least64_t;
typedef int64_t int_fast64_t;
typedef int64_t intmax_t;
#define INT_LEAST64_MIN   INT64_MIN
#define INT_LEAST64_MAX   INT64_MAX
#define INT_FAST64_MIN    INT64_MIN
#define INT_FAST64_MAX    INT64_MAX
#define INTMAX_MIN        INT64_MIN
#define INTMAX_MAX        INT64_MAX
#pragma message("64-bit signed integer type (int64_t) is supported.")
#else /* FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED */
typedef int32_t intmax_t;
#define INTMAX_MIN        INT32_MIN
#define INTMAX_MAX        INT32_MAX
#pragma message("64-bit signed integer type (int64_t) is NOT supported.")
#endif

#if FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED
#ifdef _MSC_VER
STATIC_ASSERT((sizeof(unsigned __int64) * CHAR_BIT) == 64U, "The size of unsigned __int64 must be 64-bit.");
#pragma message("The size of unsigned __int64 is 64-bit.")
typedef unsigned __int64 uint64_t; 
#elif (ULONG_MAX == UINT64_MAX)
STATIC_ASSERT((sizeof(unsigned long) * CHAR_BIT) == 64U, "The size of unsigned long must be 64-bit.");
#pragma message("The size of unsigned long is 64-bit.")
typedef unsigned long uint64_t;
#else
STATIC_ASSERT((sizeof(unsigned long long) * CHAR_BIT) == 64U, "The size of unsigned long long must be 64-bit.");
#pragma message("The size of unsigned long long is 64-bit.")
typedef unsigned long long uint64_t;
#endif
typedef uint64_t uint_least64_t;
typedef uint64_t uint_fast64_t;
typedef uint64_t uintmax_t;
#define UINT_LEAST64_MAX   UINT64_MAX
#define UINT_FAST64_MAX    UINT64_MAX
#define UINTMAX_MAX        UINT64_MAX
#pragma message("64-bit unsigned integer type (uint64_t) is supported.")
#else /* FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED */
typedef uint32_t uintmax_t;
#define UINTMAX_MAX        UINT32_MAX
#pragma message("64-bit unsigned integer type (uint64_t) is NOT supported.")
#endif

/* Integer types for storing addresses */
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(void*), "intptr_t must be of the same size as a pointer type.");
typedef ptrdiff_t intptr_t;
STATIC_ASSERT(sizeof(size_t) == sizeof(void*), "uintptr_t must be of the same size as a pointer type.");
typedef size_t uintptr_t;

/* Modify this part based on your computer architecture */
#if defined(_WIN64) || defined(WIN64)
STATIC_ASSERT((sizeof(void*) * CHAR_BIT) == 64U, "Windows 64-bit: A pointer type is supposed to be 64-bit.");
#pragma message("Windows 64-bit: The size of a pointer type is 64-bit.")
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN INT64_MIN
#endif
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX INT64_MAX
#endif
#ifndef SIZE_MAX
#define SIZE_MAX UINT64_MAX
#endif
#elif defined(_WIN32) || defined(WIN32)
STATIC_ASSERT((sizeof(void*) * CHAR_BIT) == 32U, "Windows 32-bit: A pointer type is supposed to be 32-bit.");
#pragma message("Windows 32-bit: The size of a pointer type is 32-bit.")
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN INT32_MIN
#endif
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX INT32_MAX
#endif
#ifndef SIZE_MAX
#define SIZE_MAX UINT32_MAX
#endif
#elif (LONG_MIN == INT64_MIN) && (LONG_MAX == INT64_MAX) && (ULONG_MAX == UINT64_MAX)
STATIC_ASSERT((sizeof(void*) * CHAR_BIT) == 64U, "A pointer type is supposed to be 64-bit.");
#pragma message("The size of a pointer type is 64-bit.")
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN INT64_MIN
#endif
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX INT64_MAX
#endif
#ifndef SIZE_MAX
#define SIZE_MAX UINT64_MAX
#endif
#elif (INT_MIN == INT32_MIN) && (INT_MAX == INT32_MAX) && (UINT_MAX == UINT32_MAX)
STATIC_ASSERT((sizeof(void*) * CHAR_BIT) == 32U, "A pointer type is supposed to be 32-bit.");
#pragma message("The size of a pointer type is 32-bit.")
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN INT32_MIN
#endif
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX INT32_MAX
#endif
#ifndef SIZE_MAX
#define SIZE_MAX UINT32_MAX
#endif
#elif (INT_MIN == INT16_MIN) && (INT_MAX == INT16_MAX) && (UINT_MAX == UINT16_MAX)
STATIC_ASSERT((sizeof(void*) * CHAR_BIT) == 16U, "A pointer type is supposed to be 16-bit.");
#pragma message("The size of a pointer type is 16-bit.")
#ifndef PTRDIFF_MIN
#define PTRDIFF_MIN INT16_MIN
#endif
#ifndef PTRDIFF_MAX
#define PTRDIFF_MAX INT16_MAX
#endif
#ifndef SIZE_MAX
#define SIZE_MAX UINT16_MAX
#endif
#else
#error "Please determine the width of the address space of your computer architecture and modify this part to implement PTRDIFF_MIN, PTRDIFF_MAX and SIZE_MAX."
#endif

#define INTPTR_MIN PTRDIFF_MIN
#define INTPTR_MAX PTRDIFF_MAX
#define UINTPTR_MAX SIZE_MAX

/* Function macros for minimum-width integer constants */
#define INT8_C(integer) (integer)
#define UINT8_C(integer) (integer##U)
#define INT16_C(integer) (integer)
#define UINT16_C(integer) (integer##U)

#if (INT_MIN == INT32_MIN) && (INT_MAX == INT32_MAX)
#define INT32_C(integer) (integer)
#elif (LONG_MIN == INT32_MIN) && (LONG_MAX == INT32_MAX)
#define INT32_C(integer) (integer##L)
#else
#define INT32_C(integer) (integer)
#endif

#if (UINT_MAX == UINT32_MAX)
#define UINT32_C(integer) (integer##U)
#elif (ULONG_MAX == UINT32_MAX)
#define UINT32_C(integer) (integer##UL)
#else
#define UINT32_C(integer) (integer##U)
#endif

#if (LONG_MIN == INT64_MIN) && (LONG_MAX == INT64_MAX)
#define INT64_C(integer) (integer##L)
#define INTMAX_C(integer) (integer##L)
#elif defined(LLONG_MIN) && (LLONG_MIN == INT64_MIN) && defined(LLONG_MAX) && (LLONG_MAX == INT64_MAX)
#define INT64_C(integer) (integer##LL)
#define INTMAX_C(integer) (integer##L)
#else
#define INT64_C(integer) (integer)
#define INTMAX_C(integer) (integer)
#endif

#if (ULONG_MAX == UINT64_MAX)
#define UINT64_C(integer) (integer##UL)
#define UINTMAX_C(integer) (integer##UL)
#elif defined(ULLONG_MAX) && (ULLONG_MAX == UINT64_MAX)
#define UINT64_C(integer) (integer##ULL)
#define UINTMAX_C(integer) (integer##ULL)
#else
#define UINT64_C(integer) (integer)
#define UINTMAX_C(integer) (integer)
#endif

#endif /* C++ or C version detection */

/* Bit width macros (available since C23) */
#ifndef INT8_WIDTH
#pragma message("INT8_WIDTH is not defined and it will be defined.")
#define INT8_WIDTH 8U
#endif /* INT8_WIDTH */

#ifndef INT_LEAST8_WIDTH
#pragma message("INT_LEAST8_WIDTH is not defined and it will be defined.")
#if (INT_LEAST8_MIN == INT8_MIN) && (INT_LEAST8_MAX == INT8_MAX) 
#define INT_LEAST8_WIDTH 8U
#elif (INT_LEAST8_MIN == INT16_MIN) && (INT_LEAST8_MAX == INT16_MAX)
#define INT_LEAST8_WIDTH 16U
#elif (INT_LEAST8_MIN == INT32_MIN) && (INT_LEAST8_MAX == INT32_MAX)
#define INT_LEAST8_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INT_LEAST8_MIN == INT64_MIN) && (INT_LEAST8_MAX == INT64_MAX)
#define INT_LEAST8_WIDTH 64U
#else
#pragma message("Detection of width failed for int_least8_t, its width is assumed to be 8-bit.")
#define INT_LEAST8_WIDTH INT8_WIDTH
#endif
#endif /* INT_LEAST8_WIDTH */

#ifndef INT_FAST8_WIDTH
#pragma message("INT_FAST8_WIDTH is not defined and it will be defined.")
#if (INT_FAST8_MIN == INT8_MIN) && (INT_FAST8_MAX == INT8_MAX) 
#define INT_FAST8_WIDTH 8U
#elif (INT_FAST8_MIN == INT16_MIN) && (INT_FAST8_MAX == INT16_MAX)
#define INT_FAST8_WIDTH 16U
#elif (INT_FAST8_MIN == INT32_MIN) && (INT_FAST8_MAX == INT32_MAX)
#define INT_FAST8_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INT_FAST8_MIN == INT64_MIN) && (INT_FAST8_MAX == INT64_MAX)
#define INT_FAST8_WIDTH 64U
#else
#pragma message("Detection of width failed for int_fast8_t, its width is assumed to be 8-bit.")
#define INT_FAST8_WIDTH INT8_WIDTH
#endif
#endif /* INT_FAST8_WIDTH */

#ifndef UINT8_WIDTH
#pragma message("UINT8_WIDTH is not defined and it will be defined.")
#define UINT8_WIDTH 8U
#endif /* UINT8_WIDTH */

#ifndef UINT_LEAST8_WIDTH
#pragma message("UINT_LEAST8_WIDTH is not defined and it will be defined.")
#if UINT_LEAST8_MAX == UINT8_MAX 
#define UINT_LEAST8_WIDTH 8U
#elif UINT_LEAST8_MAX == UINT16_MAX
#define UINT_LEAST8_WIDTH 16U
#elif UINT_LEAST8_MAX == UINT32_MAX
#define UINT_LEAST8_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINT_LEAST8_MAX == UINT64_MAX)
#define UINT_LEAST8_WIDTH 64U
#else
#pragma message("Detection of width failed for uint_least8_t, its width is assumed to be 8-bit.")
#define UINT_LEAST8_WIDTH UINT8_WIDTH
#endif
#endif /* UINT_LEAST8_WIDTH */

#ifndef UINT_FAST8_WIDTH
#pragma message("UINT_FAST8_WIDTH is not defined and it will be defined.")
#if UINT_FAST8_MAX == UINT8_MAX 
#define UINT_FAST8_WIDTH 8U
#elif UINT_FAST8_MAX == UINT16_MAX
#define UINT_FAST8_WIDTH 16U
#elif UINT_FAST8_MAX == UINT32_MAX
#define UINT_FAST8_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINT_FAST8_MAX == UINT64_MAX)
#define UINT_FAST8_WIDTH 64U
#else
#pragma message("Detection of width failed for uint_fast8_t, its width is assumed to be 8-bit.")
#define UINT_FAST8_WIDTH UINT8_WIDTH
#endif
#endif /* UINT_FAST8_WIDTH */

#ifndef INT16_WIDTH
#pragma message("INT16_WIDTH is not defined and it will be defined.")
#define INT16_WIDTH 16U
#endif /* INT16_WIDTH */

#ifndef INT_LEAST16_WIDTH
#pragma message("INT_LEAST16_WIDTH is not defined and it will be defined.")
#if (INT_LEAST16_MIN == INT16_MIN) && (INT_LEAST16_MAX == INT16_MAX)
#define INT_LEAST16_WIDTH 16U
#elif (INT_LEAST16_MIN == INT32_MIN) && (INT_LEAST16_MAX == INT32_MAX)
#define INT_LEAST16_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INT_LEAST16_MIN == INT64_MIN) && (INT_LEAST16_MAX == INT64_MAX)
#define INT_LEAST16_WIDTH 64U
#else
#pragma message("Detection of width failed for int_least16_t, its width is assumed to be 16-bit.")
#define INT_LEAST16_WIDTH INT16_WIDTH
#endif
#endif /* INT_LEAST16_WIDTH */

#ifndef INT_FAST16_WIDTH
#pragma message("INT_FAST16_WIDTH is not defined and it will be defined.")
#if (INT_FAST16_MIN == INT16_MIN) && (INT_FAST16_MAX == INT16_MAX)
#define INT_FAST16_WIDTH 16U
#elif (INT_FAST16_MIN == INT32_MIN) && (INT_FAST16_MAX == INT32_MAX)
#define INT_FAST16_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INT_FAST16_MIN == INT64_MIN) && (INT_FAST16_MAX == INT64_MAX)
#define INT_FAST16_WIDTH 64U
#else
#pragma message("Detection of width failed for int_fast16_t, its width is assumed to be 16-bit.")
#define INT_FAST16_WIDTH INT16_WIDTH
#endif
#endif /* INT_FAST16_WIDTH */

#ifndef UINT16_WIDTH
#pragma message("UINT16_WIDTH is not defined and it will be defined.")
#define UINT16_WIDTH 16U
#endif /* UINT16_WIDTH */

#ifndef UINT_LEAST16_WIDTH
#pragma message("UINT_LEAST16_WIDTH is not defined and it will be defined.")
#if UINT_LEAST16_MAX == UINT16_MAX
#define UINT_LEAST16_WIDTH 16U
#elif UINT_LEAST16_MAX == UINT32_MAX
#define UINT_LEAST16_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINT_LEAST16_MAX == UINT64_MAX)
#define UINT_LEAST16_WIDTH 64U
#else
#pragma message("Detection of width failed for uint_least16_t, its width is assumed to be 16-bit.")
#define UINT_LEAST16_WIDTH UINT16_WIDTH
#endif
#endif /* UINT_LEAST16_WIDTH  */

#ifndef UINT_FAST16_WIDTH
#pragma message("UINT_FAST16_WIDTH is not defined and it will be defined.")
#if UINT_FAST16_MAX == UINT16_MAX
#define UINT_FAST16_WIDTH 16U
#elif UINT_FAST16_MAX == UINT32_MAX
#define UINT_FAST16_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINT_FAST16_MAX == UINT64_MAX)
#define UINT_FAST16_WIDTH 64U
#else
#pragma message("Detection of width failed for uint_fast16_t, its width is assumed to be 16-bit.")
#define UINT_FAST16_WIDTH UINT16_WIDTH
#endif
#endif /* UINT_FAST16_WIDTH */

#ifndef INT32_WIDTH
#pragma message("INT32_WIDTH is not defined and it will be defined.")
#define INT32_WIDTH 32U
#endif /* INT32_WIDTH */

#ifndef INT_LEAST32_WIDTH
#pragma message("INT_LEAST32_WIDTH is not defined and it will be defined.")
#if (INT_LEAST32_MIN == INT32_MIN) && (INT_LEAST32_MAX == INT32_MAX)
#define INT_LEAST32_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INT_LEAST32_MIN == INT64_MIN) && (INT_LEAST32_MAX == INT64_MAX)
#define INT_LEAST32_WIDTH 64U
#else
#pragma message("Detection of width failed for int_least32_t, its width is assumed to be 32-bit.")
#define INT_LEAST32_WIDTH INT32_WIDTH
#endif
#endif /* INT_LEAST32_WIDTH */

#ifndef INT_FAST32_WIDTH
#pragma message("INT_FAST32_WIDTH is not defined and it will be defined.")
#if (INT_FAST32_MIN == INT32_MIN) && (INT_FAST32_MAX == INT32_MAX)
#define INT_FAST32_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INT_FAST32_MIN == INT64_MIN) && (INT_FAST32_MAX == INT64_MAX)
#define INT_FAST32_WIDTH 64U
#else
#pragma message("Detection of width failed for int_fast32_t, its width is assumed to be 32-bit.")
#define INT_FAST32_WIDTH INT32_WIDTH
#endif
#endif /* INT_FAST32_WIDTH */

#ifndef UINT32_WIDTH
#pragma message("UINT32_WIDTH is not defined and it will be defined.")
#define UINT32_WIDTH 32U
#endif /* UINT32_WIDTH */

#ifndef UINT_LEAST32_WIDTH
#pragma message("UINT_LEAST32_WIDTH is not defined and it will be defined.")
#if UINT_LEAST32_MAX == UINT32_MAX
#define UINT_LEAST32_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINT_LEAST32_MAX == UINT64_MAX)
#define UINT_LEAST32_WIDTH 64U
#else
#pragma message("Detection of width failed for uint_least32_t, its width is assumed to be 32-bit.")
#define UINT_LEAST32_WIDTH UINT32_WIDTH
#endif
#endif /* UINT_LEAST32_WIDTH */

#ifndef UINT_FAST32_WIDTH
#pragma message("UINT_FAST32_WIDTH is not defined and it will be defined.")
#if UINT_FAST32_MAX == UINT32_MAX
#define UINT_FAST32_WIDTH 32U
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINT_FAST32_MAX == UINT64_MAX)
#define UINT_FAST32_WIDTH 64U
#else
#pragma message("Detection of width failed for uint_fast32_t, its width is assumed to be 32-bit.")
#define UINT_FAST32_WIDTH UINT32_WIDTH
#endif
#endif /* UINT_FAST32_WIDTH */

#if FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED
#ifndef INT64_WIDTH
#pragma message("INT64_WIDTH is not defined and it will be defined.")
#define INT64_WIDTH 64U
#endif
#ifndef INT_LEAST64_WIDTH
#pragma message("INT_LEAST64_WIDTH is not defined and it will be defined.")
#define INT_LEAST64_WIDTH INT64_WIDTH
#endif
#ifndef INT_FAST64_WIDTH
#pragma message("INT_FAST64_WIDTH is not defined and it will be defined.")
#define INT_FAST64_WIDTH INT64_WIDTH
#endif
#endif /* FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED */

#if FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED
#ifndef UINT64_WIDTH
#pragma message("UINT64_WIDTH is not defined and it will be defined.")
#define UINT64_WIDTH 64U
#endif
#ifndef UINT_LEAST64_WIDTH
#pragma message("UINT_LEAST64_WIDTH is not defined and it will be defined.")
#define UINT_LEAST64_WIDTH UINT64_WIDTH
#endif
#ifndef UINT_FAST64_WIDTH
#pragma message("UINT_FAST64_WIDTH is not defined and it will be defined.")
#define UINT_FAST64_WIDTH UINT64_WIDTH
#endif
#endif /* FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED */

#ifndef INTMAX_WIDTH
#pragma message("INTMAX_WIDTH is not defined and it will be defined.")
#if (INTMAX_MIN == INT32_MIN) && (INTMAX_MAX == INT32_MAX)
#define INTMAX_WIDTH INT32_WIDTH
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INTMAX_MIN == INT64_MIN) && (INTMAX_MAX == INT64_MAX)
#define INTMAX_WIDTH INT64_WIDTH
#else
#pragma message("Detection of width failed for intmax_t, its width is assumed to be 32-bit.")
#define INTMAX_WIDTH INT32_WIDTH
#endif
#endif /* INTMAX_WIDTH */

#ifndef UINTMAX_WIDTH
#pragma message("UINTMAX_WIDTH is not defined and it will be defined.")
#if UINTMAX_MAX == UINT32_MAX
#define UINTMAX_WIDTH UINT32_WIDTH
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (UINTMAX_MAX == UINT64_MAX)
#define UINTMAX_WIDTH UINT64_WIDTH
#else
#pragma message("Detection of width failed for uintmax_t, its width is assumed to be 32-bit.")
#define UINTMAX_WIDTH UINT32_WIDTH
#endif
#endif /* UINTMAX_WIDTH */

#ifndef INTPTR_WIDTH
#pragma message("INTPTR_WIDTH is not defined and it will be defined.")
#if (INTPTR_MIN == INT16_MIN) && (INTPTR_MAX == INT16_MAX)
#define INTPTR_WIDTH INT16_WIDTH
#elif (INTPTR_MIN == INT32_MIN) && (INTPTR_MAX == INT32_MAX)
#define INTPTR_WIDTH INT32_WIDTH
#elif FIXED_WIDTH_INTEGER_TYPE_INT64_IS_SUPPORTED && (INTPTR_MIN == INT64_MIN) && (INTPTR_MAX == INT64_MAX)
#define INTPTR_WIDTH INT64_WIDTH
#else
#pragma message("Detection of width failed for intptr_t. INTPTR_WIDTH will not be defined.")
#endif
#endif /* INTPTR_WIDTH */

#ifndef UINTPTR_WIDTH
#pragma message("UINTPTR_WIDTH is not defined and it will be defined.")
#if UINTPTR_MAX == UINT16_MAX
#define UINTPTR_WIDTH UINT16_WIDTH
#elif UINTPTR_MAX == UINT32_MAX
#define UINTPTR_WIDTH UINT32_WIDTH
#elif FIXED_WIDTH_INTEGER_TYPE_UINT64_IS_SUPPORTED && (UINTPTR_MAX == UINT64_MAX)
#define UINTPTR_WIDTH UINT64_WIDTH
#else
#pragma message("Detection of width failed for uintptr_t. UINTPTR_WIDTH will not be defined.")
#endif
#endif /* UINTPTR_WIDTH */

#endif /* include guard */
