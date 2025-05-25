#include "dynamic_array.h"
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This program opens a list of files and print their contents as binary data and ASCII characters

static size_t get_file_size(FILE* file)
{
	assert(file != NULL);
	size_t size = 0U;
	const long current_position = ftell(file);
	if (current_position >= 0) {
		const long offset = 0;
		const int error_code = fseek(file, offset, SEEK_END);
		if (error_code == 0) {
			const long new_pos = ftell(file);
			if (new_pos >= 0) {
				size = (size_t) new_pos;
			}
		}
		fseek(file, current_position, SEEK_SET);
	}
	return size;
}

static void print_binary_data(FILE *file, const unsigned char* data, size_t number_of_bytes)
{
	const size_t bytes_per_line = 32U;
	const size_t number_of_lines = number_of_bytes / bytes_per_line;
	const size_t remaining_bytes = number_of_bytes % bytes_per_line;

	for (size_t i = 0U; i < number_of_lines; ++i) {
		const size_t offset = i * bytes_per_line;
		for (size_t j = 0U; j < bytes_per_line; ++j) {
			const size_t index = offset + j;
			fprintf(file, "%02X ", data[index]);
		}
		fprintf(file, "   ");
		for (size_t j = 0U; j < bytes_per_line; ++j) {
			const size_t index = offset + j;
			unsigned char c = data[index];
			if (isspace(c)) {
				c = ' ';
			} else if (!isprint(c)) {
				c = '?';
			}
			fputc(c, file);
		}
		if ((i + 1) < number_of_lines || remaining_bytes > 0U)
			fputc('\n', file);
	}

	if (remaining_bytes > 0U) {
		const size_t offset = bytes_per_line * number_of_lines;
		for (size_t i = 0U; i < remaining_bytes; ++i) {
			const size_t index = offset + i;
			fprintf(file, "%02X ", data[index]);
		}
		for (size_t i = remaining_bytes; i < bytes_per_line; ++i) {
			fprintf(file, "   ");
		}
		fprintf(file, "   ");
		for (size_t i = 0U; i < remaining_bytes; ++i) {
			const size_t index = offset + i;
			unsigned char c = data[index];
			if (isspace(c)) {
				c = ' ';
			}
			else if (!isprint(c)) {
				c = '?';
			}
			fputc(c, file);
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s <file> [additional files]\n", argv[0]);
		return 0;
	}

	dynamic_array_type(unsigned char) bytes = dynamic_array_create(unsigned char, 8U);
	for (int i = 1; i < argc; ++i) {
		errno = 0;
		size_t file_size = 0U;
		FILE *fp = fopen(argv[i], "rb");
		if (fp != NULL) {
			file_size = get_file_size(fp);
			dynamic_array_resize(unsigned char, bytes, file_size);
			fread(&dynamic_array_element(unsigned char, bytes, 0U), sizeof(dynamic_array_element(unsigned char, bytes, 0U)),
				dynamic_array_size(bytes), fp);
			fclose(fp);
			fp = NULL;
		} else {
			const int error_code = errno;
			printf("%s: %s\n", argv[i], ((error_code != 0) ? strerror(error_code) : "Cannot open file."));
		}
		printf("%s: %lu byte%s\n", argv[i], (unsigned long)(file_size), ((file_size > 1U) ? "s" : ""));
		print_binary_data(stdout, &dynamic_array_element(unsigned char, bytes, 0U), dynamic_array_size(bytes));
		printf("\n");
	}
	dynamic_array_delete(bytes);
	return 0;
}
