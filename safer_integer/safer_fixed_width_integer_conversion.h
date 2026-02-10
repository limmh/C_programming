#ifndef SAFER_FIXED_WIDTH_INTEGER_CONVERSION_H
#define SAFER_FIXED_WIDTH_INTEGER_CONVERSION_H

#include "safer_integer_conversion.h"
#include "fixed_width_integer_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* int8_t conversions */
typedef struct int8_conversion_result_type
{
	int8_t value;
	integer_conversion_error_type error;
} int8_conversion_result_type;

int8_conversion_result_type safer_int8_from_int8(int8_t value);
int8_conversion_result_type safer_int8_from_uint8(uint8_t value);
int8_conversion_result_type safer_int8_from_int16(int16_t value);
int8_conversion_result_type safer_int8_from_uint16(uint16_t value);
int8_conversion_result_type safer_int8_from_int32(int32_t value);
int8_conversion_result_type safer_int8_from_uint32(uint32_t value);
int8_conversion_result_type safer_int8_from_int64(int64_t value);
int8_conversion_result_type safer_int8_from_uint64(uint64_t value);

/* uint8_t conversions */
typedef struct uint8_conversion_result_type
{
	uint8_t value;
	integer_conversion_error_type error;
} uint8_conversion_result_type;

uint8_conversion_result_type safer_uint8_from_int8(int8_t value);
uint8_conversion_result_type safer_uint8_from_uint8(uint8_t value);
uint8_conversion_result_type safer_uint8_from_int16(int16_t value);
uint8_conversion_result_type safer_uint8_from_uint16(uint16_t value);
uint8_conversion_result_type safer_uint8_from_int32(int32_t value);
uint8_conversion_result_type safer_uint8_from_uint32(uint32_t value);
uint8_conversion_result_type safer_uint8_from_int64(int64_t value);
uint8_conversion_result_type safer_uint8_from_uint64(uint64_t value);

/* int16_t conversions */
typedef struct int16_conversion_result_type
{
	int16_t value;
	integer_conversion_error_type error;
} int16_conversion_result_type;

int16_conversion_result_type safer_int16_from_int8(int8_t value);
int16_conversion_result_type safer_int16_from_uint8(uint8_t value);
int16_conversion_result_type safer_int16_from_int16(int16_t value);
int16_conversion_result_type safer_int16_from_uint16(uint16_t value);
int16_conversion_result_type safer_int16_from_int32(int32_t value);
int16_conversion_result_type safer_int16_from_uint32(uint32_t value);
int16_conversion_result_type safer_int16_from_int64(int64_t value);
int16_conversion_result_type safer_int16_from_uint64(uint64_t value);

/* uint16_t conversions */
typedef struct uint16_conversion_result_type
{
	uint16_t value;
	integer_conversion_error_type error;
} uint16_conversion_result_type;

uint16_conversion_result_type safer_uint16_from_int8(int8_t value);
uint16_conversion_result_type safer_uint16_from_uint8(uint8_t value);
uint16_conversion_result_type safer_uint16_from_int16(int16_t value);
uint16_conversion_result_type safer_uint16_from_uint16(uint16_t value);
uint16_conversion_result_type safer_uint16_from_int32(int32_t value);
uint16_conversion_result_type safer_uint16_from_uint32(uint32_t value);
uint16_conversion_result_type safer_uint16_from_int64(int64_t value);
uint16_conversion_result_type safer_uint16_from_uint64(uint64_t value);

/* int32_t conversions */
typedef struct int32_conversion_result_type
{
	int32_t value;
	integer_conversion_error_type error;
} int32_conversion_result_type;

int32_conversion_result_type safer_int32_from_int8(int8_t value);
int32_conversion_result_type safer_int32_from_uint8(uint8_t value);
int32_conversion_result_type safer_int32_from_int16(int16_t value);
int32_conversion_result_type safer_int32_from_uint16(uint16_t value);
int32_conversion_result_type safer_int32_from_int32(int32_t value);
int32_conversion_result_type safer_int32_from_uint32(uint32_t value);
int32_conversion_result_type safer_int32_from_int64(int64_t value);
int32_conversion_result_type safer_int32_from_uint64(uint64_t value);

/* uint32_t conversions */
typedef struct uint32_conversion_result_type
{
	uint32_t value;
	integer_conversion_error_type error;
} uint32_conversion_result_type;

uint32_conversion_result_type safer_uint32_from_int8(int8_t value);
uint32_conversion_result_type safer_uint32_from_uint8(uint8_t value);
uint32_conversion_result_type safer_uint32_from_int16(int16_t value);
uint32_conversion_result_type safer_uint32_from_uint16(uint16_t value);
uint32_conversion_result_type safer_uint32_from_int32(int32_t value);
uint32_conversion_result_type safer_uint32_from_uint32(uint32_t value);
uint32_conversion_result_type safer_uint32_from_int64(int64_t value);
uint32_conversion_result_type safer_uint32_from_uint64(uint64_t value);

/* int64_t conversions */
typedef struct int64_conversion_result_type
{
	int64_t value;
	integer_conversion_error_type error;
} int64_conversion_result_type;

int64_conversion_result_type safer_int64_from_int8(int8_t value);
int64_conversion_result_type safer_int64_from_uint8(uint8_t value);
int64_conversion_result_type safer_int64_from_int16(int16_t value);
int64_conversion_result_type safer_int64_from_uint16(uint16_t value);
int64_conversion_result_type safer_int64_from_int32(int32_t value);
int64_conversion_result_type safer_int64_from_uint32(uint32_t value);
int64_conversion_result_type safer_int64_from_int64(int64_t value);
int64_conversion_result_type safer_int64_from_uint64(uint64_t value);

/* uint64_t conversions */
typedef struct uint64_conversion_result_type
{
	uint64_t value;
	integer_conversion_error_type error;
} uint64_conversion_result_type;

uint64_conversion_result_type safer_uint64_from_int8(int8_t value);
uint64_conversion_result_type safer_uint64_from_uint8(uint8_t value);
uint64_conversion_result_type safer_uint64_from_int16(int16_t value);
uint64_conversion_result_type safer_uint64_from_uint16(uint16_t value);
uint64_conversion_result_type safer_uint64_from_int32(int32_t value);
uint64_conversion_result_type safer_uint64_from_uint32(uint32_t value);
uint64_conversion_result_type safer_uint64_from_int64(int64_t value);
uint64_conversion_result_type safer_uint64_from_uint64(uint64_t value);

#ifdef __cplusplus
}
#endif

#endif
