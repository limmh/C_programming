#ifndef SAFER_INTEGER_CONVERSION_H
#define SAFER_INTEGER_CONVERSION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum integer_conversion_error_type
{
	integer_conversion_error_none = 0,
	integer_conversion_error_negative_signed_value_smaller_than_minimum_of_target_signed_integer,
	integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_signed_integer,
	integer_conversion_error_unsigned_value_greater_than_maximum_of_target_signed_integer,
	integer_conversion_error_negative_signed_value_cannot_be_represented_by_unsigned_integer,
	integer_conversion_error_positive_signed_value_greater_than_maximum_of_target_unsigned_integer,
	integer_conversion_error_unsigned_value_greater_than_maximum_of_target_unsigned_integer
} integer_conversion_error_type;

const char *integer_conversion_error_message(integer_conversion_error_type error);

typedef struct char_conversion_result_type
{
	char value;
	integer_conversion_error_type error;
} char_conversion_result_type;

char_conversion_result_type safer_char_from_char(char value);
char_conversion_result_type safer_char_from_schar(signed char value);
char_conversion_result_type safer_char_from_uchar(unsigned char value);
char_conversion_result_type safer_char_from_short(short value);
char_conversion_result_type safer_char_from_ushort(unsigned short value);
char_conversion_result_type safer_char_from_int(int value);
char_conversion_result_type safer_char_from_uint(unsigned int value);
char_conversion_result_type safer_char_from_long(long value);
char_conversion_result_type safer_char_from_ulong(unsigned long value);
char_conversion_result_type safer_char_from_llong(long long value);
char_conversion_result_type safer_char_from_ullong(unsigned long long value);

typedef struct schar_conversion_result_type
{
	signed char value;
	integer_conversion_error_type error;
} schar_conversion_result_type;

schar_conversion_result_type safer_schar_from_char(char value);
schar_conversion_result_type safer_schar_from_schar(signed char value);
schar_conversion_result_type safer_schar_from_uchar(unsigned char value);
schar_conversion_result_type safer_schar_from_short(short value);
schar_conversion_result_type safer_schar_from_ushort(unsigned short value);
schar_conversion_result_type safer_schar_from_int(int value);
schar_conversion_result_type safer_schar_from_uint(unsigned int value);
schar_conversion_result_type safer_schar_from_long(long value);
schar_conversion_result_type safer_schar_from_ulong(unsigned long value);
schar_conversion_result_type safer_schar_from_llong(long long value);
schar_conversion_result_type safer_schar_from_ullong(unsigned long long value);

typedef struct uchar_conversion_result_type
{
	unsigned char value;
	integer_conversion_error_type error;
} uchar_conversion_result_type;

uchar_conversion_result_type safer_uchar_from_char(char value);
uchar_conversion_result_type safer_uchar_from_schar(signed char value);
uchar_conversion_result_type safer_uchar_from_uchar(unsigned char value);
uchar_conversion_result_type safer_uchar_from_short(short value);
uchar_conversion_result_type safer_uchar_from_ushort(unsigned short value);
uchar_conversion_result_type safer_uchar_from_int(int value);
uchar_conversion_result_type safer_uchar_from_uint(unsigned int value);
uchar_conversion_result_type safer_uchar_from_long(long value);
uchar_conversion_result_type safer_uchar_from_ulong(unsigned long value);
uchar_conversion_result_type safer_uchar_from_llong(long long value);
uchar_conversion_result_type safer_uchar_from_ullong(unsigned long long value);

typedef struct short_conversion_result_type
{
	short value;
	integer_conversion_error_type error;
} short_conversion_result_type;

short_conversion_result_type safer_short_from_char(char value);
short_conversion_result_type safer_short_from_schar(signed char value);
short_conversion_result_type safer_short_from_uchar(unsigned char value);
short_conversion_result_type safer_short_from_short(short value);
short_conversion_result_type safer_short_from_ushort(unsigned short value);
short_conversion_result_type safer_short_from_int(int value);
short_conversion_result_type safer_short_from_uint(unsigned int value);
short_conversion_result_type safer_short_from_long(long value);
short_conversion_result_type safer_short_from_ulong(unsigned long value);
short_conversion_result_type safer_short_from_llong(long long value);
short_conversion_result_type safer_short_from_ullong(unsigned long long value);

typedef struct ushort_conversion_result_type
{
	unsigned short value;
	integer_conversion_error_type error;
} ushort_conversion_result_type;

ushort_conversion_result_type safer_ushort_from_char(char value);
ushort_conversion_result_type safer_ushort_from_schar(signed char value);
ushort_conversion_result_type safer_ushort_from_uchar(unsigned char value);
ushort_conversion_result_type safer_ushort_from_short(short value);
ushort_conversion_result_type safer_ushort_from_ushort(unsigned short value);
ushort_conversion_result_type safer_ushort_from_int(int value);
ushort_conversion_result_type safer_ushort_from_uint(unsigned int value);
ushort_conversion_result_type safer_ushort_from_long(long value);
ushort_conversion_result_type safer_ushort_from_ulong(unsigned long value);
ushort_conversion_result_type safer_ushort_from_llong(long long value);
ushort_conversion_result_type safer_ushort_from_ullong(unsigned long long value);

