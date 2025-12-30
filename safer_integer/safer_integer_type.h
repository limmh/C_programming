#ifndef SAFER_INTEGER_TYPE_H
#define SAFER_INTEGER_TYPE_H

#include "fixed_width_integer_types.h"
#include <limits.h>

/*
The purpose of the header file is to provide an generic emulated integer type implemented and user-friendly
safer integer types which support integer operation diagnostics. The safer integer types themselves DO NOT
automatically guarantee integer safety, but using them can allow us to switch between built-in integer types and
safer integer types easily.

Runtime checks are only possible for C++, so if the header file is included by a C source file, each safer integer type
is a built-in integer type. However, if the C file can be compiled as C++, then integer arithmetic operations in the file can be verified
with proper tests. Hence, the safer integer types can be used in unit tests or runtime tests to detect integer issues.

Emulated integer type: safer_integer::integer_type<native_integer_type>
User-friendly safer integer types:
- safer_bool_type: represents bool
- safer_char_type: represents char
- safer_schar_type: represents signed char
- safer_uchar_type: represents unsigned char
- safer_short_type: represents short
- safer_ushort_type: represents unsigned short
- safer_int_type: represents int
- safer_uint_type: represents unsigned int
- safer_long_type: represents long
- safer_ulong_type: represents unsigned long
- safer_llong_type: represents long long
- safer_ullong_type: represents unsigned long long
- safer_ptrdiff_type: represents ptrdiff_t
- safer_size_type: represents size_t
- safer_int8_type: represents int8_t
- safer_uint8_type: represents uint8_t
- safer_int16_type: represents int16_t
- safer_uint16_type: represents uint16_t
- safer_int32_type: represents int32_t
- safer_uint32_type: represents uint32_t
- safer_int64_type: represents int64_t
- safer_uint64_type: represents uint64_t

If the header is included by a C source file, each safer integer type will be its corresponding native integer type.
If the header is included by a C++ source file, each safer integer type will be safer_integer::integer_type<T>,
where T is the corresponding native type.

How to configure the header file?

Compiler switches and their meanings
------------------------------------
The following compiler switches are not applicable to C++ source files.
SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES: The user-friendly integer types will become native integer types.
SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO: Source file information will be stored, will increase the size of integer_type<T>
SAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES: Safer integers will throw an exception when an instance is uninitialized
SAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS: Safer integers will throw an exception when a conversion error is detected.
SAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS: Safer integers will thrown an exception when an arithmetic operation error is detected.
SAFER_INTEGER_TYPE_APPLY_SATURATED_RESULTS: The default result policy will apply saturated results for arithmetic operations (+,-,*,/)
SAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_CONVERSION_ERRORS: Error reporting for conversion errors will be disabled
SAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_OPERATION_ERRORS: Error reporting for operation errors will be disabled
SAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_UNINITIALIZED_VARIABLES: Error reporting for uninitialized safer integer variables will be disabled

By default, the compiler switches above are not defined, integer_type<T> will have the same size as T.

When source file information is included by defining SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO before header file inclusion,
each safer integer will store additional information related to the source file that defines safer integer variables.
Before C++20, DECLARE_SAFER_INTEGER(type, name) or DEFINE_SAFER_INTEGER(type, name, value) needs to be used when defining a safer integer variable
if source file information (the path or name of source file and the line number where the variable is defined) needs to be stored
because it is not possible for overloaded operators to have extra parameters with default arguments.
Constructors can have multiple parameters, so each constructor has an optional parameter with default argument related to source file information.
If variable information is available, it will be included during error reporting.
Since it is not possible to inject source file information at overloaded operator function call sites, the exact line number cannot be reported.
This is a limitation.

Runtime exceptions are disabled by default. They can be enabled by defining the relevant compiler switches.
There are three groups of errors: uninitialized variables, conversion errors and operation errors (for unary and binary operations).
The runtime exception for each group can be enabled or disabled separately.
Error reporting is enabled by default. Errors are reported to stderr by default and the output file pointer can be changed programmatically
by calling safer_integer::set_output_file_pointer(FILE*) in your application code.
*/

#if defined(__cplusplus) && !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES) && defined(SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO)

#if __cplusplus < 202002L
#include "macro_stringify.h"
#define DECLARE_SAFER_INTEGER(type, name) type name(#name " (type: " #type ") [defined at line " STRINGIFY(__LINE__) " of " __FILE__ "]")
#define DEFINE_SAFER_INTEGER(type, name, value) type name(value, #name " (type: " #type ") [defined at line " STRINGIFY(__LINE__) " of " __FILE__ "]")
#else
#include <source_location>
#define DECLARE_SAFER_INTEGER(type, name) type name
#define DEFINE_SAFER_INTEGER(type, name, value) type name = value
#endif

#else /* not __cplusplus or runtime checks are disabled or source file info is not required */

#define DECLARE_SAFER_INTEGER(type, name) type name
#define DEFINE_SAFER_INTEGER(type, name, value) type name = value

#endif

#if defined(__cplusplus)

#include "static_assert.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <limits>
#include <stdexcept>

