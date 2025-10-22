#ifndef BOOLEAN_TYPE_H
#define BOOLEAN_TYPE_H

#if defined(__cplusplus)

typedef bool Boolean_type;
#define Boolean_false false
#define Boolean_true true

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)

#if __STDC_VERSION__ < 202311L
#include <stdbool.h>
#endif

typedef bool Boolean_type;
#define Boolean_false false
#define Boolean_true true

#else

typedef unsigned char Boolean_type;
#define Boolean_false 0
#define Boolean_true (!Boolean_false)

#endif

#endif
