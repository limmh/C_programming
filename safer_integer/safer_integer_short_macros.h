#ifndef SAFER_INTEGER_SHORT_MACROS_H
#define SAFER_INTEGER_SHORT_MACROS_H

#include "safer_integer.h"
#include "safer_fixed_width_integers.h"
#include "debug_mode_integer.h"

#ifndef SAFER_INTEGER_SHORT_MACROS_CUSTOM_ASSERTION_DEFINED
#ifdef NDEBUG
#include <stdio.h>
static void safer_integer_assert(FILE *file, int Boolean_condition, const char *file_name, int line_number, const char *message)
{
	if (!Boolean_condition) {
		fprintf(file, "%s (line %d)\nAssertion failure: %s\n", file_name, line_number, message);
	}
}
#define SAFER_INTEGER_ASSERT(condition) \
	safer_integer_assert(stderr, condition, __FILE__, __LINE__, #condition)
#else
#include <assert.h>
#define SAFER_INTEGER_ASSERT(condition) assert(condition)
#endif /* NDEBUG */
#endif /* SAFER_INTEGER_SHORT_MACROS_CUSTOM_ASSERTION_DEFINED */

#define INTEGER_IS_WITHIN_RANGE(integer, minimum, maximum) \
	((integer) >= (minimum) && (integer) <= (maximum))

/* Short macros for signed integer operations */
#ifndef siadd
#define siadd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	safer_int_add(a, b))
#else
#pragma message("siadd has been defined in another file. It will not be redefined.")
#endif

#ifndef siminus
#define siminus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	safer_int_minus(a, b))
#else
#pragma message("siminus has been defined in another file. It will not be redefined.")
#endif

#ifndef sisub
#define sisub(a, b) siminus(a, b)
#else
#pragma message("sisub has been defined in another file. It will not be redefined.")
#endif

#ifndef simul
#define simul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	safer_int_multiply(a, b))
#else
#pragma message("simul has been defined in another file. It will not be redefined.")
#endif

#ifndef sidiv
#define sidiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	safer_int_divide(a, b))
#else
#pragma message("sidiv has been defined in another file. It will not be redefined.")
#endif


#ifndef sladd
#define sladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	safer_long_add(a, b))
#else
#pragma message("sladd has been defined in another file. It will not be redefined.")
#endif

#ifndef slminus
#define slminus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	safer_long_minus(a, b))
#else
#pragma message("slminus has been defined in another file. It will not be redefined.")
#endif

#ifndef slsub
#define slsub(a, b) slminus(a, b)
#else
#pragma message("slsub has been defined in another file. It will not be redefined.")
#endif

#ifndef slmul
#define slmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	safer_long_multiply(a, b))
#else
#pragma message("slmul has been defined in another file. It will not be redefined.")
#endif

#ifndef sldiv
#define sldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	safer_long_divide(a, b))
#else
#pragma message("sldiv has been defined in another file. It will not be redefined.")
#endif


#if defined(LLONG_MIN) && defined(LLONG_MAX)

#ifndef slladd
#define slladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	safer_llong_add(a, b))
#else
#pragma message("slladd has been defined in another file. It will not be redefined.")
#endif

#ifndef sllminus
#define sllminus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	safer_llong_minus(a, b))
#else
#pragma message("sllminus has been defined in another file. It will not be redefined.")
#endif

#ifndef sllsub
#define sllsub(a, b) sllminus(a, b)
#else
#pragma message("sllsub has been defined in another file. It will not be redefined.")
#endif

#ifndef sllmul
#define sllmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	safer_llong_multiply(a, b))
#else
#pragma message("sllmul has been defined in another file. It will not be redefined.")
#endif

#ifndef slldiv
#define slldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	safer_llong_divide(a, b))
#else
#pragma message("slldiv has been defined in another file. It will not be redefined.")
#endif

#endif /* Are LLONG_MIN and LLONG_MAX defined? */


/* Short macros for unsigned integer operations */
#ifndef suiadd
#define suiadd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	safer_uint_add(a, b))
#else
#pragma message("suiadd has been defined in another file. It will not be redefined.")
#endif

#ifndef suiminus
#define suiminus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	safer_uint_minus(a, b))
#else
#pragma message("suiminus has been defined in another file. It will not be redefined.")
#endif

#ifndef suisub
#define suisub(a, b) suiminus(a, b)
#else
#pragma message("suisub has been defined in another file. It will not be redefined.")
#endif

#ifndef suimul
#define suimul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	safer_uint_multiply(a, b))
#else
#pragma message("suimul has been defined in another file. It will not be redefined.")
#endif

#ifndef suidiv
#define suidiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	safer_uint_divide(a, b))
#else
#pragma message("suidiv has been defined in another file. It will not be redefined.")
#endif


#ifndef suladd
#define suladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	safer_ulong_add(a, b))
#else
#pragma message("suladd has been defined in another file. It will not be redefined.")
#endif

#ifndef sulminus
#define sulminus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	safer_ulong_minus(a, b))
#else
#pragma message("sulminus has been defined in another file. It will not be redefined.")
#endif

#ifndef sulsub
#define sulsub(a, b) sulminus(a, b)
#else
#pragma message("sulsub has been defined in another file. It will not be redefined.")
#endif

#ifndef sulmul
#define sulmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	safer_ulong_multiply(a, b))
#else
#pragma message("sulmul has been defined in another file. It will not be redefined.")
#endif

#ifndef suldiv
#define suldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	safer_ulong_divide(a, b))
#else
#pragma message("suldiv has been defined in another file. It will not be redefined.")
#endif


#if defined(ULLONG_MAX)

#ifndef sulladd
#define sulladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	safer_ullong_add(a, b))
#else
#pragma message("sulladd has been defined in another file. It will not be redefined.")
#endif

#ifndef sullminus
#define sullminus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	safer_ullong_minus(a, b))
#else
#pragma message("sullminus has been defined in another file. It will not be redefined.")
#endif

#ifndef sullsub
#define sullsub(a, b) sullminus(a, b)
#else
#pragma message("sullsub has been defined in another file. It will not be redefined.")
#endif

#ifndef sullmul
#define sullmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	safer_ullong_multiply(a, b))
#else
#pragma message("sullmul has been defined in another file. It will not be redefined.")
#endif

#ifndef sulldiv
#define sulldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	safer_ullong_divide(a, b))
#else
#pragma message("sulldiv has been defined in another file. It will not be redefined.")
#endif

#endif /* Is ULLONG_MAX defined? */


/* int8_t */
#ifndef si8add
#define si8add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safer_i8_add(a, b))
#else
#pragma message("si8add has been defined in another file. It will not be redefined.")
#endif

#ifndef si8minus
#define si8minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safer_i8_minus(a, b))
#else
#pragma message("si8minus has been defined in another file. It will not be redefined.")
#endif

#ifndef si8sub
#define si8sub(a, b) si8minus(a, b)
#else
#pragma message("si8sub has been defined in another file. It will not be redefined.")
#endif

#ifndef si8mul
#define si8mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safer_i8_multiply(a, b))
#else
#pragma message("si8mul has been defined in another file. It will not be redefined.")
#endif

#ifndef si8div
#define si8div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safer_i8_divide(a, b))
#else
#pragma message("si8div has been defined in another file. It will not be redefined.")
#endif

#ifndef i8add
#define i8add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safe_i8_add(a, b))
#else
#pragma message("i8add has been defined in another file. It will not be redefined.")
#endif

#ifndef i8minus
#define i8minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safe_i8_minus(a, b))
#else
#pragma message("i8minus has been defined in another file. It will not be redefined.")
#endif

#ifndef i8sub
#define i8sub(a, b) i8minus(a, b)
#else
#pragma message("i8sub has been defined in another file. It will not be redefined.")
#endif

#ifndef i8mul
#define i8mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	safe_i8_multiply(a, b))
#else
#pragma message("i8mul has been defined in another file. It will not be redefined.")
#endif

#ifndef i8div
#define i8div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	less_safe_i8_divide(a, b))
#else
#pragma message("i8div has been defined in another file. It will not be redefined.")
#endif

#ifndef i8rem
#define i8rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	less_safe_i8_remainder(a, b))
#else
#pragma message("i8rem has been defined in another file. It will not be redefined.")
#endif

/* uint8_t */
#ifndef su8add
#define su8add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safer_u8_add(a, b))
#else
#pragma message("su8add has been defined in another file. It will not be redefined.")
#endif

#ifndef su8minus
#define su8minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safer_u8_minus(a, b))
#else
#pragma message("su8minus has been defined in another file. It will not be redefined.")
#endif

#ifndef su8sub
#define su8sub(a, b) su8minus(a, b)
#else
#pragma message("su8sub has been defined in another file. It will not be redefined.")
#endif

#ifndef su8mul
#define su8mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safer_u8_multiply(a, b))
#else
#pragma message("su8mul has been defined in another file. It will not be redefined.")
#endif

#ifndef su8div
#define su8div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safer_u8_divide(a, b))
#else
#pragma message("su8div has been defined in another file. It will not be redefined.")
#endif

#ifndef u8add
#define u8add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safe_u8_add(a, b))
#else
#pragma message("u8add has been defined in another file. It will not be redefined.")
#endif

#ifndef u8minus
#define u8minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safe_u8_minus(a, b))
#else
#pragma message("u8minus has been defined in another file. It will not be redefined.")
#endif

#ifndef u8sub
#define u8sub(a, b) u8minus(a, b)
#else
#pragma message("u8sub has been defined in another file. It will not be redefined.")
#endif

#ifndef u8mul
#define u8mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	safe_u8_multiply(a, b))
#else
#pragma message("u8mul has been defined in another file. It will not be redefined.")
#endif

#ifndef u8div
#define u8div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	less_safe_u8_divide(a, b))
#else
#pragma message("u8div has been defined in another file. It will not be redefined.")
#endif

#ifndef u8rem
#define u8rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	less_safe_u8_remainder(a, b))
#else
#pragma message("u8rem has been defined in another file. It will not be redefined.")
#endif


/* int16_t */
#ifndef si16add
#define si16add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safer_i16_add(a, b))
#else
#pragma message("si16add has been defined in another file. It will not be redefined.")
#endif

#ifndef si16minus
#define si16minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safer_i16_minus(a, b))
#else
#pragma message("si16minus has been defined in another file. It will not be redefined.")
#endif

#ifndef si16sub
#define si16sub(a, b) si16minus(a, b)
#else
#pragma message("si16sub has been defined in another file. It will not be redefined.")
#endif

#ifndef si16mul
#define si16mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safer_i16_multiply(a, b))
#else
#pragma message("si16mul has been defined in another file. It will not be redefined.")
#endif

#ifndef si16div
#define si16div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safer_i16_divide(a, b))
#else
#pragma message("si16div has been defined in another file. It will not be redefined.")
#endif

#ifndef i16add
#define i16add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safe_i16_add(a, b))
#else
#pragma message("i16add has been defined in another file. It will not be redefined.")
#endif

#ifndef i16minus
#define i16minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safe_i16_minus(a, b))
#else
#pragma message("i16minus has been defined in another file. It will not be redefined.")
#endif

#ifndef i16sub
#define i16sub(a, b) i16minus(a, b)
#else
#pragma message("i16sub has been defined in another file. It will not be redefined.")
#endif

#ifndef i16mul
#define i16mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	safe_i16_multiply(a, b))
#else
#pragma message("i16mul has been defined in another file. It will not be redefined.")
#endif

#ifndef i16div
#define i16div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	less_safe_i16_divide(a, b))
#else
#pragma message("i16div has been defined in another file. It will not be redefined.")
#endif

#ifndef i16rem
#define i16rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	less_safe_i16_remainder(a, b))
#else
#pragma message("i16rem has been defined in another file. It will not be redefined.")
#endif

/* uint16_t */
#ifndef su16add
#define su16add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safer_u16_add(a, b))
#else
#pragma message("su16add has been defined in another file. It will not be redefined.")
#endif

#ifndef su16minus
#define su16minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safer_u16_minus(a, b))
#else
#pragma message("su16minus has been defined in another file. It will not be redefined.")
#endif

#ifndef su16sub
#define su16sub(a, b) su16minus(a, b)
#else
#pragma message("su16sub has been defined in another file. It will not be redefined.")
#endif

#ifndef su16mul
#define su16mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safer_u16_multiply(a, b))
#else
#pragma message("su16mul has been defined in another file. It will not be redefined.")
#endif

#ifndef su16div
#define su16div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safer_u16_divide(a, b))
#else
#pragma message("su16div has been defined in another file. It will not be redefined.")
#endif

#ifndef u16add
#define u16add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safe_u16_add(a, b))
#else
#pragma message("u16add has been defined in another file. It will not be redefined.")
#endif

#ifndef u16minus
#define u16minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safe_u16_minus(a, b))
#else
#pragma message("u16minus has been defined in another file. It will not be redefined.")
#endif

#ifndef u16sub
#define u16sub(a, b) u16minus(a, b)
#else
#pragma message("u16sub has been defined in another file. It will not be redefined.")
#endif

#ifndef u16mul
#define u16mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	safe_u16_multiply(a, b))
#else
#pragma message("u16mul has been defined in another file. It will not be redefined.")
#endif

#ifndef u16div
#define u16div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	less_safe_u16_divide(a, b))
#else
#pragma message("u16div has been defined in another file. It will not be redefined.")
#endif

#ifndef u16rem
#define u16rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	less_safe_u16_remainder(a, b))
#else
#pragma message("u16rem has been defined in another file. It will not be redefined.")
#endif


/* int32_t */
#ifndef si32add
#define si32add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safer_i32_add(a, b))
#else
#pragma message("si32add has been defined in another file. It will not be redefined.")
#endif

#ifndef si32minus
#define si32minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safer_i32_minus(a, b))
#else
#pragma message("si32minus has been defined in another file. It will not be redefined.")
#endif

#ifndef si32sub
#define si32sub(a, b) si32minus(a, b)
#else
#pragma message("si32sub has been defined in another file. It will not be redefined.")
#endif

#ifndef si32mul
#define si32mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safer_i32_multiply(a, b))
#else
#pragma message("si32mul has been defined in another file. It will not be redefined.")
#endif

#ifndef si32div
#define si32div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safer_i32_divide(a, b))
#else
#pragma message("si32div has been defined in another file. It will not be redefined.")
#endif

#ifndef i32add
#define i32add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safe_i32_add(a, b))
#else
#pragma message("i32add has been defined in another file. It will not be redefined.")
#endif

#ifndef i32minus
#define i32minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safe_i32_minus(a, b))
#else
#pragma message("i32minus has been defined in another file. It will not be redefined.")
#endif

#ifndef i32sub
#define i32sub(a, b) i32minus(a, b)
#else
#pragma message("i32sub has been defined in another file. It will not be redefined.")
#endif

#ifndef i32mul
#define i32mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	safe_i32_multiply(a, b))
#else
#pragma message("i32mul has been defined in another file. It will not be redefined.")
#endif

#ifndef i32div
#define i32div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	less_safe_i32_divide(a, b))
#else
#pragma message("i32div has been defined in another file. It will not be redefined.")
#endif

#ifndef i32rem
#define i32rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	less_safe_i32_remainder(a, b))
#else
#pragma message("i32rem has been defined in another file. It will not be redefined.")
#endif

/* uint32_t */
#ifndef su32add
#define su32add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safer_u32_add(a, b))
#else
#pragma message("su32add has been defined in another file. It will not be redefined.")
#endif

#ifndef su32minus
#define su32minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safer_u32_minus(a, b))
#else
#pragma message("su32minus has been defined in another file. It will not be redefined.")
#endif

#ifndef su32sub
#define su32sub(a, b) su32minus(a, b)
#else
#pragma message("su32sub has been defined in another file. It will not be redefined.")
#endif

#ifndef su32mul
#define su32mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safer_u32_multiply(a, b))
#else
#pragma message("su32mul has been defined in another file. It will not be redefined.")
#endif

#ifndef su32div
#define su32div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safer_u32_divide(a, b))
#else
#pragma message("su32div has been defined in another file. It will not be redefined.")
#endif

#ifndef u32add
#define u32add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safe_u32_add(a, b))
#else
#pragma message("u32add has been defined in another file. It will not be redefined.")
#endif

#ifndef u32minus
#define u32minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safe_u32_minus(a, b))
#else
#pragma message("u32minus has been defined in another file. It will not be redefined.")
#endif

#ifndef u32sub
#define u32sub(a, b) u32minus(a, b)
#else
#pragma message("u32sub has been defined in another file. It will not be redefined.")
#endif

#ifndef u32mul
#define u32mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	safe_u32_multiply(a, b))
#else
#pragma message("u32mul has been defined in another file. It will not be redefined.")
#endif

#ifndef u32div
#define u32div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	less_safe_u32_divide(a, b))
#else
#pragma message("u32div has been defined in another file. It will not be redefined.")
#endif

#ifndef u32rem
#define u32rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	less_safe_u32_remainder(a, b))
#else
#pragma message("u32rem has been defined in another file. It will not be redefined.")
#endif


/* int64_t */
#ifndef si64add
#define si64add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	safer_i64_add(a, b))
#else
#pragma message("si64add has been defined in another file. It will not be redefined.")
#endif

#ifndef si64minus
#define si64minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	safer_i64_minus(a, b))
#else
#pragma message("si64minus has been defined in another file. It will not be redefined.")
#endif

#ifndef si64sub
#define si64sub(a, b) si64minus(a, b)
#else
#pragma message("si64sub has been defined in another file. It will not be redefined.")
#endif

#ifndef si64mul
#define si64mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	safer_i64_multiply(a, b))
#else
#pragma message("si64mul has been defined in another file. It will not be redefined.")
#endif

#ifndef si64div
#define si64div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	safer_i64_divide(a, b))
#else
#pragma message("si64div has been defined in another file. It will not be redefined.")
#endif

/* uint64_t */
#ifndef su64add
#define su64add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	safer_u64_add(a, b))
#else
#pragma message("su64add has been defined in another file. It will not be redefined.")
#endif

#ifndef su64minus
#define su64minus(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	safer_u64_minus(a, b))
#else
#pragma message("su64minus has been defined in another file. It will not be redefined.")
#endif

#ifndef su64sub
#define su64sub(a, b) su64minus(a, b)
#else
#pragma message("su64sub has been defined in another file. It will not be redefined.")
#endif

#ifndef su64mul
#define su64mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	safer_u64_multiply(a, b))
#else
#pragma message("su64mul has been defined in another file. It will not be redefined.")
#endif

#ifndef su64div
#define su64div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	safer_u64_divide(a, b))
#else
#pragma message("su64div has been defined in another file. It will not be redefined.")
#endif


#ifndef INTEGER_DEBUG_MODE_ENABLED
#define INTEGER_DEBUG_MODE_ENABLED 1
#endif

#ifndef INTEGER_RESULT_MODE
#define INTEGER_RESULT_MODE INTEGER_RESULT_MODE_DEFAULT
#else
#if (INTEGER_RESULT_MODE != INTEGER_RESULT_MODE_DEFAULT) && \
    (INTEGER_RESULT_MODE != INTEGER_RESULT_MODE_WRAPAROUND) && \
    (INTEGER_RESULT_MODE != INTEGER_RESULT_MODE_SATURATION)
#define INTEGER_RESULT_MODE INTEGER_RESULT_MODE_DEFAULT
#endif
#endif

#if INTEGER_DEBUG_MODE_ENABLED

#define diadd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	debug_mode_int_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define disub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	debug_mode_int_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define diminus(a, b) disub(a, b)
#define dimul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	debug_mode_int_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define didiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	debug_mode_int_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define direm(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT_MIN, INT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT_MIN, INT_MAX)), \
	debug_mode_int_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define duiadd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	debug_mode_uint_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define duisub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	debug_mode_uint_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define duiminus(a, b) duisub(a, b)
#define duimul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	debug_mode_uint_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define duidiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	debug_mode_uint_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define duirem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT_MAX)), \
	debug_mode_uint_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define dladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	debug_mode_long_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dlsub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	debug_mode_long_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dlminus(a, b) dlsub(a, b)
#define dlmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	debug_mode_long_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	debug_mode_long_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dlrem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LONG_MIN, LONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LONG_MIN, LONG_MAX)), \
	debug_mode_long_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define duladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	debug_mode_ulong_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dulsub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	debug_mode_ulong_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dulminus(a, b) dulsub(a, b)
#define dulmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	debug_mode_ulong_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define duldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	debug_mode_ulong_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dulrem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULONG_MAX)), \
	debug_mode_ulong_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define dlladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	debug_mode_llong_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dllsub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	debug_mode_llong_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dllminus(a, b) dllsub(a, b)
#define dllmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	debug_mode_llong_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dlldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	debug_mode_llong_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dllrem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, LLONG_MIN, LLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, LLONG_MIN, LLONG_MAX)), \
	debug_mode_llong_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define dulladd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	debug_mode_ullong_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dullsub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	debug_mode_ullong_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dullminus(a, b) dullsub(a, b)
#define dullmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	debug_mode_ullong_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dulldiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	debug_mode_ullong_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dullrem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, ULLONG_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, ULLONG_MAX)), \
	debug_mode_ullong_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define di8add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	debug_mode_i8_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di8sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	debug_mode_i8_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di8minus(a, b) di8sub(a, b)
#define di8mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	debug_mode_i8_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di8div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	debug_mode_i8_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di8rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT8_MIN, INT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT8_MIN, INT8_MAX)), \
	debug_mode_i8_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define du8add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	debug_mode_u8_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du8sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	debug_mode_u8_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du8minus(a, b) du8sub(a, b)
#define du8mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	debug_mode_u8_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du8div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	debug_mode_u8_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du8rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT8_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT8_MAX)), \
	debug_mode_u8_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define di16add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	debug_mode_i16_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di16sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	debug_mode_i16_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di16minus(a, b) di16sub(a, b)
#define di16mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	debug_mode_i16_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di16div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	debug_mode_i16_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di16rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT16_MIN, INT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT16_MIN, INT16_MAX)), \
	debug_mode_i16_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define du16add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	debug_mode_u16_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du16sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	debug_mode_u16_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du16minus(a, b) du16sub(a, b)
#define du16mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	debug_mode_u16_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du16div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	debug_mode_u16_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du16rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT16_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT16_MAX)), \
	debug_mode_u16_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define di32add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	debug_mode_i32_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di32sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	debug_mode_i32_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di32minus(a, b) di32sub(a, b)
#define di32mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	debug_mode_i32_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di32div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	debug_mode_i32_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di32rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT32_MIN, INT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT32_MIN, INT32_MAX)), \
	debug_mode_i32_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define du32add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	debug_mode_u32_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du32sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	debug_mode_u32_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du32minus(a, b) du32sub(a, b)
#define du32mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	debug_mode_u32_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du32div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	debug_mode_u32_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du32rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT32_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT32_MAX)), \
	debug_mode_u32_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define di64add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	debug_mode_i64_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di64sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	debug_mode_i64_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di64minus(a, b) di64sub(a, b)
#define di64mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	debug_mode_i64_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di64div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	debug_mode_i64_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define di64rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, INT64_MIN, INT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, INT64_MIN, INT64_MAX)), \
	debug_mode_i64_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define du64add(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	debug_mode_u64_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du64sub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	debug_mode_u64_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du64minus(a, b) du64sub(a, b)
#define du64mul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	debug_mode_u64_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du64div(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	debug_mode_u64_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define du64rem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, UINT64_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, UINT64_MAX)), \
	debug_mode_u64_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define dpdadd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, PTRDIFF_MIN, PTRDIFF_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, PTRDIFF_MIN, PTRDIFF_MAX)), \
	debug_mode_ptrdiff_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dpdsub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, PTRDIFF_MIN, PTRDIFF_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, PTRDIFF_MIN, PTRDIFF_MAX)), \
	debug_mode_ptrdiff_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dpdminus(a, b) dpdsub(a, b)
