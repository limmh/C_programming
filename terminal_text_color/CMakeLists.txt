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

add_library(
	terminal_text_color STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/terminal_text_color.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/terminal_text_color.h"
)
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		terminal_text_color PRIVATE
		-std=${LIBRARY_C_STANDARD}
	)
endif()
target_include_directories(
	terminal_text_color PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
