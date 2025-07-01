#ifndef INLINE_OR_STATIC_H
#define INLINE_OR_STATIC_H

#ifdef __cplusplus
#define INLINE_OR_STATIC inline
#else
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#define INLINE_OR_STATIC inline
#else
#define INLINE_OR_STATIC static
#endif
#endif

#endif
