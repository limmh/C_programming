#include "Boolean_type.h"
#include "unit_testing.h"

#include <iso646.h>

static Boolean_type is_leap_year(int year)
{
	Boolean_type result = Boolean_false;
	if (year % 400 == 0) {
		result = Boolean_true;	
	} else if (year % 100 == 0) {
		result = Boolean_false;
	} else if (year % 4 == 0) {
		result = Boolean_true;
	} else {
		result = Boolean_false;
	}
	return result;
}

TEST(years_divisible_by_400, "Years divisible by 400 are leap years")
{
	ASSERT(is_leap_year(1600));
	ASSERT(is_leap_year(2000));
	ASSERT(is_leap_year(2400));
}

TEST(years_divisible_by_100_but_not_by_400, "Years divisible by 100 but not by 400 are not leap years")
{
	ASSERT(not is_leap_year(1900));
	ASSERT(not is_leap_year(2100));
	ASSERT(not is_leap_year(2200));
}

TEST(years_divisible_by_4_but_not_by_100, "Years divisible by 4 but not by 100 are leap years")
{
	ASSERT(is_leap_year(1992));
	ASSERT(is_leap_year(1996));
	ASSERT(is_leap_year(2004));
	ASSERT(is_leap_year(2008));
	ASSERT(is_leap_year(2012));
	ASSERT(is_leap_year(2016));
	ASSERT(is_leap_year(2020));
	ASSERT(is_leap_year(2024));
}

TEST(years_not_divisible_by_4, "Years not divisible by 4 are not leap years")
{
	ASSERT(not is_leap_year(1999));
	ASSERT(not is_leap_year(2001));
	ASSERT(not is_leap_year(2002));
	ASSERT(not is_leap_year(2003));
	ASSERT(not is_leap_year(2005));
	ASSERT(not is_leap_year(2006));
	ASSERT(not is_leap_year(2007));
	ASSERT(not is_leap_year(2009));
	ASSERT(not is_leap_year(2010));
	ASSERT(not is_leap_year(2011));
	ASSERT(not is_leap_year(2013));
	ASSERT(not is_leap_year(2014));
	ASSERT(not is_leap_year(2015));
	ASSERT(not is_leap_year(2017));
	ASSERT(not is_leap_year(2018));
	ASSERT(not is_leap_year(2019));
	ASSERT(not is_leap_year(2021));
	ASSERT(not is_leap_year(2022));
	ASSERT(not is_leap_year(2023));
	ASSERT(not is_leap_year(2025));
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(list_of_tests) {
		years_divisible_by_400,
		years_divisible_by_100_but_not_by_400,
		years_divisible_by_4_but_not_by_100,
		years_not_divisible_by_4
	};
	PRINT_FILE_NAME();
	RUN_TESTS(list_of_tests);
	PRINT_TEST_STATISTICS(list_of_tests);
	return 0;
}
