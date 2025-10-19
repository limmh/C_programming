# Safer Integer API

A portable C library for safer integer arithmetic with explicit error codes, clipping and convenient macros for all C standards.

## Overview

The **Safer Integer API** (`safer_integer.h` and `safer_integer_short_macros.h`) provides a set of functions and macros for performing safer arithmetic on C integer types.
It detects and reports overflows, underflows, division by zero, etc., returning results and error codes.

## Motivation
Built-in integers in the C and C++ languages have finite sizes and can only represent values within certain ranges.
By default, overflows in native arithmetic operations are not reported as errors.
Although computer processors are able to detect arithmetic overflows, there is no standard way to detect integer overflows in C and C++.

In addition, there is also undefined behavior associated with certain integer types and arithmetic operations. For example, signed integer overflows are undefined by the C standard.
The reason for making certain behavior undefined is to support multiple integer representations and to allow compilers to perform optimizations.
We tend to take integer operations for granted and we may not know implicit conversions and integer promotion rules well enough.
Because of the undefined behavior in signed integer operations, attempts to check for overflows may actually cause undefined behavior.

Here is an example which will invoke undefined behavior.

```c
bool int_overflow_detected_for_increment(int value) {
	return (value + 1) < value;
}
```
In the code example, `value` is signed and the function assumes that when `value` is `INT_MAX`, adding 1 to `value` will cause the value to wrap around to the most negative integer value.
However, since signed integer overflow is undefined behavior, compilers need not handle it. Under certain optimizations, the function above could be optimized to the following version.

```c
bool int_overflow_detected_for_increment(int value) {
	return false;
}
```

Since signed integer overflow is not defined, a complier can assume the condition `(value + 1) < value` is always untrue and can avoid the actual check. More examples of undefined behavior associated with integers can be found online.

There are a few popular safe integer libraries which target only C++ and cannot be used by C code. There are also alternatives for C, such as the SafeInt's C API, IntegerLib and stdckdint.h.
Here are some of their features and limitations.
- **SafeInt's C API (safe_math.h)**: supports operations with mixed-type operands, safe operations abort on error by default (users can customize error handling).
- **IntegerLib**: supports only built-in types and uses errno and error handler for error reporting.
- **stdckdint.h**: C23's standard checked arithmetic API, no support for checked division and not available in C standards before C23.

The Safer Integer API is an alternative safer integer C library which is portable for all available C standards.
It uses value semantics like some of existing safer integer libraries and avoids pointer semantics completely.
The functions of the API are pure functions as they do not have any external side effects. They do not modify errno and do not make use of external handlers.
The integer operations will not abort on error, but the error is returned as an error code in a custom data structure.

The implementation of the API makes use of mathematical analysis and reasoning and avoids the use of hardware intrinsics, so that the implementation is portable.
There are separate functions for checking whether arithmetic operations will cause errors without performing the actual operations.
Care is taken to ensure that the arithmetic operations performed during checks do not invoke undefined behavior.
The safer arithmetic operations make use of the checking functions.

## Features

The Safer Integer API offers:

- **Checked arithmetic** for built-in integer types such as `int`, `long`, `long long`, and their unsigned variants.
- **Error reporting** via enums and result structs.
- **Comprehensive error codes**: Explicitly distinguishes between overflow, underflow, division by zero and other error conditions.
- **Value semantics**: Results are returned as structs, not via pointer output.
- **Clipping behavior**: On overflow/underflow, results saturate to min/max.
- **Support for safe division**: The quotient and the remainder are returned as part of the result. Division by zero and `INT_MIN / -1` are detected.
- **Short macros** (e.g., `siadd`, `simul`, `sidiv`, etc.) for concise, readable code with built-in assertions for safe casting from larger operand types to smaller operand types.
- **No abort/fail-fast**: errors are reported as an error member in the returned struct, no explicit error handler.
- **Portability**: Works on C89/C90 and newer C standards; no dependency on compiler intrinsics.

## API Usage

### 1. Result Type Data Structure

Each safer integer arithmetic operation has the following return type.

```c
struct int_result_type {
	int value;
	int remainder;
	integer_operation_error_type error;
};
typedef struct int_result_type int_result_type;
```

- Signed types: `int_result_type`, `long_result_type` and `llong_result_type`
- Unsigned types: `uint_result_type`, `ulong_result_type` and `ullong_result_type`

### 2. Basic Arithmetic

```c
#include "safer_integer.h"
int a = 0, b = 1;
int_result_type result = safer_int_add(a, b);
if (result.error != integer_operation_error_none) {
    // Handle overflow/underflow/clipping
}
```

### 3. Using Macros

```c
#include "safer_integer_short_macros.h"
int a = 1;
int b = INT_MAX;
int_result_type result = siadd(a, b); // Performs addition with assertions
```

### 4. Error Handling

