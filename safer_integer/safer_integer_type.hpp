#ifndef SAFER_INTEGER_TYPE_HPP
#define SAFER_INTEGER_TYPE_HPP

#include "macro_stringify.h"
#include "macro_concatenate.h"
#include "static_assert.h"
#include <cassert>
#include <cstdio>
#include <climits>
#include <limits>

#ifdef SAFER_INTEGER_USE_CPLUSPLUS_EXCEPTION
#include <stdexcept>
#endif

#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO

#if __cplusplus < 202002L
#define DECLARE_SAFER_INTEGER(type, name) type name(#name " (type: " #type ") [defined at line " STRINGIFY(__LINE__) " of " __FILE__ "]")
#define DEFINE_SAFER_INTEGER(type, name, value) type name(value, #name " (type: " #type ") [defined at line " STRINGIFY(__LINE__) " of " __FILE__ "]")
#else
#include <source_location>
#define DECLARE_SAFER_INTEGER(type, name) type name
#define DEFINE_SAFER_INTEGER(type, name, value) type name = value
#endif

#else

#define DECLARE_SAFER_INTEGER(type, name) type name
#define DEFINE_SAFER_INTEGER(type, name, value) type name = value

#endif

namespace safer_integer {

#define OPERATIONS \
	X(operation_unknown, 0U, "unknown operation", "unknown operator") \
	X(operation_unary_plus, 1U, "unary plus", "+") \
	X(operation_unary_minus, 1U, "unary minus", "-") \
	X(operation_post_increment, 1U, "post-increment", "++") \
	X(operation_pre_increment, 1U, "pre-increment", "++") \
	X(operation_post_decrement, 1U, "post-decrement", "--") \
	X(operation_pre_decrement, 1U, "pre-decrement", "--") \
	X(operation_addition, 2U, "addition", "+") \
	X(operation_self_addition, 2U, "adding a number to self", "+=") \
	X(operation_subtraction, 2U, "subtraction", "-") \
	X(operation_self_subtraction, 2U, "subtracting a number from self", "-=") \
	X(operation_multiplication, 2U, "multiplication", "*") \
	X(operation_self_multiplication, 2U, "multiplying self by a number", "*=") \
	X(operation_division, 2U, "division", "/") \
	X(operation_self_division, 2U, "dividing self by a number", "/=") \
	X(operation_remainder, 2U, "remainder", "%") \
	X(operation_self_remainder, 2U, "remainder of dividing self by a number", "%=") \
	X(operation_comparison_equal, 2U, "equal comparison", "==") \
	X(operation_comparison_not_equal, 2U, "unequal comparison", "!=") \
	X(operation_comparison_greater, 2U, "greater than comparison", ">") \
	X(operation_comparison_greater_or_equal, 2U, "greater than or equal comparison", ">=") \
	X(operation_comparison_less, 2U, "less than comparison", "<") \
	X(operation_comparison_less_or_equal, 2U, "less than or equal comparison", "<=") \
	X(operation_logical_and, 2U, "logical AND", "&&") \
	X(operation_logical_or, 2U, "logical OR", "||") \
	X(operation_logical_not, 1U, "logical NOT", "!") \
	X(operation_bitwise_and, 2U, "bitwise AND", "&") \
	X(operation_self_bitwise_and, 2U, "self bitwise AND", "&=") \
	X(operation_bitwise_or, 2U, "bitwise OR", "|") \
	X(operation_self_bitwise_or, 2U, "self bitwise OR", "|=") \
	X(operation_bitwise_xor, 2U, "bitwise XOR", "^") \
	X(operation_self_bitwise_xor, 2U, "bitwise XOR", "^=") \
	X(operation_bitwise_not, 1U, "bitwise NOT", "~") \
	X(operation_bitwise_left_shift, 2U, "bitwise left shift", "<<") \
	X(operation_self_bitwise_left_shift, 2U, "self bitwise left shift", "<<=") \
	X(operation_bitwise_right_shift, 2U, "bitwise right shift", ">>") \
	X(operation_self_bitwise_right_shift, 2U, "self bitwise right shift", ">>=")

enum operation_type {
#define X(operation_enum_constant, number_of_operands, operation_name, operator_symbol) operation_enum_constant,
	OPERATIONS
#undef X
};

size_t operand_count(operation_type type) {
	size_t count = 0U;
#define X(operation_enum_constant, number_of_operands, operation_name, operator_symbol) \
	case operation_enum_constant: count = number_of_operands; break;
	switch (type) {
	OPERATIONS
	default:
		count = 0U;
		break;
	}
	return count;
#undef X
}

const char *operation_name(operation_type type) {
	const char *name = NULL;
#define X(operation_enum_constant, number_of_operands, operation_name, operator_symbol) \
	case operation_enum_constant: name = operation_name; break;
	switch (type) {
	OPERATIONS
	default:
		name = "unknown operation type";
		break;
	}
	assert(name != NULL);
	return name;
#undef X
}

const char *operator_symbol(operation_type type) {
	const char *symbol = NULL;
#define X(operation_enum_constant, number_of_operands, operation_name, operator_symbol) \
	case operation_enum_constant: symbol = operator_symbol; break;
	switch (type) {
	OPERATIONS
	default:
		symbol = "unknown operator";
		break;
	}
	assert(symbol != NULL);
	return symbol;
#undef X
}

#undef OPERATIONS

#define OPERATION_ERRORS \
	X(operation_error_none, "No error") \
	X(operation_error_signed_result_less_than_min, "Signed integer result < MIN") \
	X(operation_error_signed_result_more_than_max, "Signed integer result > MAX") \
	X(operation_error_division_of_signed_integer_by_zero, "Signed integer / zero") \
	X(operation_error_division_of_min_by_minus_one, "(Minimum signed integer / -1) [two's complement]") \
	X(operation_error_unsigned_result_wraparound_to_smaller, "Unsigned integer result > MAX") \
	X(operation_error_unsigned_result_wraparound_to_larger, "Unsigned integer result < zero ") \
	X(operation_error_division_of_unsigned_integer_by_zero, "Unsigned integer / zero") \
	X(operation_error_unary_negation_of_unsigned_integer, "Negation of unsigned integer") \
	X(operation_error_left_operand_of_bitwise_and_is_negative, "The left operand of the bitwise AND operation is negative.") \
	X(operation_error_right_operand_of_bitwise_and_is_negative, "The right operand of the bitwsise AND operation is negative.") \
	X(operation_error_both_operands_of_bitwise_and_are_negative, "Both the operands of the bitwise AND operation are negative.") \
	X(operation_error_left_operand_of_bitwise_or_is_negative, "The left operand of the bitwise OR operation is negative.") \
	X(operation_error_right_operand_of_bitwise_or_is_negative, "The right operand of the bitwsise OR operation is negative.") \
	X(operation_error_both_operands_of_bitwise_or_are_negative, "Both the operands of the bitwise OR operation are negative.") \
	X(operation_error_left_operand_of_bitwise_xor_is_negative, "The left operand of the bitwise XOR operation is negative.") \
	X(operation_error_right_operand_of_bitwise_xor_is_negative, "The right operand of the bitwsise XOR operation is negative.") \
	X(operation_error_both_operands_of_bitwise_xor_are_negative, "Both the operands of the bitwise XOR operation are negative.") \
	X(operation_error_operand_of_bitwise_not_is_negative, "The operand of bitwise NOT operation is negative.") \
	X(operation_error_left_operand_of_bitwise_left_shift_is_negative, "The left operand of bitwise left shift operation is negative.") \
	X(operation_error_right_operand_of_bitwise_left_shift_is_out_of_range, "The right operand of bitwise left shift operation is out of range.") \
	X(operation_error_both_operands_of_bitwsise_left_shift_are_negative_or_out_of_range, "Both operands of bitwise right shift operation are negative or out of range.") \
	X(operation_error_left_operand_of_bitwise_right_shift_is_negative, "The left operand of bitwise right shift operation is negative.") \
	X(operation_error_right_operand_of_bitwise_right_shift_is_out_of_range, "The right operand of bitwise right shift operation is out of range.") \
	X(operation_error_both_operands_of_bitwsise_right_shift_are_negative_or_out_of_range, "Both operands of bitwise right shift operation are negative or out of range.") \

enum operation_error_type {
#define X(operation_error_enum_constant, operation_error_string) operation_error_enum_constant, 
	OPERATION_ERRORS
#undef X
};

const char *operation_error_message(operation_error_type error) {
	const char *message = NULL;
#define X(operation_error_enum_constant, operation_error_string) case operation_error_enum_constant: message = operation_error_string; break;
	switch (error) {
	OPERATION_ERRORS
	default:
		message = "unknown error";
		break;
	}
	assert(message != NULL);
	return message;
#undef X
}

#undef OPERATION_ERRORS

template<typename T1, typename T2, typename result_type>
struct debug_info_type {
	const char *file_path;
	int line_number;
	operation_type operation;
	operation_error_type error;
	T1 operand_1;
	T2 operand_2;
	result_type result;

