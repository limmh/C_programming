cmake_minimum_required(VERSION 3.5)

project(C_programming)

set(LIBRARY_C_STANDARD "c89")
set(PROGRAM_C_STANDARD "c99")

if(${CMAKE_C_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
	set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS YES)
	set(CUSTOM_C_FLAGS "-Wall -Wextra -Wpedantic")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUSTOM_C_FLAGS}")
else()
	set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS NO)
endif()

# For debugging purpose
message("Compiler: ${CMAKE_C_COMPILER_ID}")
message("Standard used for building libraries: ${LIBRARY_C_STANDARD}")
message("Standard used for building programs: ${PROGRAM_C_STANDARD}")
message("Compiler supports GNU compiler flags: ${COMPILER_SUPPORTS_GNU_COMPILER_FLAGS}")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/terminal_text_color")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/unit_testing")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/programs")
