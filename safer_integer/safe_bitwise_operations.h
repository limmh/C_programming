#ifndef SAFE_BITWISE_OPERATIONS_H
#define SAFE_BITWISE_OPERATIONS_H

#include "fixed_width_integer_types.h"
#include "inline_or_static.h"

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
		result = var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) USHRT_MAX << (unsigned int) number_of_lower_bits);
			result &= (unsigned int) USHRT_MAX;
		}
	}
	return (unsigned short) result;
}

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
		result = var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) UCHAR_MAX << (unsigned int) number_of_lower_bits);
			result &= (unsigned int) UCHAR_MAX;
		}
	}
	return (unsigned char) result;
}

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
		result = var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) UINT8_MAX << (unsigned int) number_of_lower_bits);
			result &= (unsigned int) UINT8_MAX;
		}
	}
	return (uint8_t) result;
}

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
		result = var >> (unsigned int) number_of_bits;	
	} else {
		number_of_bits = total_number_of_bits;
	}
	if ((var & (1U << (unsigned int) msb_index)) != 0U) {
		const size_t number_of_lower_bits = total_number_of_bits - number_of_bits;
		if (number_of_lower_bits < total_number_of_bits) {
			result |= ((unsigned int) UINT16_MAX << (unsigned int) number_of_lower_bits);
			result &= (unsigned int) UINT16_MAX;
		}
	}
	return (uint16_t) result;
}

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

#define uc_and(a, b) safe_uchar_and(a, b)
#define uc_or(a, b) safe_uchar_or(a, b)
#define uc_xor(a, b) safe_uchar_xor(a, b)
#define uc_inv(var) safe_uchar_invert(var)
#define uc_lshift(var, nb) safe_uchar_left_shift(var, nb)
#define uc_rshift(var, nb) safe_uchar_right_shift(var, nb)
#define uc_arshift(var, nb) safe_uchar_arithmetic_right_shift(var, nb)

#define us_and(a, b) safe_ushort_and(a, b)
#define us_or(a, b) safe_ushort_or(a, b)
#define us_xor(a, b) safe_ushort_xor(a, b)
#define us_inv(var) safe_ushort_invert(var)
#define us_lshift(var, nb) safe_ushort_left_shift(var, nb)
#define us_rshift(var, nb) safe_ushort_right_shift(var, nb)
#define us_arshift(var, nb) safe_ushort_arithmetic_right_shift(var, nb)

#define ui_and(a, b) safe_uint_and(a, b)
#define ui_or(a, b) safe_uint_or(a, b)
#define ui_xor(a, b) safe_uint_xor(a, b)
#define ui_inv(var) safe_uint_invert(var)
#define ui_lshift(var, nb) safe_uint_left_shift(var, nb)
#define ui_rshift(var, nb) safe_uint_right_shift(var, nb)
#define ui_arshift(var, nb) safe_uint_arithmetic_right_shift(var, nb)

#define ul_and(a, b) safe_ulong_and(a, b)
#define ul_or(a, b) safe_ulong_or(a, b)
#define ul_xor(a, b) safe_ulong_xor(a, b)
#define ul_inv(var) safe_ulong_invert(var)
#define ul_lshift(var, nb) safe_ulong_left_shift(var, nb)
#define ul_rshift(var, nb) safe_ulong_right_shift(var, nb)
#define ul_arshift(var, nb) safe_ulong_arithmetic_right_shift(var, nb)

#define ull_and(a, b) safe_ullong_and(a, b)
#define ull_or(a, b) safe_ullong_or(a, b)
#define ull_xor(a, b) safe_ullong_xor(a, b)
#define ull_inv(var) safe_ullong_invert(var)
#define ull_lshift(var, nb) safe_ullong_left_shift(var, nb)
#define ull_rshift(var, nb) safe_ullong_right_shift(var, nb)
#define ull_arshift(var, nb) safe_ullong_arithmetic_right_shift(var, nb)

#define u8_and(a, b) safe_u8_and(a, b)
#define u8_or(a, b) safe_u8_or(a, b)
#define u8_xor(a, b) safe_u8_xor(a, b)
#define u8_inv(var) safe_u8_invert(var)
#define u8_lshift(var, nb) safe_u8_left_shift(var, nb)
#define u8_rshift(var, nb) safe_u8_right_shift(var, nb)
#define u8_arshift(var, nb) safe_u8_arithmetic_right_shift(var, nb)

#define u16_and(a, b) safe_u16_and(a, b)
#define u16_or(a, b) safe_u16_or(a, b)
#define u16_xor(a, b) safe_u16_xor(a, b)
#define u16_inv(var) safe_u16_invert(var)
#define u16_lshift(var, nb) safe_u16_left_shift(var, nb)
#define u16_rshift(var, nb) safe_u16_right_shift(var, nb)
#define u16_arshift(var, nb) safe_u16_arithmetic_right_shift(var, nb)

#define u32_and(a, b) safe_u32_and(a, b)
#define u32_or(a, b) safe_u32_or(a, b)
#define u32_xor(a, b) safe_u32_xor(a, b)
#define u32_inv(var) safe_u32_invert(var)
#define u32_lshift(var, nb) safe_u32_left_shift(var, nb)
#define u32_rshift(var, nb) safe_u32_right_shift(var, nb)
#define u32_arshift(var, nb) safe_u32_arithmetic_right_shift(var, nb)

#define u64_and(a, b) safe_u64_and(a, b)
#define u64_or(a, b) safe_u64_or(a, b)
#define u64_xor(a, b) safe_u64_xor(a, b)
#define u64_inv(var) safe_u64_invert(var)
#define u64_lshift(var, nb) safe_u64_left_shift(var, nb)
#define u64_rshift(var, nb) safe_u64_right_shift(var, nb)
#define u64_arshift(var, nb) safe_u64_arithmetic_right_shift(var, nb)

#endif
