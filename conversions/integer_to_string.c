#include "integer_to_string.h"
#include "Boolean_type.h"
#include "sizeof_array.h"
#include "static_assert.h"
#include "string_reference.h"

#include <assert.h>
#include <iso646.h>
#include <stddef.h>

static const char lowercase_characters[] = {
	'0','1','2','3','4','5',
	'6','7','8','9','a','b',
	'c','d','e','f','g','h',
	'i','j','k','l','m','n',
	'o','p','q','r','s','t',
	'u','v','w','x','y','z'
};

static const char uppercase_characters[] = {
	'0','1','2','3','4','5',
	'6','7','8','9','A','B',
	'C','D','E','F','G','H',
	'I','J','K','L','M','N',
	'O','P','Q','R','S','T',
	'U','V','W','X','Y','Z'
};

STATIC_ASSERT(sizeof_array(lowercase_characters) == sizeof_array(uppercase_characters), "The two arrays must have the same size.");

typedef struct int_to_string_settings_type {
	Boolean_type use_uppercase; /* Boolean_false: lowercase, Boolean_true: uppercase */
	Boolean_type add_prefix;    /* Boolean_false: no prefix for octal or hexadecimal, Boolean_true: add a prefix for octal or hexadecimal */
	Boolean_type add_plus_sign; /* Boolean_false: no plus sign for positive integers, Boolean_true: add a plus sign for positive integers */
} int_to_string_settings_type;

static int_to_string_settings_type
int_to_string_options_to_settings(int_to_string_option_type options)
{
	STATIC_ASSERT(sizeof(uint32_t) >= sizeof(int_to_string_option_type), "The size of uint32_t shall be at least the size of enum type.");
	const uint32_t bit_pattern = (uint32_t) options;
	int_to_string_settings_type settings = {Boolean_false};
	settings.use_uppercase = (bit_pattern & 0x1U) == (uint32_t) int_to_string_option_uppercase;
	settings.add_prefix = (bit_pattern & 0x2U) == (uint32_t) int_to_string_option_add_prefix;
	settings.add_plus_sign = (bit_pattern & 0x4U) == (uint32_t) int_to_string_option_add_plus_sign;
	return settings;
}

i32string_type i32_to_i32string(int32_t value, int base, int_to_string_option_type options)
{
	int32_t absolute_value = 0, offset = 0, carry = 0;
	size_t index = 0U, length = 0U;
	i32string_type string = {{0}};
	const char *characters = NULL;
	int_to_string_settings_type settings = {Boolean_false};

	assert(base >= 2 and base <= 36);
	if (base < 2) {
		base = 2;
	} else if (base > 36) {
		base = 36;
	}

	settings = int_to_string_options_to_settings(options);
	characters = settings.use_uppercase ? uppercase_characters : lowercase_characters;

	if (value != INT32_MIN) {
		absolute_value = (value >= 0) ? value : -value;
		offset = 0;
	} else {
		absolute_value = INT32_MAX;
		offset = 1;
	}

	assert(absolute_value >= 0);
	while (absolute_value > 0) {
		int32_t remainder = absolute_value % base;
		absolute_value = absolute_value / base;
		if (index != 0U) {
			remainder += carry;
		} else {
			remainder += offset;
		}
		if (remainder != base) {
			carry = 0;
		} else {
			carry = 1;
			remainder = 0;
		}
		assert(remainder >= 0 and remainder < (int32_t) sizeof_array(lowercase_characters));
		string.content[index++] = characters[remainder];
	}

	if (carry != 0) {
		string.content[index++] = characters[carry];
	}

	if (settings.add_prefix) {
		if (base == 16) {
			string.content[index++] = settings.use_uppercase ? 'X' : 'x';
			string.content[index++] = '0';
		} else if (base == 8) {
			string.content[index++] = '0';
		} else if (base == 2) {
			string.content[index++] = settings.use_uppercase ? 'B' : 'b';
			string.content[index++] = '0';
		}
	}

	if (value < 0) {
		string.content[index++] = '-';
	} else if (value == 0) {
		assert(index == 0U);
		string.content[index++] = characters[0];
	} else if (settings.add_plus_sign) {
		string.content[index++] = '+';
	}

	length = index;
	assert(length < sizeof_array(string.content));
	stringref_reverse_string(string_to_stringref(string.content, length));
	string.content[index] = '\0';
	return string;
}

