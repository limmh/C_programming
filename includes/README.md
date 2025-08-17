# includes

This folder contains core header files providing utility macros, types, and portable constructs for C and C++ projects. These files are designed to improve portability, safety, and code clarity, and are suitable for use in a wide range of applications.

---

## Overview of Provided Headers

### 1. `Boolean_type.h`

Provides a portable boolean type for both C and C++.  
- In C99/C++: defines `Boolean_type` as built-in `bool`, `Boolean_true` as `true`, and `Boolean_false` as `false`.  
- In C89: defines `Boolean_type` as `unsigned char`, with `Boolean_true` and `Boolean_false` macros.
- Ensures consistent boolean logic across compilers and standards.

### 2. `sizeof_array.h`

Defines a macro for determining the number of elements in a static one-dimensional array:
```c
#define SIZEOF_ARRAY(ARRAY) ( sizeof(ARRAY) / sizeof((ARRAY)[0]) )
#define sizeof_array(array) SIZEOF_ARRAY(array)
```
- Use only with actual arrays, not pointers.

### 3. `macro_alignof.h`

Provides a portable macro for determining type alignment:
- Uses C11/C++11 `alignof` if available.
- Otherwise, falls back to a safe trick with `offsetof`.
```c
#define ALIGNOF(TYPE) /* implementation */
```

### 4. `static_assert.h`

Compile-time assertion macro, compatible with C89, C99, C11 and C++:
- Uses `static_assert` where available.
- Otherwise, creates a negative-sized array to trigger compilation errors when assertions fail.
```c
STATIC_ASSERT(sizeof(size_t) == sizeof(void*), "size_t and pointer type must have the same size.");
```

### 5. `macro_stringify.h`

Macros for converting macro arguments to string literals:
```c
#define STRINGIFY_(VALUE) #VALUE
#define STRINGIFY(VALUE)  STRINGIFY_(VALUE)
```

### 6. `inline_or_static.h`

Defines a macro to abstract between `inline` and `static` based on language standard:
- C89: `static`
- newer C standards or C++: `inline`
```c
#define INLINE_OR_STATIC /* inline or static */
```

### 7. `string_reference.h`

Provides types and utilities for referencing parts of strings without copying:
- `stringref_type` (mutable) and `const_stringref_type` (immutable).
- Helper functions to convert between types and to or from raw strings.
- Functions to copy referenced data into buffers with bounds checking.
- Useful for efficient string handling and parsing.

**Example usage:**
```c
const char *mystr = "This is an example.";
stringref_type ref = string_to_stringref(mystr, strlen(mystr));
if (stringref_is_valid(ref)) {
    // Use ref.string and ref.length
}
```

---

## How to Use

Include the relevant headers in your C or C++ source files:
```c
#include "Boolean_type.h"
#include "sizeof_array.h"
#include "macro_alignof.h"
#include "static_assert.h"
#include "macro_stringify.h"
#include "inline_or_static.h"
#include "string_reference.h"
```

These headers do not define any global state and are safe to include in multiple translation units.

---

## Portability

- All headers are designed to work with C89 and later, as well as C++ projects.
- Where newer language features are available, they are used; otherwise, portable workarounds are provided.

---

## License

MIT License

---

## Contributing

Pull requests and suggestions are welcome.
