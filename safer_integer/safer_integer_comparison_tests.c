#include "safer_integer_comparison.h"
#include "unit_testing.h"

TEST(int_and_uint_comparison_test, "Comparing int and unsigned int")
{
	ASSERT(i_lt_u(INT_MIN, UINT_MAX));
	ASSERT(i_le_u(INT_MIN, UINT_MAX));
	ASSERT(i_ne_u(INT_MIN, UINT_MAX));
	ASSERT(i_lt_u(-1, 1U));
	ASSERT(i_le_u(-1, 1U));
	ASSERT(i_ne_u(-1, 1U));
	ASSERT(i_lt_u(INT_MAX - 1, (unsigned int) INT_MAX));
	ASSERT(i_le_u(INT_MAX - 1, (unsigned int) INT_MAX));
	ASSERT(i_ne_u(INT_MAX - 1, (unsigned int) INT_MAX));
	ASSERT(i_eq_u(0, 0U));
	ASSERT(i_le_u(0, 0U));
	ASSERT(i_ge_u(0, 0U));
	ASSERT(i_eq_u(INT_MAX, UINT_MAX / 2U));
	ASSERT(i_le_u(INT_MAX, UINT_MAX / 2U));
	ASSERT(i_ge_u(INT_MAX, UINT_MAX / 2U));
	ASSERT(i_eq_u(INT_MAX, (unsigned int) INT_MAX));
	ASSERT(i_le_u(INT_MAX, (unsigned int) INT_MAX));
	ASSERT(i_ge_u(INT_MAX, (unsigned int) INT_MAX));
	ASSERT(i_gt_u(INT_MAX, 0U));
	ASSERT(i_ge_u(INT_MAX, 0U));
	ASSERT(i_ne_u(INT_MAX, 0U));
	ASSERT(i_gt_u(INT_MAX, (unsigned int) (INT_MAX - 1)));
	ASSERT(i_ge_u(INT_MAX, (unsigned int) (INT_MAX - 1)));
	ASSERT(i_ne_u(INT_MAX, (unsigned int) (INT_MAX - 1)));
}

TEST(uint_and_int_comparison_test, "Comparing unsigned int and int")
{
	ASSERT(u_lt_i((unsigned int) (INT_MAX - 1), INT_MAX));
	ASSERT(u_le_i((unsigned int) (INT_MAX - 1), INT_MAX));
	ASSERT(u_ne_i((unsigned int) (INT_MAX - 1), INT_MAX));
	ASSERT(u_lt_i(0U, INT_MAX));
	ASSERT(u_le_i(0U, INT_MAX));
	ASSERT(u_ne_i(0U, INT_MAX));
	ASSERT(u_eq_i(0U, 0));
	ASSERT(u_le_i(0U, 0));
	ASSERT(u_ge_i(0U, 0));
	ASSERT(u_eq_i(UINT_MAX / 2U, INT_MAX));
	ASSERT(u_le_i(UINT_MAX / 2U, INT_MAX));
	ASSERT(u_ge_i(UINT_MAX / 2U, INT_MAX));
	ASSERT(u_eq_i((unsigned int) INT_MAX, INT_MAX));
	ASSERT(u_le_i((unsigned int) INT_MAX, INT_MAX));
	ASSERT(u_ge_i((unsigned int) INT_MAX, INT_MAX));
	ASSERT(u_gt_i(1U, -1));
	ASSERT(u_ge_i(1U, -1));
	ASSERT(u_ne_i(1U, -1));
	ASSERT(u_gt_i((unsigned int) INT_MAX, INT_MAX - 1));
	ASSERT(u_ge_i((unsigned int) INT_MAX, INT_MAX - 1));
	ASSERT(u_ne_i((unsigned int) INT_MAX, INT_MAX - 1));
	ASSERT(u_gt_i(UINT_MAX, INT_MIN));
	ASSERT(u_ge_i(UINT_MAX, INT_MIN));
	ASSERT(u_ne_i(UINT_MAX, INT_MIN));
}