#define dpdmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, PTRDIFF_MIN, PTRDIFF_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, PTRDIFF_MIN, PTRDIFF_MAX)), \
	debug_mode_ptrdiff_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dpddiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, PTRDIFF_MIN, PTRDIFF_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, PTRDIFF_MIN, PTRDIFF_MAX)), \
	debug_mode_ptrdiff_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dpdrem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, PTRDIFF_MIN, PTRDIFF_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, PTRDIFF_MIN, PTRDIFF_MAX)), \
	debug_mode_ptrdiff_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#define dszadd(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, SIZE_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, SIZE_MAX)), \
	debug_mode_size_add(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dszsub(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, SIZE_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, SIZE_MAX)), \
	debug_mode_size_minus(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dszminus(a, b) dszsub(a, b)
#define dszmul(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, SIZE_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, SIZE_MAX)), \
	debug_mode_size_multiply(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dszdiv(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, SIZE_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, SIZE_MAX)), \
	debug_mode_size_divide(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))
#define dszrem(a, b) \
	(SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(a, 0, SIZE_MAX)), \
	 SAFER_INTEGER_ASSERT(INTEGER_IS_WITHIN_RANGE(b, 0, SIZE_MAX)), \
	debug_mode_size_remainder(a, b, (integer_result_mode_type) INTEGER_RESULT_MODE, __FILE__, __LINE__))

