# ABI Compatibility Test: Reference Type Emulation in C

## Overview

This project demonstrates how to **emulate C++-style reference semantics in C** using macro techniques. It simplifies C interfaces to resemble C++ references instead of classic pointer patterns, which can make code cleaner, safer, and more expressive.

The main components are:

- A set of macros that provide reference-like behavior for variables, arrays, and function arguments in C (`reference_type_emulation.h`).
- Function and struct APIs that showcase operating on scalars and arrays via references, similar to their C++ counterparts.
- Example code that tests the reference emulation through swaps, comparisons, printing, and sorting arrays.

---

## Reference Type Emulation

### Motivation

C++ reference types were first introduced to support passing objects by reference without pointer semantics to overloaded operators.
References are not limited to member functions of classes, but can be used as paramaters in non-member functions and as aliases to variables.
At function interfaces, both pointers and references are usually variable or object addresses in assembly or machine code.

C++ references have several distinct advantages:
- Cannot be null or uninitialized.
- Simplify function implementations (no need for pointer checks).
- Has value or object semantics (no need for explicit dereferencing).

C does not natively support references. This project **emulates reference semantics in C** using constant pointers and macros.

### Macros Provided (from `includes/reference_type_emulation.h`)

- `REF(reference)` —  Declare a reference-type variable.
- `REF_OF(object)` — Initialize a reference to an object.
- `DEREF(reference)` — Dereference the reference (access the underlying object).

#### C Usage Example

```c
#include "reference_type_emulation.h"

int a = 42;
int REF(ref_a) = REF_OF(a);
++DEREF(ref_a);
```

#### C++ Usage Example

The macros use native reference semantics under C++ compilation, allowing code compatibility between C and C++ code that uses the macros.

---

## API Overview

### Types

- `int_array_10_type`
    ```c
    typedef struct int_array_10_type {
        int array[10];
    } int_array_10_type;
    ```
- `int_array_10_refs_type`
    ```c
    typedef struct int_array_10_refs_type {
        int REF(ref_array_a)[10];
        int REF(ref_array_b)[10];
    } int_array_10_refs_type;
    ```

### Functions (see `ABI_compatibility_test.h`)

#### Scalar Reference Functions
- `void int_swap(int REF(a), int REF(b));`
- `int REF(int_ref_max(int REF(a), int REF(b)));`
- `int REF(int_ref_min(int REF(a), int REF(b)));`

#### Array Reference Functions
- `int_array_10_type REF(int_array_10_ref_max_sum(int_array_10_type REF(a), int_array_10_type REF(b)));`
- `int_array_10_type REF(int_array_10_ref_min_sum(int_array_10_type REF(a), int_array_10_type REF(b)));`
- `void int_array_10_print(const int REF(ref_array)[10]);`

#### Reference-Based Sort Functions
- `int_array_10_refs_type int_array_10_refs_sort_v1(int_array_10_refs_type array_refs, int REF(sort_func)(const void *, const void *));`
- `int_array_10_refs_type REF(int_array_10_refs_sort_v2(int_array_10_refs_type REF(array_refs), int REF(sort_func)(const void *, const void *)));`

---

## Example Usage

See `ABI_compatibility_test_code.c` for practical demonstrations.

- Swapping two integers by reference—no explicit pointers needed.
- Finding max/min of two referenced integers.
- Comparing and printing arrays by reference.
- Sorting arrays using reference-emulated function pointers and `qsort`.

### Demo Output

The test code prints values before/after swaps, array sums, sorted orders, and verifies that reference operations work as expected.

---

## How Reference Emulation Works

The macros and API work together so you can:

- Pass variables and arrays to functions by reference without exposing pointers in your user code.
- Write safer, cleaner code that eases transition between C and C++ or helps create ABI-stable interfaces.

## File Descriptions

- **reference_type_emulation.h**  
  Provides the macros and documentation for reference emulation in C.

- **ABI_compatibility_test.h and ABI_compatibility_test.c**  
  Declare and implement reference-based operations for integers and arrays.

- **ABI_compatibility_test_code.c**  
  Shows example usage and demonstrates correctness of reference emulation.

---

## Getting Started

1. **Include `reference_type_emulation.h`** in your C source files.
2. Use the macros (`REF`, `REF_OF`, `DEREF`) as described above.
3. Link and run `ABI_compatibility_test_code.c` to see test output.

---

## License

MIT License

---