namespace safer_integer {

#define OPERATIONS \
	OP(operation_unknown, 0U, "unknown operation", "unknown operator", false) \
	OP(operation_unary_plus, 1U, "unary plus", "+", false) \
	OP(operation_unary_minus, 1U, "unary minus", "-", false) \
	OP(operation_post_increment, 1U, "post-increment", "++", false) \
	OP(operation_pre_increment, 1U, "pre-increment", "++", false) \
	OP(operation_post_decrement, 1U, "post-decrement", "--", false) \
	OP(operation_pre_decrement, 1U, "pre-decrement", "--", false) \
	OP(operation_addition, 2U, "addition", "+", false) \
	OP(operation_self_addition, 2U, "adding a number to self", "+=", false) \
	OP(operation_subtraction, 2U, "subtraction", "-", false) \
	OP(operation_self_subtraction, 2U, "subtracting a number from self", "-=", false) \
	OP(operation_multiplication, 2U, "multiplication", "*", false) \
	OP(operation_self_multiplication, 2U, "multiplying self by a number", "*=", false) \
	OP(operation_division, 2U, "division", "/", false) \
	OP(operation_self_division, 2U, "dividing self by a number", "/=", false) \
	OP(operation_remainder, 2U, "remainder", "%", false) \
	OP(operation_self_remainder, 2U, "remainder of dividing self by a number", "%=", false) \
	OP(operation_comparison_equal, 2U, "equal comparison", "==", true) \
	OP(operation_comparison_not_equal, 2U, "unequal comparison", "!=", true) \
	OP(operation_comparison_greater, 2U, "greater than comparison", ">", true) \
	OP(operation_comparison_greater_or_equal, 2U, "greater than or equal comparison", ">=", true) \
	OP(operation_comparison_less, 2U, "less than comparison", "<", true) \
	OP(operation_comparison_less_or_equal, 2U, "less than or equal comparison", "<=", true) \
	OP(operation_bitwise_and, 2U, "bitwise AND", "&", false) \
	OP(operation_self_bitwise_and, 2U, "self bitwise AND", "&=", false) \
	OP(operation_bitwise_or, 2U, "bitwise OR", "|", false) \
	OP(operation_self_bitwise_or, 2U, "self bitwise OR", "|=", false) \
	OP(operation_bitwise_xor, 2U, "bitwise XOR", "^", false) \
	OP(operation_self_bitwise_xor, 2U, "bitwise XOR", "^=", false) \
	OP(operation_bitwise_not, 1U, "bitwise NOT", "~", false) \
	OP(operation_bitwise_left_shift, 2U, "bitwise left shift", "<<", false) \
	OP(operation_self_bitwise_left_shift, 2U, "self bitwise left shift", "<<=", false) \
	OP(operation_bitwise_right_shift, 2U, "bitwise right shift", ">>", false) \
	OP(operation_self_bitwise_right_shift, 2U, "self bitwise right shift", ">>=", false)

enum operation_type {
#define OP(operation_enum_constant, number_of_operands, operation_name, operator_symbol, returns_Boolean_result) operation_enum_constant,
	OPERATIONS
#undef OP
};

size_t operand_count(operation_type type) {
	size_t count = 0U;
#define OP(operation_enum_constant, number_of_operands, operation_name, operator_symbol, returns_Boolean_result) \
	case operation_enum_constant: count = number_of_operands; break;
	switch (type) {
	OPERATIONS
	default:
		count = 0U;
		break;
	}
	return count;
#undef OP
}

const char *operation_name(operation_type type) {
	const char *name = NULL;
#define OP(operation_enum_constant, number_of_operands, operation_name, operator_symbol, returns_Boolean_result) \
	case operation_enum_constant: name = operation_name; break;
	switch (type) {
	OPERATIONS
	default:
		name = "unknown operation type";
		break;
	}
	assert(name != NULL);
	return name;
#undef OP
}

const char *operator_symbol(operation_type type) {
	const char *symbol = NULL;
#define OP(operation_enum_constant, number_of_operands, operation_name, operator_symbol, returns_Boolean_result) \
	case operation_enum_constant: symbol = operator_symbol; break;
	switch (type) {
	OPERATIONS
	default:
		symbol = "unknown operator";
		break;
	}
	assert(symbol != NULL);
	return symbol;
#undef OP
}

bool operation_returns_Boolean_result(operation_type type) {
	bool returns_Boolean = false;
#define OP(operation_enum_constant, number_of_operands, operation_name, operator_symbol, returns_Boolean_result) \
	case operation_enum_constant: returns_Boolean = returns_Boolean_result; break;
	switch (type) {
	OPERATIONS
	default:
		returns_Boolean = false;
		break;
	}
	return returns_Boolean;
}

#undef OPERATIONS

#define OPERATION_ERRORS \
	OPERROR(operation_error_none, "No error") \
	OPERROR(operation_error_left_operand_cannot_be_represented_by_promoted_type, "The value of the left operand cannot be represented by the promoted type.") \
	OPERROR(operation_error_right_operand_cannot_be_represented_by_promoted_type, "The value of the right operand cannot be represented by the promoted type.") \
	OPERROR(operation_error_signed_result_less_than_min, "Signed integer result < MIN") \
	OPERROR(operation_error_signed_result_more_than_max, "Signed integer result > MAX") \
	OPERROR(operation_error_division_of_signed_integer_by_zero, "Signed integer / zero") \
	OPERROR(operation_error_division_of_min_by_minus_one, "(Minimum signed integer / -1) [two's complement]") \
	OPERROR(operation_error_unsigned_result_wraparound_to_smaller, "Unsigned integer result > MAX") \
	OPERROR(operation_error_unsigned_result_wraparound_to_larger, "Unsigned integer result < zero") \
	OPERROR(operation_error_division_of_unsigned_integer_by_zero, "Unsigned integer / zero") \
	OPERROR(operation_error_unary_negation_of_unsigned_integer, "Negation of unsigned integer") \
	OPERROR(operation_error_left_operand_of_bitwise_and_is_negative, "The left operand of the bitwise AND operation is negative.") \
	OPERROR(operation_error_right_operand_of_bitwise_and_is_negative, "The right operand of the bitwise AND operation is negative.") \
	OPERROR(operation_error_both_operands_of_bitwise_and_are_negative, "Both the operands of the bitwise AND operation are negative.") \
	OPERROR(operation_error_left_operand_of_bitwise_or_is_negative, "The left operand of the bitwise OR operation is negative.") \
	OPERROR(operation_error_right_operand_of_bitwise_or_is_negative, "The right operand of the bitwise OR operation is negative.") \
	OPERROR(operation_error_both_operands_of_bitwise_or_are_negative, "Both the operands of the bitwise OR operation are negative.") \
	OPERROR(operation_error_left_operand_of_bitwise_xor_is_negative, "The left operand of the bitwise XOR operation is negative.") \
	OPERROR(operation_error_right_operand_of_bitwise_xor_is_negative, "The right operand of the bitwise XOR operation is negative.") \
	OPERROR(operation_error_both_operands_of_bitwise_xor_are_negative, "Both the operands of the bitwise XOR operation are negative.") \
	OPERROR(operation_error_operand_of_bitwise_not_is_negative, "The operand of the bitwise NOT operation is negative.") \
	OPERROR(operation_error_left_operand_of_bitwise_left_shift_is_negative, "The left operand of the bitwise left shift operation is negative.") \
	OPERROR(operation_error_right_operand_of_bitwise_left_shift_is_out_of_range, "The right operand of the bitwise left shift operation is out of range.") \
	OPERROR(operation_error_both_operands_of_bitwise_left_shift_are_negative_or_out_of_range, "Both the operands of the bitwise left shift operation are negative or out of range.") \
	OPERROR(operation_error_left_operand_of_bitwise_right_shift_is_negative, "The left operand of the bitwise right shift operation is negative.") \
	OPERROR(operation_error_right_operand_of_bitwise_right_shift_is_out_of_range, "The right operand of the bitwise right shift operation is out of range.") \
	OPERROR(operation_error_both_operands_of_bitwise_right_shift_are_negative_or_out_of_range, "Both the operands of the bitwise right shift operation are negative or out of range.")

enum operation_error_type {
#define OPERROR(operation_error_enum_constant, operation_error_string) operation_error_enum_constant, 
	OPERATION_ERRORS
#undef OPERROR
};

const char *operation_error_message(operation_error_type error) {
	const char *message = NULL;
#define OPERROR(operation_error_enum_constant, operation_error_string) case operation_error_enum_constant: message = operation_error_string; break;
	switch (error) {
	OPERATION_ERRORS
	default:
		message = "unknown error";
		break;
	}
	assert(message != NULL);
	return message;
#undef OPERROR
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
	typedef ptrdiff_t ptrdiff_type;
	typedef size_t size_type;
};

// Default Promotion Policy - must be specialized for all possible combinations of two integer types, except for ptrdiff_type and size_type because they are typedefs
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
#elif (USHRT_MAX == UINT_MAX)
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
#else
#pragma message("It seems that sizeof(unsigned short) is larger than sizeof(unsigned int).")
#pragma message("Please check your compiler for more details.")
#endif

template<> struct DPP<DIP::int_type, DIP::bool_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::char_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::schar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::uchar_type> {typedef DIP::int_type type;};
template<> struct DPP<DIP::int_type, DIP::short_type> {typedef DIP::int_type type;};
#if USHRT_MAX < INT_MAX
template<> struct DPP<DIP::int_type, DIP::ushort_type> {typedef DIP::int_type type;};
#elif (USHRT_MAX == UINT_MAX)
template<> struct DPP<DIP::int_type, DIP::ushort_type> {typedef DIP::uint_type type;};
#else
#pragma message("It seems that sizeof(unsigned short) is larger than sizeof(unsigned int).")
#pragma message("Please check your compiler for more details.")
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
#else
#pragma message("It seems that sizeof(unsigned int) is larger than sizeof(unsigned long).")
#pragma message("Please check your compiler for more details.")
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
#else
#pragma message("It seems that sizeof(unsigned int) is larger than sizeof(unsigned long).")
#pragma message("Please check your compiler for more details.")
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
#else
#pragma message("It seems that sizeof(unsigned long) is larger than sizeof(unsigned long long).")
#pragma message("Please check your compiler for more details.")
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
#else
#pragma message("It seems that sizeof(unsigned long) is larger than sizeof(unsigned long long).")
#pragma message("Please check your compiler for more details.")
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
template<> struct DPP<DIP::ullong_type, DIP::llong_type> {typedef DIP::ullong_type type;};
template<> struct DPP<DIP::ullong_type, DIP::ullong_type> {typedef DIP::ullong_type type;};
#endif

static
#if __cplusplus >= 201103L
thread_local
#endif
FILE *output_file_pointer = stderr;

static FILE *set_output_file_pointer(FILE *file_pointer) {
	FILE *previous_file_pointer = output_file_pointer;
	output_file_pointer = file_pointer;
	return previous_file_pointer;
}

// Default Error Policy - must provide a static member function called handle_error
template<typename T1, typename T2, typename result_type>
struct DEP {
	static void handle_error(const debug_info_type<T1, T2, result_type>& debug_info) {
#ifndef SAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_OPERATION_ERRORS
		typedef long long llong_type;
		typedef unsigned long long ullong_type;
		typedef std::numeric_limits<T1> T1_info;
		typedef std::numeric_limits<T2> T2_info;
		typedef std::numeric_limits<result_type> result_type_info;
		const result_type min_result = result_type_info::min();
		const result_type max_result = result_type_info::max();

		FILE *file_pointer = output_file_pointer;
		if (debug_info.error != operation_error_none and file_pointer != NULL) {
			assert(debug_info.file_path != NULL);
			assert(debug_info.line_number > 0);
			const char * const operation_name = safer_integer::operation_name(debug_info.operation);
			const char * const symbol = safer_integer::operator_symbol(debug_info.operation);
			const size_t operand_count = safer_integer::operand_count(debug_info.operation);
			const char * const error_message = safer_integer::operation_error_message(debug_info.error);
			fprintf(file_pointer, "-----\n");
			fprintf(file_pointer, "%s (line %d)\n", debug_info.file_path, debug_info.line_number);
			fprintf(file_pointer, "Error: %s\n", error_message);
			fprintf(file_pointer, "Operation: %s (%s), Number of operands: %d\n",
				operation_name, ((symbol[0] != '\0') ? symbol : "[no symbol]"), static_cast<int>(operand_count));

			if (operand_count >= 1U) {
				const T1 operand_1 = debug_info.operand_1;
				const T1 T1_min = T1_info::min();
				const T1 T1_max = T1_info::max();

				if (T1_info::is_signed) {
					fprintf(file_pointer, "Operand 1 [signed, %d-byte, min: %lld, max: %lld]: %lld",
						static_cast<int>(sizeof(operand_1)), static_cast<llong_type>(T1_min),
						static_cast<llong_type>(T1_max), static_cast<llong_type>(operand_1));
				} else {
					fprintf(file_pointer, "Operand 1 [unsigned, %d-byte, min: %llu, max: %llu]: %llu",
						static_cast<int>(sizeof(operand_1)), static_cast<ullong_type>(T1_min),
						static_cast<ullong_type>(T1_max), static_cast<ullong_type>(operand_1));
				}

				if (debug_info.error == operation_error_left_operand_cannot_be_represented_by_promoted_type) {
					if (result_type_info::is_signed) {
						fprintf(file_pointer, " -> %lld [signed, %d-byte, min: %lld, max: %lld]",
							static_cast<llong_type>(static_cast<result_type>(operand_1)), static_cast<int>(sizeof(result_type)),
							static_cast<llong_type>(min_result), static_cast<llong_type>(max_result));
					} else {
						fprintf(file_pointer, " -> %llu [unsigned, %d-byte, min: %llu, max: %llu]",
							static_cast<ullong_type>(static_cast<result_type>(operand_1)), static_cast<int>(sizeof(result_type)),
							static_cast<ullong_type>(min_result), static_cast<ullong_type>(max_result));
					}
				}

				fprintf(file_pointer, "\n");
			}

			if (operand_count >= 2U) {
				const T2 operand_2 = debug_info.operand_2;
				const T2 T2_min = T2_info::min();
				const T2 T2_max = T2_info::max();

				if (T2_info::is_signed) {
					fprintf(file_pointer, "Operand 2 [signed, %d-byte, min: %lld, max: %lld]: %lld",
						static_cast<int>(sizeof(operand_2)), static_cast<llong_type>(T2_min),
						static_cast<llong_type>(T2_max), static_cast<llong_type>(operand_2));
				} else {
					fprintf(file_pointer, "Operand 2 [unsigned, %d-byte, min: %llu, max: %llu]: %llu",
						static_cast<int>(sizeof(operand_2)), static_cast<ullong_type>(T2_min),
						static_cast<ullong_type>(T2_max), static_cast<ullong_type>(operand_2));
				}

				if (debug_info.error == operation_error_right_operand_cannot_be_represented_by_promoted_type) {
					if (result_type_info::is_signed) {
						fprintf(file_pointer, " -> %lld [signed, %d-byte, min: %lld, max: %lld]",
							static_cast<llong_type>(static_cast<result_type>(operand_2)), static_cast<int>(sizeof(result_type)),
							static_cast<llong_type>(min_result), static_cast<llong_type>(max_result));
					} else {
						fprintf(file_pointer, " -> %llu [unsigned, %d-byte, min: %llu, max: %llu]",
							static_cast<ullong_type>(static_cast<result_type>(operand_2)), static_cast<int>(sizeof(result_type)),
							static_cast<ullong_type>(min_result), static_cast<ullong_type>(max_result));
					}
				}

				fprintf(file_pointer, "\n");
			}

			if (operand_count >= 1U) {
				const result_type result = debug_info.result;
				if (not safer_integer::operation_returns_Boolean_result(debug_info.operation)) {
					if (result_type_info::is_signed) {
						fprintf(file_pointer, "Result [signed, %d-byte, min: %lld, max: %lld]: %lld\n",
							static_cast<int>(sizeof(result)), static_cast<llong_type>(min_result),
							static_cast<llong_type>(max_result), static_cast<llong_type>(result));
					} else {
						fprintf(file_pointer, "Result [unsigned, %d-byte, min: %llu, max: %llu]: %llu\n",
							static_cast<int>(sizeof(result)), static_cast<ullong_type>(min_result),
							static_cast<ullong_type>(max_result), static_cast<ullong_type>(result));
					}
				} else {
					typedef std::numeric_limits<bool> bool_type_info;
					fprintf(file_pointer, "Result [%ssigned, %d-byte, min: %d, max: %d]: %d\n",
						(bool_type_info::is_signed ? "" : "un"), static_cast<int>(sizeof(bool)),
						static_cast<int>(bool_type_info::min()), static_cast<int>(bool_type_info::max()), static_cast<bool>(result));
				}
			}

			fprintf(file_pointer, "-----\n");
		}
#endif

#ifdef SAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
		if (debug_info.error != operation_error_none) {
			throw std::runtime_error(safer_integer::operation_error_message(debug_info.error));
		}
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
#ifdef SAFER_INTEGER_TYPE_APPLY_SATURATED_RESULTS
		const result_type min_result = std::numeric_limits<result_type>::min();
		const result_type max_result = std::numeric_limits<result_type>::max();
#endif
		typename to_unsigned_type<result_type>::type value1 =
			static_cast<typename to_unsigned_type<result_type>::type>(operand_1);
		typename to_unsigned_type<result_type>::type value2 =
			static_cast<typename to_unsigned_type<result_type>::type>(operand_2);
		result_type result = static_cast<result_type>(0);
		bool operation_is_supported = true;
		switch (operation) {
		case operation_unary_plus:
			result = static_cast<result_type>(value1);
			break;
#ifdef SAFER_INTEGER_TYPE_APPLY_SATURATED_RESULTS
		case operation_unary_minus:
			if (std::numeric_limits<result_type>::is_signed) {
				if (static_cast<result_type>(value1) != min_result) {
					result = -static_cast<result_type>(value1);
				} else {
					result = max_result;
				}
			} else {
				result = static_cast<result_type>(0);
			}
			break;
		case operation_post_increment:
		case operation_pre_increment: // intended
			if (static_cast<result_type>(value1) != max_result) {
				result = static_cast<result_type>(value1) + 1;
			} else {
				result = max_result;
			}
			break;
		case operation_post_decrement:
		case operation_pre_decrement: // intended
			if (static_cast<result_type>(value1) != min_result) {
				result = static_cast<result_type>(value1) - 1;
			} else {
				result = min_result;
			}
			break;
		case operation_addition:
		case operation_self_addition: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) + static_cast<result_type>(value2);
			} else if (error == operation_error_signed_result_more_than_max) {
				result = max_result;
			} else if (error == operation_error_signed_result_less_than_min) {
				result = min_result;
			} else if (error == operation_error_unsigned_result_wraparound_to_larger) {
				result = min_result;
			} else if (error == operation_error_unsigned_result_wraparound_to_smaller) {
				result = max_result;
			} else {
				result = static_cast<result_type>(value1) + static_cast<result_type>(value2);
			}
			break;
		case operation_subtraction:
		case operation_self_subtraction: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) - static_cast<result_type>(value2);
			} else if (error == operation_error_signed_result_more_than_max) {
				result = max_result;
			} else if (error == operation_error_signed_result_less_than_min) {
				result = min_result;
			} else if (error == operation_error_unsigned_result_wraparound_to_larger) {
				result = min_result;
			} else if (error == operation_error_unsigned_result_wraparound_to_smaller) {
				result = max_result;
			} else {
				result = static_cast<result_type>(value1) - static_cast<result_type>(value2);
			}
			break;
		case operation_multiplication:
		case operation_self_multiplication: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) * static_cast<result_type>(value2);
			} else if (error == operation_error_signed_result_more_than_max) {
				result = max_result;
			} else if (error == operation_error_signed_result_less_than_min) {
				result = min_result;
			} else if (error == operation_error_unsigned_result_wraparound_to_larger) {
				result = min_result;
			} else if (error == operation_error_unsigned_result_wraparound_to_smaller) {
				result = max_result;
			} else {
				result = static_cast<result_type>(value1) * static_cast<result_type>(value2);
			}
			break;
		case operation_division:
		case operation_self_division: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) / static_cast<result_type>(value2);
			} else if (error == operation_error_division_of_signed_integer_by_zero) {
				if (value1 < 0) {
					result = min_result;
				} else if (value1 > 0) {
					result = max_result;
				} else {
					result = static_cast<result_type>(0);
				}
			} else if (error == operation_error_division_of_unsigned_integer_by_zero) {
				if (value1 != 0) {
					result = max_result;
				} else {
					result = static_cast<result_type>(0);
				}
			} else if (error == operation_error_division_of_min_by_minus_one) {
				result = max_result;
			} else {
				result = static_cast<result_type>(value1) / static_cast<result_type>(value2);
			}
			break;
		case operation_remainder:
		case operation_self_remainder: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) % static_cast<result_type>(value2);
			} else if (error == operation_error_division_of_signed_integer_by_zero) {
				result = static_cast<result_type>(0);
			} else if (error == operation_error_division_of_unsigned_integer_by_zero) {
				result = static_cast<result_type>(0);
			} else if (error == operation_error_division_of_min_by_minus_one) {
				result = static_cast<result_type>(0);
			} else {
				result = static_cast<result_type>(value1) % static_cast<result_type>(value2);
			}
			break;