typedef struct int_conversion_result_type
{
	int value;
	integer_conversion_error_type error;
} int_conversion_result_type;

int_conversion_result_type safer_int_from_char(char value);
int_conversion_result_type safer_int_from_schar(signed char value);
int_conversion_result_type safer_int_from_uchar(unsigned char value);
int_conversion_result_type safer_int_from_short(short value);
int_conversion_result_type safer_int_from_ushort(unsigned short value);
int_conversion_result_type safer_int_from_int(int value);
int_conversion_result_type safer_int_from_uint(unsigned int value);
int_conversion_result_type safer_int_from_long(long value);
int_conversion_result_type safer_int_from_ulong(unsigned long value);
int_conversion_result_type safer_int_from_llong(long long value);
int_conversion_result_type safer_int_from_ullong(unsigned long long value);

typedef struct uint_conversion_result_type
{
	unsigned int value;
	integer_conversion_error_type error;
} uint_conversion_result_type;

uint_conversion_result_type safer_uint_from_char(char value);
uint_conversion_result_type safer_uint_from_schar(signed char value);
uint_conversion_result_type safer_uint_from_uchar(unsigned char value);
uint_conversion_result_type safer_uint_from_short(short value);
uint_conversion_result_type safer_uint_from_ushort(unsigned short value);
uint_conversion_result_type safer_uint_from_int(int value);
uint_conversion_result_type safer_uint_from_uint(unsigned int value);
uint_conversion_result_type safer_uint_from_long(long value);
uint_conversion_result_type safer_uint_from_ulong(unsigned long value);
uint_conversion_result_type safer_uint_from_llong(long long value);
uint_conversion_result_type safer_uint_from_ullong(unsigned long long value);

typedef struct long_conversion_result_type
{
	long value;
	integer_conversion_error_type error;
} long_conversion_result_type;

long_conversion_result_type safer_long_from_char(char value);
long_conversion_result_type safer_long_from_schar(signed char value);
long_conversion_result_type safer_long_from_uchar(unsigned char value);
long_conversion_result_type safer_long_from_short(short value);
long_conversion_result_type safer_long_from_ushort(unsigned short value);
long_conversion_result_type safer_long_from_int(int value);
long_conversion_result_type safer_long_from_uint(unsigned int value);
long_conversion_result_type safer_long_from_long(long value);
long_conversion_result_type safer_long_from_ulong(unsigned long value);
long_conversion_result_type safer_long_from_llong(long long value);
long_conversion_result_type safer_long_from_ullong(unsigned long long value);

typedef struct ulong_conversion_result_type
{
	unsigned long value;
	integer_conversion_error_type error;
} ulong_conversion_result_type;

ulong_conversion_result_type safer_ulong_from_char(char value);
ulong_conversion_result_type safer_ulong_from_schar(signed char value);
ulong_conversion_result_type safer_ulong_from_uchar(unsigned char value);
ulong_conversion_result_type safer_ulong_from_short(short value);
ulong_conversion_result_type safer_ulong_from_ushort(unsigned short value);
ulong_conversion_result_type safer_ulong_from_int(int value);
ulong_conversion_result_type safer_ulong_from_uint(unsigned int value);
ulong_conversion_result_type safer_ulong_from_long(long value);
ulong_conversion_result_type safer_ulong_from_ulong(unsigned long value);
ulong_conversion_result_type safer_ulong_from_llong(long long value);
ulong_conversion_result_type safer_ulong_from_ullong(unsigned long long value);

typedef struct llong_conversion_result_type
{
	long long value;
	integer_conversion_error_type error;
} llong_conversion_result_type;

llong_conversion_result_type safer_llong_from_char(char value);
llong_conversion_result_type safer_llong_from_schar(signed char value);
llong_conversion_result_type safer_llong_from_uchar(unsigned char value);
llong_conversion_result_type safer_llong_from_short(short value);
llong_conversion_result_type safer_llong_from_ushort(unsigned short value);
llong_conversion_result_type safer_llong_from_int(int value);
llong_conversion_result_type safer_llong_from_uint(unsigned int value);
llong_conversion_result_type safer_llong_from_long(long value);
llong_conversion_result_type safer_llong_from_ulong(unsigned long value);
llong_conversion_result_type safer_llong_from_llong(long long value);
llong_conversion_result_type safer_llong_from_ullong(unsigned long long value);

typedef struct ullong_conversion_result_type
{
	unsigned long long value;
	integer_conversion_error_type error;
} ullong_conversion_result_type;

ullong_conversion_result_type safer_ullong_from_char(char value);
ullong_conversion_result_type safer_ullong_from_schar(signed char value);
ullong_conversion_result_type safer_ullong_from_uchar(unsigned char value);
ullong_conversion_result_type safer_ullong_from_short(short value);
ullong_conversion_result_type safer_ullong_from_ushort(unsigned short value);
ullong_conversion_result_type safer_ullong_from_int(int value);
ullong_conversion_result_type safer_ullong_from_uint(unsigned int value);
ullong_conversion_result_type safer_ullong_from_long(long value);
ullong_conversion_result_type safer_ullong_from_ulong(unsigned long value);
ullong_conversion_result_type safer_ullong_from_llong(long long value);
ullong_conversion_result_type safer_ullong_from_ullong(unsigned long long value);

#ifdef __cplusplus
}
#endif

#endif
