cmake_minimum_required(VERSION 3.5)

project(C_programming)

set(LIBRARY_C_STANDARD "90")

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang|IntelLLVM|XLClang|IBMClang")
	set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS YES)
	set(CUSTOM_C_FLAGS "-Wall -Wconversion -Wextra -Wpedantic")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUSTOM_C_FLAGS}")
	set(PROGRAM_C_STANDARD "99")
elseif(${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
	set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS NO)
	set(PROGRAM_C_STANDARD "11")
else()
	set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS NO)
	se(PROGRAM_C_STANDARD "99")
endif()

# For debugging purpose
message("Compiler: ${CMAKE_C_COMPILER_ID}")
message("C Standard used for building libraries: ${LIBRARY_C_STANDARD}")
message("C Standard used for building programs: ${PROGRAM_C_STANDARD}")
message("Compiler supports GNU compiler flags: ${COMPILER_SUPPORTS_GNU_COMPILER_FLAGS}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/terminal_text_color")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/unit_testing")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/programs")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/safer_integer")