#else
		case operation_unary_minus:
			result = static_cast<result_type>(~value1 + 1U);
			break;
		case operation_post_increment:
		case operation_pre_increment: // intended
			result = static_cast<result_type>(value1 + 1U);
			break;
		case operation_post_decrement:
		case operation_pre_decrement: // intended
			result = static_cast<result_type>(value1 - 1U);
			break;
		case operation_addition:
		case operation_self_addition: // intended
			result = static_cast<result_type>(value1 + value2);
			break;
		case operation_subtraction:
		case operation_self_subtraction: // intended
			result = static_cast<result_type>(value1 - value2);
			break;
		case operation_multiplication:
		case operation_self_multiplication: // intended
			result = static_cast<result_type>(value1) * static_cast<result_type>(value2);
			break;
		case operation_division:
		case operation_self_division: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) / static_cast<result_type>(value2);
			} else if (error == operation_error_division_of_signed_integer_by_zero) {
				result = static_cast<result_type>(0);
			} else if (error == operation_error_division_of_unsigned_integer_by_zero) {
				result = static_cast<result_type>(0);
			} else if (error == operation_error_division_of_min_by_minus_one) {
				result = static_cast<result_type>(value1);
			} else {
				result = static_cast<result_type>(value1) / static_cast<result_type>(value2);
			}
			break;
		case operation_remainder:
		case operation_self_remainder: // intended
			if (error == operation_error_none) {
				result = static_cast<result_type>(value1) % static_cast<result_type>(value2);
			} else if (error == operation_error_division_of_signed_integer_by_zero) {
				result = static_cast<result_type>(0);
			} else if (error == operation_error_division_of_unsigned_integer_by_zero) {
				result = static_cast<result_type>(0);
			} else if (error == operation_error_division_of_min_by_minus_one) {
				result = static_cast<result_type>(value1);
			} else {
				result = static_cast<result_type>(value1) % static_cast<result_type>(value2);
			}
			break;
