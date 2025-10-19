if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for safer_integer.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

# library
add_library(
	safer_integer STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer.h"
)
set_target_properties(
	safer_integer PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safer_integer PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

# test program
add_executable(
	safer_integer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_tests.c"
)
set_target_properties(
	safer_integer_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safer_integer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safer_integer_tests
	safer_integer
	terminal_text_color
	unit_testing
)
