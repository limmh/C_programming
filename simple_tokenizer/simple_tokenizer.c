#include "simple_tokenizer.h"
#include "Boolean_type.h"
#include "static_assert.h"

#include <assert.h>
#include <ctype.h>
#include <iso646.h>
#include <string.h>

typedef enum byte_token_type_enum {
	byte_token_unknown = 0,
	byte_token_letter,
	byte_token_digit,
	byte_token_punctuation,
	byte_token_space,
	byte_token_newline,
	byte_token_zero,
	byte_token_control,
	byte_token_extended_ascii,
	byte_token_first_of_two_utf8_bytes,
	byte_token_first_of_three_utf8_bytes,
	byte_token_first_of_four_utf8_bytes
} byte_token_type_enum;

static byte_token_type_enum get_byte_token_type(char ch)
{
	byte_token_type_enum token_type = byte_token_unknown;
	const unsigned char byte = (unsigned char) ch;
	if ((byte >= 'A' and byte <= 'Z') or (byte >= 'a' and byte <= 'z')) {
		token_type = byte_token_letter;
	} else if (byte >= '0' and byte <= '9') {
		token_type = byte_token_digit;
	} else if (byte == ' ' or byte == '\t') {
		token_type = byte_token_space;
	} else if (byte == '\r' or byte == '\n') {
		token_type = byte_token_newline;
	} else if (byte == '\0') {
		token_type = byte_token_zero;
	} else if (ispunct(byte) and byte < 128U) {
		token_type = byte_token_punctuation;
	} else if (byte < 128U) {
		token_type = byte_token_control;
	} else if (((unsigned int) byte & 0xE0U) == 0xC0U) { /* byte pattern: 110xxxxx */
		token_type = byte_token_first_of_two_utf8_bytes;
	} else if (((unsigned int) byte & 0xF0U) == 0xE0U) { /* byte pattern: 1110xxxx */
		token_type = byte_token_first_of_three_utf8_bytes;
	} else if (((unsigned int) byte & 0xF8U) == 0xF0U) { /* byte pattern: 11110xxx */
		token_type = byte_token_first_of_four_utf8_bytes;
	} else {
		token_type = byte_token_extended_ascii;
	}
	return token_type;
}

static simple_tokenizer_token_type_enum
byte_token_type_to_simple_tokenizer_token_type(byte_token_type_enum byte_token_type)
{
	simple_tokenizer_token_type_enum token_type = simple_tokenizer_token_unknown;
	assert(byte_token_type != byte_token_unknown);
	switch (byte_token_type) {
	case byte_token_letter:
		token_type = simple_tokenizer_token_letters;
		break;
	case byte_token_digit:
		token_type = simple_tokenizer_token_digits;
		break;
	case byte_token_punctuation:
		token_type = simple_tokenizer_token_punctuation;
		break;
	case byte_token_space:
		token_type = simple_tokenizer_token_spaces;
		break;
	case byte_token_newline:
		token_type = simple_tokenizer_token_newline;
		break;
	case byte_token_zero:
		token_type = simple_tokenizer_token_zeros;
		break;
	case byte_token_control:
		token_type = simple_tokenizer_token_control_character;
		break;
	case byte_token_extended_ascii:
		token_type = simple_tokenizer_token_extended_ascii_character;
		break;
	case byte_token_first_of_two_utf8_bytes:
	case byte_token_first_of_three_utf8_bytes:
	case byte_token_first_of_four_utf8_bytes:
		token_type = simple_tokenizer_token_utf8_character;
		break;
	default:
		break;
	}
	return token_type;
}

const char *simple_tokenizer_token_type_name(simple_tokenizer_token_type_enum token_type)
{
	const char *token_type_name = "";
	switch (token_type) {
	case simple_tokenizer_token_letters:
		token_type_name = "letters";
		break;
	case simple_tokenizer_token_digits:
		token_type_name = "digits";
		break;
	case simple_tokenizer_token_punctuation:
		token_type_name = "punctuation";
		break;
	case simple_tokenizer_token_spaces:
		token_type_name = "spaces";
		break;
	case simple_tokenizer_token_newline:
		token_type_name = "new line";
		break;
	case simple_tokenizer_token_zeros:
		token_type_name = "zero bytes";
		break;
	case simple_tokenizer_token_control_character:
		token_type_name = "control";
		break;
	case simple_tokenizer_token_extended_ascii_character:
		token_type_name = "extended ASCII";
		break;
	case simple_tokenizer_token_utf8_character:
		token_type_name = "UTF-8 character";
		break;
	default:
		token_type_name = "unknown";
		break;
	}
	return token_type_name;
}

