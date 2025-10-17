if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for unit_testing.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

# library
add_library(
	unit_testing STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/unit_testing.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/unit_testing.h"
)
set_target_properties(
	unit_testing PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
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
set_target_properties(
	unit_testing_example PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
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
