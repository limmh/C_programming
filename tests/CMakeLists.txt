if (NOT DEFINED PROGRAM_C_STANDARD)
	message("PROGRAM_C_STANDARD was not defined for programs.")
	if (${CMAKE_C_COMPILER_ID} STREQUAL "MSVC")
		set(PROGRAM_C_STANDARD "11")
	else()
		set(PROGRAM_C_STANDARD "99")
	endif()
	message("PROGRAM_C_STANDARD is defined as ${PROGRAM_C_STANDARD}.")
endif()

# Programs
add_executable(
	string_reference_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/string_reference_tests.c"
)
set_target_properties(
	string_reference_tests PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	string_reference_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	string_reference_tests
	terminal_text_color
	unit_testing
)