TEST(long_and_ulong_comparison_test, "Comparing long and unsigned long")
{
	ASSERT(l_lt_ul(LONG_MIN, ULONG_MAX));
	ASSERT(l_le_ul(LONG_MIN, ULONG_MAX));
	ASSERT(l_ne_ul(LONG_MIN, ULONG_MAX));
	ASSERT(l_lt_ul(-1, 1U));
	ASSERT(l_le_ul(-1, 1U));
	ASSERT(l_ne_ul(-1, 1U));
	ASSERT(l_lt_ul(LONG_MAX - 1, (unsigned long) LONG_MAX));
	ASSERT(l_le_ul(LONG_MAX - 1, (unsigned long) LONG_MAX));
	ASSERT(l_ne_ul(LONG_MAX - 1, (unsigned long) LONG_MAX));
	ASSERT(l_eq_ul(0, 0U));
	ASSERT(l_le_ul(0, 0U));
	ASSERT(l_ge_ul(0, 0U));
	ASSERT(l_eq_ul(LONG_MAX, ULONG_MAX / 2U));
	ASSERT(l_le_ul(LONG_MAX, ULONG_MAX / 2U));
	ASSERT(l_ge_ul(LONG_MAX, ULONG_MAX / 2U));
	ASSERT(l_eq_ul(LONG_MAX, (unsigned long) LONG_MAX));
	ASSERT(l_le_ul(LONG_MAX, (unsigned long) LONG_MAX));
	ASSERT(l_ge_ul(LONG_MAX, (unsigned long) LONG_MAX));
	ASSERT(l_gt_ul(LONG_MAX, 0U));
	ASSERT(l_ge_ul(LONG_MAX, 0U));
	ASSERT(l_ne_ul(LONG_MAX, 0U));
	ASSERT(l_gt_ul(LONG_MAX, (unsigned long) (LONG_MAX - 1)));
	ASSERT(l_ge_ul(LONG_MAX, (unsigned long) (LONG_MAX - 1)));
	ASSERT(l_ne_ul(LONG_MAX, (unsigned long) (LONG_MAX - 1)));
}

TEST(ulong_and_long_comparison_test, "Comparing unsigned long and long")
{
	ASSERT(ul_lt_l((unsigned long) (LONG_MAX - 1), LONG_MAX));
	ASSERT(ul_le_l((unsigned long) (LONG_MAX - 1), LONG_MAX));
	ASSERT(ul_ne_l((unsigned long) (LONG_MAX - 1), LONG_MAX));
	ASSERT(ul_lt_l(0U, LONG_MAX));
	ASSERT(ul_le_l(0U, LONG_MAX));
	ASSERT(ul_ne_l(0U, LONG_MAX));
	ASSERT(ul_eq_l(0U, 0));
	ASSERT(ul_le_l(0U, 0));
	ASSERT(ul_ge_l(0U, 0));
	ASSERT(ul_eq_l(ULONG_MAX / 2U, LONG_MAX));
	ASSERT(ul_le_l(ULONG_MAX / 2U, LONG_MAX));
	ASSERT(ul_ge_l(ULONG_MAX / 2U, LONG_MAX));
	ASSERT(ul_eq_l((unsigned long) LONG_MAX, LONG_MAX));
	ASSERT(ul_le_l((unsigned long) LONG_MAX, LONG_MAX));
	ASSERT(ul_ge_l((unsigned long) LONG_MAX, LONG_MAX));
	ASSERT(ul_gt_l(1U, -1));
	ASSERT(ul_ge_l(1U, -1));
	ASSERT(ul_ne_l(1U, -1));
	ASSERT(ul_gt_l((unsigned long) LONG_MAX, LONG_MAX - 1));
	ASSERT(ul_ge_l((unsigned long) LONG_MAX, LONG_MAX - 1));
	ASSERT(ul_ne_l((unsigned long) LONG_MAX, LONG_MAX - 1));
	ASSERT(ul_gt_l(ULONG_MAX, LONG_MIN));
	ASSERT(ul_ge_l(ULONG_MAX, LONG_MIN));
	ASSERT(ul_ne_l(ULONG_MAX, LONG_MIN));
}

