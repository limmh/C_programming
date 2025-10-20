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
- **Support for fixed width integer types**, such as `int8_t`, `int16_t`, `int32_t`, `int64_t` and their unsigned variants.
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

Each safer integer arithmetic operation has a return type of the following form.

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

### 7. When to use the API

Consider using the API if you have one of the following situations.
- Arithmetic operations are to be performed on operands without obvious upper bound or lower bound, and you want to start with a smaller integer type first.
- When a larger integer type is not available or supported, e.g. arithmetic operations are performed on integers of long long type.
  Intermediate arithmetic operations may overflow, but casting to larger type (e.g. 128-bit integer type) is not possible on many platforms due to lack of 128-bit support.
- Integer overflows in arithmetic operations have to be detected and reported by your C or C++ applications, but you do not want to implement overflow detection by yourself.

## Example

```c
#include "safer_integer_short_macros.h"
#include <stdio.h>

/* Assume there is no integer type wider than long long */
long long llong_average(long long a, long long b) {
	llong_result_type result = slladd(a, b);
	if (result.error == integer_operation_error_none) {
		result.value /= 2LL; /* OK: division by a positive integer will not cause widening of result */
	} else {
		/* Try a less accurate calculation */
		result.value = (a / 2LL) + (b / 2LL); /* OK */
		/* report the error */
		fprintf(stderr, "%s\n", integer_operation_error_message(result.error));
		fprintf(stderr, "Operation: addition, operand 1: %lld, operand 2: %lld\n", a, a);
				
	}
	return result.value;
}

int main(void) {
	long long a = 5000LL, b = 10000LL;
	long long c = LLONG_MIN, d = LLONG_MIN;
	long long e = LLONG_MAX, f = LLONG_MAX;
	long long result = 0LL;
	result = llong_average(a, b); /* No error */
	printf("average(%lld, %lld) = %lld\n", a, b, result);
	result = llong_average(c, d); /* Error will be printed */
	printf("average(%lld, %lld) = %lld\n", c, d, result);
	result = llong_average(e, f); /* Error will be printed */
	printf("average(%lld, %lld) = %lld\n", e, f, result);
	return 0;
}
```

## Macros

### Macros wrapping safer functions for built-in integer types

|Macro                  |Function              |Integer Operation |Operand Type       |Return Type        |
|---------------------|--------------------|-----------------|-----------------|------------------|
|siadd                  |safer_int_add         |Addition          |int                |int_result_type    |
|sisub (or siminus)     |safer_int_minus       |Subtraction       |int                |int_result_type    |
|simul                  |safer_int_multiply    |Multiplication    |int                |int_result_type    |
|sidiv                  |safer_int_divide      |Division          |int                |int_result_type    |
|suiadd                 |safer_uint_add        |Addition          |unsigned int       |uint_result_type   |
|suisub (or suiminus)   |safer_uint_minus      |Subtraction       |unsigned int       |uint_result_type   |
|suimul                 |safer_uint_multiply   |Multiplication    |unsigned int       |uint_result_type   |
|suidiv                 |safer_uint_divide     |Division          |unsigned int       |uint_result_type   |
|sladd                  |safer_long_add        |Addition          |long               |long_result_type   |
|slsub (or slminus)     |safer_long_minus      |Subtraction       |long               |long_result_type   |
|slmul                  |safer_long_multiply   |Multiplication    |long               |long_result_type   |
|sldiv                  |safer_long_divide     |Division          |long               |long_result_type   |
|suladd                 |safer_ulong_add       |Addition          |unsigned long      |ulong_result_type  |
|sulsub (or sulminus)   |safer_ulong_minus     |Subtraction       |unsigned long      |ulong_result_type  |
|sulmul                 |safer_ulong_multiply  |Multiplication    |unsigned long      |ulong_result_type  |
|suldiv                 |safer_ulong_divide    |Division          |unsigned long      |ulong_result_type  |
|slladd                 |safer_llong_add       |Addition          |long long          |llong_result_type  |
|sllsub (or sllminus)   |safer_llong_minus     |Subtraction       |long long          |llong_result_type  |
|sllmul                 |safer_llong_multiply  |Multiplication    |long long          |llong_result_type  |
|slldiv                 |safer_llong_divide    |Division          |long long          |llong_result_type  |
|sulladd                |safer_ullong_add      |Addition          |unsigned long long |ullong_result_type |
|sullsub (or sullminus) |safer_ullong_minus    |Subtraction       |unsigned long long |ullong_result_type |
|sullmul                |safer_ullong_multiply |Multiplication    |unsigned long long |ullong_result_type |
|sulldiv                |safer_ullong_divide   |Division          |unsigned long long |ullong_result_type |

