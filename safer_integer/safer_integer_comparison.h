#ifndef SAFER_INTEGER_COMPARISON_H
#define SAFER_INTEGER_COMPARISON_H

#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

/*
Return values and comparison results:
-1 : a < b
 0 : a == b
 1 : a > b
For short and unsigned short comparisons, use the int and unsigned version.
For signed char and unsigned char comparisons, use the int and unsigned version too.
For int8_t and uint8_t comparisons, use the int version or the int16_t and uint16_t version.
*/

INLINE_OR_STATIC int safer_int_and_uint_compare(int a, unsigned int b) {
	int result = 0;
	if (a < 0) {
		result = -1;
	} else {
		const unsigned int ua = (unsigned int) a;
		if (ua < b) {
			result = -1;
		} else if (ua > b) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_uint_and_int_compare(unsigned int a, int b) {
	int result = 0;
	if (b < 0) {
		result = 1;
	} else {
		const unsigned int ub = (unsigned int) b;
		if (a < ub) {
			result = -1;
		} else if (a > ub) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_long_and_ulong_compare(long a, unsigned long b) {
	int result = 0;
	if (a < 0L) {
		result = -1;
	} else {
		const unsigned long ua = (unsigned long) a;
		if (ua < b) {
			result = -1;
		} else if (ua > b) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_ulong_and_long_compare(unsigned long a, long b) {
	int result = 0;
	if (b < 0L) {
		result = 1;
	} else {
		const unsigned long ub = (unsigned long) b;
		if (a < ub) {
			result = -1;
		} else if (a > ub) {
			result = 1;
		}
	}
	return result;
}
INLINE_OR_STATIC int safer_llong_and_ullong_compare(long long a, unsigned long long b) {
	int result = 0;
	if (a < 0LL) {
		result = -1;
	} else {
		const unsigned long long ua = (unsigned long long) a;
		if (ua < b) {
			result = -1;
		} else if (ua > b) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_ullong_and_llong_compare(unsigned long long a, long long b) {
	int result = 0;
	if (b < 0LL) {
		result = 1;
	} else {
		const unsigned long long ub = (unsigned long long) b;
		if (a < ub) {
			result = -1;
		} else if (a > ub) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_i16_and_u16_compare(int16_t a, uint16_t b) {
#if (INT_MIN < INT16_MIN) && (INT_MAX > INT16_MAX) && (UINT_MAX > UINT16_MAX)
	int result = 0;
	if ((int) a < (int) b) {
		result = -1;
	} else if ((int) a > (int) b) {
		result = 1;
	}
#else
	const int result = safer_int_and_uint_compare(a, b);
#endif
	return result;
}

INLINE_OR_STATIC int safer_u16_and_i16_compare(uint16_t a, int16_t b) {
#if (INT_MIN < INT16_MIN) && (INT_MAX > INT16_MAX) && (UINT_MAX > UINT16_MAX)
	int result = 0;
	if ((int) a < (int) b) {
		result = -1;
	} else if ((int) a > (int) b) {
		result = 1;
	}
#else
	const int result = safer_uint_and_int_compare(a, b);
#endif
	return result;
}

INLINE_OR_STATIC int safer_i32_and_u32_compare(int32_t a, uint32_t b) {
#if (INT_MIN == INT32_MIN) && (INT_MAX == INT32_MAX) && (UINT_MAX == UINT32_MAX)
	const int result = safer_int_and_uint_compare(a, b);
#elif (LONG_MIN == INT32_MIN) && (LONG_MAX == INT32_MAX) && (ULONG_MAX == UINT32_MAX)
	const int result = safer_long_and_ulong_compare(a, b);
#else
#error "Error: The comparison function cannot be implemented properly."
#endif
	return result;
}

INLINE_OR_STATIC int safer_u32_and_i32_compare(uint32_t a, int32_t b) {
#if (INT_MIN == INT32_MIN) && (INT_MAX == INT32_MAX) && (UINT_MAX == UINT32_MAX)
	const int result = safer_uint_and_int_compare(a, b);
#elif (LONG_MIN == INT32_MIN) && (LONG_MAX == INT32_MAX) && (ULONG_MAX == UINT32_MAX)
	const int result = safer_ulong_and_long_compare(a, b);
#else
#error "Error: The comparison function cannot be implemented properly."
#endif
	return result;
}

INLINE_OR_STATIC int safer_i64_and_u64_compare(int64_t a, uint64_t b) {
#if (LONG_MIN == INT64_MIN) && (LONG_MAX == INT64_MAX) && (ULONG_MAX == UINT64_MAX)
	const int result = safer_long_and_ulong_compare(a, b);
#elif (LLONG_MIN == INT64_MIN) && (LLONG_MAX == INT64_MAX) && (ULLONG_MAX == UINT64_MAX)
	const int result = safer_llong_and_ullong_compare(a, b);
#else
#error "Error: The comparison function cannot be implemented properly."
#endif
	return result;
}

INLINE_OR_STATIC int safer_u64_and_i64_compare(uint64_t a, int64_t b) {
#if (LONG_MIN == INT64_MIN) && (LONG_MAX == INT64_MAX) && (ULONG_MAX == UINT64_MAX)
	const int result = safer_ulong_and_long_compare(a, b);
#elif (LLONG_MIN == INT64_MIN) && (LLONG_MAX == INT64_MAX) && (ULLONG_MAX == UINT64_MAX)
	const int result = safer_ullong_and_llong_compare(a, b);
#else
#error "Error: The comparison function cannot be implemented properly."
#endif
	return result;
}

#define i_eq_u(i, u) (safer_int_and_uint_compare(i, u) == 0)
#define i_ge_u(i, u) (safer_int_and_uint_compare(i, u) >= 0)
#define i_gt_u(i, u) (safer_int_and_uint_compare(i, u) > 0)
#define i_le_u(i, u) (safer_int_and_uint_compare(i, u) <= 0)
#define i_lt_u(i, u) (safer_int_and_uint_compare(i, u) < 0)
#define u_eq_i(u, i) (safer_uint_and_int_compare(u, i) == 0)
#define u_ge_i(u, i) (safer_uint_and_int_compare(u, i) >= 0)
#define u_gt_i(u, i) (safer_uint_and_int_compare(u, i) > 0)
#define u_le_i(u, i) (safer_uint_and_int_compare(u, i) <= 0)
#define u_lt_i(u, i) (safer_uint_and_int_compare(u, i) < 0)

#define l_eq_ul(l, ul) (safer_long_and_ulong_compare(l, ul) == 0)
#define l_ge_ul(l, ul) (safer_long_and_ulong_compare(l, ul) >= 0)
#define l_gt_ul(l, ul) (safer_long_and_ulong_compare(l, ul) > 0)
#define l_le_ul(l, ul) (safer_long_and_ulong_compare(l, ul) <= 0)
#define l_lt_ul(l, ul) (safer_long_and_ulong_compare(l, ul) < 0)
#define ul_eq_l(ul, l) (safer_ulong_and_long_compare(ul, l) == 0)
#define ul_ge_l(ul, l) (safer_ulong_and_long_compare(ul, l) >= 0)
#define ul_gt_l(ul, l) (safer_ulong_and_long_compare(ul, l) > 0)
#define ul_le_l(ul, l) (safer_ulong_and_long_compare(ul, l) <= 0)
#define ul_lt_l(ul, l) (safer_ulong_and_long_compare(ul, l) < 0)

#define ll_eq_ull(ll, ull) (safer_llong_and_ullong_compare(ll, ull) == 0)
#define ll_ge_ull(ll, ull) (safer_llong_and_ullong_compare(ll, ull) >= 0)
#define ll_gt_ull(ll, ull) (safer_llong_and_ullong_compare(ll, ull) > 0)
#define ll_le_ull(ll, ull) (safer_llong_and_ullong_compare(ll, ull) <= 0)
#define ll_lt_ull(ll, ull) (safer_llong_and_ullong_compare(ll, ull) < 0)
#define ull_eq_ll(ull, ll) (safer_ullong_and_llong_compare(ull, ll) == 0)
#define ull_ge_ll(ull, ll) (safer_ullong_and_llong_compare(ull, ll) >= 0)
#define ull_gt_ll(ull, ll) (safer_ullong_and_llong_compare(ull, ll) > 0)
#define ull_le_ll(ull, ll) (safer_ullong_and_llong_compare(ull, ll) <= 0)
#define ull_lt_ll(ull, ll) (safer_ullong_and_llong_compare(ull, ll) < 0)

#define i16_eq_u16(i16, u16) (safer_i16_and_u16_compare(i16, u16) == 0)
#define i16_ge_u16(i16, u16) (safer_i16_and_u16_compare(i16, u16) >= 0)
#define i16_gt_u16(i16, u16) (safer_i16_and_u16_compare(i16, u16) > 0)
#define i16_le_u16(i16, u16) (safer_i16_and_u16_compare(i16, u16) <= 0)
#define i16_lt_u16(i16, u16) (safer_i16_and_u16_compare(i16, u16) < 0)
#define u16_eq_i16(u16, i16) (safer_u16_and_i16_compare(u16, i16) == 0)
#define u16_ge_i16(u16, i16) (safer_u16_and_i16_compare(u16, i16) >= 0)
#define u16_gt_i16(u16, i16) (safer_u16_and_i16_compare(u16, i16) > 0)
#define u16_le_i16(u16, i16) (safer_u16_and_i16_compare(u16, i16) <= 0)
#define u16_lt_i16(u16, i16) (safer_u16_and_i16_compare(u16, i16) < 0)

#define i32_eq_u32(i32, u32) (safer_i32_and_u32_compare(i32, u32) == 0)
#define i32_ge_u32(i32, u32) (safer_i32_and_u32_compare(i32, u32) >= 0)
#define i32_gt_u32(i32, u32) (safer_i32_and_u32_compare(i32, u32) > 0)
#define i32_le_u32(i32, u32) (safer_i32_and_u32_compare(i32, u32) <= 0)
#define i32_lt_u32(i32, u32) (safer_i32_and_u32_compare(i32, u32) < 0)
#define u32_eq_i32(u32, i32) (safer_u32_and_i32_compare(u32, i32) == 0)
#define u32_ge_i32(u32, i32) (safer_u32_and_i32_compare(u32, i32) >= 0)
#define u32_gt_i32(u32, i32) (safer_u32_and_i32_compare(u32, i32) > 0)
#define u32_le_i32(u32, i32) (safer_u32_and_i32_compare(u32, i32) <= 0)
#define u32_lt_i32(u32, i32) (safer_u32_and_i32_compare(u32, i32) < 0)

#define i64_eq_u64(i64, u64) (safer_i64_and_u64_compare(i64, u64) == 0)
#define i64_ge_u64(i64, u64) (safer_i64_and_u64_compare(i64, u64) >= 0)
#define i64_gt_u64(i64, u64) (safer_i64_and_u64_compare(i64, u64) > 0)
#define i64_le_u64(i64, u64) (safer_i64_and_u64_compare(i64, u64) <= 0)
#define i64_lt_u64(i64, u64) (safer_i64_and_u64_compare(i64, u64) < 0)
#define u64_eq_i64(u64, i64) (safer_u64_and_i64_compare(u64, i64) == 0)
#define u64_ge_i64(u64, i64) (safer_u64_and_i64_compare(u64, i64) >= 0)
#define u64_gt_i64(u64, i64) (safer_u64_and_i64_compare(u64, i64) > 0)
#define u64_le_i64(u64, i64) (safer_u64_and_i64_compare(u64, i64) <= 0)
#define u64_lt_i64(u64, i64) (safer_u64_and_i64_compare(u64, i64) < 0)

#endif