TEST(llong_and_ullong_comparison_test, "Comparing long long and unsigned long long")
{
	ASSERT(ll_lt_ull(LLONG_MIN, ULLONG_MAX));
	ASSERT(ll_le_ull(LLONG_MIN, ULLONG_MAX));
	ASSERT(ll_ne_ull(LLONG_MIN, ULLONG_MAX));
	ASSERT(ll_lt_ull(-1, 1U));
	ASSERT(ll_le_ull(-1, 1U));
	ASSERT(ll_ne_ull(-1, 1U));
	ASSERT(ll_lt_ull(LLONG_MAX - 1, (unsigned long long) LLONG_MAX));
	ASSERT(ll_le_ull(LLONG_MAX - 1, (unsigned long long) LLONG_MAX));
	ASSERT(ll_ne_ull(LLONG_MAX - 1, (unsigned long long) LLONG_MAX));
	ASSERT(ll_eq_ull(0, 0U));
	ASSERT(ll_le_ull(0, 0U));
	ASSERT(ll_ge_ull(0, 0U));
	ASSERT(ll_eq_ull(LLONG_MAX, ULLONG_MAX / 2U));
	ASSERT(ll_le_ull(LLONG_MAX, ULLONG_MAX / 2U));
	ASSERT(ll_ge_ull(LLONG_MAX, ULLONG_MAX / 2U));
	ASSERT(ll_eq_ull(LLONG_MAX, (unsigned long long) LLONG_MAX));
	ASSERT(ll_le_ull(LLONG_MAX, (unsigned long long) LLONG_MAX));
	ASSERT(ll_ge_ull(LLONG_MAX, (unsigned long long) LLONG_MAX));
	ASSERT(ll_gt_ull(LLONG_MAX, 0U));
	ASSERT(ll_ge_ull(LLONG_MAX, 0U));
	ASSERT(ll_ne_ull(LLONG_MAX, 0U));
	ASSERT(ll_gt_ull(LLONG_MAX, (unsigned long long) (LLONG_MAX - 1)));
	ASSERT(ll_ge_ull(LLONG_MAX, (unsigned long long) (LLONG_MAX - 1)));
	ASSERT(ll_ne_ull(LLONG_MAX, (unsigned long long) (LLONG_MAX - 1)));
}

TEST(ullong_and_llong_comparison_test, "Comparing unsigned long long and long long")
{
	ASSERT(ull_lt_ll((unsigned long long) (LLONG_MAX - 1), LLONG_MAX));
	ASSERT(ull_le_ll((unsigned long long) (LLONG_MAX - 1), LLONG_MAX));
	ASSERT(ull_ne_ll((unsigned long long) (LLONG_MAX - 1), LLONG_MAX));
	ASSERT(ull_lt_ll(0U, LLONG_MAX));
	ASSERT(ull_le_ll(0U, LLONG_MAX));
	ASSERT(ull_ne_ll(0U, LLONG_MAX));
	ASSERT(ull_eq_ll(0U, 0));
	ASSERT(ull_le_ll(0U, 0));
	ASSERT(ull_ge_ll(0U, 0));
	ASSERT(ull_eq_ll(ULLONG_MAX / 2U, LLONG_MAX));
	ASSERT(ull_le_ll(ULLONG_MAX / 2U, LLONG_MAX));
	ASSERT(ull_ge_ll(ULLONG_MAX / 2U, LLONG_MAX));
	ASSERT(ull_eq_ll((unsigned long long) LLONG_MAX, LLONG_MAX));
	ASSERT(ull_le_ll((unsigned long long) LLONG_MAX, LLONG_MAX));
	ASSERT(ull_ge_ll((unsigned long long) LLONG_MAX, LLONG_MAX));
	ASSERT(ull_gt_ll(1U, -1));
	ASSERT(ull_ge_ll(1U, -1));
	ASSERT(ull_ne_ll(1U, -1));
	ASSERT(ull_gt_ll((unsigned long long) LLONG_MAX, LLONG_MAX - 1));
	ASSERT(ull_ge_ll((unsigned long long) LLONG_MAX, LLONG_MAX - 1));
	ASSERT(ull_ne_ll((unsigned long long) LLONG_MAX, LLONG_MAX - 1));
	ASSERT(ull_gt_ll(ULLONG_MAX, LLONG_MIN));
	ASSERT(ull_ge_ll(ULLONG_MAX, LLONG_MIN));
	ASSERT(ull_ne_ll(ULLONG_MAX, LLONG_MIN));
}