#else

#define diadd(a, b) ((int) (a) + (int) (b))
#define disub(a, b) ((int) (a) - (int) (b))
#define diminus(a, b) disub(a, b)
#define dimul(a, b) ((int) (a) * (int) (b))
#define didiv(a, b) ((int) (a) / (int) (b))
#define direm(a, b) ((int) (a) % (int) (b))

#define duiadd(a, b) ((unsigned int) (a) + (unsigned int) (b))
#define duisub(a, b) ((unsigned int) (a) - (unsigned int) (b))
#define duiminus(a, b) duisub(a, b)
#define duimul(a, b) ((unsigned int) (a) * (unsigned int) (b))
#define duidiv(a, b) ((unsigned int) (a) / (unsigned int) (b))
#define duirem(a, b) ((unsigned int) (a) % (unsigned int) (b))

#define dladd(a, b) ((long) (a) + (long) (b))
#define dlsub(a, b) ((long) (a) - (long) (b))
#define dlminus(a, b) dlsub(a, b)
#define dlmul(a, b) ((long) (a) * (long) (b))
#define dldiv(a, b) ((long) (a) / (long) (b))
#define dlrem(a, b) ((long) (a) % (long) (b))

#define duladd(a, b) ((unsigned long) (a) + (unsigned long) (b))
#define dulsub(a, b) ((unsigned long) (a) - (unsigned long) (b))
#define dulminus(a, b) dulsub(a, b)
#define dulmul(a, b) ((unsigned long) (a) * (unsigned long) (b))
#define duldiv(a, b) ((unsigned long) (a) / (unsigned long) (b))
#define dulrem(a, b) ((unsigned long) (a) % (unsigned long) (b))