size_t simple_tokenizer_tokenize(const char *string, size_t string_length, simple_tokenizer_token_type *ptokens, size_t number_of_tokens)
{
	size_t index = 0U;
	simple_tokenizer_token_type_enum token_type = simple_tokenizer_token_unknown;
	size_t token_length = 0U;
	const char *p_first_char = NULL;
	size_t total_number_of_tokens = 0U;

	assert(string != NULL);

	for (index = 0U; index < string_length; ++index) {
		const char byte = string[index];
		simple_tokenizer_token_type_enum new_token_type = simple_tokenizer_token_unknown;
		Boolean_type add_token = Boolean_false;
		size_t new_token_length = 1U;
		byte_token_type_enum byte_token_type = get_byte_token_type(byte);

		switch (byte_token_type) {
		case byte_token_first_of_two_utf8_bytes:
			if ((index + 1U) < string_length) {
				const_stringref_type stringref = string_to_const_stringref(&string[index], 2U);
				simple_tokenizer_utf8_char_type utf8_char = simple_tokenizer_stringref_to_utf8_char(stringref);
				if (simple_tokenizer_utf8_char_error_none == utf8_char.error) {
					++new_token_length;
				} else {
					byte_token_type = byte_token_extended_ascii;
				}
			} else {
				byte_token_type = byte_token_extended_ascii;
			}
			break;
		case byte_token_first_of_three_utf8_bytes:
			if ((index + 2U) < string_length) {
				const_stringref_type stringref = string_to_const_stringref(&string[index], 3U);
				simple_tokenizer_utf8_char_type utf8_char = simple_tokenizer_stringref_to_utf8_char(stringref);
				if (simple_tokenizer_utf8_char_error_none == utf8_char.error) {
					new_token_length += 2U;
				} else {
					byte_token_type = byte_token_extended_ascii;
				}
			} else {
				byte_token_type = byte_token_extended_ascii;
			}
			break;
		case byte_token_first_of_four_utf8_bytes:
			if ((index + 3U) < string_length) {
				const_stringref_type stringref = string_to_const_stringref(&string[index], 4U);
				simple_tokenizer_utf8_char_type utf8_char = simple_tokenizer_stringref_to_utf8_char(stringref);
				if (simple_tokenizer_utf8_char_error_none == utf8_char.error) {
					new_token_length += 3U;
				} else {
					byte_token_type = byte_token_extended_ascii;
				}
			} else {
				byte_token_type = byte_token_extended_ascii;
			}
			break;
		default:
			break;
		}

		new_token_type = byte_token_type_to_simple_tokenizer_token_type(byte_token_type);

		switch (token_type) {
		case simple_tokenizer_token_unknown:
			token_type = new_token_type;
			token_length = new_token_length;
			p_first_char = &string[index];
			index += (new_token_length - 1U); /* intended */
			break;
		case simple_tokenizer_token_letters:
		case simple_tokenizer_token_digits:
		case simple_tokenizer_token_spaces:
		case simple_tokenizer_token_zeros: /* fall through intended */
			if (new_token_type == token_type) {
				token_length += new_token_length;
			} else {
				add_token = Boolean_true;
			}
			break;
		case simple_tokenizer_token_punctuation:
		case simple_tokenizer_token_control_character:
		case simple_tokenizer_token_extended_ascii_character: /* fall through intended */
			assert(1U == token_length);
			add_token = Boolean_true;
			break;
		case simple_tokenizer_token_utf8_character:
			assert(token_length > 1U and token_length <= 4U);
			add_token = Boolean_true;
			break;
		case simple_tokenizer_token_newline:
			if (new_token_type == token_type) {
				if (token_length == 1U and *p_first_char == '\r' and byte == '\n') {
					token_length += new_token_length;
				} else {
					add_token = Boolean_true;
				}
			} else {
				add_token = Boolean_true;
			}
		default:
			break;
		}

		if (add_token) {
			if (ptokens != NULL and total_number_of_tokens < number_of_tokens) {
				const size_t token_index = total_number_of_tokens;
				ptokens[token_index].type = token_type;
				ptokens[token_index].value = string_to_const_stringref(p_first_char, token_length);
			}
			++total_number_of_tokens;
			token_type = new_token_type;
			token_length = new_token_length;
			p_first_char = &string[index];
			index += (new_token_length - 1U); /* intended */
		}
	}

	if (p_first_char != NULL) {
		if (ptokens != NULL and total_number_of_tokens < number_of_tokens) {
			const size_t token_index = total_number_of_tokens;
			ptokens[token_index].type = token_type;
			ptokens[token_index].value = string_to_const_stringref(p_first_char, token_length);
		}
		++total_number_of_tokens;
	}

	return total_number_of_tokens;
}

