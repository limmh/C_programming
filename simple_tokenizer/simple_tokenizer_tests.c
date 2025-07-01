#include "simple_tokenizer.h"
#include "sizeof_array.h"
#include "unit_testing.h"
#include <string.h>

TEST(test_with_empty_string, "Empty string => no token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize("", 0U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 0U);
	number_of_tokens = simple_tokenizer_tokenize("", 0U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 0U);
}

TEST(test_with_only_spaces, "Only spaces => 1 token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize(" ", 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize(" ", 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length)
		ASSERT_EQUAL(token.value.string[0], ' ');

	number_of_tokens = simple_tokenizer_tokenize("  ", 2U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("  ", 2U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 2U);
	if (2U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], ' ');
		ASSERT_EQUAL(token.value.string[1], ' ');
	}

	number_of_tokens = simple_tokenizer_tokenize("   ", 3U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("   ", 3U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 3U);
	if (3U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], ' ');
		ASSERT_EQUAL(token.value.string[1], ' ');
		ASSERT_EQUAL(token.value.string[2], ' ');
	}
}

TEST(test_with_only_tabs, "Only tabs => 1 token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize("\t", 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("\t", 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length)
		ASSERT_EQUAL(token.value.string[0], '\t');

	number_of_tokens = simple_tokenizer_tokenize("\t\t", 2U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("\t\t", 2U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 2U);
	if (2U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], '\t');
		ASSERT_EQUAL(token.value.string[1], '\t');
	}

	number_of_tokens = simple_tokenizer_tokenize("\t\t\t", 3U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("\t\t\t", 3U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 3U);
	if (3U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], '\t');
		ASSERT_EQUAL(token.value.string[1], '\t');
		ASSERT_EQUAL(token.value.string[2], '\t');
	}
}

TEST(test_with_spaces_and_tabs, "Spaces and tabs => 1 token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize("\t ", 2U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("\t ", 2U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 2U);
	if (2U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], '\t');
		ASSERT_EQUAL(token.value.string[1], ' ');
	}

	number_of_tokens = simple_tokenizer_tokenize(" \t \t", 4U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize(" \t \t", 4U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(token.value.length, 4U);
	if (4U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], ' ');
		ASSERT_EQUAL(token.value.string[1], '\t');
		ASSERT_EQUAL(token.value.string[2], ' ');
		ASSERT_EQUAL(token.value.string[3], '\t');
	}
}

TEST(test_with_only_English_letters, "Only English letters => 1 token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize("a", 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("a", 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length)
		ASSERT_EQUAL(token.value.string[0], 'a');

	number_of_tokens = simple_tokenizer_tokenize("abc", 3U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("abc", 3U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(token.value.length, 3U);
	if (3U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], 'a');
		ASSERT_EQUAL(token.value.string[1], 'b');
		ASSERT_EQUAL(token.value.string[2], 'c');
	}

	number_of_tokens = simple_tokenizer_tokenize("ABC", 3U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("ABC", 3U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(token.value.length, 3U);
	if (3U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], 'A');
		ASSERT_EQUAL(token.value.string[1], 'B');
		ASSERT_EQUAL(token.value.string[2], 'C');
	}
}

TEST(test_with_two_words_separated_by_space, "Two words separated by a space => 3 tokens")
{
	const char *text = "Hello World";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[3] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(text, strlen(text), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	number_of_tokens = simple_tokenizer_tokenize(text, strlen(text), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);

	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 5U);
	if (5U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "Hello", 5U), 0);

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(tokens[1].value.string[0], ' ');

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 5U);
	if (5U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "World", 5U), 0);
}

