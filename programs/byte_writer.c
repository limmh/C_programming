#include "dynamic_array.h"
#include <errno.h>
#include <iso646.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint8_t hexadecimal_pair_to_byte(char upper_half_byte, char lower_half_byte)
{
	const char u = upper_half_byte;
	const bool u_is_digit = (u >= '0') and (u <= '9');
	const bool u_is_between_A_and_F = (u >= 'A') and (u <= 'F');
	const bool u_is_between_a_and_f = (u >= 'a') and (u <= 'f');
	const char l = lower_half_byte;
	const bool l_is_digit = (l >= '0') and (l <= '9');
	const bool l_is_between_A_and_F = (l >= 'A') and (l <= 'F');
	const bool l_is_between_a_and_f = (l >= 'a') and (l <= 'f');

	assert(u_is_digit or u_is_between_A_and_F or u_is_between_a_and_f);
	assert(l_is_digit or l_is_between_A_and_F or l_is_between_a_and_f);

	uint32_t u_value = 0U;
	if (u_is_digit) {
		u_value = (uint32_t)(u - '0');
	} else if (u_is_between_A_and_F) {
		u_value = (uint32_t)((u - 'A') + 10); 
	} else if (u_is_between_a_and_f) {
		u_value = (uint32_t)((u - 'a') + 10);
	}
	assert(u_value < 16U);

	uint32_t l_value = 0U;
	if (l_is_digit) {
		l_value = (uint32_t)(l - '0');
	} else if (l_is_between_A_and_F) {
		l_value = (uint32_t)((l - 'A') + 10);
	} else if (l_is_between_a_and_f) {
		l_value = (uint32_t)((l - 'a') + 10);
	}
	assert(l_value < 16U);

	return (uint8_t) ((u_value << 4U) | l_value);
}

static void insert_into_char_dynamic_array_if_not_found(dynamic_array_type(char) *p_dynarray, char c)
{
	dynamic_array_type(char) *p = p_dynarray;
	const size_t N = dynamic_array_size(*p);
	bool found = false;
	for (size_t i = 0U; i < N; ++i) {
		const char element = dynamic_array_element(char, *p, i);
		if (element == c) {
			found = true;
			break;
		}
	}

	if (!found) {
		dynamic_array_append_element(char, *p, c);
	}
}

static dynamic_array_type(char)
get_string_from_input(void)
{
	dynamic_array_type(char) array = dynamic_array_create(char, 0U);
	int c = fgetc(stdin);
	while (c != '\n' and c != EOF) {
		dynamic_array_append_element(char, array, c);
		c = fgetc(stdin);
	}
	dynamic_array_append_element(char, array, '\0');
	return array;
}

int main(int argc, char **argv)
{
	dynamic_array_type(char) hexadecimal_characters = dynamic_array_create(char, 0U);
	dynamic_array_type(char) invalid_characters = dynamic_array_create(char, 0U);

	for (int i = 1; i < argc; ++i) {
		const size_t length = strlen(argv[i]);
		for (size_t n = 0U; n < length; ++n) {
			const char c = argv[i][n];
			if ((c >= '0' and c <= '9') or (c >= 'A' and c <= 'F') or (c >= 'a' and c <= 'f')) {
				dynamic_array_append_element(char, hexadecimal_characters, c);
			} else if (c == ' ' or c == '\t' or c == '\r' or c == '\n') {
				continue;
			} else {
				insert_into_char_dynamic_array_if_not_found(&invalid_characters, c);
			}
		}
	}

	const size_t number_of_invalid_characters = dynamic_array_size(invalid_characters);
	if (number_of_invalid_characters > 1U) {
		for (size_t i = 0U; i < number_of_invalid_characters; ++i) {
			const char c = dynamic_array_element(char, invalid_characters, i);
			if (i == 0U) {
				printf("%c", c);
			} else if (i < (number_of_invalid_characters - 1U)) {
				printf(", %c", c);
			} else {
				printf(" and %c", c);
			}
		}
		printf(" are not valid hexadecimal characters.\n");
	} else if (number_of_invalid_characters == 1U) {
		const char c = dynamic_array_element(char, invalid_characters, 0U);
		printf("%c is not a valid hexadecimal character.\n", (int)c);
	}

	int error_code = 0;
	if (number_of_invalid_characters == 0U) {
		const size_t number_of_hexadecimal_characters = dynamic_array_size(hexadecimal_characters);
		if (number_of_hexadecimal_characters == 0U) {
			printf("There are no bytes to write.\n");
		} else if ((number_of_hexadecimal_characters % 2) != 0) {
			const size_t n = number_of_hexadecimal_characters;
			error_code = 2;
			printf("There %s %lu hexadecimal character%s. There must be an even number of characters.\n",
				((n > 1U) ? "are" : "is"),(unsigned long) n, ((n > 1U) ? "s" : ""));
		} else {
			const size_t N = number_of_hexadecimal_characters / 2U;
			dynamic_array_type(uint8_t) bytes = dynamic_array_create(uint8_t, 0U);

			for (size_t i = 0U; i < N; ++i) {
				const size_t index1 = 2U * i;
				const size_t index2 = 2U * i + 1U;
				const char upper_half = dynamic_array_element(char, hexadecimal_characters, index1);
				const char lower_half = dynamic_array_element(char, hexadecimal_characters, index2);
				const uint8_t byte = hexadecimal_pair_to_byte(upper_half, lower_half);
				dynamic_array_append_element(uint8_t, bytes, byte);
			}

			printf("Enter a file name or path: ");
			dynamic_array_type(char) input_string = get_string_from_input();

			FILE *file = fopen(&dynamic_array_element(char, input_string, 0U), "wb");
			if (file != NULL) {
				const uint8_t *data = &dynamic_array_element(uint8_t, bytes, 0U);
				const size_t number_of_bytes_to_write = dynamic_array_length(bytes);
				const size_t number_of_bytes_written =
					fwrite(data, sizeof(data[0]), number_of_bytes_to_write, file);
				printf("Number of bytes to write: %lu\n", (unsigned long) number_of_bytes_to_write);
				printf("Number of bytes written: %lu\n", (unsigned long) number_of_bytes_to_write);
				if (number_of_bytes_written == number_of_bytes_to_write) {
					printf("OK\n");
				} else {
					error_code = 4;
					printf("NOT OK\n");
				}
				fclose(file);
			} else {
				error_code = 3;
				printf("Error: %s\n", strerror(errno));
			}

			dynamic_array_delete(input_string);
			dynamic_array_delete(bytes);
		}
	} else {
		error_code = 1;
	}

	dynamic_array_delete(invalid_characters);
	dynamic_array_delete(hexadecimal_characters);
	return error_code;
}