TEST(int16_and_uint16_comparison_test, "Comparing int16_t and uint16_t")
{
	ASSERT(i16_lt_u16(INT16_MIN, UINT16_MAX));
	ASSERT(i16_le_u16(INT16_MIN, UINT16_MAX));
	ASSERT(i16_ne_u16(INT16_MIN, UINT16_MAX));
	ASSERT(i16_lt_u16(-1, 1U));
	ASSERT(i16_le_u16(-1, 1U));
	ASSERT(i16_ne_u16(-1, 1U));
	ASSERT(i16_lt_u16(INT16_MAX - 1, (uint16_t) INT16_MAX));
	ASSERT(i16_le_u16(INT16_MAX - 1, (uint16_t) INT16_MAX));
	ASSERT(i16_ne_u16(INT16_MAX - 1, (uint16_t) INT16_MAX));
	ASSERT(i16_eq_u16(0, 0U));
	ASSERT(i16_le_u16(0, 0U));
	ASSERT(i16_ge_u16(0, 0U));
	ASSERT(i16_eq_u16(INT16_MAX, UINT16_MAX / 2U));
	ASSERT(i16_le_u16(INT16_MAX, UINT16_MAX / 2U));
	ASSERT(i16_ge_u16(INT16_MAX, UINT16_MAX / 2U));
	ASSERT(i16_eq_u16(INT16_MAX, (uint16_t) INT16_MAX));
	ASSERT(i16_le_u16(INT16_MAX, (uint16_t) INT16_MAX));
	ASSERT(i16_ge_u16(INT16_MAX, (uint16_t) INT16_MAX));
	ASSERT(i16_gt_u16(INT16_MAX, 0U));
	ASSERT(i16_ge_u16(INT16_MAX, 0U));
	ASSERT(i16_ne_u16(INT16_MAX, 0U));
	ASSERT(i16_gt_u16(INT16_MAX, (uint16_t) (INT16_MAX - 1)));
	ASSERT(i16_ge_u16(INT16_MAX, (uint16_t) (INT16_MAX - 1)));
	ASSERT(i16_ne_u16(INT16_MAX, (uint16_t) (INT16_MAX - 1)));
}

TEST(uint16_and_int16_comparison_test, "Comparing uint16_t and int16_t")
{
	ASSERT(u16_lt_i16((uint16_t) (INT16_MAX - 1), INT16_MAX));
	ASSERT(u16_le_i16((uint16_t) (INT16_MAX - 1), INT16_MAX));
	ASSERT(u16_ne_i16((uint16_t) (INT16_MAX - 1), INT16_MAX));
	ASSERT(u16_lt_i16(0U, INT16_MAX));
	ASSERT(u16_le_i16(0U, INT16_MAX));
	ASSERT(u16_ne_i16(0U, INT16_MAX));
	ASSERT(u16_eq_i16(0U, 0));
	ASSERT(u16_le_i16(0U, 0));
	ASSERT(u16_ge_i16(0U, 0));
	ASSERT(u16_eq_i16(UINT16_MAX / 2U, INT16_MAX));
	ASSERT(u16_le_i16(UINT16_MAX / 2U, INT16_MAX));
	ASSERT(u16_ge_i16(UINT16_MAX / 2U, INT16_MAX));
	ASSERT(u16_eq_i16((uint16_t) INT16_MAX, INT16_MAX));
	ASSERT(u16_le_i16((uint16_t) INT16_MAX, INT16_MAX));
	ASSERT(u16_ge_i16((uint16_t) INT16_MAX, INT16_MAX));
	ASSERT(u16_gt_i16(1U, -1));
	ASSERT(u16_ge_i16(1U, -1));
	ASSERT(u16_ne_i16(1U, -1));
	ASSERT(u16_gt_i16((uint16_t) INT16_MAX, INT16_MAX - 1));
	ASSERT(u16_ge_i16((uint16_t) INT16_MAX, INT16_MAX - 1));
	ASSERT(u16_ne_i16((uint16_t) INT16_MAX, INT16_MAX - 1));
	ASSERT(u16_gt_i16(UINT16_MAX, INT16_MIN));
	ASSERT(u16_ge_i16(UINT16_MAX, INT16_MIN));
	ASSERT(u16_ne_i16(UINT16_MAX, INT16_MIN));
}