TEST(test_with_multiple_words_separated_by_spaces, "Multiple words separated by spaces => multiple tokens")
{
	const char *text = "The quick brown fox jumps over the lazy dog";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[17] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(text, strlen(text), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 17U);
	number_of_tokens = simple_tokenizer_tokenize(text, strlen(text), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 17U);

	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 3U);
	if (3U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "The", 3U), 0);

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 5U);
	if (5U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "quick", 5U), 0);

	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 1U);
	if (1U == tokens[3].value.length)
		ASSERT_EQUAL(memcmp(tokens[3].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 5U);
	if (5U == tokens[4].value.length)
		ASSERT_EQUAL(memcmp(tokens[4].value.string, "brown", 5U), 0);

	ASSERT_EQUAL(tokens[5].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[5].value.length, 1U);
	if (1U == tokens[5].value.length)
		ASSERT_EQUAL(memcmp(tokens[5].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[6].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[6].value.length, 3U);
	if (3U == tokens[6].value.length)
		ASSERT_EQUAL(memcmp(tokens[6].value.string, "fox", 3U), 0);

	ASSERT_EQUAL(tokens[7].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[7].value.length, 1U);
	if (1U == tokens[7].value.length)
		ASSERT_EQUAL(memcmp(tokens[7].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[8].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[8].value.length, 5U);
	if (5U == tokens[8].value.length)
		ASSERT_EQUAL(memcmp(tokens[8].value.string, "jumps", 5U), 0);

	ASSERT_EQUAL(tokens[9].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[9].value.length, 1U);
	if (1U == tokens[9].value.length)
		ASSERT_EQUAL(memcmp(tokens[9].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[10].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[10].value.length, 4U);
	if (4U == tokens[10].value.length)
		ASSERT_EQUAL(memcmp(tokens[10].value.string, "over", 4U), 0);

	ASSERT_EQUAL(tokens[11].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[11].value.length, 1U);
	if (1U == tokens[11].value.length)
		ASSERT_EQUAL(memcmp(tokens[11].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[12].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[12].value.length, 3U);
	if (3U == tokens[12].value.length)
		ASSERT_EQUAL(memcmp(tokens[12].value.string, "the", 3U), 0);

	ASSERT_EQUAL(tokens[13].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[13].value.length, 1U);
	if (1U == tokens[13].value.length)
		ASSERT_EQUAL(memcmp(tokens[13].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[14].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[14].value.length, 4U);
	if (4U == tokens[14].value.length)
		ASSERT_EQUAL(memcmp(tokens[14].value.string, "lazy", 4U), 0);

	ASSERT_EQUAL(tokens[15].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[15].value.length, 1U);
	if (1U == tokens[15].value.length)
		ASSERT_EQUAL(memcmp(tokens[15].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[16].type, simple_tokenizer_token_letters);
	ASSERT_UINT_EQUAL(tokens[16].value.length, 3U);
	if (3U == tokens[16].value.length)
		ASSERT_EQUAL(memcmp(tokens[16].value.string, "dog", 3U), 0);
}

TEST(test_with_only_digits, "Only digits => 1 token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize("0", 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("0", 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length)
		ASSERT_EQUAL(token.value.string[0], '0');

	number_of_tokens = simple_tokenizer_tokenize("123", 3U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("123", 3U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(token.value.length, 3U);
	if (3U == token.value.length) {
		ASSERT_EQUAL(token.value.string[0], '1');
		ASSERT_EQUAL(token.value.string[1], '2');
		ASSERT_EQUAL(token.value.string[2], '3');
	}

	number_of_tokens = simple_tokenizer_tokenize("0123456789", 10U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize("0123456789", 10U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(token.value.length, 10U);
	if (10U == token.value.length)
		ASSERT_EQUAL(memcmp(token.value.string, "0123456789", 10U), 0);
}

TEST(test_with_only_a_single_punctuation_character, "A single punctuation character => 1 token")
{
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize(".", 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize(".", 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length)
		ASSERT_EQUAL(token.value.string[0], '.');

	number_of_tokens = simple_tokenizer_tokenize(",", 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize(",", 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_punctuation);
	if (1U == token.value.length)
		ASSERT_EQUAL(token.value.string[0], ',');
}

TEST(test_with_multiple_punctuation_characters, "Multiple punctuation characters => a token for each punctuation character")
{
	const char *punctuation_characters = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[32] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(punctuation_characters,
						strlen(punctuation_characters), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 32U);
	number_of_tokens = simple_tokenizer_tokenize(punctuation_characters,
						strlen(punctuation_characters), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 32U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(tokens[0].value.string[0], '!');

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(tokens[1].value.string[0], '"');

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(tokens[2].value.string[0], '#');

	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 1U);
	if (1U == tokens[3].value.length)
		ASSERT_EQUAL(tokens[3].value.string[0], '$');

	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 1U);
	if (1U == tokens[4].value.length)
		ASSERT_EQUAL(tokens[4].value.string[0], '%');

	ASSERT_EQUAL(tokens[5].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[5].value.length, 1U);
	if (1U == tokens[5].value.length)
		ASSERT_EQUAL(tokens[5].value.string[0], '&');

	ASSERT_EQUAL(tokens[6].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[6].value.length, 1U);
	if (1U == tokens[6].value.length)
		ASSERT_EQUAL(tokens[6].value.string[0], '\'');

	ASSERT_EQUAL(tokens[7].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[7].value.length, 1U);
	if (1U == tokens[7].value.length)
		ASSERT_EQUAL(tokens[7].value.string[0], '(');

	ASSERT_EQUAL(tokens[8].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[8].value.length, 1U);
	if (1U == tokens[8].value.length)
		ASSERT_EQUAL(tokens[8].value.string[0], ')');

	ASSERT_EQUAL(tokens[9].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[9].value.length, 1U);
	if (1U == tokens[9].value.length)
		ASSERT_EQUAL(tokens[9].value.string[0], '*');

	ASSERT_EQUAL(tokens[10].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[10].value.length, 1U);
	if (1U == tokens[10].value.length)
		ASSERT_EQUAL(tokens[10].value.string[0], '+');

	ASSERT_EQUAL(tokens[11].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[11].value.length, 1U);
	if (1U == tokens[11].value.length)
		ASSERT_EQUAL(tokens[11].value.string[0], ',');

	ASSERT_EQUAL(tokens[12].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[12].value.length, 1U);
	if (1U == tokens[12].value.length)
		ASSERT_EQUAL(tokens[12].value.string[0], '-');

	ASSERT_EQUAL(tokens[13].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[13].value.length, 1U);
	if (1U == tokens[13].value.length)
		ASSERT_EQUAL(tokens[13].value.string[0], '.');

	ASSERT_EQUAL(tokens[14].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[14].value.length, 1U);
	if (1U == tokens[14].value.length)
		ASSERT_EQUAL(tokens[14].value.string[0], '/');

	ASSERT_EQUAL(tokens[15].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[15].value.length, 1U);
	if (1U == tokens[15].value.length)
		ASSERT_EQUAL(tokens[15].value.string[0], ':');

	ASSERT_EQUAL(tokens[16].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[16].value.length, 1U);
	if (1U == tokens[16].value.length)
		ASSERT_EQUAL(tokens[16].value.string[0], ';');

	ASSERT_EQUAL(tokens[17].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[17].value.length, 1U);
	if (1U == tokens[17].value.length)
		ASSERT_EQUAL(tokens[17].value.string[0], '<');

	ASSERT_EQUAL(tokens[18].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[18].value.length, 1U);
	if (1U == tokens[18].value.length)
		ASSERT_EQUAL(tokens[18].value.string[0], '=');

	ASSERT_EQUAL(tokens[19].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[19].value.length, 1U);
	if (1U == tokens[19].value.length)
		ASSERT_EQUAL(tokens[19].value.string[0], '>');

	ASSERT_EQUAL(tokens[20].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[20].value.length, 1U);
	if (1U == tokens[20].value.length)
		ASSERT_EQUAL(tokens[20].value.string[0], '?');

	ASSERT_EQUAL(tokens[21].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[21].value.length, 1U);
	if (1U == tokens[21].value.length)
		ASSERT_EQUAL(tokens[21].value.string[0], '@');

	ASSERT_EQUAL(tokens[22].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[22].value.length, 1U);
	if (1U == tokens[22].value.length)
		ASSERT_EQUAL(tokens[22].value.string[0], '[');

	ASSERT_EQUAL(tokens[23].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[23].value.length, 1U);
	if (1U == tokens[23].value.length)
		ASSERT_EQUAL(tokens[23].value.string[0], '\\');

	ASSERT_EQUAL(tokens[24].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[24].value.length, 1U);
	if (1U == tokens[24].value.length)
		ASSERT_EQUAL(tokens[24].value.string[0], ']');

	ASSERT_EQUAL(tokens[25].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[25].value.length, 1U);
	if (1U == tokens[25].value.length)
		ASSERT_EQUAL(tokens[25].value.string[0], '^');

	ASSERT_EQUAL(tokens[26].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[26].value.length, 1U);
	if (1U == tokens[26].value.length)
		ASSERT_EQUAL(tokens[26].value.string[0], '_');

	ASSERT_EQUAL(tokens[27].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[27].value.length, 1U);
	if (1U == tokens[27].value.length)
		ASSERT_EQUAL(tokens[27].value.string[0], '`');

	ASSERT_EQUAL(tokens[28].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[28].value.length, 1U);
	if (1U == tokens[28].value.length)
		ASSERT_EQUAL(tokens[28].value.string[0], '{');

	ASSERT_EQUAL(tokens[29].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[29].value.length, 1U);
	if (1U == tokens[29].value.length)
		ASSERT_EQUAL(tokens[29].value.string[0], '|');

	ASSERT_EQUAL(tokens[30].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[30].value.length, 1U);
	if (1U == tokens[30].value.length)
		ASSERT_EQUAL(tokens[30].value.string[0], '}');

	ASSERT_EQUAL(tokens[31].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[31].value.length, 1U);
	if (1U == tokens[31].value.length)
		ASSERT_EQUAL(tokens[31].value.string[0], '~');
}

TEST(test_with_simple_arithmetic_expression_1, "A simple arithmetic expression => multiple tokens")
{
	const char *expression = "10 + 10";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[5] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);
	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);

	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 2U);
	if (2U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "10", 2U), 0);

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "+", 1U), 0);

	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 1U);
	if (1U == tokens[3].value.length)
		ASSERT_EQUAL(memcmp(tokens[3].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 2U);
	if (2U == tokens[4].value.length)
		ASSERT_EQUAL(memcmp(tokens[4].value.string, "10", 2U), 0);
}

TEST(test_with_simple_arithmetic_expression_2, "A simple arithmetic expression => multiple tokens")
{
	const char *expression = "2 - 1";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[5] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);
	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);

	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "2", 1U), 0);

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "-", 1U), 0);

	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 1U);
	if (1U == tokens[3].value.length)
		ASSERT_EQUAL(memcmp(tokens[3].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 1U);
	if (1U == tokens[4].value.length)
		ASSERT_EQUAL(memcmp(tokens[4].value.string, "1", 1U), 0);
}

