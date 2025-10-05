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
	unit_testing STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/unit_testing.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/unit_testing.h"
)
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		unit_testing PRIVATE
		-std=${LIBRARY_C_STANDARD}
	)
endif()
target_include_directories(
	unit_testing PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../terminal_text_color"
)
target_link_libraries(
	unit_testing
	terminal_text_color
)

# test program
add_executable(
	unit_testing_example
	"${CMAKE_CURRENT_SOURCE_DIR}/unit_testing_example.c"
)
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		unit_testing_example PRIVATE
		-std=${PROGRAM_C_STANDARD}
	)
endif()
target_include_directories(
	unit_testing_example PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	unit_testing_example
	terminal_text_color
	unit_testing
)