	debug_info_type(
		operation_type operation_,
		operation_error_type error_,
		T1 operand_1_,
		T2 operand_2_,
		result_type result_,
		const char *file_path_,
		int line_number_
	) : file_path(file_path_), line_number(line_number_), operation(operation_), error(error_),
		operand_1(operand_1_), operand_2(operand_2_), result(result_)
	{
		assert(file_path != NULL);
		assert(line_number > 0);
	}
};

// Default Integer Policy
struct DIP {
	typedef bool bool_type;
	typedef char char_type;
	typedef signed char schar_type;
	typedef unsigned char uchar_type;
	typedef short short_type;
	typedef unsigned short ushort_type;
	typedef int int_type;
	typedef unsigned int uint_type;
	typedef long long_type;
	typedef unsigned long ulong_type;
	typedef long long llong_type;
	typedef unsigned long long ullong_type;
};

// Default Promotion Policy - must be specialized for all possible combinations of two integer types
template<typename T1, typename T2> struct DPP;

template<> struct DPP<DIP::bool_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::short_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::ushort_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::bool_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::bool_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::bool_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::char_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::short_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::ushort_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::char_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::char_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::char_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::schar_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::short_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::ushort_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::schar_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::schar_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::schar_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::uchar_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::short_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::ushort_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::uchar_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uchar_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::uchar_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::short_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::short_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::ushort_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::short_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::short_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::short_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

#if USHRT_MAX < INT_MAX
template<> struct DPP<DIP::ushort_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::short_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::ushort_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::ushort_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::ushort_type, DIP::ulong_type> {typedef DIP::ulong_type type;};
#elif (USHRT_MAX == UINT_MAX) && (UINT_MAX < LONG_MAX)
template<> struct DPP<DIP::ushort_type, DIP::bool_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::char_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::schar_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::uchar_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::short_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::ushort_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::int_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::ushort_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::ushort_type, DIP::ulong_type> {typedef DIP::ulong_type type;};
#endif

template<> struct DPP<DIP::int_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::short_type> {typedef DIP::int_type type;};
#if USHRT_MAX < INT_MAX
template<> struct DPP<DIP::int_type, DIP::ushort_type> {typedef DIP::int_type type;};
#elif (USHRT_MAX == UINT_MAX) && (UINT_MAX < LONG_MAX)
template<> struct DPP<DIP::int_type, DIP::ushort_type> {typedef DIP::uint_type type;};
#endif
template<> struct DPP<DIP::int_type, DIP::int_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::uint_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::int_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::int_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::uint_type, DIP::bool_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::char_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::schar_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::uchar_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::short_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::ushort_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::int_type> {typedef DIP::uint_type type;};
template<> struct DPP<DIP::uint_type, DIP::uint_type> {typedef DIP::uint_type type;};
#if UINT_MAX < LONG_MAX
template<> struct DPP<DIP::uint_type, DIP::long_type> {typedef DIP::long_type type;};
#elif UINT_MAX == ULONG_MAX
template<> struct DPP<DIP::uint_type, DIP::long_type> {typedef DIP::ulong_type type;};
#endif
template<> struct DPP<DIP::uint_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::long_type, DIP::bool_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::char_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::schar_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::uchar_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::short_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::ushort_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::int_type> {typedef DIP::long_type type;};
#if UINT_MAX < LONG_MAX
template<> struct DPP<DIP::long_type, DIP::uint_type> {typedef DIP::long_type type;};
#elif UINT_MAX == ULONG_MAX
template<> struct DPP<DIP::long_type, DIP::uint_type> {typedef DIP::ulong_type type;};
#endif
template<> struct DPP<DIP::long_type, DIP::long_type> {typedef DIP::long_type type;};
template<> struct DPP<DIP::long_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

template<> struct DPP<DIP::ulong_type, DIP::bool_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::char_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::schar_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::uchar_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::short_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::ushort_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::int_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::uint_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::long_type> {typedef DIP::ulong_type type;};
template<> struct DPP<DIP::ulong_type, DIP::ulong_type> {typedef DIP::ulong_type type;};

#if defined(LLONG_MIN) && defined(LLONG_MAX) && defined(ULLONG_MAX)
template<> struct DPP<DIP::bool_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::bool_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::char_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::char_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::schar_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::schar_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::uchar_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::uchar_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::short_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::short_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ushort_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::ushort_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::int_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::int_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::uint_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::uint_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::long_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::long_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
#if ULONG_MAX < LLONG_MAX
template<> struct DPP<DIP::ulong_type, DIP::llong_type> {typedef DIP::llong_type type;};
#elif ULONG_MAX == ULLONG_MAX
template<> struct DPP<DIP::ulong_type, DIP::llong_type> {typedef DIP::ullong_type type;};
#endif
template<> struct DPP<DIP::ulong_type, DIP::ullong_type> {typedef DIP::ullong_type type;};

template<> struct DPP<DIP::llong_type, DIP::bool_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::char_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::schar_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::uchar_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::short_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::ushort_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::int_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::uint_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::long_type> {typedef DIP::llong_type type;};
#if ULONG_MAX < LLONG_MAX
template<> struct DPP<DIP::llong_type, DIP::ulong_type> {typedef DIP::llong_type type;};
#elif ULONG_MAX == ULLONG_MAX
template<> struct DPP<DIP::llong_type, DIP::ulong_type> {typedef DIP::ullong_type type;};
#endif
template<> struct DPP<DIP::llong_type, DIP::llong_type> {typedef DIP::llong_type type;};
template<> struct DPP<DIP::llong_type, DIP::ullong_type> {typedef DIP::ullong_type type;};

template<> struct DPP<DIP::ullong_type, DIP::bool_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::char_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::schar_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::uchar_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::short_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::ushort_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::int_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::uint_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::long_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::ulong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::llong_type> {typedef DIP::ullong_type type;};\
template<> struct DPP<DIP::ullong_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
#endif

static FILE *output_file_pointer = stderr;

static FILE *set_output_file_pointer(FILE *file_pointer) {
	FILE *previous_file_pointer = output_file_pointer;
	output_file_pointer = file_pointer;
	return previous_file_pointer;
}

template<typename T1, typename T2, typename result_type>
// Default Error Policy - must provide a static member function called handle_error
struct DEP {
	static void handle_error(const debug_info_type<T1, T2, result_type>& debug_info) {
		typedef long long llong_type;
		typedef unsigned long long ullong_type;
		typedef std::numeric_limits<T1> T1_info;
		typedef std::numeric_limits<T2> T2_info;
		typedef std::numeric_limits<result_type> result_type_info;

		if (output_file_pointer == NULL) {
			return;
		}

		assert(debug_info.file_path != NULL);
		assert(debug_info.line_number > 0);

		const char * const operation_name = safer_integer::operation_name(debug_info.operation);
		const char * const symbol = safer_integer::operator_symbol(debug_info.operation);
		const size_t operand_count = safer_integer::operand_count(debug_info.operation);
		const char * const error_message = safer_integer::operation_error_message(debug_info.error);

		fprintf(output_file_pointer, "%s (line %d): %s\n", debug_info.file_path, debug_info.line_number, error_message);
		fprintf(output_file_pointer, "Operation: %s (%s), Number of operands: %d\n",
			operation_name,  ((symbol[0] != '\0') ? symbol : "[no symbol]"), (int)operand_count);

		if (operand_count >= 1U) {
			if (T1_info::is_signed) {
				fprintf(output_file_pointer, "Operand 1 [signed, %d-byte, min: %lld, max: %lld]: %lld\n",
					(int) sizeof(debug_info.operand_1), (llong_type) T1_info::min(), (llong_type) T1_info::max(), (llong_type) debug_info.operand_1);
			} else {
				fprintf(output_file_pointer, "Operand 1 [unsigned, %d-byte, min: %llu, max: %llu]: %llu\n",
					(int) sizeof(debug_info.operand_1), (ullong_type) T1_info::min(), (ullong_type) T1_info::max(), (ullong_type) debug_info.operand_1);
			}
		}

		if (operand_count >= 2U) {
			if (T2_info::is_signed) {
				fprintf(output_file_pointer, "Operand 2 [signed, %d-byte, min: %lld, max: %lld]: %lld\n",
					(int) sizeof(debug_info.operand_2), (llong_type) T2_info::min(), (llong_type) T2_info::max(), (llong_type) debug_info.operand_2);
			} else {
				fprintf(output_file_pointer, "Operand 2 [unsigned, %d-byte, min: %llu, max: %llu]: %llu\n",
					(int) sizeof(debug_info.operand_2), (ullong_type) T2_info::min(), (ullong_type) T2_info::max(), (ullong_type) debug_info.operand_2);
			}
		}

		if (operand_count > 0U) {
			if (result_type_info::is_signed) {
				fprintf(output_file_pointer, "Result [signed, %d-byte, min: %lld, max: %lld]: %lld\n",
					(int) sizeof(debug_info.result), (llong_type) result_type_info::min(), (llong_type) result_type_info::max(), (llong_type) debug_info.result);
			} else {
				fprintf(output_file_pointer, "Result [unsigned, %d-byte, min: %llu, max: %llu]: %llu\n",
					(int) sizeof(debug_info.result), (ullong_type) result_type_info::min(), (ullong_type) result_type_info::max(), (ullong_type) debug_info.result);
			}
		}

		fprintf(output_file_pointer, "\n");

#ifdef SAFER_INTEGER_USE_CPLUSPLUS_EXCEPTION
		throw std::runtime_error(error_message);
#endif
	}
};

// Converts a signed type to an unsigned type of the same rank
template<typename T> struct to_unsigned_type;
template<> struct to_unsigned_type<bool> {typedef bool type;};
template<> struct to_unsigned_type<char> {typedef unsigned char type;};
template<> struct to_unsigned_type<signed char> {typedef unsigned char type;};
template<> struct to_unsigned_type<unsigned char> {typedef unsigned char type;};
template<> struct to_unsigned_type<short> {typedef unsigned short type;};
template<> struct to_unsigned_type<unsigned short> {typedef unsigned short type;};
template<> struct to_unsigned_type<int> {typedef unsigned int type;};
template<> struct to_unsigned_type<unsigned int> {typedef unsigned int type;};
template<> struct to_unsigned_type<long> {typedef unsigned long type;};
template<> struct to_unsigned_type<unsigned long> {typedef unsigned long type;};
template<> struct to_unsigned_type<long long> {typedef unsigned long long type;};
template<> struct to_unsigned_type<unsigned long long> {typedef unsigned long long type;};

// Default Result Policy - must provide a static member function called calculate_result
template<typename T1, typename T2, typename result_type>
struct DRP {
	static result_type calculate_result(operation_type operation, operation_error_type error, T1 operand_1, T2 operand_2) {
		typename to_unsigned_type<result_type>::type value1 =
			static_cast<typename to_unsigned_type<result_type>::type>(operand_1);
		typename to_unsigned_type<result_type>::type value2 =
			static_cast<typename to_unsigned_type<result_type>::type>(operand_2);
		result_type result = static_cast<result_type>(0);
		switch (operation) {
		case operation_unary_plus:
			result = static_cast<result_type>(value1);
			break;
		case operation_unary_minus:
			result = static_cast<result_type>(~value1 + 1U);
			break;
		case operation_post_increment:
			result = static_cast<result_type>(value1);
			break;
		case operation_pre_increment:
			result = static_cast<result_type>(value1 + 1U);
			break;
		case operation_post_decrement:
			result = static_cast<result_type>(value1);
			break;
		case operation_pre_decrement:
			result = static_cast<result_type>(value1 - 1U);
			break;
		case operation_addition:
		case operation_self_addition:
			result = static_cast<result_type>(value1 + value2);
			break;
		case operation_subtraction:
		case operation_self_subtraction:
			result = static_cast<result_type>(value1 - value2);
			break;
		case operation_multiplication:
		case operation_self_multiplication:
			result = static_cast<result_type>(value1 * value2);
			break;
		case operation_division:
		case operation_self_division:
			if (error == operation_error_division_of_min_by_minus_one) {
				result = static_cast<result_type>(value1);
			}
			break;
		case operation_remainder:
		case operation_self_remainder:
			break;
		case operation_comparison_equal:
			result = value1 == value2;
			break;
		case operation_comparison_not_equal:
			result = value1 != value2;
			break;
		case operation_comparison_greater:
			result = value1 > value2;
			break;
		case operation_comparison_greater_or_equal:
			result = value1 >= value2;
			break;
		case operation_comparison_less:
			result = value1 < value2;
			break;
		case operation_comparison_less_or_equal:
			result = value1 <= value2;
			break;
		case operation_logical_and:
			result = value1 && value2;
			break;
		case operation_logical_or:
			result = value1 || value2;
			break;
		case operation_logical_not:
			result = !value1;
			break;
		case operation_bitwise_and:
		case operation_self_bitwise_and:
			result = static_cast<result_type>(value1 & value2);
			break;
		case operation_bitwise_or:
		case operation_self_bitwise_or:
			result = static_cast<result_type>(value1 | value2);
			break;
		case operation_bitwise_xor:
		case operation_self_bitwise_xor:
			result = static_cast<result_type>(value1 ^ value2);
			break;
		case operation_bitwise_not:
			result = static_cast<result_type>(~value1);
			break;
		case operation_bitwise_left_shift:
		case operation_self_bitwise_left_shift:
			result = static_cast<result_type>(value1 << value2);
			break;
		case operation_bitwise_right_shift:
		case operation_self_bitwise_right_shift:
			result = static_cast<result_type>(value1 >> value2);
			break;
		default:
			result = static_cast<result_type>(value1);
			break;
		}
		return result;
	}
};

template<typename T>
operation_error_type check_signed_addition(T a, T b)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and type_info::is_signed);
	const T maximum_value = type_info::max();
	const T minimum_value = type_info::min();
	const T zero = T(0);
	operation_error_type error = operation_error_none;
	if (a > zero) { // OK condition: (a + b) <= maximum value, where a > 0 and b > 0
		if (b > zero and b > (maximum_value - a)) {
			error = operation_error_signed_result_more_than_max;
		}
	} else if (a < zero) { // OK condition: (a + b) >= minimum value, where a < 0 and b < 0
		if (b < zero and b < (minimum_value - a)) {
			error = operation_error_signed_result_less_than_min;
		}
	}
	return error;
}