TEST(test_with_simple_arithmetic_expression_3, "A simple arithmetic expression => multiple tokens")
{
	const char *expression = "1 * 1";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[5] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);
	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);

	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "1", 1U), 0);

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "*", 1U), 0);

	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 1U);
	if (1U == tokens[3].value.length)
		ASSERT_EQUAL(memcmp(tokens[3].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 1U);
	if (1U == tokens[4].value.length)
		ASSERT_EQUAL(memcmp(tokens[4].value.string, "1", 1U), 0);
}

TEST(test_with_simple_arithmetic_expression_4, "A simple arithmetic expression => multiple tokens")
{
	const char *expression = "1 / 1";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[5] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);
	number_of_tokens = simple_tokenizer_tokenize(expression, strlen(expression), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 5U);

	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "1", 1U), 0);

	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_punctuation);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "/", 1U), 0);

	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_spaces);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 1U);
	if (1U == tokens[3].value.length)
		ASSERT_EQUAL(memcmp(tokens[3].value.string, " ", 1U), 0);

	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_digits);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 1U);
	if (1U == tokens[4].value.length)
		ASSERT_EQUAL(memcmp(tokens[4].value.string, "1", 1U), 0);
}

TEST(test_with_newlines, "Multiple newline characters together => a token for each newline character")
{
	const char *newlines = "";
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[3] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	newlines = "\n\n\n";
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "\n", 1U), 0);
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, "\n", 1U), 0);
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "\n", 1U), 0);

	newlines = "\r\r\r";
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "\r", 1U), 0);
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, "\r", 1U), 0);
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "\r", 1U), 0);

	newlines = "\r\n\r\n\r\n";
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 2U);
	if (2U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "\r\n", 2U), 0);
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 2U);
	if (2U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, "\r\n", 2U), 0);
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 2U);
	if (2U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "\r\n", 2U), 0);

	newlines = "\r\r\n\n";
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	number_of_tokens = simple_tokenizer_tokenize(newlines, strlen(newlines), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL(memcmp(tokens[0].value.string, "\r", 1U), 0);
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 2U);
	if (2U == tokens[1].value.length)
		ASSERT_EQUAL(memcmp(tokens[1].value.string, "\r\n", 2U), 0);
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_newline);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL(memcmp(tokens[2].value.string, "\n", 1U), 0);

}