#define dlladd(a, b) ((long long) (a) + (long long) (b))
#define dllsub(a, b) ((long long) (a) - (long long) (b))
#define dllminus(a, b) dllsub(a, b)
#define dllmul(a, b) ((long long) (a) * (long long) (b))
#define dlldiv(a, b) ((long long) (a) / (long long) (b))
#define dllrem(a, b) ((long long) (a) % (long long) (b))

#define dulladd(a, b) ((unsigned long long) (a) + (unsigned long long) (b))
#define dullsub(a, b) ((unsigned long long) (a) - (unsigned long long) (b))
#define dullminus(a, b) dullsub(a, b)
#define dullmul(a, b) ((unsigned long long) (a) * (unsigned long long) (b))
#define dulldiv(a, b) ((unsigned long long) (a) / (unsigned long long) (b))
#define dullrem(a, b) ((unsigned long long) (a) % (unsigned long long) (b))

#define di8add(a, b) (int8_t) ((a) + (b))
#define di8sub(a, b) (int8_t) ((a) - (b))
#define di8minus(a, b) di8sub(a, b)
#define di8mul(a, b) (int8_t) ((a) * (b))
#define di8div(a, b) (int8_t) ((a) / (b))
#define di8rem(a, b) (int8_t) ((a) % (b))