template<typename T>
operation_error_type check_signed_subtraction(T a, T b)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and type_info::is_signed);
	const T maximum_value = type_info::max();
	const T minimum_value = type_info::min();
	const T zero = static_cast<T>(0);
	operation_error_type error = operation_error_none;
	if (a >= zero) { // OK condition: (a - b) <= maximum value, where a >= 0 and b < 0
		if (b < zero and a > (maximum_value + b)) {
			error = operation_error_signed_result_more_than_max;
		}
	} else { // OK condition: (a - b) >= minimum value, where a < 0 and b > 0
		if (b > zero and a < (minimum_value + b)) {
			error = operation_error_signed_result_less_than_min;
		}
	}
	return error;
}

template<typename T>
operation_error_type check_signed_multiplication(T a, T b)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and type_info::is_signed);
	const T maximum_value = type_info::max();
	const T minimum_value = type_info::min();
	const T zero = static_cast<T>(0);
	operation_error_type error = operation_error_none;
	if (a > zero) {
		if (b > zero and b > (maximum_value / a)) { // OK condition: (a * b) <= maximum value, where a > 0 and b > 0
			error = operation_error_signed_result_more_than_max;
		} else if (b < zero and b < (minimum_value / a)) { // OK condition: (a * b) >= minimum value, where a > 0 and b < 0
			error = operation_error_signed_result_less_than_min;
		}
	} else if (a < zero) {
		if (b > zero and a < (minimum_value / b)) { // OK condition: (a * b) >=  minimum value, where a < 0 and b > 0
			error = operation_error_signed_result_less_than_min;
		} else if (b < zero and  b < (maximum_value / a)) { // OK condition: (a * b) <= maximum value, where a < 0 and b < 0
			error = operation_error_signed_result_more_than_max;
		}
	}
	return error;
}

