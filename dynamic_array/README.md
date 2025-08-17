# dynamic_array

A robust, generic dynamic array library.

## Overview

This library provides an opaque, type-agnostic dynamic array implementation, supporting safe memory management, extensible error reporting, custom memory allocators, and a comprehensive set of macros for ease of use.
The API is designed for safety and correctness, suitable for high security and high reliability applications.

## Features

- Type-safe element access via macros.
- Custom allocator support.
- Runtime checks for buffer overflows, memory allocation failures, element size mismatches, and more.
- Exception handling and customizable error reporting.
- Automatic resizing and zero-initialization of elements.

## Usage Example

```c
#include "dynamic_array.h"

dynamic_array_type(int) arr = dynamic_array_create(int, 16);  // Create a dynamic array for ints
dynamic_array_append_element(int, arr, 42);                   // Append an element
int value = dynamic_array_element(int, arr, 0);               // Access an element
dynamic_array_delete(arr);                                    // Clean up
```

## Main Types

- `dynamic_array_type(element_type)`: Opaque array type (use in variable declarations).
- `dynamic_array_allocator_type`: Structure for custom memory allocators.
- `dynamic_array_error_type`: Enum of error codes (for error reporting and debugging).
- `dynamic_array_debug_info_type`: Carries file/line/struct size information for diagnostics.

## Key Macros

- Creation: `dynamic_array_create(type, size)`, `dynamic_array_create_with_allocator(type, size, allocator)`
- Cleanup: `dynamic_array_delete(array)`
- Element access: `dynamic_array_element(type, array, index)`
- Adding/removing elements: `dynamic_array_append_element`, `dynamic_array_add_element_at_index`, `dynamic_array_remove_element_at_index`, etc.
- Resizing: `dynamic_array_resize(type, array, new_size)`
- Capacity and size: `dynamic_array_capacity(array)`, `dynamic_array_size(array)`
- Error handling: `dynamic_array_set_exception_handler`, `dynamic_array_set_error_reporting_handler`
- Diagnostics: `dynamic_array_check(array)`

## Error Handling

You can provide exception and error reporting handlers. By default, errors terminate the program.

## Compatibility

- C89 and newer C standards.

## License

MIT License
