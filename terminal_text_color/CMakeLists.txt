if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for terminal_text_color.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

add_library(
	terminal_text_color STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/terminal_text_color.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/terminal_text_color.h"
)
set_target_properties(
	terminal_text_color PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	terminal_text_color PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
