#ifndef SAFER_INTEGER_COMPARISON_H
#define SAFER_INTEGER_COMPARISON_H

#include "fixed_width_integer_types.h"
#include "Boolean_type.h"
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

#if defined(LLONG_MIN) && defined(LLONG_MAX) && defined(ULLONG_MAX)
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
#endif

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
	int result = 0;
	if (a < (int32_t) 0) {
		result = -1;
	} else {
		const uint32_t ua = (uint32_t) a;
		if (ua < b) {
			result = -1;
		} else if (ua > b) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_u32_and_i32_compare(uint32_t a, int32_t b) {
	int result = 0;
	if (b < (int32_t) 0) {
		result = 1;
	} else {
		const uint32_t ub = (uint32_t) b;
		if (a < ub) {
			result = -1;
		} else if (a > ub) {
			result = 1;
		}
	}
	return result;
}

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
INLINE_OR_STATIC int safer_i64_and_u64_compare(int64_t a, uint64_t b) {
	int result = 0;
	if (a < (int64_t) 0) {
		result = -1;
	} else {
		const uint64_t ua = (uint64_t) a;
		if (ua < b) {
			result = -1;
		} else if (ua > b) {
			result = 1;
		}
	}
	return result;
}

INLINE_OR_STATIC int safer_u64_and_i64_compare(uint64_t a, int64_t b) {
	int result = 0;
	if (b < (int64_t) 0) {
		result = 1;
	} else {
		const uint64_t ub = (uint64_t) b;
		if (a < ub) {
			result = -1;
		} else if (a > ub) {
			result = 1;
		}
	}
	return result;
}
#endif

INLINE_OR_STATIC Boolean_type i_eq_u(int i, unsigned int u) { return (safer_int_and_uint_compare(i, u) == 0); }
INLINE_OR_STATIC Boolean_type i_ne_u(int i, unsigned int u) { return (safer_int_and_uint_compare(i, u) != 0); }
INLINE_OR_STATIC Boolean_type i_ge_u(int i, unsigned int u) { return (safer_int_and_uint_compare(i, u) >= 0); }
INLINE_OR_STATIC Boolean_type i_gt_u(int i, unsigned int u) { return (safer_int_and_uint_compare(i, u) > 0);  }
INLINE_OR_STATIC Boolean_type i_le_u(int i, unsigned int u) { return (safer_int_and_uint_compare(i, u) <= 0); }
INLINE_OR_STATIC Boolean_type i_lt_u(int i, unsigned int u) { return (safer_int_and_uint_compare(i, u) < 0);  }

INLINE_OR_STATIC Boolean_type u_eq_i(unsigned int u, int i) { return (safer_uint_and_int_compare(u, i) == 0); }
INLINE_OR_STATIC Boolean_type u_ne_i(unsigned int u, int i) { return (safer_uint_and_int_compare(u, i) != 0); }
INLINE_OR_STATIC Boolean_type u_ge_i(unsigned int u, int i) { return (safer_uint_and_int_compare(u, i) >= 0); }
INLINE_OR_STATIC Boolean_type u_gt_i(unsigned int u, int i) { return (safer_uint_and_int_compare(u, i) > 0);  }
INLINE_OR_STATIC Boolean_type u_le_i(unsigned int u, int i) { return (safer_uint_and_int_compare(u, i) <= 0); }
INLINE_OR_STATIC Boolean_type u_lt_i(unsigned int u, int i) { return (safer_uint_and_int_compare(u, i) < 0);  }

INLINE_OR_STATIC Boolean_type l_eq_ul(long l, unsigned long ul) { return (safer_long_and_ulong_compare(l, ul) == 0); }
INLINE_OR_STATIC Boolean_type l_ne_ul(long l, unsigned long ul) { return (safer_long_and_ulong_compare(l, ul) != 0); }
INLINE_OR_STATIC Boolean_type l_ge_ul(long l, unsigned long ul) { return (safer_long_and_ulong_compare(l, ul) >= 0); }
INLINE_OR_STATIC Boolean_type l_gt_ul(long l, unsigned long ul) { return (safer_long_and_ulong_compare(l, ul) > 0);  }
INLINE_OR_STATIC Boolean_type l_le_ul(long l, unsigned long ul) { return (safer_long_and_ulong_compare(l, ul) <= 0); }
INLINE_OR_STATIC Boolean_type l_lt_ul(long l, unsigned long ul) { return (safer_long_and_ulong_compare(l, ul) < 0);  }

INLINE_OR_STATIC Boolean_type ul_eq_l(unsigned long ul, long l) { return (safer_ulong_and_long_compare(ul, l) == 0); }
INLINE_OR_STATIC Boolean_type ul_ne_l(unsigned long ul, long l) { return (safer_ulong_and_long_compare(ul, l) != 0); }
INLINE_OR_STATIC Boolean_type ul_ge_l(unsigned long ul, long l) { return (safer_ulong_and_long_compare(ul, l) >= 0); }
INLINE_OR_STATIC Boolean_type ul_gt_l(unsigned long ul, long l) { return (safer_ulong_and_long_compare(ul, l) > 0);  }
INLINE_OR_STATIC Boolean_type ul_le_l(unsigned long ul, long l) { return (safer_ulong_and_long_compare(ul, l) <= 0); }
INLINE_OR_STATIC Boolean_type ul_lt_l(unsigned long ul, long l) { return (safer_ulong_and_long_compare(ul, l) < 0);  }

#if defined(LLONG_MIN) && defined(LLONG_MAX) && defined(ULLONG_MAX)
INLINE_OR_STATIC Boolean_type ll_eq_ull(long long ll, unsigned long long ull) { return (safer_llong_and_ullong_compare(ll, ull) == 0); }
INLINE_OR_STATIC Boolean_type ll_ne_ull(long long ll, unsigned long long ull) { return (safer_llong_and_ullong_compare(ll, ull) != 0); }
INLINE_OR_STATIC Boolean_type ll_ge_ull(long long ll, unsigned long long ull) { return (safer_llong_and_ullong_compare(ll, ull) >= 0); }
INLINE_OR_STATIC Boolean_type ll_gt_ull(long long ll, unsigned long long ull) { return (safer_llong_and_ullong_compare(ll, ull) > 0);  }
INLINE_OR_STATIC Boolean_type ll_le_ull(long long ll, unsigned long long ull) { return (safer_llong_and_ullong_compare(ll, ull) <= 0); }
INLINE_OR_STATIC Boolean_type ll_lt_ull(long long ll, unsigned long long ull) { return (safer_llong_and_ullong_compare(ll, ull) < 0);  }

INLINE_OR_STATIC Boolean_type ull_eq_ll(unsigned long long ull, long long ll) { return (safer_ullong_and_llong_compare(ull, ll) == 0); }
INLINE_OR_STATIC Boolean_type ull_ne_ll(unsigned long long ull, long long ll) { return (safer_ullong_and_llong_compare(ull, ll) != 0); }
INLINE_OR_STATIC Boolean_type ull_ge_ll(unsigned long long ull, long long ll) { return (safer_ullong_and_llong_compare(ull, ll) >= 0); }
INLINE_OR_STATIC Boolean_type ull_gt_ll(unsigned long long ull, long long ll) { return (safer_ullong_and_llong_compare(ull, ll) > 0);  }
INLINE_OR_STATIC Boolean_type ull_le_ll(unsigned long long ull, long long ll) { return (safer_ullong_and_llong_compare(ull, ll) <= 0); }
INLINE_OR_STATIC Boolean_type ull_lt_ll(unsigned long long ull, long long ll) { return (safer_ullong_and_llong_compare(ull, ll) < 0);  }
#endif

INLINE_OR_STATIC Boolean_type i16_eq_u16(int16_t i16, uint16_t u16) { return (safer_i16_and_u16_compare(i16, u16) == 0); }
INLINE_OR_STATIC Boolean_type i16_ne_u16(int16_t i16, uint16_t u16) { return (safer_i16_and_u16_compare(i16, u16) != 0); }
INLINE_OR_STATIC Boolean_type i16_ge_u16(int16_t i16, uint16_t u16) { return (safer_i16_and_u16_compare(i16, u16) >= 0); }
INLINE_OR_STATIC Boolean_type i16_gt_u16(int16_t i16, uint16_t u16) { return (safer_i16_and_u16_compare(i16, u16) > 0);  }
INLINE_OR_STATIC Boolean_type i16_le_u16(int16_t i16, uint16_t u16) { return (safer_i16_and_u16_compare(i16, u16) <= 0); }
INLINE_OR_STATIC Boolean_type i16_lt_u16(int16_t i16, uint16_t u16) { return (safer_i16_and_u16_compare(i16, u16) < 0);  }

INLINE_OR_STATIC Boolean_type u16_eq_i16(uint16_t u16, int16_t i16) { return (safer_u16_and_i16_compare(u16, i16) == 0); }
INLINE_OR_STATIC Boolean_type u16_ne_i16(uint16_t u16, int16_t i16) { return (safer_u16_and_i16_compare(u16, i16) != 0); }
INLINE_OR_STATIC Boolean_type u16_ge_i16(uint16_t u16, int16_t i16) { return (safer_u16_and_i16_compare(u16, i16) >= 0); }
INLINE_OR_STATIC Boolean_type u16_gt_i16(uint16_t u16, int16_t i16) { return (safer_u16_and_i16_compare(u16, i16) > 0);  }
INLINE_OR_STATIC Boolean_type u16_le_i16(uint16_t u16, int16_t i16) { return (safer_u16_and_i16_compare(u16, i16) <= 0); }
INLINE_OR_STATIC Boolean_type u16_lt_i16(uint16_t u16, int16_t i16) { return (safer_u16_and_i16_compare(u16, i16) < 0);  }

INLINE_OR_STATIC Boolean_type i32_eq_u32(int32_t i32, uint32_t u32) { return (safer_i32_and_u32_compare(i32, u32) == 0); }
INLINE_OR_STATIC Boolean_type i32_ne_u32(int32_t i32, uint32_t u32) { return (safer_i32_and_u32_compare(i32, u32) != 0); }
INLINE_OR_STATIC Boolean_type i32_ge_u32(int32_t i32, uint32_t u32) { return (safer_i32_and_u32_compare(i32, u32) >= 0); }
INLINE_OR_STATIC Boolean_type i32_gt_u32(int32_t i32, uint32_t u32) { return (safer_i32_and_u32_compare(i32, u32) > 0);  }
INLINE_OR_STATIC Boolean_type i32_le_u32(int32_t i32, uint32_t u32) { return (safer_i32_and_u32_compare(i32, u32) <= 0); }
INLINE_OR_STATIC Boolean_type i32_lt_u32(int32_t i32, uint32_t u32) { return (safer_i32_and_u32_compare(i32, u32) < 0);  }

INLINE_OR_STATIC Boolean_type u32_eq_i32(uint32_t u32, int32_t i32) { return (safer_u32_and_i32_compare(u32, i32) == 0); }
INLINE_OR_STATIC Boolean_type u32_ne_i32(uint32_t u32, int32_t i32) { return (safer_u32_and_i32_compare(u32, i32) != 0); }
INLINE_OR_STATIC Boolean_type u32_ge_i32(uint32_t u32, int32_t i32) { return (safer_u32_and_i32_compare(u32, i32) >= 0); }
INLINE_OR_STATIC Boolean_type u32_gt_i32(uint32_t u32, int32_t i32) { return (safer_u32_and_i32_compare(u32, i32) > 0);  }
INLINE_OR_STATIC Boolean_type u32_le_i32(uint32_t u32, int32_t i32) { return (safer_u32_and_i32_compare(u32, i32) <= 0); }
INLINE_OR_STATIC Boolean_type u32_lt_i32(uint32_t u32, int32_t i32) { return (safer_u32_and_i32_compare(u32, i32) < 0);  }

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)
INLINE_OR_STATIC Boolean_type i64_eq_u64(int64_t i64, uint64_t u64) { return (safer_i64_and_u64_compare(i64, u64) == 0); }
INLINE_OR_STATIC Boolean_type i64_ne_u64(int64_t i64, uint64_t u64) { return (safer_i64_and_u64_compare(i64, u64) != 0); }
INLINE_OR_STATIC Boolean_type i64_ge_u64(int64_t i64, uint64_t u64) { return (safer_i64_and_u64_compare(i64, u64) >= 0); }
INLINE_OR_STATIC Boolean_type i64_gt_u64(int64_t i64, uint64_t u64) { return (safer_i64_and_u64_compare(i64, u64) > 0);  }
INLINE_OR_STATIC Boolean_type i64_le_u64(int64_t i64, uint64_t u64) { return (safer_i64_and_u64_compare(i64, u64) <= 0); }
INLINE_OR_STATIC Boolean_type i64_lt_u64(int64_t i64, uint64_t u64) { return (safer_i64_and_u64_compare(i64, u64) < 0);  }

INLINE_OR_STATIC Boolean_type u64_eq_i64(uint64_t u64, int64_t i64) { return (safer_u64_and_i64_compare(u64, i64) == 0); }
INLINE_OR_STATIC Boolean_type u64_ne_i64(uint64_t u64, int64_t i64) { return (safer_u64_and_i64_compare(u64, i64) != 0); }
INLINE_OR_STATIC Boolean_type u64_ge_i64(uint64_t u64, int64_t i64) { return (safer_u64_and_i64_compare(u64, i64) >= 0); }
INLINE_OR_STATIC Boolean_type u64_gt_i64(uint64_t u64, int64_t i64) { return (safer_u64_and_i64_compare(u64, i64) > 0);  }
INLINE_OR_STATIC Boolean_type u64_le_i64(uint64_t u64, int64_t i64) { return (safer_u64_and_i64_compare(u64, i64) <= 0); }
INLINE_OR_STATIC Boolean_type u64_lt_i64(uint64_t u64, int64_t i64) { return (safer_u64_and_i64_compare(u64, i64) < 0);  }
#endif

#endif
