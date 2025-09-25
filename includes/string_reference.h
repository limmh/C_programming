#ifndef STRING_REFERENCE_H
#define STRING_REFERENCE_H

#include "Boolean_type.h"
#include "inline_or_static.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
String reference: a data structure that can reference part of a string or the whole string
The life time of the underlying string must be longer than the reference itself
*/

/* string content is mutable */
typedef struct stringref_type
{
	char *string;
	size_t length;
} stringref_type;

/* string content is not mutable */
typedef struct const_stringref_type
{
	const char *string;
	size_t length;
} const_stringref_type;

INLINE_OR_STATIC const_stringref_type  stringref_to_const_stringref(stringref_type stringref)
{
	const_stringref_type const_stringref = {NULL, 0U};
	const_stringref.string = stringref.string;
	const_stringref.length = stringref.length;
	return const_stringref;
}

INLINE_OR_STATIC Boolean_type stringref_is_valid(stringref_type stringref)
{
	return (stringref.string != NULL);
}

INLINE_OR_STATIC Boolean_type const_stringref_is_valid(const_stringref_type const_stringref)
{
	return (const_stringref.string != NULL);
}

INLINE_OR_STATIC stringref_type  string_to_stringref(char *string, size_t length)
{
	stringref_type stringref = {NULL, 0U};
	stringref.string = string;
	stringref.length = length;
	return stringref;
}

INLINE_OR_STATIC const_stringref_type  string_to_const_stringref(const char *string, size_t length)
{
	const_stringref_type const_stringref = {NULL, 0U};
	const_stringref.string = string;
	const_stringref.length = length;
	return const_stringref;
}

INLINE_OR_STATIC void const_stringref_to_string(const_stringref_type stringref, char *buffer, size_t buffer_size)
{
	assert(stringref.string != NULL);
	assert(buffer != NULL);
	if (stringref.string != NULL && buffer != NULL && buffer_size > 0U) {
		const size_t number_of_bytes = buffer_size - 1U;
		const size_t number_of_bytes_to_copy = (stringref.length <= number_of_bytes) ? stringref.length : number_of_bytes;
		const size_t index_of_last_byte = number_of_bytes_to_copy;
		memcpy(buffer, stringref.string, number_of_bytes_to_copy);
		buffer[index_of_last_byte] = '\0'; 
	}
}

INLINE_OR_STATIC void stringref_to_string(stringref_type stringref, char *buffer, size_t buffer_size)
{
	const_stringref_to_string(stringref_to_const_stringref(stringref), buffer, buffer_size);
}

#ifdef __cplusplus
}
#endif

#endif
