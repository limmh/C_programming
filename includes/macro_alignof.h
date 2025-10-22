#ifndef MACRO_ALIGNOF_H
#define MACRO_ALIGNOF_H

#if defined( __cplusplus) && (__cplusplus >= 201103L)
#define ALIGNOF(TYPE) alignof(TYPE)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#include <stdalign.h>
#define ALIGNOF(TYPE) alignof(TYPE)
#else
#include <stddef.h>
#define ALIGNOF(TYPE) offsetof(struct {char ch; TYPE data;}, data)
#endif

#endif