simple_tokenizer_utf8_char_type  simple_tokenizer_stringref_to_utf8_char(const_stringref_type utf8_char_stringref)
{
	simple_tokenizer_utf8_char_type utf8_char = {
		{0U}, 0U, 0U, simple_tokenizer_utf8_char_error_none
	};

	STATIC_ASSERT(sizeof(unsigned int) > 2U, "The size of an unsigned integer shall be greater than 2 bytes.");
	assert(utf8_char_stringref.string != NULL);
	assert(utf8_char_stringref.length >= 1U and utf8_char_stringref.length <= 4U);

	if (utf8_char_stringref.string == NULL or utf8_char_stringref.length < 1U) {
		utf8_char.error = simple_tokenizer_utf8_char_error_no_character;
	} else if (utf8_char_stringref.length > 4) {
		utf8_char.error = simple_tokenizer_utf8_char_error_more_than_4_bytes;
	}

	utf8_char.number_of_bytes = utf8_char_stringref.length;

	switch (utf8_char_stringref.length) {
	case 1U:
		{
			const unsigned int byte1 = (unsigned int) utf8_char_stringref.string[0];
			utf8_char.bytes[0] = (unsigned char) byte1;

			if (byte1 < 0x80U) {
				utf8_char.unicode_value = byte1;
			} else {
				utf8_char.error = simple_tokenizer_utf8_char_error_first_byte_incorrect;
			}
		}
		break;
	case 2U:
		{
			const unsigned int byte1 = (unsigned int) utf8_char_stringref.string[0];
			const unsigned int byte2 = (unsigned int) utf8_char_stringref.string[1];
			utf8_char.bytes[0] = (unsigned char) byte1;
			utf8_char.bytes[1] = (unsigned char) byte2;

			if ((byte1 & 0xE0U) == 0xC0U) {
				if ((byte2 & 0xC0U) == 0x80U) {
					utf8_char.unicode_value = (byte2 & 0x3FU) | ((byte1 & 0x1FU) << 6U);
				} else {
					utf8_char.error = simple_tokenizer_utf8_char_error_second_byte_incorrect;
				}
			} else {
				utf8_char.error = simple_tokenizer_utf8_char_error_first_byte_incorrect;
			}
		}
		break;
	case 3U:
		{
			const unsigned int byte1 = (unsigned int) utf8_char_stringref.string[0];
			const unsigned int byte2 = (unsigned int) utf8_char_stringref.string[1];
			const unsigned int byte3 = (unsigned int) utf8_char_stringref.string[2];
			utf8_char.bytes[0] = (unsigned char) byte1;
			utf8_char.bytes[1] = (unsigned char) byte2;
			utf8_char.bytes[2] = (unsigned char) byte3;

			if ((byte1 & 0xF0U) == 0xE0U) {
				if ((byte2 & 0xC0U) == 0x80U) {
					if ((byte3 & 0xC0U) == 0x80U)  {
						utf8_char.unicode_value = (byte3 & 0x3FU) | ((byte2 & 0x3FU) << 6U) | ((byte1 & 0x0FU) << 12U);
					} else {
						utf8_char.error = simple_tokenizer_utf8_char_error_third_byte_incorrect;
					}
				} else {
					utf8_char.error = simple_tokenizer_utf8_char_error_second_byte_incorrect;
				}
			} else {
				utf8_char.error = simple_tokenizer_utf8_char_error_first_byte_incorrect;
			}
		}
		break;
	case 4U:
		{
			const unsigned int byte1 = (unsigned int) utf8_char_stringref.string[0];
			const unsigned int byte2 = (unsigned int) utf8_char_stringref.string[1];
			const unsigned int byte3 = (unsigned int) utf8_char_stringref.string[2];
			const unsigned int byte4 = (unsigned int) utf8_char_stringref.string[3];
			utf8_char.bytes[0] = (unsigned char) byte1;
			utf8_char.bytes[1] = (unsigned char) byte2;
			utf8_char.bytes[2] = (unsigned char) byte3;
			utf8_char.bytes[3] = (unsigned char) byte4;

			if ((byte1 & 0xF8U) == 0xF0U) {
				if ((byte2 & 0xC0U) == 0x80U) {
					if ((byte3 & 0xC0U) == 0x80U) {
						if ((byte4 & 0xC0U) == 0x80U) {
							utf8_char.unicode_value = (byte4 & 0x3FU) | ((byte3 & 0x3FU) << 6U) |
										((byte2 & 0x3FU) << 12U) | ((byte1 & 0x07U) << 18U);
						} else {
							utf8_char.error = simple_tokenizer_utf8_char_error_fourth_byte_incorrect;
						}
					} else {
						utf8_char.error = simple_tokenizer_utf8_char_error_third_byte_incorrect;
					}
				} else {
					utf8_char.error = simple_tokenizer_utf8_char_error_second_byte_incorrect;
				}
			} else {
				utf8_char.error = simple_tokenizer_utf8_char_error_first_byte_incorrect;
			}
		}
		break;
	default:
		utf8_char.number_of_bytes = 1U;
		break;
	}

	if (utf8_char.unicode_value >= 0xD800U and utf8_char.unicode_value <= 0xDFFFU) {
		utf8_char.error = simple_tokenizer_utf8_char_error_unicode_value_is_surrogate_half;
	}

	return utf8_char;
}
