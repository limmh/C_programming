#include "string_to_integer.h"
#include "Boolean_type.h"
#include "safer_fixed_width_integers.h"
#include "string_reference.h"
#include "sizeof_array.h"
#include <assert.h>
#include <iso646.h>

INLINE_OR_STATIC Boolean_type character_is_decimal_digit(char ch)
{
	return (ch >= '0' and ch <= '9');
}

INLINE_OR_STATIC Boolean_type character_is_uppercase_alphabet(char ch)
{
	return (ch >= 'A' and ch <= 'Z');
}

INLINE_OR_STATIC Boolean_type character_is_lowercase_alphabet(char ch)
{
	return (ch >= 'a' and ch <= 'z');
}

INLINE_OR_STATIC Boolean_type character_is_whitespace(char ch)
{
	return (ch == ' ' or ch == '\t' or ch == '\r' or ch == '\n');
}

INLINE_OR_STATIC Boolean_type character_is_hexadecimal_digit(char ch)
{
	return character_is_decimal_digit(ch) or (ch >= 'A' and ch <= 'F') or (ch >= 'a' and ch <= 'f');
}

INLINE_OR_STATIC Boolean_type character_is_binary_digit(char ch)
{
	return (ch == '0' or ch == '1');
}

INLINE_OR_STATIC Boolean_type character_is_valid_digit(char ch)
{
	return character_is_decimal_digit(ch) or character_is_uppercase_alphabet(ch) or character_is_lowercase_alphabet(ch);
}

INLINE_OR_STATIC Boolean_type digit_is_supported_by_base(char ch, int base)
{
	Boolean_type result = Boolean_false;
	assert(base >= 2 and base <= 36);
	if (character_is_decimal_digit(ch)) {
		const int value = ch - '0';
		result = value < base;
	} else if (character_is_lowercase_alphabet(ch)) {
		const int value = ch - 'a' + 10;
		result = value < base;
	} else if (character_is_uppercase_alphabet(ch)) {
		const int value = ch - 'A' + 10;
		result = value < base;
	}
	return result;
}

INLINE_OR_STATIC int32_t digit_to_integer(char ch)
{
	int32_t integer = 0;
	if (character_is_decimal_digit(ch)) {
		integer = ch - '0';
	} else if (character_is_uppercase_alphabet(ch)) {
		integer = ch - 'A' + 10;
	} else if (character_is_lowercase_alphabet(ch)) {
		integer = ch - 'a' + 10;
	} else {
		assert(Boolean_false);
	}
	return integer;
}

INLINE_OR_STATIC size_t index_of_first_non_whitespace_character(const char *string, size_t length)
{
	size_t index = 0U;
	assert(string != NULL);
	assert(length > 0U);
	for (; index < length; ++index) {
		const char ch = string[index];
		if (character_is_whitespace(ch)) {
			continue;
		}
		break;
	}
	assert(index <= length);
	return index;
}

INLINE_OR_STATIC size_t safer_string_length(const char *string, size_t maximum_length)
{
	size_t index = 0U;
	for (; index < maximum_length; ++index) {
		if (string[index] == '\0') {
			break; 
		}
	}
	return index;
}

typedef enum string_parsing_state_type {
	string_parsing_state_start = 0,
	string_parsing_state_leading_whitespaces,
	string_parsing_state_sign,
	string_parsing_state_whitespace_after_sign,
	string_parsing_state_prefix,
	string_parsing_state_invalid_prefix,
	string_parsing_state_digits,
	string_parsing_state_digit_not_supported_by_base,
	string_parsing_state_trailing_whitespaces,
	string_parsing_state_invalid_character,
	string_parsing_state_trailing_invalid_character
} string_parsing_state_type;

typedef struct int_string_info_type {
	const char *string;
	size_t length;
	size_t start_index; /* digit start index */
	size_t end_index; /* digit end index */
	int base;
	string_to_int_error_type error;
	Boolean_type contains_valid_integer;
	Boolean_type integer_is_negative;
} int_string_info_type;