### Macros wrapping safer functions for fixed width integer types

|Macro                  |Function              |Integer Operation |Operand Type   |Return Type        |
|---------------------|--------------------|-----------------|-------------|------------------|
|si8add                 |safer_i8_add          |Addition          |int8_t         |i8_result_type     |
|si8sub (or si8minus)   |safer_i8_minus        |Subtraction       |int8_t         |i8_result_type     |
|si8mul                 |safer_i8_multiply     |Multiplication    |int8_t         |i8_result_type     |
|si8div                 |safer_i8_divide       |Division          |int8_t         |i8_result_type     |
|su8add                 |safer_u8_add          |Addition          |uint8_t        |u8_result_type     |
|su8sub (or su8minus)   |safer_u8_minus        |Subtraction       |uint8_t        |u8_result_type     |
|su8mul                 |safer_u8_multiply     |Multiplication    |uint8_t        |u8_result_type     |
|su8div                 |safer_u8_divide       |Division          |uint8_t        |u8_result_type     |
|si16add                |safer_i16_add         |Addition          |int16_t        |i16_result_type    |
|si16sub (or si16minus) |safer_i16_minus       |Subtraction       |int16_t        |i16_result_type    |
|si16mul                |safer_i16_multiply    |Multiplication    |int16_t        |i16_result_type    |
|si16div                |safer_i16_divide      |Division          |int16_t        |i16_result_type    |
|su16add                |safer_u16_add         |Addition          |uint16_t       |u16_result_type    |
|su16sub (or su16minus) |safer_u16_minus       |Subtraction       |uint16_t       |u16_result_type    |
|su16mul                |safer_u16_multiply    |Multiplication    |uint16_t       |u16_result_type    |
|su16div                |safer_u16_divide      |Division          |uint16_t       |u16_result_type    |
|si32add                |safer_i32_add         |Addition          |int32_t        |i32_result_type    |
|si32sub (or si32minus) |safer_i32_minus       |Subtraction       |int32_t        |i32_result_type    |
|si32mul                |safer_i32_multiply    |Multiplication    |int32_t        |i32_result_type    |
|si32div                |safer_i32_divide      |Division          |int32_t        |i32_result_type    |
|su32add                |safer_u32_add         |Addition          |uint32_t       |u32_result_type    |
|su32sub (or su32minus) |safer_u32_minus       |Subtraction       |uint32_t       |u32_result_type    |
|su32mul                |safer_u32_multiply    |Multiplication    |uint32_t       |u32_result_type    |
|su32div                |safer_u32_divide      |Division          |uint32_t       |u32_result_type    |
|si64add                |safer_i64_add         |Addition          |int64_t        |i64_result_type    |
|si64sub (or si64minus) |safer_i64_minus       |Subtraction       |int64_t        |i64_result_type    |
|si64mul                |safer_i64_multiply    |Multiplication    |int64_t        |i64_result_type    |
|si64div                |safer_i64_divide      |Division          |int64_t        |i64_result_type    |
|su64add                |safer_u64_add         |Addition          |uint64_t       |u64_result_type    |
|su64sub (or su64minus) |safer_u64_minus       |Subtraction       |uint64_t       |u64_result_type    |
|su64mul                |safer_u64_multiply    |Multiplication    |uint64_t       |u64_result_type    |
|su64div                |safer_u64_divide      |Division          |uint64_t       |u64_result_type    |

### Macros wrapping safe and less safe functions for fixed width integer types

