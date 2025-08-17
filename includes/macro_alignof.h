#ifndef MACRO_ALIGNOF_H
#define MACRO_ALIGNOF_H

#ifndef STANDARD_ALIGNOF_IS_AVAILABLE
#if defined( __cplusplus) && (__cplusplus >= 201103L)
#define STANDARD_ALIGNOF_IS_AVAILABLE 1
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#define STANDARD_ALIGNOF_IS_AVAILABLE 1
#else
#define STANDARD_ALIGNOF_IS_AVAILABLE 0
#endif
#endif

#if STANDARD_ALIGNOF_IS_AVAILABLE == 1
#ifndef __cplusplus
#include <stdalign.h>
#endif
#define ALIGNOF(TYPE) alignof(TYPE)
#else
#include <stddef.h>
#define ALIGNOF(TYPE) offsetof(struct {char ch; TYPE data;}, data)
#endif

#endif
