cmake_minimum_required(VERSION 3.5)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(MY_C_FLAGS, "-Wall -Wextra -Wpedantic")
endif()

project(C_programming)

set(DIR "${CMAKE_CURRENT_SOURCE_DIR}")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MY_C_FLAGS}")
endif()

# Libraries
add_library(dynamic_array STATIC "${DIR}/dynamic_array/dynamic_array.c" "${DIR}/dynamic_array/dynamic_array.h")
target_compile_options(dynamic_array PRIVATE -DNDEBUG)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(dynamic_array PRIVATE -std=c89)
endif()
target_include_directories(dynamic_array PRIVATE "${DIR}/includes")

add_library(simple_tokenizer STATIC "${DIR}/simple_tokenizer/simple_tokenizer.c" "${DIR}/simple_tokenizer/simple_tokenizer.h")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(simple_tokenizer PRIVATE -std=c89)
endif()
target_include_directories(simple_tokenizer PRIVATE "${DIR}/includes" "${DIR}/simple_tokenizer")

add_library(terminal_text_color STATIC "${DIR}/terminal_text_color/terminal_text_color.c" "${DIR}/terminal_text_color/terminal_text_color.h")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(terminal_text_color PRIVATE -std=c89)
endif()
target_include_directories(terminal_text_color PRIVATE "${DIR}/includes")

add_library(unit_testing STATIC "${DIR}/unit_testing/unit_testing.c" "${DIR}/unit_testing/unit_testing.h")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(unit_testing PRIVATE -std=c89)
endif()
target_include_directories(unit_testing PRIVATE "${DIR}/includes" "${DIR}/terminal_text_color")
target_link_libraries(unit_testing terminal_text_color)

# Tests
add_executable(dynamic_array_tests "${DIR}/dynamic_array/dynamic_array_tests.c" "${DIR}/dynamic_array/static_pool.c")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(dynamic_array_tests PRIVATE -std=c89)
endif()
target_include_directories(dynamic_array_tests PRIVATE "${DIR}/includes" "${DIR}/dynamic_array" "${DIR}/unit_testing")
target_link_libraries(dynamic_array_tests dynamic_array terminal_text_color unit_testing)

add_executable(simple_tokenizer_tests "${DIR}/simple_tokenizer/simple_tokenizer_tests.c")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(dynamic_array_tests PRIVATE -std=c89)
endif()
target_include_directories(simple_tokenizer_tests PRIVATE "${DIR}/includes" "${DIR}/simple_tokenizer" "${DIR}/unit_testing")
target_link_libraries(simple_tokenizer_tests simple_tokenizer terminal_text_color unit_testing)

add_executable(static_pool_tests "${DIR}/dynamic_array/static_pool_tests.c" "${DIR}/dynamic_array/static_pool.c")
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(static_pool_tests PRIVATE -std=c89)
endif()
target_include_directories(static_pool_tests PRIVATE "${DIR}/includes" "${DIR}/dynamic_array" "${DIR}/unit_testing")
target_link_libraries(static_pool_tests terminal_text_color unit_testing)

add_executable(unit_testing_example unit_testing/unit_testing_example.c)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(unit_testing_example PRIVATE -std=c89)
endif()
target_include_directories(unit_testing_example PRIVATE "${DIR}/includes" "${DIR}/unit_testing")
target_link_libraries(unit_testing_example terminal_text_color unit_testing)

# Programs
add_executable(binary_viewer "${DIR}/programs/binary_viewer.c")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(binary_viewer PRIVATE -std=c99)
endif()
target_include_directories(binary_viewer PRIVATE "${DIR}/includes" "${DIR}/dynamic_array")
target_link_libraries(binary_viewer dynamic_array)

add_executable(evaluate_expression "${DIR}/programs/evaluate_expression.c")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(evaluate_expression PRIVATE -std=c99)
endif()
target_include_directories(evaluate_expression PRIVATE "${DIR}/includes" "${DIR}/dynamic_array" "${DIR}/simple_tokenizer")
target_link_libraries(evaluate_expression dynamic_array simple_tokenizer)
