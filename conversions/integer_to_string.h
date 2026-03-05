#ifndef INTEGER_TO_STRING_H
#define INTEGER_TO_STRING_H

#include "fixed_width_integer_types.h"
#include "inline_or_static.h"
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum int_to_string_option_type {
	int_to_string_option_default = 0,
	/*-------------------------------*/
	int_to_string_option_lowercase = 0, /* uses a to z for number bases greater than 10 */
	int_to_string_option_uppercase = 1, /* uses A to Z for number bases greater than 10 */
	/*-------------------------------*/
	int_to_string_option_add_prefix = 2, /* adds 0 in front of an octal integer, 0x in front of a hexadecimal integer, or 0b in front of a binary integer */
	/*-------------------------------*/
	int_to_string_option_add_plus_sign = 4 /* adds + in front of positive integers */
} int_to_string_option_type;

typedef struct i32string_type {
	char content[(sizeof(int32_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus (optional) or minus sign and NUL */
} i32string_type;

typedef struct u32string_type {
	char content[(sizeof(uint32_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus sign (optional) and NUL */
} u32string_type;

typedef struct i64string_type {
	char content[(sizeof(int64_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus (optional) or minus sign and NUL */
} i64string_type;

typedef struct u64string_type {
	char content[(sizeof(uint64_t) * CHAR_BIT) + 4U]; /* includes prefix (optional), plus sign (optional) and NUL */
} u64string_type;

/* The string content is always null-terminated. */
i32string_type i32_to_i32string(int32_t value, int base, int_to_string_option_type options);
u32string_type u32_to_u32string(uint32_t value, int base, int_to_string_option_type options);
i64string_type i64_to_i64string(int64_t value, int base, int_to_string_option_type options);
u64string_type u64_to_u64string(uint64_t value, int base, int_to_string_option_type options);

/* i32_to_i32string variants for bases 2, 8, 10 and 16 */
INLINE_OR_STATIC i32string_type base2_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_default);
}

INLINE_OR_STATIC i32string_type base2_i32_to_i32string_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i32string_type base2_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base2_i32_to_i32string_with_prefix_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base8_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 8, int_to_string_option_default);
}

INLINE_OR_STATIC i32string_type base8_i32_to_i32string_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 8, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i32string_type base8_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base8_i32_to_i32string_with_prefix_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 8, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base10_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 10, int_to_string_option_default);
}

INLINE_OR_STATIC i32string_type base10_i32_to_i32string_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 10, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i32string_type base10_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 10, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base10_i32_to_i32string_with_prefix_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 10, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base16_i32_to_i32string(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_default);
}

INLINE_OR_STATIC i32string_type base16_i32_to_i32string_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i32string_type base16_i32_to_i32string_with_prefix(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i32string_type base16_i32_to_i32string_with_prefix_in_uppercase(int32_t value) {
	return i32_to_i32string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/* u32_to_u32string variants for bases 2, 8, 10 and 16 */
INLINE_OR_STATIC u32string_type base2_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_default);
}

INLINE_OR_STATIC u32string_type base2_u32_to_u32string_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u32string_type base2_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base2_u32_to_u32string_with_prefix_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base8_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 8, int_to_string_option_default);
}

INLINE_OR_STATIC u32string_type base8_u32_to_u32string_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 8, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u32string_type base8_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base8_u32_to_u32string_with_prefix_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 8, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base10_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 10, int_to_string_option_default);
}

INLINE_OR_STATIC u32string_type base10_u32_to_u32string_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 10, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u32string_type base10_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 10, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base10_u32_to_u32string_with_prefix_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 10, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base16_u32_to_u32string(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_default);
}

INLINE_OR_STATIC u32string_type base16_u32_to_u32string_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u32string_type base16_u32_to_u32string_with_prefix(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u32string_type base16_u32_to_u32string_with_prefix_in_uppercase(uint32_t value) {
	return u32_to_u32string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/* i64_to_i64string variants for bases 2, 8, 10 and 16 */
INLINE_OR_STATIC i64string_type base2_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_default);
}

INLINE_OR_STATIC i64string_type base2_i64_to_i64string_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i64string_type base2_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base2_i64_to_i64string_with_prefix_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base8_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 8, int_to_string_option_default);
}

INLINE_OR_STATIC i64string_type base8_i64_to_i64string_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 8, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i64string_type base8_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base8_i64_to_i64string_with_prefix_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 8, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base10_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 10, int_to_string_option_default);
}

INLINE_OR_STATIC i64string_type base10_i64_to_i64string_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 10, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i64string_type base10_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 10, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base10_i64_to_i64string_with_prefix_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 10, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base16_i64_to_i64string(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_default);
}

INLINE_OR_STATIC i64string_type base16_i64_to_i64string_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_uppercase);
}

INLINE_OR_STATIC i64string_type base16_i64_to_i64string_with_prefix(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC i64string_type base16_i64_to_i64string_with_prefix_in_uppercase(int64_t value) {
	return i64_to_i64string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

/* u64_to_u64string variants for bases 2, 8, 10 and 16 */
INLINE_OR_STATIC u64string_type base2_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_default);
}

INLINE_OR_STATIC u64string_type base2_u64_to_u64string_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u64string_type base2_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base2_u64_to_u64string_with_prefix_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 2, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base8_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 8, int_to_string_option_default);
}

INLINE_OR_STATIC u64string_type base8_u64_to_u64string_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 8, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u64string_type base8_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 8, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base8_u64_to_u64string_with_prefix_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 8, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base10_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 10, int_to_string_option_default);
}

INLINE_OR_STATIC u64string_type base10_u64_to_u64string_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 10, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u64string_type base10_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 10, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base10_u64_to_u64string_with_prefix_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 10, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base16_u64_to_u64string(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_default);
}

INLINE_OR_STATIC u64string_type base16_u64_to_u64string_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_uppercase);
}

INLINE_OR_STATIC u64string_type base16_u64_to_u64string_with_prefix(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_lowercase | int_to_string_option_add_prefix);
}

INLINE_OR_STATIC u64string_type base16_u64_to_u64string_with_prefix_in_uppercase(uint64_t value) {
	return u64_to_u64string(value, 16, int_to_string_option_uppercase | int_to_string_option_add_prefix);
}

#ifdef __cplusplus
}
#endif

#endif