#define du8add(a, b) (uint8_t) ((unsigned int) (a) + (unsigned int) (b))
#define du8sub(a, b) (uint8_t) ((unsigned int) (a) - (unsigned int) (b))
#define du8minus(a, b) du8sub(a, b)
#define du8mul(a, b) (uint8_t) ((unsigned int) (a) * (unsigned int) (b))
#define du8div(a, b) (uint8_t) ((unsigned int) (a) / (unsigned int) (b))
#define du8rem(a, b) (uint8_t) ((unsigned int) (a) % (unsigned int) (b))

#define di16add(a, b) (int16_t) ((a) + (b))
#define di16sub(a, b) (int16_t) ((a) - (b))
#define di16minus(a, b) di16sub(a, b)
#define di16mul(a, b) (int16_t) ((a) * (b))
#define di16div(a, b) (int16_t) ((a) / (b))
#define di16rem(a, b) (int16_t) ((a) % (b))

#define du16add(a, b) (uint16_t) ((unsigned int) (a) + (unsigned int) (b))
#define du16sub(a, b) (uint16_t) ((unsigned int) (a) - (unsigned int) (b))
#define du16minus(a, b) du16sub(a, b)
#define du16mul(a, b) (uint16_t) ((unsigned int) (a) * (unsigned int) (b))
#define du16div(a, b) (uint16_t) ((unsigned int) (a) / (unsigned int) (b))
#define du16rem(a, b) (uint16_t) ((unsigned int) (a) % (unsigned int) (b))