template<typename T>
operation_error_type check_signed_division(T dividend, T divisor)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and type_info::is_signed);
	const T maximum_value = type_info::max();
	const T minimum_value = type_info::min();
	const T zero = static_cast<T>(0);
	const T minus_one = static_cast<T>(-1);
	operation_error_type error = operation_error_none;
	if (divisor == zero) {
		error = operation_error_division_of_signed_integer_by_zero;
	} else if (divisor == minus_one) {
		if (dividend == minimum_value and minimum_value == (-maximum_value + minus_one)) {
			error = operation_error_division_of_min_by_minus_one;
		}
	}
	return error;
}

template<typename T>
operation_error_type check_unsigned_addition(T a, T b)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and (not type_info::is_signed));
	const T maximum_value = type_info::max();
	return (b <= (maximum_value - a)) ? operation_error_none : operation_error_unsigned_result_wraparound_to_smaller;
}

template<typename T>
operation_error_type check_unsigned_subtraction(T a, T b)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and (not type_info::is_signed));
	return (a >= b) ? operation_error_none : operation_error_unsigned_result_wraparound_to_larger;
}

template<typename T>
operation_error_type check_unsigned_multiplication(T a, T b)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and (not type_info::is_signed));
	const T zero = static_cast<T>(0U);
	operation_error_type error = operation_error_none;
	if (a != zero and b != zero) {
		const T maximum_value = type_info::max();
		if (b > (maximum_value / a)) {
			error = operation_error_unsigned_result_wraparound_to_smaller;
		}
	}
	return error;
}

template<typename T>
operation_error_type check_unsigned_division(T dividend, T divisor)
{
	typedef std::numeric_limits<T> type_info;
	assert(type_info::is_integer and (not type_info::is_signed));
	const T zero = static_cast<T>(0U);
	return (divisor != zero) ? operation_error_none : operation_error_division_of_unsigned_integer_by_zero;
}

template<typename T1, typename T2>
operation_error_type check_bitwise_and_operation(T1 a, T2 b) {
	typedef std::numeric_limits<T1> type1_info;
	typedef std::numeric_limits<T2> type2_info;
	operation_error_type error = operation_error_none;
	if (type1_info::is_signed and (a < 0)) {
		if (type2_info::is_signed and (b < 0)) {
			error = operation_error_both_operands_of_bitwise_and_are_negative;
		} else {
			error = operation_error_left_operand_of_bitwise_and_is_negative;
		}
	} else {
		if (type2_info::is_signed and (b < 0)) {
			error = operation_error_right_operand_of_bitwise_and_is_negative;
		}
	}
	return error;
}

template<typename T1, typename T2>
operation_error_type check_bitwise_or_operation(T1 a, T2 b) {
	typedef std::numeric_limits<T1> type1_info;
	typedef std::numeric_limits<T2> type2_info;
	operation_error_type error = operation_error_none;
	if (type1_info::is_signed and (a < 0)) {
		if (type2_info::is_signed and (b < 0)) {
			error = operation_error_both_operands_of_bitwise_or_are_negative;
		} else {
			error = operation_error_left_operand_of_bitwise_or_is_negative;
		}
	} else {
		if (type2_info::is_signed and (b < 0)) {
			error = operation_error_right_operand_of_bitwise_or_is_negative;
		}
	}
	return error;
}

template<typename T1, typename T2>
operation_error_type check_bitwise_xor_operation(T1 a, T2 b) {
	typedef std::numeric_limits<T1> type1_info;
	typedef std::numeric_limits<T2> type2_info;
	operation_error_type error = operation_error_none;
	if (type1_info::is_signed and (a < 0)) {
		if (type2_info::is_signed and (b < 0)) {
			error = operation_error_both_operands_of_bitwise_xor_are_negative;
		} else {
			error = operation_error_left_operand_of_bitwise_xor_is_negative;
		}
	} else {
		if (type2_info::is_signed and (b < 0)) {
			error = operation_error_right_operand_of_bitwise_xor_is_negative;
		}
	}
	return error;
}