u32string_type u32_to_u32string(uint32_t value, int base, int_to_string_option_type options)
{
	uint32_t value_ = value;
	size_t index = 0U, length = 0U;
	u32string_type string = {{0}};
	const char *characters = NULL;
	int_to_string_settings_type settings = {Boolean_false};

	assert(base >= 2 and base <= 36);
	if (base < 2) {
		base = 2;
	} else if (base > 36) {
		base = 36;
	}

	settings = int_to_string_options_to_settings(options);
	characters = settings.use_uppercase ? uppercase_characters : lowercase_characters;

	while (value_ > 0U) {
		const uint32_t remainder = value_ % (uint32_t) base;
		value_ = value_ / (uint32_t) base;
		assert(remainder < sizeof_array(lowercase_characters));
		string.content[index++] = characters[remainder];
	}

	if (settings.add_prefix) {
		if (base == 16) {
			string.content[index++] = settings.use_uppercase ? 'X' : 'x';
			string.content[index++] = '0';
		} else if (base == 8) {
			string.content[index++] = '0';
		} else if (base == 2) {
			string.content[index++] = settings.use_uppercase ? 'B' : 'b';
			string.content[index++] = '0';
		}
	}

	if (value == 0U) {
		assert(index == 0U);
		string.content[index++] = characters[0];
	} else if (settings.add_plus_sign) {
		string.content[index++] = '+';
	}

	length = index;
	assert(length < sizeof_array(string.content));
	stringref_reverse_string(string_to_stringref(string.content, length));
	string.content[index] = '\0';
	return string;
}

i64string_type i64_to_i64string(int64_t value, int base, int_to_string_option_type options)
{
	int64_t absolute_value = 0, offset = 0, carry = 0;
	size_t index = 0U, length = 0U;
	i64string_type string = {{0}};
	const char *characters = NULL;
	int_to_string_settings_type settings = {Boolean_false};

	assert(base >= 2 and base <= 36);
	if (base < 2) {
		base = 2;
	} else if (base > 36) {
		base = 36;
	}

	settings = int_to_string_options_to_settings(options);
	characters = settings.use_uppercase ? uppercase_characters : lowercase_characters;
	
	if (value != INT64_MIN) {
		absolute_value = (value >= 0) ? value : -value;
		offset = 0;
	} else {
		absolute_value = INT64_MAX;
		offset = 1;
	}

	assert(absolute_value >= 0);
	while (absolute_value > 0) {
		int64_t remainder = absolute_value % base;
		absolute_value = absolute_value / base;
		if (index != 0U) {
			remainder += carry;
		} else {
			remainder += offset;
		}
		if (remainder != base) {
			carry = 0;
		} else {
			carry = 1;
			remainder = 0;
		}
		assert(remainder >= 0 and remainder < (int64_t) sizeof_array(lowercase_characters));
		string.content[index++] = characters[remainder];
	}

	if (carry != 0) {
		string.content[index++] = characters[carry];
	}

	if (settings.add_prefix) {
		if (base == 16) {
			string.content[index++] = settings.use_uppercase ? 'X' : 'x';
			string.content[index++] = '0';
		} else if (base == 8) {
			string.content[index++] = '0';
		} else if (base == 2) {
			string.content[index++] = settings.use_uppercase ? 'B' : 'b';
			string.content[index++] = '0';
		}
	}

	if (value < 0) {
		string.content[index++] = '-';
	} else if (value == 0) {
		assert(index == 0U);
		string.content[index++] = characters[0];
	} else if (settings.add_plus_sign) {
		string.content[index++] = '+';
	}

	length = index;
	assert(length < sizeof_array(string.content));
	stringref_reverse_string(string_to_stringref(string.content, length));
	string.content[index] = '\0';
	return string;
}

u64string_type u64_to_u64string(uint64_t value, int base, int_to_string_option_type options)
{
	uint64_t value_ = value;
	size_t index = 0U, length = 0U;
	u64string_type string = {{0}};
	const char *characters = NULL;
	int_to_string_settings_type settings = {Boolean_false};

	assert(base >= 2 and base <= 36);
	if (base < 2) {
		base = 2;
	} else if (base > 36) {
		base = 36;
	}

	settings = int_to_string_options_to_settings(options);
	characters = settings.use_uppercase ? uppercase_characters : lowercase_characters;

	while (value_ > 0U) {
		const uint64_t remainder = value_ % (uint64_t) base;
		value_ = value_ / (uint64_t) base;
		assert(remainder < sizeof_array(lowercase_characters));
		string.content[index++] = characters[remainder];
	}

	if (settings.add_prefix) {
		if (base == 16) {
			string.content[index++] = settings.use_uppercase ? 'X' : 'x';
			string.content[index++] = '0';
		} else if (base == 8) {
			string.content[index++] = '0';
		} else if (base == 2) {
			string.content[index++] = settings.use_uppercase ? 'B' : 'b';
			string.content[index++] = '0';
		}
	}

	if (value == 0U) {
		assert(index == 0U);
		string.content[index++] = characters[0];
	} else if (settings.add_plus_sign) {
		string.content[index++] = '+';
	}

	length = index;
	assert(length < sizeof_array(string.content));
	stringref_reverse_string(string_to_stringref(string.content, length));
	string.content[index] = '\0';
	return string;
}
