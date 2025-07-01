#ifndef SIMPLE_TOKENIZER_H
#define SIMPLE_TOKENIZER_H

#include "string_reference.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum simple_tokenizer_token_type_enum
{
	simple_tokenizer_token_unknown = 0,
	simple_tokenizer_token_letters,
	simple_tokenizer_token_digits,
	simple_tokenizer_token_punctuation,
	simple_tokenizer_token_spaces,
	simple_tokenizer_token_newline,
	simple_tokenizer_token_zeros,
	simple_tokenizer_token_control_character,
	simple_tokenizer_token_extended_ascii_character,
	simple_tokenizer_token_utf8_character
} simple_tokenizer_token_type_enum;

typedef struct simple_tokenizer_token_type
{
	simple_tokenizer_token_type_enum type;
	const_stringref_type value;
} simple_tokenizer_token_type;

typedef enum simple_tokenizer_utf8_char_error_type
{
	simple_tokenizer_utf8_char_error_none = 0,
	simple_tokenizer_utf8_char_error_no_character = 1,
	simple_tokenizer_utf8_char_error_more_than_4_bytes,
	simple_tokenizer_utf8_char_error_first_byte_incorrect,
	simple_tokenizer_utf8_char_error_second_byte_incorrect,
	simple_tokenizer_utf8_char_error_third_byte_incorrect,
	simple_tokenizer_utf8_char_error_fourth_byte_incorrect,
	simple_tokenizer_utf8_char_error_unicode_value_is_surrogate_half
} simple_tokenizer_utf8_char_error_type;

typedef struct simple_tokenizer_utf8_char_type
{
	unsigned char bytes[4];
	unsigned int number_of_bytes;
	unsigned int unicode_value;
	simple_tokenizer_utf8_char_error_type error;
} simple_tokenizer_utf8_char_type;

const char *simple_tokenizer_token_type_name(simple_tokenizer_token_type_enum token_type);

size_t simple_tokenizer_tokenize(const char *string, size_t string_length, simple_tokenizer_token_type *ptokens, size_t number_of_tokens);

simple_tokenizer_utf8_char_type  simple_tokenizer_stringref_to_utf8_char(const_stringref_type utf8_char_stringref);

#ifdef __cplusplus
}
#endif

#endif