TEST(int32_and_uint32_comparison_test, "Comparing int32_t and uint32_t")
{
	ASSERT(i32_lt_u32(INT32_MIN, UINT32_MAX));
	ASSERT(i32_le_u32(INT32_MIN, UINT32_MAX));
	ASSERT(i32_ne_u32(INT32_MIN, UINT32_MAX));
	ASSERT(i32_lt_u32(-1, 1U));
	ASSERT(i32_le_u32(-1, 1U));
	ASSERT(i32_ne_u32(-1, 1U));
	ASSERT(i32_lt_u32(INT32_MAX - 1, (uint32_t) INT32_MAX));
	ASSERT(i32_le_u32(INT32_MAX - 1, (uint32_t) INT32_MAX));
	ASSERT(i32_ne_u32(INT32_MAX - 1, (uint32_t) INT32_MAX));
	ASSERT(i32_eq_u32(0, 0U));
	ASSERT(i32_le_u32(0, 0U));
	ASSERT(i32_ge_u32(0, 0U));
	ASSERT(i32_eq_u32(INT32_MAX, UINT32_MAX / 2U));
	ASSERT(i32_le_u32(INT32_MAX, UINT32_MAX / 2U));
	ASSERT(i32_ge_u32(INT32_MAX, UINT32_MAX / 2U));
	ASSERT(i32_eq_u32(INT32_MAX, (uint32_t) INT32_MAX));
	ASSERT(i32_le_u32(INT32_MAX, (uint32_t) INT32_MAX));
	ASSERT(i32_ge_u32(INT32_MAX, (uint32_t) INT32_MAX));
	ASSERT(i32_gt_u32(INT32_MAX, 0U));
	ASSERT(i32_ge_u32(INT32_MAX, 0U));
	ASSERT(i32_ne_u32(INT32_MAX, 0U));
	ASSERT(i32_gt_u32(INT32_MAX, (uint32_t) (INT32_MAX - 1)));
	ASSERT(i32_ge_u32(INT32_MAX, (uint32_t) (INT32_MAX - 1)));
	ASSERT(i32_ne_u32(INT32_MAX, (uint32_t) (INT32_MAX - 1)));
}

TEST(uint32_and_int32_comparison_test, "Comparing uint32_t and int32_t")
{
	ASSERT(u32_lt_i32((uint32_t) (INT32_MAX - 1), INT32_MAX));
	ASSERT(u32_le_i32((uint32_t) (INT32_MAX - 1), INT32_MAX));
	ASSERT(u32_ne_i32((uint32_t) (INT32_MAX - 1), INT32_MAX));
	ASSERT(u32_lt_i32(0U, INT32_MAX));
	ASSERT(u32_le_i32(0U, INT32_MAX));
	ASSERT(u32_ne_i32(0U, INT32_MAX));
	ASSERT(u32_eq_i32(0U, 0));
	ASSERT(u32_le_i32(0U, 0));
	ASSERT(u32_ge_i32(0U, 0));
	ASSERT(u32_eq_i32(UINT32_MAX / 2U, INT32_MAX));
	ASSERT(u32_le_i32(UINT32_MAX / 2U, INT32_MAX));
	ASSERT(u32_ge_i32(UINT32_MAX / 2U, INT32_MAX));
	ASSERT(u32_eq_i32((uint32_t) INT32_MAX, INT32_MAX));
	ASSERT(u32_le_i32((uint32_t) INT32_MAX, INT32_MAX));
	ASSERT(u32_ge_i32((uint32_t) INT32_MAX, INT32_MAX));
	ASSERT(u32_gt_i32(1U, -1));
	ASSERT(u32_ge_i32(1U, -1));
	ASSERT(u32_ne_i32(1U, -1));
	ASSERT(u32_gt_i32((uint32_t) INT32_MAX, INT32_MAX - 1));
	ASSERT(u32_ge_i32((uint32_t) INT32_MAX, INT32_MAX - 1));
	ASSERT(u32_ne_i32((uint32_t) INT32_MAX, INT32_MAX - 1));
	ASSERT(u32_gt_i32(UINT32_MAX, INT32_MIN));
	ASSERT(u32_ge_i32(UINT32_MAX, INT32_MIN));
	ASSERT(u32_ne_i32(UINT32_MAX, INT32_MIN));
}