TEST(test_with_single_extended_ASCII_character, "An extended ASCII character => 1 token")
{
	unsigned char extended_ascii = 128U;
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type token = {simple_tokenizer_token_unknown, {NULL, 0U}};

	number_of_tokens = simple_tokenizer_tokenize((const char*) &extended_ascii, 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize((const char*) &extended_ascii, 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_extended_ascii_character);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length) {
		ASSERT_EQUAL((unsigned char)token.value.string[0], 128);
	}

	extended_ascii = 255U;
	number_of_tokens = simple_tokenizer_tokenize((const char*) &extended_ascii, 1U, NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	number_of_tokens = simple_tokenizer_tokenize((const char*) &extended_ascii, 1U, &token, 1U);
	ASSERT_UINT_EQUAL(number_of_tokens, 1U);
	ASSERT_EQUAL(token.type, simple_tokenizer_token_extended_ascii_character);
	ASSERT_UINT_EQUAL(token.value.length, 1U);
	if (1U == token.value.length) {
		ASSERT_EQUAL((unsigned char)token.value.string[0], 255);
	}
}

TEST(test_with_multiple_extended_ASCII_characters,
	"Multiple extended ASCII characters (with no multibyte UTF-8 characters) => 1 token for each character")
{
	unsigned char extended_ascii_characters[] = {128U, 191U, 255U};
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[3] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize((const char*) extended_ascii_characters,
				sizeof_array(extended_ascii_characters), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	number_of_tokens = simple_tokenizer_tokenize((const char*) extended_ascii_characters,
				sizeof_array(extended_ascii_characters), tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 3U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_extended_ascii_character);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 1U);
	if (1U == tokens[0].value.length)
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[0], 128);
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_extended_ascii_character);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 1U);
	if (1U == tokens[1].value.length)
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[0], 191);
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_extended_ascii_character);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 1U);
	if (1U == tokens[2].value.length)
		ASSERT_EQUAL((unsigned char)tokens[2].value.string[0], 255);
}