template<typename T>
operation_error_type check_bitwise_not_operation(T a) {
	typedef std::numeric_limits<T> type_info;
	operation_error_type error = operation_error_none;
	if (type_info::is_signed and (a < 0)) {
		error = operation_error_operand_of_bitwise_not_is_negative;
	}
	return error;
}

template<typename T1, typename T2>
operation_error_type check_left_shift_operation(T1 lhs, T2 rhs) {
	typedef std::numeric_limits<T1> type1_info;
	typedef std::numeric_limits<T2> type2_info;
	const size_t width = sizeof(lhs) * CHAR_BIT;
	const bool left_operand_is_not_negative = not (type1_info::is_signed and (lhs < 0));
	const bool right_operand_within_range = (type2_info::is_signed) ?
		((rhs >= 0) and (rhs < width)) : (rhs >= width);
	operation_error_type error = operation_error_none;
	if (left_operand_is_not_negative) {
		if (not right_operand_within_range) {
			error = operation_error_right_operand_of_bitwise_right_shift_is_out_of_range;
		}
	} else {
		if (right_operand_within_range) {
			error = operation_error_left_operand_of_bitwise_left_shift_is_negative;
		} else {
			error = operation_error_both_operands_of_bitwsise_left_shift_are_negative_or_out_of_range;
		}
	}
	return error;
}

template<typename T1, typename T2>
operation_error_type check_right_shift_operation(T1 lhs, T2 rhs) {
	typedef std::numeric_limits<T1> type1_info;
	typedef std::numeric_limits<T2> type2_info;
	const size_t width = sizeof(lhs) * CHAR_BIT;
	const bool left_operand_is_not_negative = not (type1_info::is_signed and (lhs < 0));
	const bool right_operand_within_range = (type2_info::is_signed) ?
		((rhs >= 0) and (rhs < width)) : (rhs < width);
	operation_error_type error = operation_error_none;
	if (left_operand_is_not_negative) {
		if (not right_operand_within_range) {
			error = operation_error_right_operand_of_bitwise_right_shift_is_out_of_range;
		}
	} else {
		if (right_operand_within_range) {
			error = operation_error_left_operand_of_bitwise_right_shift_is_negative;
		} else {
			error = operation_error_both_operands_of_bitwsise_right_shift_are_negative_or_out_of_range;
		}
	}
	return error;
}

template<typename T, typename U>
bool can_cast_properly(U src_integer)
{
	typedef std::numeric_limits<T> dst_type_info;
	typedef std::numeric_limits<U> src_type_info;
	STATIC_ASSERT(dst_type_info::is_integer, "The destination type must be an integer type.");
	STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
	const T dst_min = dst_type_info::min();
	const T dst_max = dst_type_info::max();
	bool result = false;
	if (dst_type_info::is_signed) {
		if (src_type_info::is_signed) {
			result = (src_integer >= dst_min) and (src_integer <= dst_max);
		} else {
			result = (src_integer <= dst_max);
		}
	} else {
		assert(dst_min == 0);
		if (src_type_info::is_signed) {
			result = (src_integer >= 0) and (src_integer <= dst_max);
		} else {
			result = (src_integer <= dst_max);
		}
	}
	return result;
}

// a generic type  that emulates built-in integer types
template<typename T, typename integer_policy = DIP>
struct integer_type {
	typedef T underlying_type;
	typedef std::numeric_limits<T> type_info;
	STATIC_ASSERT(type_info::is_integer, "The template parameter type T must be an integer type.");

	STATIC_ASSERT(sizeof(typename integer_policy::bool_type) == 1U, "The size of bool_type shall be 1-byte.");
	STATIC_ASSERT(sizeof(typename integer_policy::char_type) == sizeof(typename integer_policy::schar_type), "char_type and schar_type must have the same size.");
	STATIC_ASSERT(sizeof(typename integer_policy::char_type) == sizeof(typename integer_policy::uchar_type), "char_type and uchar_type must have the same size.");
	STATIC_ASSERT(sizeof(typename integer_policy::char_type) <= sizeof(typename integer_policy::short_type), "The size of char_type must not exceed the size of short_type.");
	STATIC_ASSERT(sizeof(typename integer_policy::short_type) == sizeof(typename integer_policy::ushort_type), "short_type and ushort_type must have the same size.");
	STATIC_ASSERT(sizeof(typename integer_policy::short_type) <= sizeof(typename integer_policy::int_type), "The size of short_type must not exceed the size of int_type.");
	STATIC_ASSERT(sizeof(typename integer_policy::int_type) == sizeof(typename integer_policy::uint_type), "int_type and uint_type must have the same_size.");
	STATIC_ASSERT(sizeof(typename integer_policy::int_type) <= sizeof(typename integer_policy::long_type), "The size of int_type must not exceed the size of long_type.");
	STATIC_ASSERT(sizeof(typename integer_policy::long_type) == sizeof(typename integer_policy::ulong_type), "long_type and ulong_type must have the same size.");
 	STATIC_ASSERT(sizeof(typename integer_policy::long_type) <= sizeof(typename integer_policy::llong_type), "The size of long_type must not exceed the size of llong_type.");
	STATIC_ASSERT(sizeof(typename integer_policy::llong_type) == sizeof(typename integer_policy::ullong_type), "llong_type and ullong_type must have the same size.");

	static void print_source_file_info(const integer_type<T, integer_policy>& self) {
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
		if (output_file_pointer != NULL) {
#if __cplusplus < 202002L
			fprintf(output_file_pointer, "Variable: %s\n", self.m_source_file_info);
#else
			fprintf(output_file_pointer, "%s (line %u, column %u): %s [Refer to the variable defined here]\n",
				self.m_source_file_info.file_name(), self.m_source_file_info.line(),
				self.m_source_file_info.column(), self.m_source_file_info.function_name() );
#endif
		}
#endif
	}

	static void print_message(const char *message) {
		if (output_file_pointer != NULL and message != NULL) {
			fprintf(output_file_pointer, "%s", message);
		}
	}

	template<typename src_type>
	static void check_and_report_truncation_or_signedness_error(const integer_type<T, integer_policy>& self, src_type src) {
		typedef long long llong_type;
		typedef unsigned long long ullong_type;
		typedef std::numeric_limits<src_type> src_type_info;
		if (not can_cast_properly<T>(src) and (output_file_pointer != NULL)) {
			print_source_file_info(self);
			if (src_type_info::is_signed) {
				if (type_info::is_signed)
					fprintf(output_file_pointer, "Truncation error: %lld [signed, %d-byte, min: %lld, max: %lld] -> %lld [signed, %d-byte, min: %lld, max: %lld]\n\n",
					(llong_type) src, (int) sizeof(src), (llong_type) src_type_info::min(), (llong_type) src_type_info::max(),
					(llong_type) self.m_value, (int) sizeof(self.m_value), (llong_type) type_info::min(), (llong_type) type_info::max());
				else
					fprintf(output_file_pointer, "Signedness error: %lld [signed, %d-byte, min: %lld, max: %lld] -> %llu [unsigned, %d-byte, min: %llu, max: %llu]\n\n",
					(llong_type) src, (int) sizeof(src), (llong_type) src_type_info::min(), (llong_type) src_type_info::max(),
					(ullong_type) self.m_value, (int) sizeof(self.m_value), (ullong_type) type_info::min(), (ullong_type) type_info::max());
			} else {
				if (type_info::is_signed)
					fprintf(output_file_pointer, "Signedness error: %llu [unsigned, %d-byte, min: %llu, max: %llu] -> %lld [signed, %d-byte, min: %lld, max: %lld]\n\n",
					(ullong_type) src, (int) sizeof(src), (ullong_type) src_type_info::min(), (ullong_type) src_type_info::max(),
					(llong_type) self.m_value, (int) sizeof(self.m_value), (llong_type) type_info::min(), (llong_type) type_info::max());
				else
					fprintf(output_file_pointer, "Truncation error: %llu [unsigned, %d-byte, min: %llu, max: %llu] -> %llu [unsigned, %d-byte, min: %llu, max: %llu]\n\n",
					(ullong_type) src, (int) sizeof(src), (ullong_type) src_type_info::min(), (ullong_type) src_type_info::max(),
					(ullong_type) self.m_value, (int) sizeof(self.m_value), (ullong_type) type_info::min(), (ullong_type) type_info::max());
			}

#ifdef SAFER_INTEGER_USE_CPLUSPLUS_EXCEPTION
			throw std::runtime_error("Truncation or signedness error.");
#endif
		}
	}