static int_string_info_type string_to_int_get_string_info(const char *string, size_t length, int base)
{
	int_string_info_type info = {0};
	size_t index = 0U;
	string_parsing_state_type state = string_parsing_state_start;
	Boolean_type should_terminate_early = Boolean_false;
	Boolean_type is_leading_zero = Boolean_true;
	info.string = string;
	info.length = length;
	info.base = base;
	info.start_index = 0U;
	info.end_index = info.start_index;
	info.error = string_to_int_error_none;
	info.contains_valid_integer = Boolean_false;
	info.integer_is_negative = Boolean_false;

	if (string == NULL) {
		info.error = string_to_int_error_null_string;
	} else if (length == 0U) {
		info.error = string_to_int_error_zero_length;
	} else if (string[0] == '\0') {
		info.error = string_to_int_error_empty_string;
	} else if (base < 2) {
		info.error = string_to_int_error_invalid_base;
	} else if (base > 36) {
		info.error = string_to_int_error_unsupported_base;
	} else {
		index = index_of_first_non_whitespace_character(string, length);
		if (index >= length or string[index] == '\0') {
			info.error = string_to_int_error_only_whitespaces;
		}
		info.start_index = index;
		info.end_index = info.start_index;
		state = string_parsing_state_leading_whitespaces;
	}

	if (info.error != string_to_int_error_none) {
		return info;
	}

	for (; index < length; ++index) {
		const char ch = string[index];
		switch (state) {
		case string_parsing_state_start:
		case string_parsing_state_leading_whitespaces: /* fall through intended */
			assert(ch != '\0');
			if (ch == '-' or ch == '+') {
				state = string_parsing_state_sign;
				info.integer_is_negative = ch == '-';
			} else if (ch == '0' and index + 1U < length) {
				state = string_parsing_state_prefix;
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_invalid_character;
				info.error = string_to_int_error_invalid_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				is_leading_zero = ch == '0';
				info.contains_valid_integer = Boolean_true;
				info.end_index = info.start_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_sign:
			if (ch == '\0') {
				should_terminate_early = Boolean_true;
				info.error = string_to_int_error_incomplete_string;
			} else if (ch == '0' and index + 1U < length) {
				state = string_parsing_state_prefix;
			} else if (character_is_whitespace(ch)) {
				state = string_parsing_state_whitespace_after_sign;
				info.error = string_to_int_error_whitespace_after_sign;
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_invalid_character;
				info.error = string_to_int_error_invalid_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				if (is_leading_zero and ch != '0') {
					is_leading_zero = Boolean_false;
				}
				info.contains_valid_integer = Boolean_true;
				info.end_index = info.start_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_prefix:
			assert(index > 0U);
			if (ch == '\0') {
				should_terminate_early = Boolean_true;
				info.error = string_to_int_error_incomplete_string;
			} else if (base == 2) {
				if (character_is_binary_digit(ch)) {
					state = string_parsing_state_digits;
					is_leading_zero = ch == '0';
					info.contains_valid_integer = Boolean_true;
					info.end_index = info.start_index = index;
				} else if (ch == 'B' or ch == 'b') {
					state = string_parsing_state_digits;
					info.contains_valid_integer = (index + 1U < length) and digit_is_supported_by_base(string[index + 1U], base);
					info.start_index = (index + 1U < length) ? (index + 1U) : index;
					info.end_index = info.start_index;
				} else {
					state = string_parsing_state_invalid_prefix;
					info.error = string_to_int_error_invalid_prefix;
				}
			} else if (base == 16) {
				if (character_is_hexadecimal_digit(ch)) {
					state = string_parsing_state_digits;
					is_leading_zero = ch == '0';
					info.contains_valid_integer = Boolean_true;
					info.end_index = info.start_index = index;
				} else if (ch == 'X' or ch == 'x') {
					state = string_parsing_state_digits;
					info.contains_valid_integer = (index + 1U < length) and digit_is_supported_by_base(string[index + 1U], base);
					info.start_index = (index + 1U < length) ? (index + 1U) : index;
					info.end_index = info.start_index;
				} else {
					state = string_parsing_state_invalid_prefix;
					info.error = string_to_int_error_invalid_prefix;
				}
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_invalid_character;
				info.error = string_to_int_error_invalid_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				is_leading_zero = ch == '0';
				info.contains_valid_integer = Boolean_true;
				info.end_index = info.start_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_digits:
			if (ch == '\0') {
				should_terminate_early = Boolean_true;
			} else if (character_is_whitespace(ch)) {
				state = string_parsing_state_trailing_whitespaces;
			} else if (not character_is_valid_digit(ch)) {
				state = string_parsing_state_trailing_invalid_character;
				info.error = string_to_int_error_invalid_trailing_character;
			} else if (digit_is_supported_by_base(ch, base)) {
				state = string_parsing_state_digits;
				if (is_leading_zero) {
					is_leading_zero = ch == '0';
					info.start_index = index;
				}
				info.end_index = index;
			} else {
				state = string_parsing_state_digit_not_supported_by_base;
				info.error = string_to_int_error_digit_not_supported_by_base;
			}
			break;
		case string_parsing_state_trailing_whitespaces:
			if (ch == '\0') {
				should_terminate_early = Boolean_true;
			} else if (not character_is_whitespace(ch)) {
				state = string_parsing_state_trailing_invalid_character;
				info.error = string_to_int_error_invalid_trailing_character;
			}
			break;
		default:
			break;
		}

		if (should_terminate_early or info.error != string_to_int_error_none) {
			break;
		}
	}

	assert(info.string == string);
	assert(info.length == length);
	assert(info.base == base);
	assert(info.start_index <= info.end_index);
	assert(info.end_index <= length);
	return info;
}

static string_to_int_error_type integer_operation_error_to_string_to_int_error(integer_operation_error_type integer_op_error)
{
	string_to_int_error_type error = string_to_int_error_none;
	switch (integer_op_error) {
	case integer_operation_error_none:
		error = string_to_int_error_none;
		break;
	case integer_operation_error_signed_integer_result_smaller_than_minimum:
		error = string_to_int_error_value_smaller_than_minimum_signed_value;
		break;
	case integer_operation_error_signed_integer_result_greater_than_maximum:
		error = string_to_int_error_value_greater_than_maximum_signed_value;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller:
		error = string_to_int_error_value_greater_than_maximum_unsigned_value;
		break;
	case integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger:
		error = string_to_int_error_value_smaller_than_minimum_unsigned_value;
		break;
	default:
		error = string_to_int_error_unknown;
		break;
	}
	return error;
}

const char *string_to_int_error_message(string_to_int_error_type error)
{
	const char *message = NULL;
	switch (error) {
	case string_to_int_error_none:
		message = "No error.";
		break;
	case string_to_int_error_null_string:
		message = "The string is null.";
		break;
	case string_to_int_error_zero_length:
		message = "The string has zero length.";
		break;
	case string_to_int_error_empty_string:
		message = "The string is empty.";
		break;
	case string_to_int_error_invalid_base:
		message = "The number base is invalid.";
		break;
	case string_to_int_error_unsupported_base:
		message = "The number base is not supported.";
		break;
	case string_to_int_error_only_whitespaces:
		message = "The string contains only whitespaces.";
		break;
	case string_to_int_error_incomplete_string:
		message = "The string is incomplete.";
		break;
	case string_to_int_error_invalid_character:
		message = "An invalid character is found.";
		break;
	case string_to_int_error_invalid_prefix:
		message = "The prefix is invalid.";
		break;
	case string_to_int_error_whitespace_after_sign:
		message = "There is a whitespace after the sign.";
		break;
	case string_to_int_error_digit_not_supported_by_base:
		message = "A digit which is not supported by the number base is found.";
		break;
	case string_to_int_error_invalid_trailing_character:
		message = "An invalid trailing character is found.";
		break;
	case string_to_int_error_value_smaller_than_minimum_signed_value:
		message = "The integer value in the string is lower than the minimum of the signed integer.";
		break;
	case string_to_int_error_value_greater_than_maximum_signed_value:
		message = "The integer value in the string is higher than the maximum of the signed integer.";
		break;
	case string_to_int_error_value_smaller_than_minimum_unsigned_value:
		message = "The integer value in the string is lower than the minimum of the unsigned integer.";
		break;
	case string_to_int_error_value_greater_than_maximum_unsigned_value:
		message = "The integer value in the string is higher than the maximum of the unsigned integer.";
		break;
	default:
		message = "Unknown error.";
		break;
	}
	assert(message != NULL);
	return message;
}

string_to_i32_result_type string_to_i32(const char *string, size_t length, int base)
{
	size_t index = 0U;
	const int32_t minimum = INT32_MIN, maximum = INT32_MAX;
	int32_t integer = 0, limit = 0;
	string_to_i32_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		if (not info.integer_is_negative) {
			limit = maximum / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int32_t digit_value = digit_to_integer(info.string[index]);
				if (integer < limit) {
					integer *= base;
				} else {
					const i32_result_type r = safer_i32_multiply(integer, base);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (integer < limit) {
					integer += digit_value;
				} else {
					const i32_result_type r = safer_i32_add(integer, digit_value);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			limit = minimum / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int32_t digit_value = digit_to_integer(info.string[index]);
				if (integer > limit) {
					integer *= base;
				} else {
					const i32_result_type r = safer_i32_multiply(integer, base);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (integer > limit) {
					integer -= digit_value;
				} else {
					const i32_result_type r = safer_i32_minus(integer, digit_value);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		}
		result.value = integer;
	}
	return result;
}

string_to_i32_result_type i32string_to_i32_(const i32string_type *p_i32string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_i32string->content, sizeof_array(p_i32string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_i32(conststrref.string, length, base);
}


string_to_u32_result_type string_to_u32(const char *string, size_t length, int base)
{
	size_t index = 0U;
	const uint32_t maximum = UINT32_MAX;
	uint32_t integer = 0U, limit = 0U;
	string_to_u32_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);
	result.error = info.error;

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		if (not info.integer_is_negative) {
			limit = maximum / (uint32_t) (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const uint32_t digit_value = (uint32_t) digit_to_integer(info.string[index]);
				if (integer < limit) {
					integer *= (uint32_t) base;
				} else {
					const u32_result_type r = safer_u32_multiply(integer, (uint32_t) base);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (integer < limit) {
					integer += digit_value;
				} else {
					const u32_result_type r = safer_u32_add(integer, digit_value);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			integer = 0U;
			result.error = string_to_int_error_value_smaller_than_minimum_unsigned_value;
		}
		result.value = integer;
	}
	return result;
}

string_to_u32_result_type u32string_to_u32_(const u32string_type *p_u32string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_u32string->content, sizeof_array(p_u32string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_u32(conststrref.string, length, base);
}

string_to_i64_result_type string_to_i64(const char *string, size_t length, int base)
{
	size_t index = 0U;
	const int64_t minimum = INT64_MIN, maximum = INT64_MAX;
	int64_t integer = 0, limit = 0;
	string_to_i64_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		if (not info.integer_is_negative) {
			limit = maximum / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int64_t digit_value = digit_to_integer(info.string[index]);
				if (integer < limit) {
					integer *= base;
				} else {
					const i64_result_type r = safer_i64_multiply(integer, base);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (integer < limit) {
					integer += digit_value;
				} else {
					const i64_result_type r = safer_i64_add(integer, digit_value);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			limit = minimum / (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const int64_t digit_value = digit_to_integer(info.string[index]);
				if (integer > limit) {
					integer *= base;
				} else {
					const i64_result_type r = safer_i64_multiply(integer, base);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (integer > limit) {
					integer -= digit_value;
				} else {
					const i64_result_type r = safer_i64_minus(integer, digit_value);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		}
		result.value = integer;
	}
	return result;
}

string_to_i64_result_type i64string_to_i64_(const i64string_type *p_i64string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_i64string->content, sizeof_array(p_i64string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_i64(conststrref.string, length, base);
}

string_to_u64_result_type string_to_u64(const char *string, size_t length, int base)
{
	size_t index = 0U;
	const uint64_t maximum = UINT64_MAX;
	uint64_t integer = 0U, limit = 0U;
	string_to_u64_result_type result = {0};
	int_string_info_type info = string_to_int_get_string_info(string, length, base);

	if (info.error == string_to_int_error_none and not info.contains_valid_integer) {
		result.error = string_to_int_error_incomplete_string;
	} else {
		result.error = info.error;
	}

	if (info.contains_valid_integer) {
		if (not info.integer_is_negative) {
			limit = maximum / (uint64_t) (base * base);
			for (index = info.start_index; index <= info.end_index; ++index) {
				const uint64_t digit_value = (uint64_t) digit_to_integer(info.string[index]);
				if (integer < limit) {
					integer *= (uint64_t) base;
				} else {
					const u64_result_type r = safer_u64_multiply(integer, (uint64_t) base);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
				if (integer < limit) {
					integer += digit_value;
				} else {
					const u64_result_type r = safer_u64_add(integer, digit_value);
					integer = r.value;
					result.error = integer_operation_error_to_string_to_int_error(r.error);
					if (result.error != string_to_int_error_none)
						break;
				}
			}
		} else {
			integer = 0U;
			result.error = string_to_int_error_value_smaller_than_minimum_unsigned_value;
		}
		result.value = integer;
	}
	return result;
}

string_to_u64_result_type u64string_to_u64_(const u64string_type *p_u64string, int base)
{
	size_t length = 0U;
	const_stringref_type conststrref = string_to_const_stringref(p_u64string->content, sizeof_array(p_u64string->content));
	length = const_stringref_string_length(conststrref);
	return string_to_u64(conststrref.string, length, base);
}