TEST(test_with_two_byte_utf8_characters, "Two-byte UTF-8 characters => 1 token for each UTF-8 character")
{
	const unsigned char utf8_characters[] = {
		0xC3U, 0x84U, /* umlauted A */
		0xC3U, 0xA4U, /* umlauted a */
		0xC3U, 0x96U, /* umlauted O */
		0xC3U, 0xB6U, /* umlauted o */
		0xC3U, 0x9CU, /* umlauted U */
		0xC3U, 0xBCU, /* umlauted u */
		0xC3U, 0x9FU  /* ss */
	};
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[7] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize((const char*) utf8_characters, sizeof_array(utf8_characters), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 7U);
	number_of_tokens = simple_tokenizer_tokenize((const char*) utf8_characters, sizeof_array(utf8_characters),
				tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 7U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 2U);
	if (2U == tokens[0].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[1], 0x84);
	}
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 2U);
	if (2U == tokens[1].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[1], 0xA4);
	}
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 2U);
	if (2U == tokens[2].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[2].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[2].value.string[1], 0x96);
	}
	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 2U);
	if (2U == tokens[3].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[3].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[3].value.string[1], 0xB6);
	}
	ASSERT_EQUAL(tokens[4].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[4].value.length, 2U);
	if (2U == tokens[4].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[4].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[4].value.string[1], 0x9C);
	}
	ASSERT_EQUAL(tokens[5].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[5].value.length, 2U);
	if (2U == tokens[5].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[5].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[5].value.string[1], 0xBC);
	}
	ASSERT_EQUAL(tokens[6].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[6].value.length, 2U);
	if (2U == tokens[6].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[6].value.string[0], 0xC3);
		ASSERT_EQUAL((unsigned char)tokens[6].value.string[1], 0x9F);
	}
}