TEST(int64_and_uint64_comparison_test, "Comparing int64_t and uint64_t")
{
	ASSERT(i64_lt_u64(INT64_MIN, UINT64_MAX));
	ASSERT(i64_le_u64(INT64_MIN, UINT64_MAX));
	ASSERT(i64_ne_u64(INT64_MIN, UINT64_MAX));
	ASSERT(i64_lt_u64(-1, 1U));
	ASSERT(i64_le_u64(-1, 1U));
	ASSERT(i64_ne_u64(-1, 1U));
	ASSERT(i64_lt_u64(INT64_MAX - 1, (uint64_t) INT64_MAX));
	ASSERT(i64_le_u64(INT64_MAX - 1, (uint64_t) INT64_MAX));
	ASSERT(i64_ne_u64(INT64_MAX - 1, (uint64_t) INT64_MAX));
	ASSERT(i64_eq_u64(0, 0U));
	ASSERT(i64_le_u64(0, 0U));
	ASSERT(i64_ge_u64(0, 0U));
	ASSERT(i64_eq_u64(INT64_MAX, UINT64_MAX / 2U));
	ASSERT(i64_le_u64(INT64_MAX, UINT64_MAX / 2U));
	ASSERT(i64_ge_u64(INT64_MAX, UINT64_MAX / 2U));
	ASSERT(i64_eq_u64(INT64_MAX, (uint64_t) INT64_MAX));
	ASSERT(i64_le_u64(INT64_MAX, (uint64_t) INT64_MAX));
	ASSERT(i64_ge_u64(INT64_MAX, (uint64_t) INT64_MAX));
	ASSERT(i64_gt_u64(INT64_MAX, 0U));
	ASSERT(i64_ge_u64(INT64_MAX, 0U));
	ASSERT(i64_ne_u64(INT64_MAX, 0U));
	ASSERT(i64_gt_u64(INT64_MAX, (uint64_t) (INT64_MAX - 1)));
	ASSERT(i64_ge_u64(INT64_MAX, (uint64_t) (INT64_MAX - 1)));
	ASSERT(i64_ne_u64(INT64_MAX, (uint64_t) (INT64_MAX - 1)));
}

TEST(uint64_and_int64_comparison_test, "Comparing uint64_t and int64_t")
{
	ASSERT(u64_lt_i64((uint64_t) (INT64_MAX - 1), INT64_MAX));
	ASSERT(u64_le_i64((uint64_t) (INT64_MAX - 1), INT64_MAX));
	ASSERT(u64_ne_i64((uint64_t) (INT64_MAX - 1), INT64_MAX));
	ASSERT(u64_lt_i64(0U, INT64_MAX));
	ASSERT(u64_le_i64(0U, INT64_MAX));
	ASSERT(u64_ne_i64(0U, INT64_MAX));
	ASSERT(u64_eq_i64(0U, 0));
	ASSERT(u64_le_i64(0U, 0));
	ASSERT(u64_ge_i64(0U, 0));
	ASSERT(u64_eq_i64(UINT64_MAX / 2U, INT64_MAX));
	ASSERT(u64_le_i64(UINT64_MAX / 2U, INT64_MAX));
	ASSERT(u64_ge_i64(UINT64_MAX / 2U, INT64_MAX));
	ASSERT(u64_eq_i64((uint64_t) INT64_MAX, INT64_MAX));
	ASSERT(u64_le_i64((uint64_t) INT64_MAX, INT64_MAX));
	ASSERT(u64_ge_i64((uint64_t) INT64_MAX, INT64_MAX));
	ASSERT(u64_gt_i64(1U, -1));
	ASSERT(u64_ge_i64(1U, -1));
	ASSERT(u64_ne_i64(1U, -1));
	ASSERT(u64_gt_i64((uint64_t) INT64_MAX, INT64_MAX - 1));
	ASSERT(u64_ge_i64((uint64_t) INT64_MAX, INT64_MAX - 1));
	ASSERT(u64_ne_i64((uint64_t) INT64_MAX, INT64_MAX - 1));
	ASSERT(u64_gt_i64(UINT64_MAX, INT64_MIN));
	ASSERT(u64_ge_i64(UINT64_MAX, INT64_MIN));
	ASSERT(u64_ne_i64(UINT64_MAX, INT64_MIN));
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		int_and_uint_comparison_test,
		uint_and_int_comparison_test,
		long_and_ulong_comparison_test,
		ulong_and_long_comparison_test,
		llong_and_ullong_comparison_test,
		ullong_and_llong_comparison_test,
		int16_and_uint16_comparison_test,
		uint16_and_int16_comparison_test,
		int32_and_uint32_comparison_test,
		uint32_and_int32_comparison_test,
		int64_and_uint64_comparison_test,
		uint64_and_int64_comparison_test
	};
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
