cmake_minimum_required(VERSION 3.5)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(MY_C_FLAGS, "-Wall -Wpedantic")
endif()

project(C_programming)

include_directories(includes)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MY_C_FLAGS}")
endif()

add_library(dynamic_array STATIC  dynamic_array/dynamic_array.c dynamic_array/dynamic_array.h)
target_compile_options(dynamic_array PRIVATE -DNDEBUG)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(dynamic_array PRIVATE -std=c89)
endif()

add_library(terminal_text_color STATIC terminal_text_color/terminal_text_color.c terminal_text_color/terminal_text_color.h)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(terminal_text_color PRIVATE -std=c89)
endif()

add_library(unit_testing STATIC unit_testing/unit_testing.c unit_testing/unit_testing.h)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(unit_testing PRIVATE -std=c89)
endif()
target_include_directories(unit_testing PRIVATE terminal_text_color)
target_link_libraries(unit_testing terminal_text_color)

add_executable(dynamic_array_tests dynamic_array/dynamic_array_tests.c dynamic_array/static_pool.c)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(dynamic_array_tests PRIVATE -std=c89)
endif()
target_include_directories(dynamic_array_tests PRIVATE dynamic_array unit_testing)
target_link_libraries(dynamic_array_tests dynamic_array terminal_text_color unit_testing)

add_executable(static_pool_tests dynamic_array/static_pool_tests.c dynamic_array/static_pool.c)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(static_pool_tests PRIVATE -std=c89)
endif()
target_include_directories(static_pool_tests PRIVATE dynamic_array unit_testing)
target_link_libraries(static_pool_tests terminal_text_color unit_testing)

add_executable(unit_testing_example unit_testing/unit_testing_example.c)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(unit_testing_example PRIVATE -std=c89)
endif()
target_include_directories(unit_testing_example PRIVATE unit_testing)
target_link_libraries(unit_testing_example terminal_text_color unit_testing)

add_executable(binary_viewer programs/binary_viewer.c)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(binary_viewer PRIVATE -std=c99)
endif()
target_include_directories(binary_viewer PRIVATE dynamic_array)
target_link_libraries(binary_viewer dynamic_array)
