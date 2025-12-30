#ifndef BOOLEAN_TYPE_H
#define BOOLEAN_TYPE_H

/*
Boolean_type : Boolean type for C89 (size: 1-byte, signedness: unsigned)
Boolean_false: Equivalent to false
Boolean_true : Equivalent to true
INTEGER_TO_BOOLEAN(integer): A macro which allows an integer to be properly converted to either Boolean_false or Boolean_true for C89

Notes:
- For C++, Boolean_type is the native bool type.
- For C99 and newer C standards, Boolean_type is _Bool.
- For C++, C99 and newer C standards, any integer will be implicitly converted to Boolean type properly
when being assigned to a Boolean variable.
*/

#if defined(__cplusplus)

typedef bool Boolean_type;
#define Boolean_false false
#define Boolean_true true
#define INTEGER_TO_BOOLEAN(integer) (integer)

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)

#if __STDC_VERSION__ < 202311L
#include <stdbool.h>
#endif

typedef bool Boolean_type;
#define Boolean_false false
#define Boolean_true true
#define INTEGER_TO_BOOLEAN(integer) (integer)

#else

typedef unsigned char Boolean_type;
#define Boolean_false 0
#define Boolean_true (!Boolean_false)
#define INTEGER_TO_BOOLEAN(integer) ((integer) != 0)

#endif

#endif