TEST(test_with_three_byte_utf8_characters, "Three-byte UTF-8 characters => 1 token for each UTF-8 character")
{
	const unsigned char utf8_characters[] = {
		0xE4U, 0xBDU, 0xA0U,
		0xE5U, 0xA5U, 0xBDU,
		0xE5U, 0x90U, 0x97U,
		0xEFU, 0xBCU, 0x9FU
	};
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[4] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize((const char*) utf8_characters, sizeof_array(utf8_characters), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 4U);
	number_of_tokens = simple_tokenizer_tokenize((const char*) utf8_characters, sizeof_array(utf8_characters),
				tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 4U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 3U);
	if (3U == tokens[0].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[0], 0xE4);
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[1], 0xBD);
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[2], 0xA0);
	}
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 3U);
	if (3U == tokens[1].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[0], 0xE5);
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[1], 0xA5);
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[2], 0xBD);
	}
	ASSERT_EQUAL(tokens[2].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[2].value.length, 3U);
	if (3U == tokens[2].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[2].value.string[0], 0xE5);
		ASSERT_EQUAL((unsigned char)tokens[2].value.string[1], 0x90);
		ASSERT_EQUAL((unsigned char)tokens[2].value.string[2], 0x97);
	}
	ASSERT_EQUAL(tokens[3].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[3].value.length, 3U);
	if (3U == tokens[3].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[3].value.string[0], 0xEF);
		ASSERT_EQUAL((unsigned char)tokens[3].value.string[1], 0xBC);
		ASSERT_EQUAL((unsigned char)tokens[3].value.string[2], 0x9F);
	}
}

TEST(test_with_four_byte_utf8_characters, "Four-byte UTF-8 characters => 1 token for each UTF-8 character")
{
	const unsigned char utf8_characters[] = {
		0xF0U, 0x9FU, 0x98U, 0x80U,
		0xF0U, 0x9FU, 0x90U, 0xB1U
	};
	size_t number_of_tokens = 0U;
	simple_tokenizer_token_type tokens[2] = {
		{simple_tokenizer_token_unknown, {NULL, 0U}}
	};

	number_of_tokens = simple_tokenizer_tokenize((const char*) utf8_characters, sizeof_array(utf8_characters), NULL, 0U);
	ASSERT_UINT_EQUAL(number_of_tokens, 2U);
	number_of_tokens = simple_tokenizer_tokenize((const char*) utf8_characters, sizeof_array(utf8_characters),
				tokens, sizeof_array(tokens));
	ASSERT_UINT_EQUAL(number_of_tokens, 2U);
	ASSERT_EQUAL(tokens[0].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[0].value.length, 4U);
	if (4U == tokens[0].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[0], 0xF0);
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[1], 0x9F);
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[2], 0x98);
		ASSERT_EQUAL((unsigned char)tokens[0].value.string[3], 0x80);
	}
	ASSERT_EQUAL(tokens[1].type, simple_tokenizer_token_utf8_character);
	ASSERT_UINT_EQUAL(tokens[1].value.length, 4U);
	if (4U == tokens[1].value.length) {
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[0], 0xF0);
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[1], 0x9F);
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[2], 0x90);
		ASSERT_EQUAL((unsigned char)tokens[1].value.string[3], 0xB1);
	}
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		test_with_empty_string,
		test_with_only_spaces,
		test_with_only_tabs,
		test_with_spaces_and_tabs,
		test_with_only_English_letters,
		test_with_two_words_separated_by_space,
		test_with_multiple_words_separated_by_spaces,
		test_with_only_digits,
		test_with_only_a_single_punctuation_character,
		test_with_multiple_punctuation_characters,
		test_with_simple_arithmetic_expression_1,
		test_with_simple_arithmetic_expression_2,
		test_with_simple_arithmetic_expression_3,
		test_with_simple_arithmetic_expression_4,
		test_with_newlines,
		test_with_single_extended_ASCII_character,
		test_with_multiple_extended_ASCII_characters,
		test_with_two_byte_utf8_characters,
		test_with_three_byte_utf8_characters,
		test_with_four_byte_utf8_characters
	};

	SET_OUTPUT_FILE(stdout);
	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);
	return 0;
}
