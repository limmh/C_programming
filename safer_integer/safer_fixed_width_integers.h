#ifndef SAFER_FIXED_WIDTH_INTEGERS_H
#define SAFER_FIXED_WIDTH_INTEGERS_H

#include "fixed_width_integer_types.h"
#include "safer_integer.h"
#include "inline_or_static.h"
#include "static_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct i8_result_type
{
	int8_t value;
	int8_t remainder;
	integer_operation_error_type error;
} i8_result_type;

typedef struct u8_result_type
{
	uint8_t value;
	uint8_t remainder;
	integer_operation_error_type error;
} u8_result_type;

typedef struct i16_result_type
{
	int16_t value;
	int16_t remainder;
	integer_operation_error_type error;
} i16_result_type;

typedef struct u16_result_type
{
	uint16_t value;
	uint16_t remainder;
	integer_operation_error_type error;
} u16_result_type;

typedef struct i32_result_type
{
	int32_t value;
	int32_t remainder;
	integer_operation_error_type error;
} i32_result_type;

typedef struct u32_result_type
{
	uint32_t value;
	uint32_t remainder;
	integer_operation_error_type error;
} u32_result_type;

/* int8_t */
i8_result_type safer_i8_add(int8_t a, int8_t b);
i8_result_type safer_i8_minus(int8_t a, int8_t b);
i8_result_type safer_i8_multiply(int8_t a, int8_t b);
i8_result_type safer_i8_divide(int8_t a, int8_t b);

int16_t safe_i8_add(int8_t a, int8_t b);
int16_t safe_i8_minus(int8_t a, int8_t b);
int16_t safe_i8_multiply(int8_t a, int8_t b);
int16_t less_safe_i8_divide(int8_t a, int8_t b);
int8_t less_safe_i8_remainder(int8_t a, int8_t b);

/* uint8_t */
u8_result_type safer_u8_add(uint8_t a, uint8_t b);
u8_result_type safer_u8_minus(uint8_t a, uint8_t b);
u8_result_type safer_u8_multiply(uint8_t a, uint8_t b);
u8_result_type safer_u8_divide(uint8_t a, uint8_t b);

uint16_t safe_u8_add(uint8_t a, uint8_t b);
int16_t safe_u8_minus(uint8_t a, uint8_t b);
uint16_t safe_u8_multiply(uint8_t a, uint8_t b);
uint8_t less_safe_u8_divide(uint8_t a, uint8_t b);
uint8_t less_safe_u8_remainder(uint8_t a, uint8_t b);

/* int16_t */
i16_result_type safer_i16_add(int16_t a, int16_t b);
i16_result_type safer_i16_minus(int16_t a, int16_t b);
i16_result_type safer_i16_multiply(int16_t a, int16_t b);
i16_result_type safer_i16_divide(int16_t a, int16_t b);

int32_t safe_i16_add(int16_t a, int16_t b);
int32_t safe_i16_minus(int16_t a, int16_t b);
int32_t safe_i16_multiply(int16_t a, int16_t b);
int32_t less_safe_i16_divide(int16_t a, int16_t b);
int16_t less_safe_i16_remainder(int16_t a, int16_t b);

/* uint16_t */
u16_result_type safer_u16_add(uint16_t a, uint16_t b);
u16_result_type safer_u16_minus(uint16_t a, uint16_t b);
u16_result_type safer_u16_multiply(uint16_t a, uint16_t b);
u16_result_type safer_u16_divide(uint16_t a, uint16_t b);

uint32_t safe_u16_add(uint16_t a, uint16_t b);
int32_t safe_u16_minus(uint16_t a, uint16_t b);
uint32_t safe_u16_multiply(uint16_t a, uint16_t b);
uint16_t less_safe_u16_divide(uint16_t a, uint16_t b);
uint16_t less_safe_u16_remainder(uint16_t a, uint16_t b);

/* int32_t */
i32_result_type safer_i32_add(int32_t a, int32_t b);
i32_result_type safer_i32_minus(int32_t a, int32_t b);
i32_result_type safer_i32_multiply(int32_t a, int32_t b);
i32_result_type safer_i32_divide(int32_t a, int32_t b);

/* uint32_t */
u32_result_type safer_u32_add(uint32_t a, uint32_t b);
u32_result_type safer_u32_minus(uint32_t a, uint32_t b);
u32_result_type safer_u32_multiply(uint32_t a, uint32_t b);
u32_result_type safer_u32_divide(uint32_t a, uint32_t b);

#if defined(INT64_MIN) && defined(INT64_MAX) && defined(UINT64_MAX)

typedef struct i64_result_type
{
	int64_t value;
	int64_t remainder;
	integer_operation_error_type error;
} i64_result_type;

typedef struct u64_result_type
{
	uint64_t value;
	uint64_t remainder;
	integer_operation_error_type error;
} u64_result_type;

int64_t safe_i32_add(int32_t a, int32_t b);
int64_t safe_i32_minus(int32_t a, int32_t b);
int64_t safe_i32_multiply(int32_t a, int32_t b);
int64_t less_safe_i32_divide(int32_t a, int32_t b);
int32_t less_safe_i32_remainder(int32_t a, int32_t b);

