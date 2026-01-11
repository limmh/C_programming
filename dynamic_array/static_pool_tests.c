#include "fixed_width_integer_types.h"
#include "static_pool.h"
#include "static_assert.h"
#include "unit_testing.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

STATIC_ASSERT(sizeof(uintptr_t) == sizeof(void*), "The size of uintptr_t must be the same as the size of a pointer type.");

static void print_LHS_and_RHS_as_addresses(uintptr_t LHS, uintptr_t RHS)
{
	printf("LHS: %p, RHS: %p\n", (const void*) LHS, (const void*) RHS);
}

#define COMPARE_ADDRESSES(LHS, OPERATOR, RHS) COMPARE_USING_OPERATOR(uintptr_t, LHS, OPERATOR, RHS, print_LHS_and_RHS_as_addresses)
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
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 1U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk1);
	memcpy(memory, &byte_value, sizeof(byte_value));

	memory = static_pool_reallocate(&pool, memory, 2U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk2);
	ASSERT(memcmp(memory, &byte_value, sizeof(byte_value)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_2_bytes_to_more_bytes, "Initial size: 2")
{
	const unsigned char byte_values[2] = {'A', 'B'};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 2U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk2);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 3U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk3);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_4_bytes_to_more_bytes, "Initial size: 4")
{
	const unsigned char byte_values[4] = {'A','B','C','D'};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 4U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk3);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 5U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk4);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_8_bytes_to_more_bytes, "Initial size: 8")
{
	const unsigned char byte_values[8] = {'A','B','C','D','E','F','G','H'};
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 8U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk4);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 9U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk5);
	ASSERT(memcmp(memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_16_bytes_to_more_bytes, "Initial size: 16")
{
	const unsigned char byte_values[16] = {
		'A','B','C','D','E','F','G','H',
		'I','J','K','L','M','N','O','P'
	};
	static_pool_type pool = {0};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 16U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk5);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 17U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk6);
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
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 32U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk6);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 33U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk7);
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
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 64U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk7);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 65U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk8);
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
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 128U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk8);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 129U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk9);
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
	static_pool_type pool = {0U};
	void *memory = NULL;

	memory = static_pool_allocate(&pool, 256U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk9);
	memcpy(memory, byte_values, sizeof(byte_values));

	memory = static_pool_reallocate(&pool, memory, 257U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk10);
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

	static_pool_deallocate(&pool, memory);
}

TEST(from_512_bytes_to_256_bytes, "Initial size: 512")
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

	new_memory = static_pool_reallocate(&pool, memory, 256U);
	ASSERT_ADDRESSES_EQUAL(new_memory, pool.chunk9);
	ASSERT(memcmp(new_memory, byte_values, sizeof(byte_values)) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_128_bytes_to_64_bytes, "Initial size: 128")
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
	static_pool_type pool = {0U};
	void *memory = NULL;
	void *new_memory = NULL;

	memory = static_pool_allocate(&pool, 128U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk8);
	memcpy(memory, byte_values, sizeof(byte_values));

	new_memory = static_pool_reallocate(&pool, memory, 64U);
	ASSERT_ADDRESSES_EQUAL(new_memory, pool.chunk7);
	ASSERT(memcmp(new_memory, byte_values, 64U) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(from_64_bytes_to_32_bytes, "Initial size: 64")
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
	static_pool_type pool = {0U};
	void *memory = NULL;
	void *new_memory = NULL;

	memory = static_pool_allocate(&pool, 64U);
	ASSERT_ADDRESSES_EQUAL(memory, pool.chunk7);
	memcpy(memory, byte_values, sizeof(byte_values));

	new_memory = static_pool_reallocate(&pool, memory, 32U);
	ASSERT_ADDRESSES_EQUAL(new_memory, pool.chunk6);
	ASSERT(memcmp(new_memory, byte_values, 32U) == 0);

	static_pool_deallocate(&pool, memory);
}

TEST(largest_chunk_size, "Largest chunk size")
{
	const size_t largest_chunk_size = static_pool_largest_chunk_size();
	ASSERT_EQUAL(largest_chunk_size, 512U);
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
		from_512_bytes_to_256_bytes,
		from_128_bytes_to_64_bytes,
		from_64_bytes_to_32_bytes,
		largest_chunk_size
	};

	PRINT_FILE_NAME();
	RUN_TESTS(tests);
	PRINT_TEST_STATISTICS(tests);

	return 0;
}