	integer_type(
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		const char *info = "<unknown info>"
#else
		const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(static_cast<T>(0))
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
		print_source_file_info(*this);
		print_message("The safer integer variable is default initialized to zero. [A native integer will not be initialized.]\n\n");
#ifdef SAFER_INTEGER_USE_CPLUSPLUS_EXCEPTION
		throw std::runtime_error("The variable is not initialized.\n");
#endif
	}

	integer_type(T src
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(src)
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
	}

	template<typename U>
	integer_type(U src
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(static_cast<T>(src))
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
		typedef std::numeric_limits<U> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		check_and_report_truncation_or_signedness_error(*this, src);
	}

	integer_type(const integer_type& src
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(src.m_value)
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
	}

	template<typename U>
	integer_type(const integer_type<U>& rhs
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(static_cast<T>(static_cast<U>(rhs)))
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
		typedef std::numeric_limits<U> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		const U src = static_cast<U>(rhs);
		check_and_report_truncation_or_signedness_error(*this, src);
	}

	integer_type& operator=(T src) {
		m_value = src;
		return *this;
	}

	template<typename U>
	integer_type& operator=(U src) {
		typedef std::numeric_limits<U> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		check_and_report_truncation_or_signedness_error(*this, src);
		return *this;
	}

	integer_type& operator=(const integer_type& src) {
		m_value = src.m_value;
		return *this;
	}

	template<typename U>
	integer_type& operator=(const integer_type<U>& rhs) {
		typedef std::numeric_limits<U> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		const U src = static_cast<U>(rhs);
		check_and_report_truncation_or_signedness_error(*this, src);
		return *this;
	}

	operator T() const {
		return m_value;
	}

private:
	T m_value;

#ifdef SAFER_INTEGER_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	const char *m_source_file_info;
#else
	std::source_location m_source_file_info;
#endif
#endif
};

// operator functions that support integer promotion
template<typename T, typename integer_policy, typename promotion_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_unary_plus(const integer_type<T, integer_policy>& operand) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	return result_integer_type(static_cast<result_type>(static_cast<T>(operand)));
}

