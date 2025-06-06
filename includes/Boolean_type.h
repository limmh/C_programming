#ifndef BOOLEAN_TYPE_H
#define BOOLEAN_TYPE_H

#ifdef __cplusplus
typedef bool Boolean_type;
#define Boolean_false false
#define Boolean_true true
#else
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#include <stdbool.h>
typedef bool Boolean_type;
#define Boolean_false false
#define Boolean_true true
#else
typedef unsigned char Boolean_type;
#define Boolean_false 0
#define Boolean_true (!Boolean_false)
#endif
#endif

#endif
