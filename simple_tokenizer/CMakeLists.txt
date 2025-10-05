if (NOT DEFINED COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang|IntelLLVM|XLClang|IBMClang")
		set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS YES)
	else()
		set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS NO)
	endif()
endif()

if (NOT DEFINED LIBRARY_C_STANDARD)
	set(LIBRARY_C_STANDARD "c89")
endif()

if (NOT DEFINED PROGRAM_C_STANDARD)
	set(PROGRAM_C_STANDARD "c99")
endif()

# library
add_library(
	simple_tokenizer STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer.h"
)
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		simple_tokenizer PRIVATE
		-std=${LIBRARY_C_STANDARD}
	)
endif()
target_include_directories(
	simple_tokenizer PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

# test program
add_executable(
	simple_tokenizer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer_tests.c"
)
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		dynamic_array_tests PRIVATE
		-std=${PROGRAM_C_STANDARD}
	)
endif()
target_include_directories(
	simple_tokenizer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing")
target_link_libraries(
	simple_tokenizer_tests
	simple_tokenizer
	terminal_text_color
	unit_testing
)