template<typename T, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_unary_minus(const integer_type<T, integer_policy>& operand) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type value = static_cast<result_type>(static_cast<T>(operand));
	result_type result = static_cast<result_type>(0);
	if (result_type_info::is_signed) {
		const result_type min = result_type_info::min();
		const result_type max = result_type_info::max();
		const result_type one = static_cast<result_type>(1);
		if ((value == min) and (min == - max - one)) {
			const operation_type operation = operation_unary_minus;
			const operation_error_type error = operation_error_signed_result_more_than_max;
			const T operand_1 = static_cast<T>(operand);
			const T operand_2 = static_cast<T>(0);
			result = result_policy::calculate_result(operation, error, operand_1, operand_2);
			debug_info_type<T,T,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
			integer_type<T, integer_policy>::print_source_file_info(operand);
			error_policy::handle_error(debug_info);
		} else {
			result = -value;
		}
	} else {
		const operation_type operation = operation_unary_minus;
		const operation_error_type error = operation_error_unary_negation_of_unsigned_integer;
		const T operand_1 = static_cast<T>(operand);
		const T operand_2 = static_cast<T>(0);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T,T,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T, integer_policy>::print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T, typename integer_policy, typename result_policy, typename error_policy>
integer_type<T, integer_policy>
operator_post_increment(integer_type<T, integer_policy>& operand, int unused) {
	typedef typename std::numeric_limits<T> type_info;
	T value = static_cast<T>(operand);
	const T previous_value = value;
	if (value != type_info::max()) {
		value++;
	} else {
		const operation_type operation = operation_post_increment;
		const operation_error_type error = (type_info::is_signed) ?
			operation_error_signed_result_more_than_max :
			operation_error_unsigned_result_wraparound_to_smaller;
		const T operand_1 = static_cast<T>(operand);
		const T operand_2 = static_cast<T>(0);
		value = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T,T,T> debug_info(operation, error, operand_1, operand_2, value, __FILE__, __LINE__);
		integer_type<T, integer_policy>::print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	operand = value;
	return integer_type<T, integer_policy>(previous_value);
}

template<typename T, typename integer_policy, typename result_policy, typename error_policy>
integer_type<T, integer_policy>&
operator_pre_increment(integer_type<T, integer_policy>& operand) {
	typedef typename std::numeric_limits<T> type_info;
	T value = static_cast<T>(operand);
	if (value != type_info::max()) {
		++value;
	} else {
		const operation_type operation = operation_pre_increment;
		const operation_error_type error = (type_info::is_signed) ?
			operation_error_signed_result_more_than_max :
			operation_error_unsigned_result_wraparound_to_smaller;
		const T operand_1 = static_cast<T>(operand);
		const T operand_2 = static_cast<T>(0);
		value = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T,T,T> debug_info(operation, error, operand_1, operand_2, value, __FILE__, __LINE__);
		integer_type<T, integer_policy>::print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	operand = value;
	return operand;
}

template<typename T, typename integer_policy, typename result_policy, typename error_policy>
integer_type<T, integer_policy>
operator_post_decrement(integer_type<T, integer_policy>& operand, int unused) {
	typedef typename std::numeric_limits<T> type_info;
	T value = static_cast<T>(operand);
	const T previous_value = value;
	if (value != type_info::min()) {
		value--;
	} else {
		const operation_type operation = operation_post_decrement;
		const operation_error_type error = (type_info::is_signed) ?
			operation_error_signed_result_less_than_min :
			operation_error_unsigned_result_wraparound_to_larger;
		const T operand_1 = static_cast<T>(operand);
		const T operand_2 = static_cast<T>(0);
		value = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T,T,T> debug_info(operation, error, operand_1, operand_2, value, __FILE__, __LINE__);
		integer_type<T, integer_policy>::print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	operand = value;
	return integer_type<T, integer_policy>(previous_value);
}

template<typename T, typename integer_policy, typename result_policy, typename error_policy>
integer_type<T, integer_policy>&
operator_pre_decrement(integer_type<T, integer_policy>& operand) {
	typedef typename std::numeric_limits<T> type_info;
	T value = static_cast<T>(operand);
	if (value != type_info::min()) {
		--value;
	} else {
		const operation_type operation = operation_pre_decrement;
		const operation_error_type error = (type_info::is_signed) ?
			operation_error_signed_result_less_than_min :
			operation_error_unsigned_result_wraparound_to_larger;
		const T operand_1 = static_cast<T>(operand);
		const T operand_2 = static_cast<T>(0);
		value = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T,T,T> debug_info(operation, error, operand_1, operand_2, value, __FILE__, __LINE__);
		integer_type<T, integer_policy>::print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	operand = value;
	return operand;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_plus(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_addition(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_addition(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) + static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_addition;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_minus(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_subtraction(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_subtraction(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) - static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_subtraction;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_multiply(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_multiplication(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_multiplication(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) * static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_multiplication;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_divide(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) / static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_division;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_remainder(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) % static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_remainder;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_plus_assignment(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_addition(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_addition(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) + static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_addition;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_minus_assignment(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_subtraction(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_subtraction(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) - static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_subtraction;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_multiply_assignment(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_multiplication(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_multiplication(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) * static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_multiplication;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_divide_assignment(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) / static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_division;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_remainder_assignment(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = (result_type_info::is_signed) ?
		check_signed_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs)) :
		check_unsigned_division(static_cast<result_type>(lhs), static_cast<result_type>(rhs));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) % static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_remainder;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy>
bool comparison_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	return (static_cast<result_type>(lhs) == static_cast<result_type>(rhs));
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy>
bool comparison_not_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	return (static_cast<result_type>(lhs) != static_cast<result_type>(rhs));
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy>
bool comparison_greater_than(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	return (static_cast<result_type>(lhs) > static_cast<result_type>(rhs));
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy>
bool comparison_greater_than_or_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	return (static_cast<result_type>(lhs) >= static_cast<result_type>(rhs));
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy>
bool comparison_less_than(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	return (static_cast<result_type>(lhs) < static_cast<result_type>(rhs));
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy>
bool comparison_less_than_or_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	return (static_cast<result_type>(lhs) <= static_cast<result_type>(rhs));
}

template<typename T1, typename T2, typename integer_policy>
bool logical_and(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	return ((operand_1 != 0) && (operand_2 != 0));
}

template<typename T1, typename T2, typename integer_policy>
bool logical_or(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	return ((operand_1 != 0) || (operand_2 != 0));
}

template<typename T, typename integer_policy>
bool logical_not(const integer_type<T, integer_policy>& operand) {
	const T operand_ = static_cast<T>(operand);
	return !(operand_ != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_and(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = check_bitwise_and_operation(static_cast<T1>(operand1), static_cast<T2>(operand2));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) & static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_bitwise_and;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_or(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = check_bitwise_or_operation(static_cast<T1>(operand1), static_cast<T2>(operand2));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) | static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_bitwise_or;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_xor(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, operand2);
	const operation_error_type error = check_bitwise_xor_operation(static_cast<T1>(operand1), static_cast<T2>(operand2));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) ^ static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_bitwise_xor;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_not(const integer_type<T, integer_policy>& operand) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, operand_, operand);
	const operation_error_type error = check_bitwise_not_operation(static_cast<T>(operand));
	if (error == operation_error_none) {
		result = ~static_cast<result_type>(operand_);
	} else {
		const operation_type operation = operation_bitwise_not;
		const T operand_1 = static_cast<T>(operand);
		const T operand_2 = static_cast<T>(0);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T,T,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T, integer_policy>::print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>
operator_bitwise_left_shift(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const operation_error_type error = check_left_shift_operation(static_cast<T1>(operand1), static_cast<T2>(operand2));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) << static_cast<result_type>(static_cast<T2>(operand2));
	} else {
		const operation_type operation = operation_bitwise_left_shift;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>
operator_bitwise_right_shift(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, operand1);
	const operation_error_type error = check_right_shift_operation(static_cast<T1>(operand1), static_cast<T2>(operand2));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) >> static_cast<result_type>(static_cast<T2>(operand2));
	} else {
		const operation_type operation = operation_bitwise_right_shift;
		const T1 operand_1 = static_cast<T1>(operand1);
		const T2 operand_2 = static_cast<T2>(operand2);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(operand1);
		integer_type<T2, integer_policy>::print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return result_integer_type(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_and(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = check_bitwise_and_operation(static_cast<T1>(self), static_cast<T2>(value));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) & static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_bitwise_and;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_or(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = check_bitwise_or_operation(static_cast<T1>(self), static_cast<T2>(value));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) | static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_bitwise_or;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_xor(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const DEFINE_SAFER_INTEGER(result_integer_type, rhs, value);
	const operation_error_type error = check_bitwise_xor_operation(static_cast<T1>(self), static_cast<T2>(value));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) ^ static_cast<result_type>(rhs);
	} else {
		const operation_type operation = operation_self_bitwise_xor;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_left_shift(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const operation_error_type error = check_left_shift_operation(static_cast<T1>(self), static_cast<T2>(value));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) << static_cast<result_type>(static_cast<T2>(value));
	} else {
		const operation_type operation = operation_self_bitwise_left_shift;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_right_shift(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef integer_type<result_type, integer_policy> result_integer_type;
	result_type result = static_cast<result_type>(0);
	const DEFINE_SAFER_INTEGER(result_integer_type, lhs, self);
	const operation_error_type error = check_right_shift_operation(static_cast<T1>(self), static_cast<T2>(value));
	if (error == operation_error_none) {
		result = static_cast<result_type>(lhs) >> static_cast<result_type>(static_cast<T2>(value));
	} else {
		const operation_type operation = operation_self_bitwise_right_shift;
		const T1 operand_1 = static_cast<T1>(self);
		const T2 operand_2 = static_cast<T2>(value);
		result = result_policy::calculate_result(operation, error, operand_1, operand_2);
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		integer_type<T1, integer_policy>::print_source_file_info(self);
		integer_type<T2, integer_policy>::print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

} // end of namespace

// Global overloaded operators
#define SI safer_integer

// unary plus
template<typename T>
SI::integer_type<typename SI::DPP<T,T>::type, SI::DIP>
operator+(const SI::integer_type<T, SI::DIP>& operand) {
	return SI::operator_unary_plus<T, SI::DIP>(operand);
}

// unary minus
template<typename T>
SI::integer_type<typename SI::DPP<T,T>::type, SI::DIP>
operator-(const SI::integer_type<T, SI::DIP>& operand) {
	typedef typename SI::DPP<T,T>::type result_type;
	return SI::operator_unary_minus<
		T, SI::DIP, SI::DPP<T,T>, SI::DRP<T,T,result_type>, SI::DEP<T,T,result_type>
	>(operand);
}

// post-increment
template<typename T>
SI::integer_type<T, SI::DIP>
operator++(SI::integer_type<T, SI::DIP>& operand, int unused) {
	return SI::operator_post_increment<
		T, SI::DIP, SI::DRP<T,T,T>, SI::DEP<T,T,T>
	>(operand, unused);
}

// pre-increment
template<typename T>
SI::integer_type<T, SI::DIP>&
operator++(SI::integer_type<T, SI::DIP>& operand) {
	return SI::operator_pre_increment<
		T, SI::DIP, SI::DRP<T,T,T>, SI::DEP<T,T,T>
	>(operand);
}

// post-decrement
template<typename T>
SI::integer_type<T, SI::DIP>
operator--(SI::integer_type<T, SI::DIP>& operand, int unused) {
	return SI::operator_post_decrement<
		T, SI::DIP, SI::DRP<T,T,T>, SI::DEP<T,T,T>
	>(operand, unused);
}

// pre-decrement
template<typename T>
SI::integer_type<T, SI::DIP>&
operator--(SI::integer_type<T, SI::DIP>& operand) {
	return SI::operator_pre_decrement<
		T, SI::DIP, SI::DRP<T,T,T>, SI::DEP<T,T,T>
	>(operand);
}

// addition
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator+(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_plus<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator+(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a + SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator+(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) + b;
}

// subtraction
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator-(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_minus<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator-(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a - SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator-(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) - b;
}

// multiplication
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator*(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_multiply<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator*(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a * SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator*(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) * b;
}

// division
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator/(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_divide<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator/(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a / SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator/(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) / b;
}

// remainder
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator%(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_remainder<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator%(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a % SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator%(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) % b;
}

// adding a number to self
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator+=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_plus_assignment<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator+=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self += SI::integer_type<T2, SI::DIP>(value);
}

// subtracting number from self
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator-=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_minus_assignment<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator-=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self -= SI::integer_type<T2, SI::DIP>(value);
}

// muliplying self by a number
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator*=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_multiply_assignment<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator*=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self *= SI::integer_type<T2, SI::DIP>(value);
}

// dividing self by a number
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator/=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_divide_assignment<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator/=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self /= SI::integer_type<T2, SI::DIP>(value);
}

// remainder after dividing self by a number
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator%=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_remainder_assignment<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator%=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self %= SI::integer_type<T2, SI::DIP>(value);
}

// equal comparison
template<typename T1, typename T2>
bool operator==(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::comparison_equal<T1, T2, SI::DIP, SI::DPP<T1,T2> >(a, b);
}

template<typename T1, typename T2>
bool operator==(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a == SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator==(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) == b;
}

// unequal comparison
template<typename T1, typename T2>
bool operator!=(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::comparison_not_equal<T1, T2, SI::DIP, SI::DPP<T1,T2> >(a, b);
}

template<typename T1, typename T2>
bool operator!=(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a != SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator!=(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) != b;
}

// greater than comparison
template<typename T1, typename T2>
bool operator>(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::comparison_greater_than<T1, T2, SI::DIP, SI::DPP<T1,T2> >(a, b);
}

template<typename T1, typename T2>
bool operator>(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a > SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator>(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) > b;
}

// greater than or equal comparison
template<typename T1, typename T2>
bool operator>=(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::comparison_greater_than_or_equal<T1, T2, SI::DIP, SI::DPP<T1,T2> >(a, b);
}

template<typename T1, typename T2>
bool operator>=(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a >= SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator>=(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) >= b;
}

// less than comparison
template<typename T1, typename T2>
bool operator<(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::comparison_less_than<T1, T2, SI::DIP, SI::DPP<T1,T2> >(a, b);
}

template<typename T1, typename T2>
bool operator<(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a < SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator<(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) < b;
}

// less than or equal comparison
template<typename T1, typename T2>
bool operator<=(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::comparison_less_than_or_equal<T1, T2, SI::DIP, SI::DPP<T1,T2> >(a, b);
}

template<typename T1, typename T2>
bool operator<=(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a <= SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator<=(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) <= b;
}

// logical AND (short-circuit AND)
template<typename T1, typename T2>
bool operator&&(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::logical_and<T1, T2, SI::DIP>(a, b);
}

template<typename T1, typename T2>
bool operator&&(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a && SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator&&(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) && b;
}

// logical OR (short-circuit OR)
template<typename T1, typename T2>
bool operator||(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::logical_or<T1, T2, SI::DIP>(a, b);
}

template<typename T1, typename T2>
bool operator||(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a || SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator||(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) || b;
}

// logical NOT
template<typename T>
bool operator!(const SI::integer_type<T, SI::DIP>& a) {
	return SI::logical_not<T, SI::DIP>(a);
}

// bitwise AND
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator&(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_bitwise_and<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator&(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a & SI::integer_type<T2, SI::DIP>(b); 
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator&(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) & b;
}

// bitwise OR
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator|(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_bitwise_or<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator|(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a | SI::integer_type<T2, SI::DIP>(b); 
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator|(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) | b;
}

// bitwise XOR
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator^(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_bitwise_xor<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator^(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a ^ SI::integer_type<T2, SI::DIP>(b); 
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T2>::type, SI::DIP>
operator^(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) ^ b;
}

// bitwise NOT
template<typename T>
SI::integer_type<typename SI::DPP<T,T>::type, SI::DIP>
operator~(const SI::integer_type<T, SI::DIP>& a) {
	typedef typename SI::DPP<T,T>::type result_type;
	return SI::operator_bitwise_not<
		T, SI::DIP, SI::DPP<T,T>, SI::DRP<T,T,result_type>, SI::DEP<T,T,result_type>
	>(a);
}

// bitwise left shift
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T1>::type, SI::DIP> // integer promotion only on the LHS
operator<<(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T1>::type result_type;
	return SI::operator_bitwise_left_shift<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T1>::type, SI::DIP> // integer promotion only on the LHS
operator<<(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a << SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T1>::type, SI::DIP> // integer promotion only on the LHS
operator<<(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T1>::type result_type;
	return SI::integer_type<T1, SI::DIP>(a) << b;
}

// bitwise right shift
template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T1>::type, SI::DIP> // integer promotion only on the LHS
operator>>(const SI::integer_type<T1, SI::DIP>& a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T1>::type result_type;
	return SI::operator_bitwise_right_shift<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(a, b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T1>::type, SI::DIP> // integer promotion only on the LHS
operator>>(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a >> SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
SI::integer_type<typename SI::DPP<T1,T1>::type, SI::DIP> // integer promotion only on the LHS
operator>>(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	typedef typename SI::DPP<T1,T1>::type result_type;
	return SI::integer_type<T1, SI::DIP>(a) >> b;
}

// self bitwise AND
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator&=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_self_bitwise_and<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator&=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self &= SI::integer_type<T2, SI::DIP>(value);
}

// self bitwise OR
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator|=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_self_bitwise_or<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator|=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self |= SI::integer_type<T2, SI::DIP>(value);
}

// self bitwise XOR
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator^=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T2>::type result_type;
	return SI::operator_self_bitwise_xor<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator^=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self ^= SI::integer_type<T2, SI::DIP>(value);
}

// self bitwise left shift
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator<<=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T1>::type result_type;
	return SI::operator_self_bitwise_left_shift<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator<<=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self <<= SI::integer_type<T2, SI::DIP>(value);
}

// self bitwise right shift
template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator>>=(SI::integer_type<T1, SI::DIP>& self, const SI::integer_type<T2, SI::DIP>& value) {
	typedef typename SI::DPP<T1,T1>::type result_type;
	return SI::operator_self_bitwise_right_shift<
		T1, T2, SI::DIP, SI::DPP<T1,T1>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
	>(self, value);
}

template<typename T1, typename T2>
SI::integer_type<T1, SI::DIP>&
operator>>=(SI::integer_type<T1, SI::DIP>& self, T2 value) {
	return self >>= SI::integer_type<T2, SI::DIP>(value);
}

#undef SI

#endif
