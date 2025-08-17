#include "static_pool.h"
#include "static_assert.h"
#include "unit_testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

STATIC_ASSERT(sizeof(size_t) == sizeof(void*), "The size of size_t must be the same as the size of a pointer type.");

static void print_LHS_and_RHS_as_addresses(size_t LHS, size_t RHS)
{
	printf("LHS: %p, RHS: %p\n", (const void*) LHS, (const void*) RHS);
}

#define COMPARE_ADDRESSES(LHS, OPERATOR, RHS) COMPARE_USING_OPERATOR(size_t, LHS, OPERATOR, RHS, print_LHS_and_RHS_as_addresses)
#define ASSERT_ADDRESSES_EQUAL(LHS, RHS) COMPARE_ADDRESSES(LHS, ==, RHS)

TEST(from_0_byte_to_more_bytes, "Initial size: 0")
{
	const unsigned char byte_value = 'A';
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 0U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk1);
	memcpy(memory, &byte_value, sizeof(byte_value));

	memory = static_pool_reallocate(&pool, memory, 1U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk1);
	ASSERT(memcmp(memory, &byte_value, sizeof(byte_value)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_1_byte_to_more_bytes, "Initial size: 1")
{
	const unsigned char byte_value = 'A';
	const unsigned char zero_byte = 0U;
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 1U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk1);
	memcpy(memory, &byte_value, sizeof(byte_value));

	memory = static_pool_reallocate(&pool, memory, 2U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk2);
	ASSERT(memcmp(pool.chunk1, &zero_byte, sizeof(zero_byte)) == 0);
	ASSERT(memcmp(memory, &byte_value, sizeof(byte_value)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_2_bytes_to_more_bytes, "Initial size: 2")
{
	const unsigned char byte_values[2] = {'A', 'B'};
	const unsigned char zero_bytes[2] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 2U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk2);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 3U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk3);
	ASSERT(memcmp(pool.chunk2, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_4_bytes_to_more_bytes, "Initial size: 4")
{
	const unsigned char byte_values[4] = {'A','B','C','D'};
	const unsigned char zero_bytes[4] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 4U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk3);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 5U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk4);
	ASSERT(memcmp(pool.chunk3, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_8_bytes_to_more_bytes, "Initial size: 8")
{
	const unsigned char byte_values[8] = {'A','B','C','D','E','F','G','H'};
	const unsigned char zero_bytes[8] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 8U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk4);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 9U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk5);
	ASSERT(memcmp(pool.chunk4, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_16_bytes_to_more_bytes, "Initial size: 16")
{
	const unsigned char byte_values[16] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P'
	};
	const unsigned char zero_bytes[16] = {0U};
	static_pool_type pool = {0};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 16U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk5);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 17U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk6);
	ASSERT(memcmp(pool.chunk5, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_32_bytes_to_more_bytes, "Initial size: 32")
{
	const unsigned char byte_values[32] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f'
	};
	const unsigned char zero_bytes[32] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 32U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk6);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 33U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk7);
	ASSERT(memcmp(pool.chunk6, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_64_bytes_to_more_bytes, "Initial size: 64")
{
	const unsigned char byte_values[64] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9',',','.'
	};
	const unsigned char zero_bytes[64] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 64U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk7);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 65U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk8);
	ASSERT(memcmp(pool.chunk7, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_128_bytes_to_more_bytes, "Initial size: 128")
{
	const unsigned char byte_values[128] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9',',','.'
	};
	const unsigned char zero_bytes[128] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 128U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk8);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 129U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk9);
	ASSERT(memcmp(pool.chunk8, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_256_bytes_to_more_bytes, "Initial size: 256")
{
	const unsigned char byte_values[256] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9',',','.'
	};
	const unsigned char zero_bytes[256] = {0U};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 256U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk9);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 257U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk10);
	ASSERT(memcmp(pool.chunk9, zero_bytes, sizeof(zero_bytes)) == 0);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_512_bytes_to_more_bytes, "Initial size: 512 [Use case with failure]")
{
	const unsigned char byte_values[512] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P',
		'Q','R','S','T','U','V','W','X',
		'Y','Z','a','b','c','d','e','f',
		'g','h','i','j','k','l','m','n',
		'o','p','q','r','s','t','u','v',
		'w','x','y','z','0','1','2','3',
		'4','5','6','7','8','9',',','.'
	};
	static_pool_type pool = {0U};
	void *memory = NULL;
	void *new_memory = NULL;

	memory = static_pool_allocate(&pool, 512U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk10);
	memcpy(memory, byte_values, sizeof(byte_values));

	new_memory = static_pool_reallocate(&pool, memory, 513U);
	ASSERT_ADDRESSES_EQUAL(new_memory, NULL);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

int main(void)
{
	DEFINE_LIST_OF_TESTS(tests) {
		from_0_byte_to_more_bytes,
		from_1_byte_to_more_bytes,
		from_2_bytes_to_more_bytes,
		from_4_bytes_to_more_bytes,
		from_8_bytes_to_more_bytes,
		from_16_bytes_to_more_bytes,
		from_32_bytes_to_more_bytes,
		from_64_bytes_to_more_bytes,
		from_128_bytes_to_more_bytes,
		from_256_bytes_to_more_bytes,
		from_512_bytes_to_more_bytes,
	};

	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);

	return 0;
}
