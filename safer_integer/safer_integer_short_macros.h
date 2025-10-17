#ifndef SAFER_INTEGER_SHORT_MACROS_H
#define SAFER_INTEGER_SHORT_MACROS_H

#include "safer_integer.h"

#ifndef INTEGER_OPERATION_SHORT_MACROS_CUSTOM_ASSERTION_DEFINED
#ifdef NDEBUG
#include <stdio.h>
static void integer_operation_assert(FILE *file, int Boolean_condition, const char *file_name, int line_number, const char *message)
{
	if (!Boolean_condition) {
		fprintf(file, "%s (line %d)\nAssertion failure: %s\n", file_name, line_number, message);
	}
}
#define INTEGER_OPERATION_ASSERT(condition) \
	integer_operation_assert(stderr, condition, __FILE__, __LINE__, #condition)
#else
#include <assert.h>
#define INTEGER_OPERATION_ASSERT(condition) assert(condition)
#endif /* NDEBUG */
#endif /* INTEGER_OPERATION_SHORT_MACROS_CUSTOM_ASSERTION_DEFINED */

/* Short macros for signed integer operations */
#define INTEGER_CAN_BE_SAFELY_CAST_TO_INT(integer) \
	((integer) >= INT_MIN && (integer) <= INT_MAX)

#ifndef siadd
#define siadd(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(b)), \
	safer_int_add(a, b))
#else
#pragma message("siadd has been defined in another file. It will not be redefined.")
#endif

#ifndef siminus
#define siminus(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(b)), \
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
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(b)), \
	safer_int_multiply(a, b))
#else
#pragma message("simul has been defined in another file. It will not be redefined.")
#endif

#ifndef sidiv
#define sidiv(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_INT(b)), \
	safer_int_divide(a, b))
#else
#pragma message("sidiv has been defined in another file. It will not be redefined.")
#endif

#define INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(integer) \
	((integer) >= LONG_MIN && (integer) <= LONG_MAX)

#ifndef sladd
#define sladd(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(b)), \
	safer_long_add(a, b))
#else
#pragma message("sladd has been defined in another file. It will not be redefined.")
#endif

#ifndef slminus
#define slminus(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(b)), \
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
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(b)), \
	safer_long_multiply(a, b))
#else
#pragma message("slmul has been defined in another file. It will not be redefined.")
#endif

#ifndef sldiv
#define sldiv(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LONG(b)), \
	safer_long_divide(a, b))
#else
#pragma message("sldiv has been defined in another file. It will not be redefined.")
#endif


#if LONG_LONG_INTEGER_TYPE_IS_AVAILABLE

#define INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(integer) \
	((integer) >= LLONG_MIN && (integer) <= LLONG_MAX)

#ifndef slladd
#define slladd(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(b)), \
	safer_llong_add(a, b))
#else
#pragma message("slladd has been defined in another file. It will not be redefined.")
#endif

#ifndef sllminus
#define sllminus(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(b)), \
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
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(b)), \
	safer_llong_multiply(a, b))
#else
#pragma message("sllmul has been defined in another file. It will not be redefined.")
#endif

#ifndef slldiv
#define slldiv(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_LLONG(b)), \
	safer_llong_divide(a, b))
#else
#pragma message("slldiv has been defined in another file. It will not be redefined.")
#endif

#endif /* LONG_LONG_INTEGER_TYPE_IS_AVAILABLE */


/* Short macros for unsigned integer operations */
#define INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(integer) \
	((integer) >= 0 && (integer) <= UINT_MAX)

#ifndef suiadd
#define suiadd(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(b)), \
	safer_uint_add(a, b))
#else
#pragma message("suiadd has been defined in another file. It will not be redefined.")
#endif

#ifndef suiminus
#define suiminus(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(a)),\
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(b)),\
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
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(b)), \
	safer_uint_multiply(a, b))
#else
#pragma message("suimul has been defined in another file. It will not be redefined.")
#endif

#ifndef suidiv
#define suidiv(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_UINT(b)), \
	safer_uint_divide(a, b))
#else
#pragma message("suidiv has been defined in another file. It will not be redefined.")
#endif

#define INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(integer) \
	((integer) >= 0 && (integer) <= ULONG_MAX)

#ifndef suladd
#define suladd(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(b)), \
	safer_ulong_add(a, b))
#else
#pragma message("suladd has been defined in another file. It will not be redefined.")
#endif

#ifndef sulminus
#define sulminus(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(b)), \
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
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(b)), \
	safer_ulong_multiply(a, b))
#else
#pragma message("sulmul has been defined in another file. It will not be redefined.")
#endif

#ifndef suldiv
#define suldiv(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULONG(b)), \
	safer_ulong_divide(a, b))
#else
#pragma message("suldiv has been defined in another file. It will not be redefined.")
#endif


#if UNSIGNED_LONG_LONG_INTEGER_TYPE_IS_AVAILABLE

#define INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(integer) \
	((integer) >= 0 && (integer) <= ULLONG_MAX)

#ifndef sulladd
#define sulladd(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(b)), \
	safer_ullong_add(a, b))
#else
#pragma message("sulladd has been defined in another file. It will not be redefined.")
#endif

#ifndef sullminus
#define sullminus(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(b)), \
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
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(b)), \
	safer_ullong_multiply(a, b))
#else
#pragma message("sullmul has been defined in another file. It will not be redefined.")
#endif

#ifndef sulldiv
#define sulldiv(a, b) \
	(INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(a)), \
	 INTEGER_OPERATION_ASSERT(INTEGER_CAN_BE_SAFELY_CAST_TO_ULLONG(b)), \
	safer_ullong_divide(a, b))
#else
#pragma message("sulldiv has been defined in another file. It will not be redefined.")
#endif

#endif /* UNSIGNED_LONG_LONG_INTEGER_TYPE_IS_AVAILABLE */

#endif
