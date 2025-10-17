if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for simple_tokenizer.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

# library
add_library(
	simple_tokenizer STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/simple_tokenizer.h"
)
set_target_properties(
	simple_tokenizer PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
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
set_target_properties(
	simple_tokenizer_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
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
