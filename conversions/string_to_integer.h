#ifndef STRING_TO_INTEGER_H
#define STRING_TO_INTEGER_H

#include "integer_to_string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum string_to_int_error_type {
	string_to_int_error_unknown = -1,
	string_to_int_error_none = 0,
	string_to_int_error_null_string,
	string_to_int_error_zero_length,
	string_to_int_error_empty_string,
	string_to_int_error_invalid_base,
	string_to_int_error_unsupported_base,
	string_to_int_error_only_whitespaces,
	string_to_int_error_incomplete_string,
	string_to_int_error_invalid_character,
	string_to_int_error_invalid_prefix,
	string_to_int_error_whitespace_after_sign,
	string_to_int_error_digit_not_supported_by_base,
	string_to_int_error_invalid_trailing_character,
	string_to_int_error_value_smaller_than_minimum_signed_value,
	string_to_int_error_value_greater_than_maximum_signed_value,
	string_to_int_error_value_smaller_than_minimum_unsigned_value,
	string_to_int_error_value_greater_than_maximum_unsigned_value
} string_to_int_error_type;

typedef struct string_to_i32_result_type {
	int32_t value;
	string_to_int_error_type error;
} string_to_i32_result_type;

typedef struct string_to_u32_result_type {
	uint32_t value;
	string_to_int_error_type error;
} string_to_u32_result_type;

typedef struct string_to_i64_result_type {
	int64_t value;
	string_to_int_error_type error;
} string_to_i64_result_type;

typedef struct string_to_u64_result_type {
	uint64_t value;
	string_to_int_error_type error;
} string_to_u64_result_type;

const char *string_to_int_error_message(string_to_int_error_type error);

string_to_i32_result_type string_to_i32(const char *string, size_t length, int base);
string_to_i32_result_type i32string_to_i32_(const i32string_type *p_i32string, int base);
#define i32string_to_i32(i32string, base) i32string_to_i32_(&(i32string), base)

string_to_u32_result_type string_to_u32(const char *string, size_t length, int base);
string_to_u32_result_type u32string_to_u32_(const u32string_type *p_u32string, int base);
#define u32string_to_u32(u32string, base) u32string_to_u32_(&(u32string), base)

string_to_i64_result_type string_to_i64(const char *string, size_t length, int base);
string_to_i64_result_type i64string_to_i64_(const i64string_type *p_i64string, int base);
#define i64string_to_i64(i64string, base) i64string_to_i64_(&(i64string), base)

string_to_u64_result_type string_to_u64(const char *string, size_t length, int base);
string_to_u64_result_type u64string_to_u64_(const u64string_type *p_u64string, int base);
#define u64string_to_u64(u64string, base) u64string_to_u64_(&(u64string), base)

#ifdef __cplusplus
}
#endif

#endif