#define di32add(a, b) ((int32_t) (a) + (int32_t) (b))
#define di32sub(a, b) ((int32_t) (a) - (int32_t) (b))
#define di32minus(a, b) di32sub(a, b)
#define di32mul(a, b) ((int32_t) (a) * (int32_t) (b))
#define di32div(a, b) ((int32_t) (a) / (int32_t) (b))
#define di32rem(a, b) ((int32_t) (a) % (int32_t) (b))

#define du32add(a, b) ((uint32_t) (a) + (uint32_t) (b))
#define du32sub(a, b) ((uint32_t) (a) - (uint32_t) (b))
#define du32minus(a, b) du32sub(a, b)
#define du32mul(a, b) ((uint32_t) (a) * (uint32_t) (b))
#define du32div(a, b) ((uint32_t) (a) / (uint32_t) (b))
#define du32rem(a, b) ((uint32_t) (a) % (uint32_t) (b))

#define di64add(a, b) ((int64_t) (a) + (int64_t) (b))
#define di64sub(a, b) ((int64_t) (a) - (int64_t) (b))
#define di64minus(a, b) di64sub(a, b)
#define di64mul(a, b) ((int64_t) (a) * (int64_t) (b))
#define di64div(a, b) ((int64_t) (a) / (int64_t) (b))
#define di64rem(a, b) ((int64_t) (a) % (int64_t) (b))

