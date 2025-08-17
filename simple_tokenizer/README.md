# simple_tokenizer

A simple, extensible tokenizer for ASCII and UTF-8 text in C.

## Overview

This library provides a tokenizer utility for classifying and extracting tokens (letters, digits, punctuation, spaces, control characters, UTF-8 characters, etc.) from strings.
It also includes utilities for decoding UTF-8 characters with error detection.

## Features

- Recognizes a wide range of token types: letters, digits, punctuation, spaces, newlines, zeros, control chars, extended ASCII, UTF-8, etc.
- Decodes UTF-8 characters and reports detailed errors.

## Usage Example

```c
#include "simple_tokenizer.h"

simple_tokenizer_token_type tokens[64];
size_t token_count = simple_tokenizer_tokenize("hello 123!", 10, tokens, 64);

for (size_t i = 0; i < token_count; ++i) {
    printf("Token %zu: Type=%s, Value=%.*s\n", i,
        simple_tokenizer_token_type_name(tokens[i].type),
        (int)tokens[i].value.length, tokens[i].value.ptr);
}
```

## Main Types

- `simple_tokenizer_token_type_enum`: Token type enumeration.
- `simple_tokenizer_token_type`: Structure for a token (type + value).
- `simple_tokenizer_utf8_char_type`: Structure for a decoded UTF-8 character and its error status.
- `simple_tokenizer_utf8_char_error_type`: Enum of possible UTF-8 decoding errors.

## Key Functions

- `simple_tokenizer_token_type_name(token_type)`: Get human-readable name of token type.
- `simple_tokenizer_tokenize(str, len, ptokens, n_tokens)`: Tokenize a string.
- `simple_tokenizer_stringref_to_utf8_char(ref)`: Parse a string reference as a UTF-8 character.

## Compatibility

- Works in C and C++ projects.

## License

MIT License