#endif
		case operation_comparison_equal:
			result = static_cast<result_type>(value1) == static_cast<result_type>(value2);
			break;
		case operation_comparison_not_equal:
			result = static_cast<result_type>(value1) != static_cast<result_type>(value2);
			break;
		case operation_comparison_greater:
			result = static_cast<result_type>(value1) > static_cast<result_type>(value2);
			break;
		case operation_comparison_greater_or_equal:
			result = static_cast<result_type>(value1) >= static_cast<result_type>(value2);
			break;
		case operation_comparison_less:
			result = static_cast<result_type>(value1) < static_cast<result_type>(value2);
			break;
		case operation_comparison_less_or_equal:
			result = static_cast<result_type>(value1) <= static_cast<result_type>(value2);
			break;
		case operation_bitwise_and:
		case operation_self_bitwise_and: // intended
			result = static_cast<result_type>(value1 & value2);
			break;
		case operation_bitwise_or:
		case operation_self_bitwise_or: // intended
			result = static_cast<result_type>(value1 | value2);
			break;
		case operation_bitwise_xor:
		case operation_self_bitwise_xor: // intended
			result = static_cast<result_type>(value1 ^ value2);
			break;
		case operation_bitwise_not:
			result = static_cast<result_type>(~value1);
			break;
		case operation_bitwise_left_shift:
		case operation_self_bitwise_left_shift: // intended
			result = static_cast<result_type>(value1 << value2);
			break;
		case operation_bitwise_right_shift:
		case operation_self_bitwise_right_shift: //	intended
			result = static_cast<result_type>(value1 >> value2);
			break;
		default:
			result = static_cast<result_type>(value1);
			operation_is_supported = false;
			break;
		}
		assert(operation_is_supported);
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
	const T zero = static_cast<T>(0);
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
	const T one = static_cast<T>(1);
	operation_error_type error = operation_error_none;
	if (divisor == zero) {
		error = operation_error_division_of_signed_integer_by_zero;
	} else if (divisor == -one) {
		if (dividend == minimum_value and minimum_value == (-maximum_value - one)) {
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
		((rhs >= 0) and (rhs < width)) : (rhs < width);
	operation_error_type error = operation_error_none;
	if (left_operand_is_not_negative) {
		if (not right_operand_within_range) {
			error = operation_error_right_operand_of_bitwise_left_shift_is_out_of_range;
		}
	} else {
		if (right_operand_within_range) {
			error = operation_error_left_operand_of_bitwise_left_shift_is_negative;
		} else {
			error = operation_error_both_operands_of_bitwise_left_shift_are_negative_or_out_of_range;
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
			error = operation_error_both_operands_of_bitwise_right_shift_are_negative_or_out_of_range;
		}
	}
	return error;
}

template<typename dst_type, typename src_type>
bool can_cast_properly(src_type src_integer)
{
	typedef std::numeric_limits<dst_type> dst_type_info;
	typedef std::numeric_limits<src_type> src_type_info;
	STATIC_ASSERT(dst_type_info::is_integer, "The destination type must be an integer type.");
	STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
	const dst_type dst_min = dst_type_info::min();
	const dst_type dst_max = dst_type_info::max();
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

template<> bool can_cast_properly<bool, bool>(bool) {return true;}
template<> bool can_cast_properly<bool, char>(char) {return true;}
template<> bool can_cast_properly<bool, signed char>(signed char) {return true;}
template<> bool can_cast_properly<bool, unsigned char>(unsigned char) {return true;}
template<> bool can_cast_properly<bool, short>(short) {return true;}
template<> bool can_cast_properly<bool, unsigned short>(unsigned short) {return true;}
template<> bool can_cast_properly<bool, int>(int) {return true;}
template<> bool can_cast_properly<bool, unsigned int>(unsigned int) {return true;}
template<> bool can_cast_properly<bool, long>(long) {return true;}
template<> bool can_cast_properly<bool, unsigned long>(unsigned long) {return true;}
template<> bool can_cast_properly<bool, long long>(long long) {return true;}
template<> bool can_cast_properly<bool, unsigned long long>(unsigned long long) {return true;}

template<> bool can_cast_properly<char, bool>(bool) {return true;}
template<> bool can_cast_properly<signed char, bool>(bool) {return true;}
template<> bool can_cast_properly<unsigned char, bool>(bool) {return true;}
template<> bool can_cast_properly<short, bool>(bool) {return true;}
template<> bool can_cast_properly<unsigned short, bool>(bool) {return true;}
template<> bool can_cast_properly<int, bool>(bool) {return true;}
template<> bool can_cast_properly<unsigned int, bool>(bool) {return true;}
template<> bool can_cast_properly<long, bool>(bool) {return true;}
template<> bool can_cast_properly<unsigned long, bool>(bool) {return true;}
template<> bool can_cast_properly<long long, bool>(bool) {return true;}
template<> bool can_cast_properly<unsigned long long, bool>(bool) {return true;}

template<typename T1, typename T2, typename promoted_type>
operation_error_type check_integer_promotion_for_binary_operation(T1 lhs, T2 rhs) {
	operation_error_type error = operation_error_none;
	if (not can_cast_properly<promoted_type, T1>(lhs)) {
		error = operation_error_left_operand_cannot_be_represented_by_promoted_type;
	} else if (not can_cast_properly<promoted_type, T2>(rhs)) {
		error = operation_error_right_operand_cannot_be_represented_by_promoted_type;
	}
	return error;
}

// For type comparison
template<typename T, typename U> struct is_same_type {static const bool value = false;};
template<typename T> struct is_same_type<T, T> { static const bool value = true; };

// For checking whether a type is a native integer type
template<typename T> struct is_builtin_integer_type {static const bool value = false;};
template<> struct is_builtin_integer_type<bool> {static const bool value = true;};
template<> struct is_builtin_integer_type<char> {static const bool value = true;};
template<> struct is_builtin_integer_type<signed char> {static const bool value = true;};
template<> struct is_builtin_integer_type<unsigned char> {static const bool value = true;};
template<> struct is_builtin_integer_type<short> {static const bool value = true;};
template<> struct is_builtin_integer_type<unsigned short> {static const bool value = true;};
template<> struct is_builtin_integer_type<int> {static const bool value = true;};
template<> struct is_builtin_integer_type<unsigned int> {static const bool value = true;};
template<> struct is_builtin_integer_type<long> {static const bool value = true;};
template<> struct is_builtin_integer_type<unsigned long> {static const bool value = true;};
#if defined(LLONG_MIN) && defined(LLONG_MAX)
template<> struct is_builtin_integer_type<long long> {static const bool value = true;};
#endif
#if defined(ULLONG_MAX)
template<> struct is_builtin_integer_type<unsigned long long> {static const bool value = true;};
#endif

// "Substition failure is not an error" (SFINAE) technique: enable_if
template<bool condition, typename T = void> struct enable_if {};
template<typename T> struct enable_if<true, T> {typedef T type;};

#if __cplusplus >= 201103L
#define NO_DERIVED_TYPE_ALLOWED final
#else
#define NO_DERIVED_TYPE_ALLOWED
#endif	

// a generic type  that emulates built-in integer types
template<typename T, typename integer_policy = DIP>
struct integer_type NO_DERIVED_TYPE_ALLOWED {
	typedef T native_type;
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

	template <typename native_integer_type, typename integer_policy_type>
	friend void print_source_file_info(const integer_type<native_integer_type, integer_policy_type>& self);

	integer_type(
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		const char *info = "<unknown info>"
#else
		const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(static_cast<T>(0))
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
		print_source_file_info(*this);
#ifndef SAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_UNINITIALIZED_VARIABLES
		FILE* file_pointer = output_file_pointer;
		if (file_pointer != NULL) {
			fprintf(file_pointer, "The safer integer variable is initialized to zero by default. A built-in integer will not be initialized.\n");
		}
#endif
		// do not throw an exception if you want the integer to be used in a container
#ifdef SAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
		throw std::runtime_error("An uninitialized integer variable is detected.");
#endif
	}

	integer_type(T src
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(src)
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
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
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(static_cast<T>(src))
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
		typedef T dst_type;
		typedef U src_type;
		typedef std::numeric_limits<src_type> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		check_and_report_truncation_or_signedness_error<dst_type, src_type>(*this, src);
	}

	integer_type(const integer_type& src
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(src.m_value)
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
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
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		, const char *info = "<unknown info>"
#else
		, const std::source_location& location = std::source_location::current()
#endif
#endif
	) : m_value(static_cast<T>(static_cast<U>(rhs)))
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	, m_source_file_info(info)
#else
	, m_source_file_info(location)
#endif
#endif
	{
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		assert(m_source_file_info != NULL);
		if (m_source_file_info == NULL) {
			m_source_file_info = "<unknown info>";
		}
#endif
#endif
		typedef T dst_type;
		typedef U src_type;
		typedef std::numeric_limits<src_type> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		const src_type src = static_cast<src_type>(rhs);
		check_and_report_truncation_or_signedness_error<dst_type, src_type>(*this, src);
	}

	~integer_type() {
		m_value = 0;
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
		m_source_file_info = NULL;
#else
		memset(&m_source_file_info, 0, sizeof(m_source_file_info));
#endif
#endif
	}

	integer_type& operator=(T src) {
		m_value = src;
		return *this;
	}

	template<typename U>
	integer_type& operator=(U src) {
		typedef T dst_type;
		typedef U src_type;
		typedef std::numeric_limits<src_type> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		check_and_report_truncation_or_signedness_error<dst_type, src_type>(*this, src);
		m_value = static_cast<T>(src);
		return *this;
	}

	integer_type& operator=(const integer_type& src) {
		m_value = src.m_value;
		return *this;
	}

	template<typename U>
	integer_type& operator=(const integer_type<U>& rhs) {
		typedef T dst_type;
		typedef U src_type;
		typedef std::numeric_limits<src_type> src_type_info;
		STATIC_ASSERT(src_type_info::is_integer, "The source type must be an integer type.");
		const src_type src = static_cast<src_type>(rhs);
		check_and_report_truncation_or_signedness_error<dst_type, src_type>(*this, src);
		m_value = static_cast<T>(src);
		return *this;
	}

	operator T() const {
		return m_value;
	}

#if __cplusplus >= 201103L
	template<typename U, typename Enable = typename enable_if<is_builtin_integer_type<U>::value and (not is_same_type<U, T>::value), void>::type>
	operator U() const {
		typedef U dst_type;
		typedef T src_type;
		typedef std::numeric_limits<dst_type> dst_type_info;
		STATIC_ASSERT(dst_type_info::is_integer, "The destination type must be an integer");
		check_and_report_truncation_or_signedness_error<dst_type, src_type>(*this, m_value);
		return static_cast<U>(m_value);
	}
#endif

	bool operator!() const {
		return (m_value == 0);
	}

private:
	template<typename dst_type, typename src_type>
	static void check_and_report_truncation_or_signedness_error(const integer_type<T, integer_policy>& self, src_type src) {
		typedef long long llong_type;
		typedef unsigned long long ullong_type;
		typedef std::numeric_limits<src_type> src_type_info;
		typedef std::numeric_limits<dst_type> dst_type_info;
		FILE* file_pointer = output_file_pointer;

		if (not can_cast_properly<dst_type>(src)) {
			print_source_file_info(self);
#ifndef SAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_CONVERSION_ERRORS
			if (file_pointer != NULL) {
				const src_type src_min = src_type_info::min();
				const src_type src_max = src_type_info::max();
				const dst_type dst_min = dst_type_info::min();
				const dst_type dst_max = dst_type_info::max();
				const dst_type value = static_cast<dst_type>(src);

				if (src_type_info::is_signed) {
					if (dst_type_info::is_signed)
						fprintf(file_pointer, "Truncation error: %lld [signed, %d-byte, min: %lld, max: %lld] -> %lld [signed, %d-byte, min: %lld, max: %lld]\n",
							static_cast<llong_type>(src), static_cast<int>(sizeof(src)), static_cast<llong_type>(src_min), static_cast<llong_type>(src_max),
							static_cast<llong_type>(value), static_cast<int>(sizeof(value)), static_cast<llong_type>(dst_min), static_cast<llong_type>(dst_max));
					else
						fprintf(file_pointer, "Signedness error: %lld [signed, %d-byte, min: %lld, max: %lld] -> %llu [unsigned, %d-byte, min: %llu, max: %llu]\n",
							static_cast<llong_type>(src), static_cast<int>(sizeof(src)), static_cast<llong_type>(src_min), static_cast<llong_type>(src_max),
							static_cast<ullong_type>(value), static_cast<int>(sizeof(value)), static_cast<ullong_type>(dst_min), static_cast<ullong_type>(dst_max));
				} else {
					if (dst_type_info::is_signed)
						fprintf(file_pointer, "Signedness error: %llu [unsigned, %d-byte, min: %llu, max: %llu] -> %lld [signed, %d-byte, min: %lld, max: %lld]\n",
							static_cast<ullong_type>(src), static_cast<int>(sizeof(src)), static_cast<ullong_type>(src_min), static_cast<ullong_type>(src_max),
							static_cast<llong_type>(value), static_cast<int>(sizeof(value)), static_cast<llong_type>(dst_min), static_cast<llong_type>(dst_max));
					else
						fprintf(file_pointer, "Truncation error: %llu [unsigned, %d-byte, min: %llu, max: %llu] -> %llu [unsigned, %d-byte, min: %llu, max: %llu]\n",
							static_cast<ullong_type>(src), static_cast<int>(sizeof(src)), static_cast<ullong_type>(src_min), static_cast<ullong_type>(src_max),
							static_cast<ullong_type>(value), static_cast<int>(sizeof(value)), static_cast<ullong_type>(dst_min), static_cast<ullong_type>(dst_max));
				}
			}
#endif
#ifdef SAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
			throw std::runtime_error("An integer truncation or signedness error is detected.");
#endif
		}
	}

	// member variables
	T m_value;

	// optional member variables
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
#if __cplusplus < 202002L
	const char *m_source_file_info;
#else
	std::source_location m_source_file_info;
#endif
#endif
};

#undef NO_DERIVED_TYPE_ALLOWED

template<typename native_integer_type, typename integer_policy_type>
void print_source_file_info(const integer_type<native_integer_type, integer_policy_type>& self) {
#ifdef SAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	if (output_file_pointer != NULL) {
#if __cplusplus < 202002L
		fprintf(output_file_pointer, "Variable: %s\n", self.m_source_file_info);
#else
		fprintf(output_file_pointer, "Refer to the variable defined here: %s (line %u, column %u)\n",
			self.m_source_file_info.file_name(), self.m_source_file_info.line(), self.m_source_file_info.column());
#endif
	}
#endif
}

// operator functions that support integer promotion
template<typename T, typename integer_policy, typename promotion_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_unary_plus(const integer_type<T, integer_policy>& operand) {
	typedef typename promotion_policy::type result_type;
	return integer_type<result_type, integer_policy>(static_cast<result_type>(static_cast<T>(operand)));
}

template<typename T, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_unary_minus(const integer_type<T, integer_policy>& operand) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
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
			print_source_file_info(operand);
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
		print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
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
		print_source_file_info(operand);
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
		print_source_file_info(operand);
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
		print_source_file_info(operand);
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
		print_source_file_info(operand);
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
	const operation_type operation = operation_addition;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_addition(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_addition(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_minus(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	const operation_type operation = operation_subtraction;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_subtraction(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_subtraction(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_multiply(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	const operation_type operation = operation_multiplication;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_multiplication(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_multiplication(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_divide(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	const operation_type operation = operation_division;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_remainder(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	const operation_type operation = operation_remainder;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1, T2, result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_plus_assignment(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	typedef typename std::numeric_limits<result_type> result_type_info;
	const operation_type operation = operation_self_addition;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_addition(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_addition(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
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
	const operation_type operation = operation_self_subtraction;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_subtraction(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_subtraction(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
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
	const operation_type operation = operation_self_multiplication;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_multiplication(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_multiplication(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
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
	const operation_type operation = operation_self_division;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
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
	const operation_type operation = operation_self_remainder;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, result_type>(operand_1, operand_2);
	if (error == operation_error_none) {
		if (result_type_info::is_signed) {
			error = check_signed_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		} else {
			error = check_unsigned_division(static_cast<result_type>(operand_1), static_cast<result_type>(operand_2));
		}
	}
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
bool operator_compare_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type promoted_type;
	const operation_type operation = operation_comparison_equal;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, promoted_type>(operand_1, operand_2);
	const promoted_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,promoted_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return (result != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
bool operator_compare_not_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type promoted_type;
	const operation_type operation = operation_comparison_not_equal;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, promoted_type>(operand_1, operand_2);
	const promoted_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,promoted_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return (result != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename	result_policy, typename error_policy>
bool operator_compare_greater_than(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type promoted_type;
	const operation_type operation = operation_comparison_greater;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, promoted_type>(operand_1, operand_2);
	const promoted_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,promoted_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return (result != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename	result_policy, typename error_policy>
bool operator_compare_greater_than_or_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type promoted_type;
	const operation_type operation = operation_comparison_greater_or_equal;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, promoted_type>(operand_1, operand_2);
	const promoted_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,promoted_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return (result != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename	result_policy, typename error_policy>
bool operator_compare_less_than(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type promoted_type;
	const operation_type operation = operation_comparison_less;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, promoted_type>(operand_1, operand_2);
	const promoted_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,promoted_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return (result != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename	result_policy, typename error_policy>
bool operator_compare_less_than_or_equal(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type promoted_type;
	const operation_type operation = operation_comparison_less_or_equal;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_integer_promotion_for_binary_operation<T1, T2, promoted_type>(operand_1, operand_2);
	const promoted_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,promoted_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return (result != 0);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_and(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_bitwise_and;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_bitwise_and_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_or(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_bitwise_or;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_bitwise_or_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_xor(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_bitwise_xor;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_bitwise_xor_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<typename promotion_policy::type, integer_policy>
operator_bitwise_not(const integer_type<T, integer_policy>& operand) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_bitwise_not;
	const T operand_1 = static_cast<T>(operand);
	const T operand_2 = static_cast<T>(0);
	const operation_error_type error = check_bitwise_not_operation(operand_1);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T,T,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>
operator_bitwise_left_shift(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_bitwise_left_shift;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_left_shift_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>
operator_bitwise_right_shift(const integer_type<T1, integer_policy>& operand1, const integer_type<T2, integer_policy>& operand2) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_bitwise_right_shift;
	const T1 operand_1 = static_cast<T1>(operand1);
	const T2 operand_2 = static_cast<T2>(operand2);
	const operation_error_type error = check_right_shift_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(operand1);
		print_source_file_info(operand2);
		error_policy::handle_error(debug_info);
	}
	return integer_type<result_type, integer_policy>(result);
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_and(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_self_bitwise_and;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	const operation_error_type error = check_bitwise_and_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_or(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_self_bitwise_or;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	const operation_error_type error = check_bitwise_or_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_xor(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_self_bitwise_xor;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	const operation_error_type error = check_bitwise_xor_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_left_shift(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_self_bitwise_left_shift;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	const operation_error_type error = check_left_shift_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

template<typename T1, typename T2, typename integer_policy, typename promotion_policy, typename result_policy, typename error_policy>
integer_type<T1, integer_policy>&
operator_self_bitwise_right_shift(integer_type<T1, integer_policy>& self, const integer_type<T2, integer_policy>& value) {
	typedef typename promotion_policy::type result_type;
	const operation_type operation = operation_self_bitwise_right_shift;
	const T1 operand_1 = static_cast<T1>(self);
	const T2 operand_2 = static_cast<T2>(value);
	const operation_error_type error = check_right_shift_operation(operand_1, operand_2);
	const result_type result = result_policy::calculate_result(operation, error, operand_1, operand_2);
	if (error != operation_error_none) {
		debug_info_type<T1,T2,result_type> debug_info(operation, error, operand_1, operand_2, result, __FILE__, __LINE__);
		print_source_file_info(self);
		print_source_file_info(value);
		error_policy::handle_error(debug_info);
	}
	self = result;
	return self;
}

} // end of namespace safer_integer

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

// multiplying self by a number
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
	typedef typename SI::DPP<T1, T2>::type promoted_type;
	return SI::operator_compare_equal<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,promoted_type>, SI::DEP<T1,T2,promoted_type>
	>(a, b);
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
	typedef typename SI::DPP<T1, T2>::type promoted_type;
	return SI::operator_compare_not_equal<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,promoted_type>, SI::DEP<T1,T2,promoted_type>
	>(a, b);
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
	typedef typename SI::DPP<T1, T2>::type promoted_type;
	return SI::operator_compare_greater_than<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,promoted_type>, SI::DEP<T1,T2,promoted_type>
	>(a, b);
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
	typedef typename SI::DPP<T1, T2>::type promoted_type;
	return SI::operator_compare_greater_than_or_equal<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,promoted_type>, SI::DEP<T1,T2,promoted_type>
	>(a, b);
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
	typedef typename SI::DPP<T1, T2>::type promoted_type;
	return SI::operator_compare_less_than<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,promoted_type>, SI::DEP<T1,T2,promoted_type>
	>(a, b);
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
	typedef typename SI::DPP<T1, T2>::type promoted_type;
	return SI::operator_compare_less_than_or_equal<
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,promoted_type>, SI::DEP<T1,T2,promoted_type>
	>(a, b);
}

template<typename T1, typename T2>
bool operator<=(const SI::integer_type<T1, SI::DIP>& a, T2 b) {
	return a <= SI::integer_type<T2, SI::DIP>(b);
}

template<typename T1, typename T2>
bool operator<=(T1 a, const SI::integer_type<T2, SI::DIP>& b) {
	return SI::integer_type<T1, SI::DIP>(a) <= b;
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
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
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
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
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
		T1, T2, SI::DIP, SI::DPP<T1,T2>, SI::DRP<T1,T2,result_type>, SI::DEP<T1,T2,result_type>
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

// Specializing std::numeric_limits for safer_integer::integer_type

#if __cplusplus >= 201103L
#define CONSTEXPR constexpr
#define NO_EXCEPTION noexcept
#else
#define CONSTEXPR const
#define NO_EXCEPTION throw()
#endif

// Specialization of std::numeric_limits for safer_integer::integer_type
namespace std {
template<typename T, typename integer_policy>
struct numeric_limits< safer_integer::integer_type<T, integer_policy> >
{
	static CONSTEXPR bool is_specialized = std::numeric_limits<T>::is_specialized;
	static CONSTEXPR bool is_integer = std::numeric_limits<T>::is_integer;
	static CONSTEXPR bool is_signed = std::numeric_limits<T>::is_signed;
	static CONSTEXPR bool is_exact = std::numeric_limits<T>::is_exact;
	static CONSTEXPR bool has_infinity = std::numeric_limits<T>::has_infinity;
	static CONSTEXPR bool has_quiet_NaN = std::numeric_limits<T>::has_quiet_NaN;
	static CONSTEXPR bool has_signaling_NaN = std::numeric_limits<T>::has_signaling_NaN;
	static CONSTEXPR std::float_denorm_style has_denorm = std::numeric_limits<T>::has_denorm;
	static CONSTEXPR bool has_denorm_loss = std::numeric_limits<T>::has_denorm_loss;
	static CONSTEXPR std::float_round_style round_style = std::numeric_limits<T>::round_style;
	static CONSTEXPR bool is_iec559 = std::numeric_limits<T>::is_iec559;
	static CONSTEXPR bool is_bounded = std::numeric_limits<T>::is_bounded;
	static CONSTEXPR bool is_modulo = std::numeric_limits<T>::is_modulo;
	static CONSTEXPR int digits = std::numeric_limits<T>::digits;
	static CONSTEXPR int digits10 = std::numeric_limits<T>::digits10;
#if __cplusplus >= 201103L
	static CONSTEXPR int max_digits10 = std::numeric_limits<T>::max_digits10;
#endif
	static CONSTEXPR int radix = std::numeric_limits<T>::radix;
	static CONSTEXPR int min_exponent = std::numeric_limits<T>::min_exponent;
	static CONSTEXPR int min_exponent10 = std::numeric_limits<T>::min_exponent10;
	static CONSTEXPR int max_exponent = std::numeric_limits<T>::max_exponent;
	static CONSTEXPR int max_exponent10 = std::numeric_limits<T>::max_exponent10;
	static CONSTEXPR bool traps = std::numeric_limits<T>::traps;
	static CONSTEXPR bool tinyness_before = std::numeric_limits<T>::tinyness_before;

	static safer_integer::integer_type<T, integer_policy> min() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::min());
	}

	static safer_integer::integer_type<T, integer_policy> max() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::max());
	}

#if __cplusplus >= 201103L
	static safer_integer::integer_type<T, integer_policy> lowest() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::lowest());
	}
#endif

	static safer_integer::integer_type<T, integer_policy> epsilon() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::epsilon());
	}

	static safer_integer::integer_type<T, integer_policy> round_error() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::round_error());
	}

	static safer_integer::integer_type<T, integer_policy> infinity() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::infinity());
	}

	static safer_integer::integer_type<T, integer_policy> quiet_NaN() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::quiet_NaN());
	}

	static safer_integer::integer_type<T, integer_policy> signaling_NaN() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::signaling_NaN());
	}

	static safer_integer::integer_type<T, integer_policy> denorm_min() NO_EXCEPTION {
		return safer_integer::integer_type<T, integer_policy>(std::numeric_limits<T>::denorm_min());
	}
};
} // end of namespace std

#undef NO_EXCEPTION
#undef CONSTEXPR

#endif /* __cplusplus */

#if defined(__cplusplus) && !defined(SAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES)

typedef safer_integer::integer_type<safer_integer::DIP::bool_type, safer_integer::DIP> safer_bool_type;
typedef safer_integer::integer_type<safer_integer::DIP::char_type, safer_integer::DIP> safer_char_type;
typedef safer_integer::integer_type<safer_integer::DIP::schar_type, safer_integer::DIP> safer_schar_type;
typedef safer_integer::integer_type<safer_integer::DIP::uchar_type, safer_integer::DIP> safer_uchar_type;
typedef safer_integer::integer_type<safer_integer::DIP::short_type, safer_integer::DIP> safer_short_type;
typedef safer_integer::integer_type<safer_integer::DIP::ushort_type, safer_integer::DIP> safer_ushort_type;
typedef safer_integer::integer_type<safer_integer::DIP::int_type, safer_integer::DIP> safer_int_type;
typedef safer_integer::integer_type<safer_integer::DIP::uint_type, safer_integer::DIP> safer_uint_type;
typedef safer_integer::integer_type<safer_integer::DIP::long_type, safer_integer::DIP> safer_long_type;
typedef safer_integer::integer_type<safer_integer::DIP::ulong_type, safer_integer::DIP> safer_ulong_type;
typedef safer_integer::integer_type<safer_integer::DIP::llong_type, safer_integer::DIP> safer_llong_type;
typedef safer_integer::integer_type<safer_integer::DIP::ullong_type, safer_integer::DIP> safer_ullong_type;
typedef safer_integer::integer_type<safer_integer::DIP::ptrdiff_type, safer_integer::DIP> safer_ptrdiff_type;
typedef safer_integer::integer_type<safer_integer::DIP::size_type, safer_integer::DIP> safer_size_type;
typedef safer_integer::integer_type<int8_t, safer_integer::DIP> safer_int8_type;
typedef safer_integer::integer_type<uint8_t, safer_integer::DIP> safer_uint8_type;
typedef safer_integer::integer_type<int16_t, safer_integer::DIP> safer_int16_type;
typedef safer_integer::integer_type<uint16_t, safer_integer::DIP> safer_uint16_type;
typedef safer_integer::integer_type<int32_t, safer_integer::DIP> safer_int32_type;
typedef safer_integer::integer_type<uint32_t, safer_integer::DIP> safer_uint32_type;
typedef safer_integer::integer_type<int64_t, safer_integer::DIP> safer_int64_type;
typedef safer_integer::integer_type<uint64_t, safer_integer::DIP> safer_uint64_type;

#define SAFER_BOOL_MIN std::numeric_limits<safer_bool_type>::min()
#define SAFER_BOOL_MAX std::numeric_limits<safer_bool_type>::max()
#define SAFER_CHAR_MIN std::numeric_limits<safer_char_type>::min()
#define SAFER_CHAR_MAX std::numeric_limits<safer_char_type>::max()
#define SAFER_SCHAR_MIN std::numeric_limits<safer_schar_type>::min()
#define SAFER_SCHAR_MAX std::numeric_limits<safer_schar_type>::max()
#define SAFER_UCHAR_MIN std::numeric_limits<safer_uchar_type>::min()
#define SAFER_UCHAR_MAX std::numeric_limits<safer_uchar_type>::max()
#define SAFER_SHORT_MIN std::numeric_limits<safer_short_type>::min()
#define SAFER_SHORT_MAX std::numeric_limits<safer_short_type>::max()
#define SAFER_USHORT_MIN std::numeric_limits<safer_ushort_type>::min()
#define SAFER_USHORT_MAX std::numeric_limits<safer_ushort_type>::max()
#define SAFER_INT_MIN std::numeric_limits<safer_int_type>::min()
#define SAFER_INT_MAX std::numeric_limits<safer_int_type>::max()
#define SAFER_UINT_MIN std::numeric_limits<safer_uint_type>::min()
#define SAFER_UINT_MAX std::numeric_limits<safer_uint_type>::max()
#define SAFER_LONG_MIN std::numeric_limits<safer_long_type>::min()
#define SAFER_LONG_MAX std::numeric_limits<safer_long_type>::max()
#define SAFER_ULONG_MIN std::numeric_limits<safer_ulong_type>::min()
#define SAFER_ULONG_MAX std::numeric_limits<safer_ulong_type>::max()
#define SAFER_LLONG_MIN std::numeric_limits<safer_llong_type>::min()
#define SAFER_LLONG_MAX std::numeric_limits<safer_llong_type>::max()
#define SAFER_ULLONG_MIN std::numeric_limits<safer_ullong_type>::min()
#define SAFER_ULLONG_MAX std::numeric_limits<safer_ullong_type>::max()
#define SAFER_PTRDIFF_MIN std::numeric_limits<safer_ptrdiff_type>::min()
#define SAFER_PTRDIFF_MAX std::numeric_limits<safer_ptrdiff_type>::max()
#define SAFER_SIZE_MIN std::numeric_limits<safer_size_type>::min()
#define SAFER_SIZE_MAX std::numeric_limits<safer_size_type>::max()
#define SAFER_INT8_MIN std::numeric_limits<safer_int8_type>::min()
#define SAFER_INT8_MAX std::numeric_limits<safer_int8_type>::max()
#define SAFER_UINT8_MIN std::numeric_limits<safer_uint8_type>::min()
#define SAFER_UINT8_MAX std::numeric_limits<safer_uint8_type>::max()
#define SAFER_INT16_MIN std::numeric_limits<safer_int16_type>::min()
#define SAFER_INT16_MAX std::numeric_limits<safer_int16_type>::max()
#define SAFER_UINT16_MIN std::numeric_limits<safer_uint16_type>::min()
#define SAFER_UINT16_MAX std::numeric_limits<safer_uint16_type>::max()
#define SAFER_INT32_MIN std::numeric_limits<safer_int32_type>::min()
#define SAFER_INT32_MAX std::numeric_limits<safer_int32_type>::max()
#define SAFER_UINT32_MIN std::numeric_limits<safer_uint32_type>::min()
#define SAFER_UINT32_MAX std::numeric_limits<safer_uint32_type>::max()
#define SAFER_INT64_MIN std::numeric_limits<safer_int64_type>::min()
#define SAFER_INT64_MAX std::numeric_limits<safer_int64_type>::max()
#define SAFER_UINT64_MIN std::numeric_limits<safer_uint64_type>::min()
#define SAFER_UINT64_MAX std::numeric_limits<safer_uint64_type>::max()

#define SAFER_BOOL_TYPE_IS_SIGNED std::numeric_limits<safer_bool_type>::is_signed
#define SAFER_CHAR_TYPE_IS_SIGNED std::numeric_limits<safer_char_type>::is_signed
#define SAFER_SCHAR_TYPE_IS_SIGNED std::numeric_limits<safer_schar_type>::is_signed
#define SAFER_UCHAR_TYPE_IS_SIGNED std::numeric_limits<safer_uchar_type>::is_signed
#define SAFER_SHORT_TYPE_IS_SIGNED std::numeric_limits<safer_short_type>::is_signed
#define SAFER_USHORT_TYPE_IS_SIGNED std::numeric_limits<safer_ushort_type>::is_signed
#define SAFER_INT_TYPE_IS_SIGNED std::numeric_limits<safer_int_type>::is_signed
#define SAFER_UINT_TYPE_IS_SIGNED std::numeric_limits<safer_uint_type>::is_signed
#define SAFER_LONG_TYPE_IS_SIGNED std::numeric_limits<safer_long_type>::is_signed
#define SAFER_ULONG_TYPE_IS_SIGNED std::numeric_limits<safer_ulong_type>::is_signed
#define SAFER_LLONG_TYPE_IS_SIGNED std::numeric_limits<safer_llong_type>::is_signed
#define SAFER_ULLONG_TYPE_IS_SIGNED std::numeric_limits<safer_ullong_type>::is_signed
#define SAFER_PTRDIFF_TYPE_IS_SIGNED std::numeric_limits<safer_ptrdiff_type>::is_signed
#define SAFER_SIZE_TYPE_IS_SIGNED std::numeric_limits<safer_size_type>::is_signed
#define SAFER_INT8_TYPE_IS_SIGNED std::numeric_limits<safer_int8_type>::is_signed
#define SAFER_UINT8_TYPE_IS_SIGNED std::numeric_limits<safer_uint8_type>::is_signed
#define SAFER_INT16_TYPE_IS_SIGNED std::numeric_limits<safer_int16_type>::is_signed
#define SAFER_UINT16_TYPE_IS_SIGNED std::numeric_limits<safer_uint16_type>::is_signed
#define SAFER_INT32_TYPE_IS_SIGNED std::numeric_limits<safer_int32_type>::is_signed
#define SAFER_UINT32_TYPE_IS_SIGNED std::numeric_limits<safer_uint32_type>::is_signed
#define SAFER_INT64_TYPE_IS_SIGNED std::numeric_limits<safer_int64_type>::is_signed
#define SAFER_UINT64_TYPE_IS_SIGNED std::numeric_limits<safer_uint64_type>::is_signed

#else /* not __cplusplus or runtime checks are disabled */

#include "Boolean_type.h"

#pragma message("C++ compiler not detected. Defining safer integer types as aliases to built-in integer types.")

typedef Boolean_type safer_bool_type;
typedef char safer_char_type;
typedef signed char safer_schar_type;
typedef unsigned char safer_uchar_type;
typedef short safer_short_type;
typedef unsigned short safer_ushort_type;
typedef int safer_int_type;
typedef unsigned int safer_uint_type;
typedef long safer_long_type;
typedef unsigned long safer_ulong_type;
typedef long long safer_llong_type;
typedef unsigned long long safer_ullong_type;
typedef ptrdiff_t safer_ptrdiff_type;
typedef size_t safer_size_type;
typedef int8_t safer_int8_type;
typedef uint8_t safer_uint8_type;
typedef int16_t safer_int16_type;
typedef uint16_t safer_uint16_type;
typedef int32_t safer_int32_type;
typedef uint32_t safer_uint32_type;
typedef int64_t safer_int64_type;
typedef uint64_t safer_uint64_type;

#define SAFER_BOOL_MIN Boolean_false
#define SAFER_BOOL_MAX Boolean_true
#define SAFER_CHAR_MIN CHAR_MIN
#define SAFER_CHAR_MAX CHAR_MAX
#define SAFER_SCHAR_MIN SCHAR_MIN
#define SAFER_SCHAR_MAX SCHAR_MAX
#define SAFER_UCHAR_MIN 0U
#define SAFER_UCHAR_MAX UCHAR_MAX
#define SAFER_SHORT_MIN SHRT_MIN
#define SAFER_SHORT_MAX SHRT_MAX
#define SAFER_USHORT_MIN 0U
#define SAFER_USHORT_MAX USHRT_MAX
#define SAFER_INT_MIN INT_MIN
#define SAFER_INT_MAX INT_MAX
#define SAFER_UINT_MIN 0U
#define SAFER_UINT_MAX UINT_MAX
#define SAFER_LONG_MIN LONG_MIN
#define SAFER_LONG_MAX LONG_MAX
#define SAFER_ULONG_MIN 0UL
#define SAFER_ULONG_MAX ULONG_MAX
#define SAFER_LLONG_MIN LLONG_MIN
#define SAFER_LLONG_MAX LLONG_MAX
#define SAFER_ULLONG_MIN 0ULL
#define SAFER_ULLONG_MAX ULLONG_MAX
#define SAFER_PTRDIFF_MIN PTRDIFF_MIN
#define SAFER_PTRDIFF_MAX PTRDIFF_MAX
#define SAFER_SIZE_MIN 0U
#define SAFER_SIZE_MAX SIZE_MAX
#define SAFER_INT8_MIN INT8_MIN
#define SAFER_INT8_MAX INT8_MAX
#define SAFER_UINT8_MIN 0U
#define SAFER_UINT8_MAX UINT8_MAX
#define SAFER_INT16_MIN INT16_MIN
#define SAFER_INT16_MAX INT16_MAX
#define SAFER_UINT16_MIN 0U
#define SAFER_UINT16_MAX UINT16_MAX
#define SAFER_INT32_MIN INT32_MIN
#define SAFER_INT32_MAX INT32_MAX
#define SAFER_UINT32_MIN 0U
#define SAFER_UINT32_MAX UINT32_MAX
#define SAFER_INT64_MIN INT64_MIN
#define SAFER_INT64_MAX INT64_MAX
#define SAFER_UINT64_MIN 0U
#define SAFER_UINT64_MAX UINT64_MAX

#define SAFER_BOOL_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_CHAR_TYPE_IS_SIGNED (SAFER_CHAR_MIN < 0)
#define SAFER_SCHAR_TYPE_IS_SIGNED (SAFER_SCHAR_MIN < 0)
#define SAFER_UCHAR_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_SHORT_TYPE_IS_SIGNED (SAFER_SHORT_MIN < 0)
#define SAFER_USHORT_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_INT_TYPE_IS_SIGNED (SAFER_INT_MIN < 0)
#define SAFER_UINT_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_LONG_TYPE_IS_SIGNED (SAFER_LONG_MIN < 0)
#define SAFER_ULONG_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_LLONG_TYPE_IS_SIGNED (SAFER_LLONG_MIN < 0)
#define SAFER_ULLONG_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_PTRDIFF_TYPE_IS_SIGNED (SAFER_PTRDIFF_MIN < 0)
#define SAFER_SIZE_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_INT8_TYPE_IS_SIGNED (SAFER_INT8_MIN < 0)
#define SAFER_UINT8_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_INT16_TYPE_IS_SIGNED (SAFER_INT16_MIN < 0)
#define SAFER_UINT16_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_INT32_TYPE_IS_SIGNED (SAFER_INT32_MIN < 0)
#define SAFER_UINT32_TYPE_IS_SIGNED (Boolean_false)
#define SAFER_INT64_TYPE_IS_SIGNED (SAFER_INT64_MIN < 0)
#define SAFER_UINT64_TYPE_IS_SIGNED (Boolean_false)

#endif /* __cplusplus and runtime checks are disabled */

#endif /* include guard */
