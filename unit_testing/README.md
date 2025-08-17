# unit_testing

A minimal, portable unit testing library mainly for C code.

## Overview

This header provides a lightweight, macro-driven unit testing framework for C, supporting assertion macros, comparison utilities, test definition macros, statistics collection, and customizable output. It is designed for maximum portability and minimal dependencies.

## Features

- Define tests using macros (`TEST`) and run tests easily.
- Assertion macros for integer comparisons.
- Prints failed assertions with file or line info and value details.
- Collects and prints test statistics.
- Output can be redirected to any `FILE*`.

## Usage Example

```c
#include "unit_testing.h"

TEST(my_test, "Test for addition") {
    ASSERT_INT_EQUAL(2 + 2, 4);
    ASSERT_GREATER(10, 5);
}

int main(void) {
    DEFINE_LIST_OF_TESTS(tests) { my_test };
    RUN_TESTS(tests);
    PRINT_TEST_STATISTICS(tests);
    return 0;
}
```

## Main Types

- `testing_library_test_type`: Structure for a test (function pointer, name, stats).
- `testing_library_test_statistics_type`: Structure for test suite statistics.
- Boolean assertion macros: `ASSERT`, `ASSERT_INT_EQUAL`, `ASSERT_UINT_EQUAL`, etc.

## Key Macros

- `TEST(name, description)`: Define a test.
- `ASSERT(condition)`: Basic assertion.
- `ASSERT_INT_EQUAL(lhs, rhs)`, `ASSERT_GREATER(lhs, rhs)`, etc.: Typed assertions.
- `DEFINE_LIST_OF_TESTS(tests)`: Define a test suite.
- `RUN_TESTS(tests)`: Run all tests in a suite.
- `PRINT_TEST_STATISTICS(tests)`: Print summary statistics.

## Compatibility

- Works on C89 and later, as well as C++.
- No dependencies except the standard library.

## License

MIT License
