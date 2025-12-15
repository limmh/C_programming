#ifndef SAFE_BITWISE_OPERATIONS_H
#define SAFE_BITWISE_OPERATIONS_H

#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

/* unsigned int */
INLINE_OR_STATIC unsigned int safe_uint_and(unsigned int a, unsigned int b) {
	return (a & b);
}

INLINE_OR_STATIC unsigned int safe_uint_or(unsigned int a, unsigned int b) {
	return (a | b);
}

INLINE_OR_STATIC unsigned int safe_uint_xor(unsigned int a, unsigned int b) {
	return (a ^ b);
}

INLINE_OR_STATIC unsigned int safe_uint_invert(unsigned int var) {
	return ~var;
}

INLINE_OR_STATIC unsigned int safe_uint_left_shift(unsigned int var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var << (unsigned int) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC unsigned int safe_uint_right_shift(unsigned int var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var >> (unsigned int) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC unsigned int safe_uint_arithmetic_right_shift(unsigned int var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= (UINT_MAX << (unsigned int) number_of_lower_bits);
		}
	}
	return result;
}

INLINE_OR_STATIC unsigned int safe_uint_left_rotate(unsigned int var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var << (unsigned int) effective_number_of_bits;
	right_part = var >> (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

INLINE_OR_STATIC unsigned int safe_uint_right_rotate(unsigned int var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var >> (unsigned int) effective_number_of_bits;
	right_part = var << (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

/* unsigned short */
INLINE_OR_STATIC unsigned short safe_ushort_and(unsigned short a, unsigned short b) {
	return (unsigned short) safe_uint_and(a, b);
}

INLINE_OR_STATIC unsigned short safe_ushort_or(unsigned short a, unsigned short b) {
	return (unsigned short) safe_uint_or(a, b);
}

INLINE_OR_STATIC unsigned short safe_ushort_xor(unsigned short a, unsigned short b) {
	return (unsigned short) safe_uint_xor(a, b);
}

INLINE_OR_STATIC unsigned short safe_ushort_invert(unsigned short var) {
	return (unsigned short) safe_uint_invert(var);
}

INLINE_OR_STATIC unsigned short safe_ushort_left_shift(unsigned short var, size_t number_of_bits) {
	unsigned short result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned short) ((unsigned int) var << (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC unsigned short safe_ushort_right_shift(unsigned short var, size_t number_of_bits) {
	unsigned short result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned short) ((unsigned int) var >> (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC unsigned short safe_ushort_arithmetic_right_shift(unsigned short var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned int) var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if (((unsigned int) var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) USHRT_MAX << (unsigned int) number_of_lower_bits);
		}
	}
	return (unsigned short) result;
}

INLINE_OR_STATIC unsigned short safe_ushort_left_rotate(unsigned short var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var << (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var >> (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (unsigned short) result;
}

INLINE_OR_STATIC unsigned short safe_ushort_right_rotate(unsigned short var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var >> (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var << (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (unsigned short) result;
}

/* unsigned char */
INLINE_OR_STATIC unsigned char safe_uchar_and(unsigned char a, unsigned char b) {
	return (unsigned char) safe_uint_and(a, b);
}

INLINE_OR_STATIC unsigned char safe_uchar_or(unsigned char a, unsigned char b) {
	return (unsigned char) safe_uint_or(a, b);
}

INLINE_OR_STATIC unsigned char safe_uchar_xor(unsigned char a, unsigned char b) {
	return (unsigned char) safe_uint_xor(a, b);
}

INLINE_OR_STATIC unsigned char safe_uchar_invert(unsigned char var) {
	return (unsigned char) safe_uint_invert(var);
}

INLINE_OR_STATIC unsigned char safe_uchar_left_shift(unsigned char var, size_t number_of_bits) {
	unsigned char result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned char) ((unsigned int) var << (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC unsigned char safe_uchar_right_shift(unsigned char var, size_t number_of_bits) {
	unsigned char result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned char) ((unsigned int) var >> (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC unsigned char safe_uchar_arithmetic_right_shift(unsigned char var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned int) var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if (((unsigned int) var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) UCHAR_MAX << (unsigned int) number_of_lower_bits);
		}
	}
	return (unsigned char) result;
}

INLINE_OR_STATIC unsigned char safe_uchar_left_rotate(unsigned char var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var << (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var >> (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (unsigned char) result;
}

INLINE_OR_STATIC unsigned char safe_uchar_right_rotate(unsigned char var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var >> (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var << (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (unsigned char) result;
}

/* unsigned long */
INLINE_OR_STATIC unsigned long safe_ulong_and(unsigned long a, unsigned long b) {
	return (a & b);
}

INLINE_OR_STATIC unsigned long safe_ulong_or(unsigned long a, unsigned long b) {
	return (a | b);
}

INLINE_OR_STATIC unsigned long safe_ulong_xor(unsigned long a, unsigned long b) {
	return (a ^ b);
}

INLINE_OR_STATIC unsigned long safe_ulong_invert(unsigned long a) {
	return ~a;
}

INLINE_OR_STATIC unsigned long safe_ulong_left_shift(unsigned long var, size_t number_of_bits) {
	unsigned long result = 0UL;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var << (unsigned long) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC unsigned long safe_ulong_right_shift(unsigned long var, size_t number_of_bits) {
	unsigned long result = 0UL;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var >> (unsigned long) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC unsigned long safe_ulong_arithmetic_right_shift(unsigned long var, size_t number_of_bits) {
	unsigned long result = 0UL;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = var >> (unsigned long) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1UL << (unsigned long) msb_index)) != 0UL) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= (ULONG_MAX << (unsigned long) number_of_lower_bits);
		}
	}
	return result;
}

INLINE_OR_STATIC unsigned long safe_ulong_left_rotate(unsigned long var, size_t number_of_bits)
{
	unsigned long result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var << (unsigned long) effective_number_of_bits;
	right_part = var >> (unsigned long) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

INLINE_OR_STATIC unsigned long safe_ulong_right_rotate(unsigned long var, size_t number_of_bits)
{
	unsigned long result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var >> (unsigned long) effective_number_of_bits;
	right_part = var << (unsigned long) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

/* unsigned long long */
#if defined(ULLONG_MAX)
INLINE_OR_STATIC unsigned long long safe_ullong_and(unsigned long long a, unsigned long long b) {
	return (a & b);
}

INLINE_OR_STATIC unsigned long long safe_ullong_or(unsigned long long a, unsigned long long b) {
	return (a | b);
}

INLINE_OR_STATIC unsigned long long safe_ullong_xor(unsigned long long a, unsigned long long b) {
	return (a ^ b);
}

INLINE_OR_STATIC unsigned long long safe_ullong_invert(unsigned long long a) {
	return ~a;
}

INLINE_OR_STATIC unsigned long long safe_ullong_left_shift(unsigned long long var, size_t number_of_bits) {
	unsigned long long result = 0ULL;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var << (unsigned long long) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC unsigned long long safe_ullong_right_shift(unsigned long long var, size_t number_of_bits) {
	unsigned long long result = 0ULL;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var >> (unsigned long long) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC unsigned long long safe_ullong_arithmetic_right_shift(unsigned long long var, size_t number_of_bits) {
	unsigned long long result = 0ULL;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = var >> (unsigned long long) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1ULL << (unsigned long long) msb_index)) != 0ULL) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= (ULLONG_MAX << (unsigned long long) number_of_lower_bits);
		}
	}
	return result;
}

INLINE_OR_STATIC unsigned long long safe_ullong_left_rotate(unsigned long long var, size_t number_of_bits)
{
	unsigned long long result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var << (unsigned long long) effective_number_of_bits;
	right_part = var >> (unsigned long long) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

INLINE_OR_STATIC unsigned long long safe_ullong_right_rotate(unsigned long long var, size_t number_of_bits)
{
	unsigned long long result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var >> (unsigned long long) effective_number_of_bits;
	right_part = var << (unsigned long long) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}
#endif

/* unsigned 8-bit */
INLINE_OR_STATIC uint8_t safe_u8_and(uint8_t a, uint8_t b) {
	return (uint8_t) safe_uint_and(a, b);
}

INLINE_OR_STATIC uint8_t safe_u8_or(uint8_t a, uint8_t b) {
	return (uint8_t) safe_uint_or(a, b);
}

INLINE_OR_STATIC uint8_t safe_u8_xor(uint8_t a, uint8_t b) {
	return (uint8_t) safe_uint_xor(a, b);
}

INLINE_OR_STATIC uint8_t safe_u8_invert(uint8_t var) {
	return (uint8_t) safe_uint_invert(var);
}

INLINE_OR_STATIC uint8_t safe_u8_left_shift(uint8_t var, size_t number_of_bits) {
	uint8_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (uint8_t) ((unsigned int) var << (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC uint8_t safe_u8_right_shift(uint8_t var, size_t number_of_bits) {
	uint8_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (uint8_t) ((unsigned int) var >> (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC uint8_t safe_u8_arithmetic_right_shift(uint8_t var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned int) var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if (((unsigned int) var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) UINT8_MAX << (unsigned int) number_of_lower_bits);
		}
	}
	return (uint8_t) result;
}

INLINE_OR_STATIC uint8_t safe_u8_left_rotate(uint8_t var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var << (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var >> (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (uint8_t) result;
}

INLINE_OR_STATIC uint8_t safe_u8_right_rotate(uint8_t var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var >> (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var << (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (uint8_t) result;
}

/* unsigned 16-bit */
INLINE_OR_STATIC uint16_t safe_u16_and(uint16_t a, uint16_t b) {
	return (uint16_t) safe_uint_and(a, b);
}

INLINE_OR_STATIC uint16_t safe_u16_or(uint16_t a, uint16_t b) {
	return (uint16_t) safe_uint_or(a, b);
}

INLINE_OR_STATIC uint16_t safe_u16_xor(uint16_t a, uint16_t b) {
	return (uint16_t) safe_uint_xor(a, b);
}

INLINE_OR_STATIC uint16_t safe_u16_invert(uint16_t var) {
	return (uint16_t) safe_uint_invert(var);
}

INLINE_OR_STATIC uint16_t safe_u16_left_shift(uint16_t var, size_t number_of_bits) {
	uint16_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (uint16_t) ((unsigned int) var << (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC uint16_t safe_u16_right_shift(uint16_t var, size_t number_of_bits) {
	uint16_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = (uint16_t) ((unsigned int) var >> (unsigned int) number_of_bits);
	}
	return result;
}

INLINE_OR_STATIC uint16_t safe_u16_arithmetic_right_shift(uint16_t var, size_t number_of_bits) {
	unsigned int result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = (unsigned int) var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if (((unsigned int) var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) UINT16_MAX << (unsigned int) number_of_lower_bits);
		}
	}
	return (uint16_t) result;
}

INLINE_OR_STATIC uint16_t safe_u16_left_rotate(uint16_t var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var << (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var >> (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (uint16_t) result;
}

INLINE_OR_STATIC uint16_t safe_u16_right_rotate(uint16_t var, size_t number_of_bits)
{
	unsigned int result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = (unsigned int) var >> (unsigned int) effective_number_of_bits;
	right_part = (unsigned int) var << (unsigned int) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return (uint16_t) result;
}

/* unsigned 32-bit */
INLINE_OR_STATIC uint32_t safe_u32_and(uint32_t a, uint32_t b) {
	return (a & b);
}

INLINE_OR_STATIC uint32_t safe_u32_or(uint32_t a, uint32_t b) {
	return (a | b);
}

INLINE_OR_STATIC uint32_t safe_u32_xor(uint32_t a, uint32_t b) {
	return (a ^ b);
}

INLINE_OR_STATIC uint32_t safe_u32_invert(uint32_t var) {
	return ~var;
}

INLINE_OR_STATIC uint32_t safe_u32_left_shift(uint32_t var, size_t number_of_bits) {
	uint32_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var << (uint32_t) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC uint32_t safe_u32_right_shift(uint32_t var, size_t number_of_bits) {
	uint32_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var >> (uint32_t) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC uint32_t safe_u32_arithmetic_right_shift(uint32_t var, size_t number_of_bits) {
	uint32_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = var >> (uint32_t) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & ((uint32_t) 1U << (uint32_t) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= (UINT32_MAX << (uint32_t) number_of_lower_bits);
		}
	}
	return result;
}

INLINE_OR_STATIC uint32_t safe_u32_left_rotate(uint32_t var, size_t number_of_bits)
{
	uint32_t result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var << (uint32_t) effective_number_of_bits;
	right_part = var >> (uint32_t) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

INLINE_OR_STATIC uint32_t safe_u32_right_rotate(uint32_t var, size_t number_of_bits)
{
	uint32_t result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var >> (uint32_t) effective_number_of_bits;
	right_part = var << (uint32_t) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

/* unsigned 64-bit */
#if defined(UINT64_MAX)
INLINE_OR_STATIC uint64_t safe_u64_and(uint64_t a, uint64_t b) {
	return (a & b);
}

INLINE_OR_STATIC uint64_t safe_u64_or(uint64_t a, uint64_t b) {
	return (a | b);
}

INLINE_OR_STATIC uint64_t safe_u64_xor(uint64_t a, uint64_t b) {
	return (a ^ b);
}

INLINE_OR_STATIC uint64_t safe_u64_invert(uint64_t var) {
	return ~var;
}

INLINE_OR_STATIC uint64_t safe_u64_left_shift(uint64_t var, size_t number_of_bits) {
	uint64_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var << (uint64_t) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC uint64_t safe_u64_right_shift(uint64_t var, size_t number_of_bits) {
	uint64_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	if (number_of_bits < total_number_of_bits) {
		result = var >> (uint64_t) number_of_bits;
	}
	return result;
}

INLINE_OR_STATIC uint64_t safe_u64_arithmetic_right_shift(uint64_t var, size_t number_of_bits) {
	uint64_t result = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t msb_index = total_number_of_bits - 1U; /* msb: most significant bit */
	if (number_of_bits < total_number_of_bits) {
		result = var >> (uint64_t) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & ((uint64_t) 1U << (uint64_t) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= (UINT64_MAX << (uint64_t) number_of_lower_bits);
		}
	}
	return result;
}

INLINE_OR_STATIC uint64_t safe_u64_left_rotate(uint64_t var, size_t number_of_bits)
{
	uint64_t result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var << (uint64_t) effective_number_of_bits;
	right_part = var >> (uint64_t) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}

INLINE_OR_STATIC uint64_t safe_u64_right_rotate(uint64_t var, size_t number_of_bits)
{
	uint64_t result = 0U, left_part = 0U, right_part = 0U;
	const size_t total_number_of_bits = sizeof(var) * CHAR_BIT;
	const size_t effective_number_of_bits = number_of_bits % total_number_of_bits;
	left_part = var >> (uint64_t) effective_number_of_bits;
	right_part = var << (uint64_t) (total_number_of_bits - effective_number_of_bits);
	result = left_part | right_part;
	return result;
}
#endif

/* functions with shorter names */

INLINE_OR_STATIC unsigned char uc_and(unsigned char a, unsigned char b) { return safe_uchar_and(a, b); }
INLINE_OR_STATIC unsigned char uc_or(unsigned char a, unsigned char b)  { return safe_uchar_or(a, b); }
INLINE_OR_STATIC unsigned char uc_xor(unsigned char a, unsigned char b) { return safe_uchar_xor(a, b); }
INLINE_OR_STATIC unsigned char uc_inv(unsigned char var)                { return safe_uchar_invert(var); }
INLINE_OR_STATIC unsigned char uc_lshift(unsigned char var, size_t nb)  { return safe_uchar_left_shift(var, nb); }
INLINE_OR_STATIC unsigned char uc_rshift(unsigned char var, size_t nb)  { return safe_uchar_right_shift(var, nb); }
INLINE_OR_STATIC unsigned char uc_arshift(unsigned char var, size_t nb) { return safe_uchar_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC unsigned char uc_lrotate(unsigned char var, size_t nb) { return safe_uchar_left_rotate(var, nb); }
INLINE_OR_STATIC unsigned char uc_rrotate(unsigned char var, size_t nb) { return safe_uchar_right_rotate(var, nb); }

INLINE_OR_STATIC unsigned short us_and(unsigned short a, unsigned short b) { return safe_ushort_and(a, b); }
INLINE_OR_STATIC unsigned short us_or(unsigned short a, unsigned short b)  { return safe_ushort_or(a, b); }
INLINE_OR_STATIC unsigned short us_xor(unsigned short a, unsigned short b) { return safe_ushort_xor(a, b); }
INLINE_OR_STATIC unsigned short us_inv(unsigned short var)                 { return safe_ushort_invert(var); }
INLINE_OR_STATIC unsigned short us_lshift(unsigned short var, size_t nb)   { return safe_ushort_left_shift(var, nb); }
INLINE_OR_STATIC unsigned short us_rshift(unsigned short var, size_t nb)   { return safe_ushort_right_shift(var, nb); }
INLINE_OR_STATIC unsigned short us_arshift(unsigned short var, size_t nb)  { return safe_ushort_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC unsigned short us_lrotate(unsigned short var, size_t nb)  { return safe_ushort_left_rotate(var, nb); }
INLINE_OR_STATIC unsigned short us_rrotate(unsigned short var, size_t nb)  { return safe_ushort_right_rotate(var, nb); }

INLINE_OR_STATIC unsigned int ui_and(unsigned int a, unsigned int b)  { return safe_uint_and(a, b); }
INLINE_OR_STATIC unsigned int ui_or(unsigned int a, unsigned int b)   { return safe_uint_or(a, b); }
INLINE_OR_STATIC unsigned int ui_xor(unsigned int a, unsigned int b)  { return safe_uint_xor(a, b); }
INLINE_OR_STATIC unsigned int ui_inv(unsigned int var)                { return safe_uint_invert(var); }
INLINE_OR_STATIC unsigned int ui_lshift(unsigned int var, size_t nb)  { return safe_uint_left_shift(var, nb); }
INLINE_OR_STATIC unsigned int ui_rshift(unsigned int var, size_t nb)  { return safe_uint_right_shift(var, nb); }
INLINE_OR_STATIC unsigned int ui_arshift(unsigned int var, size_t nb) { return safe_uint_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC unsigned int ui_lrotate(unsigned int var, size_t nb) { return safe_uint_left_rotate(var, nb); }
INLINE_OR_STATIC unsigned int ui_rrotate(unsigned int var, size_t nb) { return safe_uint_right_rotate(var, nb); }

INLINE_OR_STATIC unsigned long ul_and(unsigned long a, unsigned long b) { return safe_ulong_and(a, b); }
INLINE_OR_STATIC unsigned long ul_or(unsigned long a, unsigned long b)  { return safe_ulong_or(a, b); }
INLINE_OR_STATIC unsigned long ul_xor(unsigned long a, unsigned long b) { return safe_ulong_xor(a, b); }
INLINE_OR_STATIC unsigned long ul_inv(unsigned long var)                { return safe_ulong_invert(var); }
INLINE_OR_STATIC unsigned long ul_lshift(unsigned long var, size_t nb)  { return safe_ulong_left_shift(var, nb); }
INLINE_OR_STATIC unsigned long ul_rshift(unsigned long var, size_t nb)  { return safe_ulong_right_shift(var, nb); }
INLINE_OR_STATIC unsigned long ul_arshift(unsigned long var, size_t nb) { return safe_ulong_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC unsigned long ul_lrotate(unsigned long var, size_t nb) { return safe_ulong_left_rotate(var, nb); }
INLINE_OR_STATIC unsigned long ul_rrotate(unsigned long var, size_t nb) { return safe_ulong_right_rotate(var, nb); }

#if defined(ULLONG_MAX)
INLINE_OR_STATIC unsigned long long ull_and(unsigned long long a, unsigned long long b) { return safe_ullong_and(a, b); }
INLINE_OR_STATIC unsigned long long ull_or(unsigned long long a, unsigned long long b)  { return safe_ullong_or(a, b); }
INLINE_OR_STATIC unsigned long long ull_xor(unsigned long long a, unsigned long long b) { return safe_ullong_xor(a, b); }
INLINE_OR_STATIC unsigned long long ull_inv(unsigned long long var)                     { return safe_ullong_invert(var); }
INLINE_OR_STATIC unsigned long long ull_lshift(unsigned long long var, size_t nb)       { return safe_ullong_left_shift(var, nb); }
INLINE_OR_STATIC unsigned long long ull_rshift(unsigned long long var, size_t nb)       { return safe_ullong_right_shift(var, nb); }
INLINE_OR_STATIC unsigned long long ull_arshift(unsigned long long var, size_t nb)      { return safe_ullong_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC unsigned long long ull_lrotate(unsigned long long var, size_t nb)      { return safe_ullong_left_rotate(var, nb); }
INLINE_OR_STATIC unsigned long long ull_rrotate(unsigned long long var, size_t nb)      { return safe_ullong_right_rotate(var, nb); }
#endif

INLINE_OR_STATIC uint8_t u8_and(uint8_t a, uint8_t b)       { return safe_u8_and(a, b); }
INLINE_OR_STATIC uint8_t u8_or(uint8_t a, uint8_t b)        { return safe_u8_or(a, b); }
INLINE_OR_STATIC uint8_t u8_xor(uint8_t a, uint8_t b)       { return safe_u8_xor(a, b); }
INLINE_OR_STATIC uint8_t u8_inv(uint8_t var)                { return safe_u8_invert(var); }
INLINE_OR_STATIC uint8_t u8_lshift(uint8_t var, size_t nb)  { return safe_u8_left_shift(var, nb); }
INLINE_OR_STATIC uint8_t u8_rshift(uint8_t var, size_t nb)  { return safe_u8_right_shift(var, nb); }
INLINE_OR_STATIC uint8_t u8_arshift(uint8_t var, size_t nb) { return safe_u8_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC uint8_t u8_lrotate(uint8_t var, size_t nb) { return safe_u8_left_rotate(var, nb); }
INLINE_OR_STATIC uint8_t u8_rrotate(uint8_t var, size_t nb) { return safe_u8_right_rotate(var, nb); }

INLINE_OR_STATIC uint16_t u16_and(uint16_t a, uint16_t b)      { return safe_u16_and(a, b); }
INLINE_OR_STATIC uint16_t u16_or(uint16_t a, uint16_t b)       { return safe_u16_or(a, b); }
INLINE_OR_STATIC uint16_t u16_xor(uint16_t a, uint16_t b)      { return safe_u16_xor(a, b); }
INLINE_OR_STATIC uint16_t u16_inv(uint16_t var)                { return safe_u16_invert(var); }
INLINE_OR_STATIC uint16_t u16_lshift(uint16_t var, size_t nb)  { return safe_u16_left_shift(var, nb); }
INLINE_OR_STATIC uint16_t u16_rshift(uint16_t var, size_t nb)  { return safe_u16_right_shift(var, nb); }
INLINE_OR_STATIC uint16_t u16_arshift(uint16_t var, size_t nb) { return safe_u16_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC uint16_t u16_lrotate(uint16_t var, size_t nb) { return safe_u16_left_rotate(var, nb); }
INLINE_OR_STATIC uint16_t u16_rrotate(uint16_t var, size_t nb) { return safe_u16_right_rotate(var, nb); }

INLINE_OR_STATIC uint32_t u32_and(uint32_t a, uint32_t b)      { return safe_u32_and(a, b); }
INLINE_OR_STATIC uint32_t u32_or(uint32_t a, uint32_t b)       { return safe_u32_or(a, b); }
INLINE_OR_STATIC uint32_t u32_xor(uint32_t a, uint32_t b)      { return safe_u32_xor(a, b); }
INLINE_OR_STATIC uint32_t u32_inv(uint32_t var)                { return safe_u32_invert(var); }
INLINE_OR_STATIC uint32_t u32_lshift(uint32_t var, size_t nb)  { return safe_u32_left_shift(var, nb); }
INLINE_OR_STATIC uint32_t u32_rshift(uint32_t var, size_t nb)  { return safe_u32_right_shift(var, nb); }
INLINE_OR_STATIC uint32_t u32_arshift(uint32_t var, size_t nb) { return safe_u32_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC uint32_t u32_lrotate(uint32_t var, size_t nb) { return safe_u32_left_rotate(var, nb); }
INLINE_OR_STATIC uint32_t u32_rrotate(uint32_t var, size_t nb) { return safe_u32_right_rotate(var, nb); }

#if defined(UINT64_MAX)
INLINE_OR_STATIC uint64_t u64_and(uint64_t a, uint64_t b)        { return safe_u64_and(a, b); }
INLINE_OR_STATIC uint64_t u64_or(uint64_t a, uint64_t b)         { return safe_u64_or(a, b); }
INLINE_OR_STATIC uint64_t u64_xor(uint64_t a, uint64_t b)        { return safe_u64_xor(a, b); }
INLINE_OR_STATIC uint64_t u64_inv(uint64_t var)         { return safe_u64_invert(var); }
INLINE_OR_STATIC uint64_t u64_lshift(uint64_t var, size_t nb)  { return safe_u64_left_shift(var, nb); }
INLINE_OR_STATIC uint64_t u64_rshift(uint64_t var, size_t nb)  { return safe_u64_right_shift(var, nb); }
INLINE_OR_STATIC uint64_t u64_arshift(uint64_t var, size_t nb) { return safe_u64_arithmetic_right_shift(var, nb); }
INLINE_OR_STATIC uint64_t u64_lrotate(uint64_t var, size_t nb) { return safe_u64_left_rotate(var, nb); }
INLINE_OR_STATIC uint64_t u64_rrotate(uint64_t var, size_t nb) { return safe_u64_right_rotate(var, nb); }
#endif

#endif