Errors are reported as enums:
- `integer_operation_error_none`
- `integer_operation_error_signed_integer_result_smaller_than_minimum`
- `integer_operation_error_signed_integer_result_greater_than_maximum`
- `integer_operation_error_division_of_signed_integer_by_zero`
- `integer_operation_error_division_of_minimum_signed_integer_by_minus_one`
- `integer_operation_error_unsigned_integer_result_wraparound_from_larger_to_smaller`
- `integer_operation_error_unsigned_integer_result_wraparound_from_smaller_to_larger`
- `integer_operation_error_division_of_unsigned_integer_by_zero`

Obtain error messages via:
```c
printf("%s\n", integer_operation_error_message(result.error));
```

### 5. Clipping Behavior

On overflow/underflow, arithmetic functions clip the result:
- Addition/subtraction/multiplication: Clipped to min/max.
- Division: Clips to `INT_MAX` if the operation is `INT_MIN / -1`.

### 6. Supported Types

- Signed integer types: `int`, `long` and `long long`
- Unsigned integer types: `unsigned int`, `unsigned long` and `unsigned long long`

Note: `long long` and `unsigned long long` are available since C99 for most compilers or as a C89/C90 extension for some compilers.

## Example

```c
#include "safer_integer_short_macros.h"
#include <stdio.h>

int main(void) {
    int_result_type result = siadd(INT_MAX, 1);
    if (result.error != integer_operation_error_none) {
        printf("Overflow! Clipped value: %d\n", result.value);
    }
    return 0;
}
```
## Macros

|Macro                  |Function               |Operand Type       |Return Type        |
|---------------------|---------------------|------------------|-----------------|
|siadd                  |safer_int_add          |int                |int_result_type    |
|sisub (or siminus)     |safer_int_minus        |int                |int_result_type    |
|simul                  |safer_int_multiply     |int                |int_result_type    |
|sidiv                  |safer_int_divide       |int                |int_result_type    |
|suiadd                 |safer_uint_add         |unsigned int       |uint_result_type   |
|suisub (or suiminus)   |safer_uint_minus       |unsigned int       |uint_result_type   |
|suimul                 |safer_uint_multiply    |unsigned int       |uint_result_type   |
|suidiv                 |safer_uint_divide      |unsigned int       |uint_result_type   |
|sladd                  |safer_long_add         |long               |long_result_type   |
|slsub (or slminus)     |safer_long_minus       |long               |long_result_type   |
|slmul                  |safer_long_multiply    |long               |long_result_type   |
|sldiv                  |safer_long_divide      |long               |long_result_type   |
|suladd                 |safer_ulong_add        |unslgned long      |ulong_result_type  |
|sulsub (or sulminus)   |safer_ulong_minus      |unslgned long      |ulong_result_type  |
|sulmul                 |safer_ulong_multiply   |unslgned long      |ulong_result_type  |
|suldiv                 |safer_ulong_divide     |unslgned long      |ulong_result_type  |
|slladd                 |safer_llong_add        |long long          |long_result_type   |
|sllsub (or sllminus)   |safer_llong_minus      |long long          |llong_result_type  |
|sllmul                 |safer_llong_multiply   |long long          |llong_result_type  |
|slldiv                 |safer_llong_divide     |long long          |llong_result_type  |
|sulladd                |safer_ullong_add       |unslgned long long |ullong_result_type |
|sullsub (or sullminus) |safer_ullong_minus     |unslgned long long |ullong_result_type |
|sullmul                |safer_ullong_multiply  |unslgned long long |ullong_result_type |
|sulldiv                |safer_ullong_divide    |unslgned long long |ullong_result_type |

Notes:
- The macros will perform runtime assertions to check whether their operand values can fit into the function operands.
- If either or both operands of of smaller types, e.g. signed char or short, the int version should be used.  
  The safe implicit conversion (from an integer type smaller than int to int) emulates the integer promotion behavior that C usually performs.  
  Because of this, operations that support smaller types are covered by the int variants.

## Limitations

- Less friendly than native arithmetic operators like +,-,\*,/ and %.
- No support for wraparound results.  
  **Reason for no support**: Unsigned integer wraparounds are defined behavior in C and C++, so native operators can be used on unsigned integers to achieve wraparound behavior.
- No support for bitwise operations.  
  **Reason for no support**: Most operations on unsigned integers are defined, except bit shift operations where the number of bits to shift exceeds the width of the integer,
  so it makes more sense to directly use native bitwise operators on unsigned integers for bitwise operations.
- No hardware intrinsics, hence not suitable for certain applications, e.g. applications which need to perform a lot of integer calculations within a very short time.  
  **Reason for no support**: The implementation is more portable without hardware intrinsics.
- No support for fixed width integer types yet. Work in progress.

## License

This library is distributed under the MIT License. See the LICENSE file at the top level of the repository.
