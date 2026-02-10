#include "safer_fixed_width_integer_conversion.h"

/* int8_t conversions */

int8_conversion_result_type safer_int8_from_int8(int8_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int8_conversion_result_type safer_int8_from_uint8(uint8_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if ((int) value > (int) INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

int8_conversion_result_type safer_int8_from_int16(int16_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT8_MIN) {
		result.value = INT8_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

int8_conversion_result_type safer_int8_from_uint16(uint16_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if ((int32_t) value > (int32_t) INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

int8_conversion_result_type safer_int8_from_int32(int32_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT8_MIN) {
		result.value = INT8_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

int8_conversion_result_type safer_int8_from_uint32(uint32_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint32_t) INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

int8_conversion_result_type safer_int8_from_int64(int64_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT8_MIN) {
		result.value = INT8_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

int8_conversion_result_type safer_int8_from_uint64(uint64_t value)
{
	int8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint64_t) INT8_MAX) {
		result.value = INT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int8_t) value;
	}
	return result;
}

/* uint8_t conversions */

uint8_conversion_result_type safer_uint8_from_int8(int8_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

uint8_conversion_result_type safer_uint8_from_uint8(uint8_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint8_conversion_result_type safer_uint8_from_int16(int16_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int16_t) UINT8_MAX) {
		result.value = UINT8_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

uint8_conversion_result_type safer_uint8_from_uint16(uint16_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UINT8_MAX) {
		result.value = UINT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

uint8_conversion_result_type safer_uint8_from_int32(int32_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int32_t) UINT8_MAX) {
		result.value = UINT8_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

uint8_conversion_result_type safer_uint8_from_uint32(uint32_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UINT8_MAX) {
		result.value = UINT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

uint8_conversion_result_type safer_uint8_from_int64(int64_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int64_t) UINT8_MAX) {
		result.value = UINT8_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

uint8_conversion_result_type safer_uint8_from_uint64(uint64_t value)
{
	uint8_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UINT8_MAX) {
		result.value = UINT8_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint8_t) value;
	}
	return result;
}

/* int16_t conversions */

int16_conversion_result_type safer_int16_from_int8(int8_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int16_conversion_result_type safer_int16_from_uint8(uint8_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (int16_t) value;
	return result;
}

int16_conversion_result_type safer_int16_from_int16(int16_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int16_conversion_result_type safer_int16_from_uint16(uint16_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	if ((unsigned int) value > (unsigned int) INT16_MAX) {
		result.value = INT16_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int16_t) value;
	}
	return result;
}

int16_conversion_result_type safer_int16_from_int32(int32_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT16_MIN) {
		result.value = INT16_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT16_MAX) {
		result.value = INT16_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int16_t) value;
	}
	return result;
}

int16_conversion_result_type safer_int16_from_uint32(uint32_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint32_t) INT16_MAX) {
		result.value = INT16_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int16_t) value;
	}
	return result;
}

int16_conversion_result_type safer_int16_from_int64(int64_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT16_MIN) {
		result.value = INT16_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT16_MAX) {
		result.value = INT16_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int16_t) value;
	}
	return result;
}

int16_conversion_result_type safer_int16_from_uint64(uint64_t value)
{
	int16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint64_t) INT16_MAX) {
		result.value = INT16_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int16_t) value;
	}
	return result;
}

/* uint16_t conversions */

uint16_conversion_result_type safer_uint16_from_int8(int8_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint16_t) value;
	}
	return result;
}

uint16_conversion_result_type safer_uint16_from_uint8(uint8_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint16_conversion_result_type safer_uint16_from_int16(int16_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint16_t) value;
	}
	return result;
}

uint16_conversion_result_type safer_uint16_from_uint16(uint16_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint16_conversion_result_type safer_uint16_from_int32(int32_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int32_t) UINT16_MAX) {
		result.value = UINT16_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint16_t) value;
	}
	return result;
}

uint16_conversion_result_type safer_uint16_from_uint32(uint32_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UINT16_MAX) {
		result.value = UINT16_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint16_t) value;
	}
	return result;
}

uint16_conversion_result_type safer_uint16_from_int64(int64_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int64_t) UINT16_MAX) {
		result.value = UINT16_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint16_t) value;
	}
	return result;
}