|Macro               |Function                |Integer Operation |Operand Type   |Return Type |
|------------------|----------------------|----------------|--------------|-----------|
|i8add               |safe_i8_add             |Addition          |int8_t         |int16_t     |
|i8ub (or i8minus)   |safe_i8_minus           |Subtraction       |int8_t         |int16_t     |
|i8mul               |safe_i8_multiply        |Multiplication    |int8_t         |int16_t     |
|i8div               |less_safe_i8_divide     |Division          |int8_t         |int16_t     |
|i8rem               |less_safe_i8_remainder  |Remainder         |int8_t         |int8_t      |
|u8add               |safe_u8_add             |Addition          |uint8_t        |uint16_t    |
|u8ub (or u8minus)   |safe_u8_minus           |Subtraction       |uint8_t        |int16_t     |
|u8mul               |safe_u8_multiply        |Multiplication    |uint8_t        |uint16_t    |
|u8div               |less_safe_u8_divide     |Division          |uint8_t        |uint8_t     |
|u8rem               |less_safe_u8_remainder  |Remainder         |uint8_t        |uint8_t     |
|i16add              |safe_i16_add            |Addition          |int16_t        |int32_t     |
|i16ub (or i16minus) |safe_i16_minus          |Subtraction       |int16_t        |int32_t     |
|i16mul              |safe_i16_multiply       |Multiplication    |int16_t        |int32_t     |
|i16div              |less_safe_i16_divide    |Division          |int16_t        |int32_t     |
|i16rem              |less_safe_i16_remainder |Remainder         |int16_t        |int16_t     |
|u16add              |safe_u16_add            |Addition          |uint16_t       |uint32_t    |
|u16ub (or u16minus) |safe_u16_minus          |Subtraction       |uint16_t       |int32_t     |
|u16mul              |safe_u16_multiply       |Multiplication    |uint16_t       |uint32_t    |
|u16div              |less_safe_u16_divide    |Division          |uint16_t       |uint16_t    |
|u16rem              |less_safe_u16_remainder |Remainder         |uint16_t       |uint16_t    |
|i32add              |safe_i32_add            |Addition          |int32_t        |int64_t     |
|i32ub (or i32minus) |safe_i32_minus          |Subtraction       |int32_t        |int64_t     |
|i32mul              |safe_i32_multiply       |Multiplication    |int32_t        |int64_t     |
|i32div              |less_safe_i32_divide    |Division          |int32_t        |int64_t     |
|i32rem              |less_safe_i32_remainder |Remainder         |int32_t        |int32_t     |
|u32add              |safe_u32_add            |Addition          |uint32_t       |uint64_t    |
|u32ub (or u32minus) |safe_u32_minus          |Subtraction       |uint32_t       |int64_t     |
|u32mul              |safe_u32_multiply       |Multiplication    |uint32_t       |uint64_t    |
|u32div              |less_safe_u32_divide    |Division          |uint32_t       |uint32_t    |
|u32rem              |less_safe_u32_remainder |Remainder         |uint32_t       |uint32_t    |

Notes:
- The macros will perform runtime assertions to check whether their operand values can fit into the function operands.
- If either or both operands of of smaller types, e.g. signed char or short, the int version should be used.  
  The safe implicit conversion (from an integer type smaller than int to int) emulates the integer promotion behavior that C usually performs.
  Because of this, operations on integer types smaller than int are already handled by the int variants.

## Limitations

- Less friendly than native arithmetic operators like +,-,\*,/ and %.
- No support for wraparound results.  
  **Reason for no support**: Unsigned integer wraparounds are defined behavior in C and C++, so native operators can be used on unsigned integers to achieve wraparound behavior.
- No support for bitwise operations.  
  **Reason for no support**: Most operations on unsigned integers are defined, except bit shift operations where the number of bits to shift exceeds the width of the integer,
  so it makes more sense to directly use native bitwise operators on unsigned integers for bitwise operations.
- No hardware intrinsics, hence not suitable for certain applications, e.g. applications which need to perform a lot of integer calculations within a very short time.  
  **Reason for no support**: The implementation is more portable without hardware intrinsics.

## License

This library is distributed under the MIT License. See the LICENSE file at the top level of the repository.