#define du64add(a, b) ((uint64_t) (a) + (uint64_t) (b))
#define du64sub(a, b) ((uint64_t) (a) - (uint64_t) (b))
#define du64minus(a, b) du64sub(a, b)
#define du64mul(a, b) ((uint64_t) (a) * (uint64_t) (b))
#define du64div(a, b) ((uint64_t) (a) / (uint64_t) (b))
#define du64rem(a, b) ((uint64_t) (a) % (uint64_t) (b))

#define dpdadd(a, b) ((ptrdiff_t) (a) + (ptrdiff_t) (b))
#define dpdsub(a, b) ((ptrdiff_t) (a) - (ptrdiff_t) (b))
#define dpdminus(a, b) dpdsub(a, b)
#define dpdmul(a, b) ((ptrdiff_t) (a) * (ptrdiff_t) (b))
#define dpddiv(a, b) ((ptrdiff_t) (a) / (ptrdiff_t) (b))
#define dpdrem(a, b) ((ptrdiff_t) (a) % (ptrdiff_t) (b))

#define dszadd(a, b) ((size_t) (a) + (size_t) (b))
#define dszsub(a, b) ((size_t) (a) - (size_t) (b))
#define dszminus(a, b) dszsub(a, b)
#define dszmul(a, b) ((size_t) (a) * (size_t) (b))
#define dszdiv(a, b) ((size_t) (a) / (size_t) (b))
#define dszrem(a, b) ((size_t) (a) % (size_t) (b))

#endif /* INTEGER_DEBUG_MODE_ENABLED */

#endif /* include guard */