uint16_conversion_result_type safer_uint16_from_uint64(uint64_t value)
{
	uint16_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UINT16_MAX) {
		result.value = UINT16_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint16_t) value;
	}
	return result;
}

/* int32_t conversions */

int32_conversion_result_type safer_int32_from_int8(int8_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int32_conversion_result_type safer_int32_from_uint8(uint8_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (int32_t) value;
	return result;
}

int32_conversion_result_type safer_int32_from_int16(int16_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int32_conversion_result_type safer_int32_from_uint16(uint16_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (int32_t) value;
	return result;
}

int32_conversion_result_type safer_int32_from_int32(int32_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int32_conversion_result_type safer_int32_from_uint32(uint32_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint32_t) INT32_MAX) {
		result.value = INT32_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int32_t) value;
	}
	return result;
}

int32_conversion_result_type safer_int32_from_int64(int64_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < INT32_MIN) {
		result.value = INT32_MIN;
		result.error = integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer;
	} else if (value > INT32_MAX) {
		result.value = INT32_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int32_t) value;
	}
	return result;
}

int32_conversion_result_type safer_int32_from_uint64(uint64_t value)
{
	int32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint64_t) INT32_MAX) {
		result.value = INT32_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int32_t) value;
	}
	return result;
}

/* uint32_t conversions */

uint32_conversion_result_type safer_uint32_from_int8(int8_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint32_t) value;
	}
	return result;
}

uint32_conversion_result_type safer_uint32_from_uint8(uint8_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint32_conversion_result_type safer_uint32_from_int16(int16_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint32_t) value;
	}
	return result;
}

uint32_conversion_result_type safer_uint32_from_uint16(uint16_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint32_conversion_result_type safer_uint32_from_int32(int32_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint32_t) value;
	}
	return result;
}

uint32_conversion_result_type safer_uint32_from_uint32(uint32_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint32_conversion_result_type safer_uint32_from_int64(int64_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else if (value > (int64_t) UINT32_MAX) {
		result.value = UINT32_MAX;
		result.error = integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint32_t) value;
	}
	return result;
}

uint32_conversion_result_type safer_uint32_from_uint64(uint64_t value)
{
	uint32_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > UINT32_MAX) {
		result.value = UINT32_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer;
	} else {
		result.value = (uint32_t) value;
	}
	return result;
}

/* int64_t conversions */

int64_conversion_result_type safer_int64_from_int8(int8_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int64_conversion_result_type safer_int64_from_uint8(uint8_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (int64_t) value;
	return result;
}

int64_conversion_result_type safer_int64_from_int16(int16_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int64_conversion_result_type safer_int64_from_uint16(uint16_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (int64_t) value;
	return result;
}

int64_conversion_result_type safer_int64_from_int32(int32_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int64_conversion_result_type safer_int64_from_uint32(uint32_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = (int64_t) value;
	return result;
}

int64_conversion_result_type safer_int64_from_int64(int64_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

int64_conversion_result_type safer_int64_from_uint64(uint64_t value)
{
	int64_conversion_result_type result = {0, integer_conversion_error_none};
	if (value > (uint64_t) INT64_MAX) {
		result.value = INT64_MAX;
		result.error = integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer;
	} else {
		result.value = (int64_t) value;
	}
	return result;
}

/* uint64_t conversions */

uint64_conversion_result_type safer_uint64_from_int8(int8_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint64_t) value;
	}
	return result;
}

uint64_conversion_result_type safer_uint64_from_uint8(uint8_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint64_conversion_result_type safer_uint64_from_int16(int16_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint64_t) value;
	}
	return result;
}

uint64_conversion_result_type safer_uint64_from_uint16(uint16_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint64_conversion_result_type safer_uint64_from_int32(int32_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint64_t) value;
	}
	return result;
}

uint64_conversion_result_type safer_uint64_from_uint32(uint32_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}

uint64_conversion_result_type safer_uint64_from_int64(int64_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	if (value < 0) {
		result.value = 0U;
		result.error = integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer;
	} else {
		result.value = (uint64_t) value;
	}
	return result;
}

uint64_conversion_result_type safer_uint64_from_uint64(uint64_t value)
{
	uint64_conversion_result_type result = {0, integer_conversion_error_none};
	result.value = value;
	return result;
}