uint64_t safe_u32_add(uint32_t a, uint32_t b);
int64_t safe_u32_minus(uint32_t a, uint32_t b);
uint64_t safe_u32_multiply(uint32_t a, uint32_t b);
uint32_t less_safe_u32_divide(uint32_t a, uint32_t b);
uint32_t less_safe_u32_remainder(uint32_t a, uint32_t b);

/* int64_t */
i64_result_type safer_i64_add(int64_t a, int64_t b);
i64_result_type safer_i64_minus(int64_t a, int64_t b);
i64_result_type safer_i64_multiply(int64_t a, int64_t b);
i64_result_type safer_i64_divide(int64_t a, int64_t b);

/* uint64_t */
u64_result_type safer_u64_add(uint64_t a, uint64_t b);
u64_result_type safer_u64_minus(uint64_t a, uint64_t b);
u64_result_type safer_u64_multiply(uint64_t a, uint64_t b);
u64_result_type safer_u64_divide(uint64_t a, uint64_t b);

#if (PTRDIFF_MIN == INT64_MIN) && (PTRDIFF_MAX == INT64_MAX)
typedef i64_result_type ptrdiff_result_type;
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int64_t), "The size of ptrdiff_t must be the same as the size of int64_t.");
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_add(ptrdiff_t a, ptrdiff_t b) {
	return safer_i64_add(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_minus(ptrdiff_t a, ptrdiff_t b) {
	return safer_i64_minus(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_multiply(ptrdiff_t a, ptrdiff_t b) {
	return safer_i64_multiply(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_divide(ptrdiff_t a, ptrdiff_t b) {
	return safer_i64_divide(a, b);
}
#endif

#if SIZE_MAX == UINT64_MAX
typedef u64_result_type size_result_type;
STATIC_ASSERT(sizeof(size_t) == sizeof(uint64_t), "The size of size_t must be the same as the size of uint64_t.");
INLINE_OR_STATIC size_result_type safer_size_add(size_t a, size_t b) {
	return safer_u64_add(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_minus(size_t a, size_t b) {
	return safer_u64_minus(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_multiply(size_t a, size_t b) {
	return safer_u64_multiply(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_divide(size_t a, size_t b) {
	return safer_u64_divide(a, b);
}
#endif

#else

#if (PTRDIFF_MIN == INT32_MIN) && (PTRDIFF_MAX == INT32_MAX)
typedef i32_result_type ptrdiff_result_type;
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int32_t), "The size of ptrdiff_t must be the same as the size of int32_t.");
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_add(ptrdiff_t a, ptrdiff_t b) {
	return safer_i32_add(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_minus(ptrdiff_t a, ptrdiff_t b) {
	return safer_i32_minus(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_multiply(ptrdiff_t a, ptrdiff_t b) {
	return safer_i32_multiply(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_divide(ptrdiff_t a, ptrdiff_t b) {
	return safer_i32_divide(a, b);
}
#elif (PTRDIFF_MIN == INT16_MIN) && (PTRDIFF_MAX == INT16_MAX)
typedef i16_result_type ptrdiff_result_type;
STATIC_ASSERT(sizeof(ptrdiff_t) == sizeof(int16_t), "The size of ptrdiff_t must be the same as the size of int16_t.");
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_add(ptrdiff_t a, ptrdiff_t b) {
	return safer_i16_add(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_minus(ptrdiff_t a, ptrdiff_t b) {
	return safer_i16_minus(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_multiply(ptrdiff_t a, ptrdiff_t b) {
	return safer_i16_multiply(a, b);
}
INLINE_OR_STATIC ptrdiff_result_type safer_ptrdiff_divide(ptrdiff_t a, ptrdiff_t b) {
	return safer_i16_divide(a, b);
}
#else
#pragma message("The size of ptrdiff_t is not 64-bit, 32-bit or 16-bit. Please provide your own implementation.")
#endif

#if SIZE_MAX == UINT32_MAX
typedef u32_result_type size_result_type;
STATIC_ASSERT(sizeof(size_t) == sizeof(uint32_t), "The size of size_t must be the same as the size of uint32_t.");
INLINE_OR_STATIC size_result_type safer_size_add(size_t a, size_t b) {
	return safer_u32_add(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_minus(size_t a, size_t b) {
	return safer_u32_minus(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_multiply(size_t a, size_t b) {
	return safer_u32_multiply(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_divide(size_t a, size_t b) {
	return safer_u32_divide(a, b);
}
#elif SIZE_MAX == UINT16_MAX
typedef u16_result_type size_result_type;
STATIC_ASSERT(sizeof(size_t) == sizeof(uint16_t), "The size of size_t must be the same as the size of uint16_t.");
INLINE_OR_STATIC size_result_type safer_size_add(size_t a, size_t b) {
	return safer_u16_add(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_minus(size_t a, size_t b) {
	return safer_u16_minus(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_multiply(size_t a, size_t b) {
	return safer_u16_multiply(a, b);
}
INLINE_OR_STATIC size_result_type safer_size_divide(size_t a, size_t b) {
	return safer_u16_divide(a, b);
}
#else
#pragma message("The size of size_t is not 64-bit, 32-bit or 16-bit. Please provide your own implementation.")
#endif

#endif /* INT64_MIN and INT64_MAX and UINT64_MAX */

#ifdef __cplusplus
}
#endif

#endif
