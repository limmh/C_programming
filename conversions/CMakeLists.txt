if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD is not defined.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

add_library(
	conversion STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/integer_to_string.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/integer_to_string.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer.h"
)
set_target_properties(
	conversion PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	conversion PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
)
target_link_libraries(
	conversion
	safer_integer
)

add_executable(
	integer_to_string_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/integer_to_string_tests.c"
)
set_target_properties(
	integer_to_string_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	integer_to_string_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	integer_to_string_tests
	conversion
	safer_integer
	terminal_text_color
	unit_testing
)

add_executable(
	string_to_integer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/string_to_integer_tests.c"
)
set_target_properties(
	string_to_integer_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	string_to_integer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../safer_integer"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	string_to_integer_tests
	conversion
	safer_integer
	terminal_text_color
	unit_testing
)
