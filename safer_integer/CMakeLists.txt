if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD was not defined for safer_integer.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

if (NOT DEFINED PROGRAM_C_STANDARD)
	message("PROGRAM_C_STANDARD was not defined for safer_integer.")
	set(PROGRAM_C_STANDARD "99")
	message("PROGRAM_C_STANDARD is defined as ${PROGRAM_C_STANDARD}.")
endif()

# library
add_library(
	safer_integer STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_fixed_width_integers.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_fixed_width_integers.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/debug_mode_integer.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/debug_mode_integer.h"
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

add_executable(
	safer_fixed_width_integer_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_fixed_width_integer_tests.c"
)
set_target_properties(
	safer_fixed_width_integer_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safer_fixed_width_integer_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safer_fixed_width_integer_tests
	safer_integer
	terminal_text_color
	unit_testing
)

add_executable(
	debug_mode_integer_runtime_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/debug_mode_integer_runtime_tests.c"
)
set_target_properties(
	debug_mode_integer_runtime_tests PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	debug_mode_integer_runtime_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	debug_mode_integer_runtime_tests
	safer_integer
)

add_executable(
	debug_mode_integer_runtime_tests_saturation
	"${CMAKE_CURRENT_SOURCE_DIR}/debug_mode_integer_runtime_tests.c"
)
target_compile_options(
	debug_mode_integer_runtime_tests_saturation PRIVATE
	-DINTEGER_RESULT_MODE=INTEGER_RESULT_MODE_SATURATION
)
set_target_properties(
	debug_mode_integer_runtime_tests_saturation PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	debug_mode_integer_runtime_tests_saturation PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	debug_mode_integer_runtime_tests_saturation
	safer_integer
)

add_executable(
	debug_mode_integer_runtime_tests_wraparound
	"${CMAKE_CURRENT_SOURCE_DIR}/debug_mode_integer_runtime_tests.c"
)
target_compile_options(
	debug_mode_integer_runtime_tests_wraparound PRIVATE
	-DINTEGER_RESULT_MODE=INTEGER_RESULT_MODE_WRAPAROUND
)
set_target_properties(
	debug_mode_integer_runtime_tests_wraparound PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	debug_mode_integer_runtime_tests_wraparound PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	debug_mode_integer_runtime_tests_wraparound
	safer_integer
)

add_executable(
	debug_mode_integer_runtime_tests_unchecked
	"${CMAKE_CURRENT_SOURCE_DIR}/debug_mode_integer_runtime_tests.c"
)
target_compile_options(
	debug_mode_integer_runtime_tests_unchecked PRIVATE
	-DINTEGER_DEBUG_MODE_ENABLED=0
)
set_target_properties(
	debug_mode_integer_runtime_tests_unchecked PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	debug_mode_integer_runtime_tests_unchecked PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	debug_mode_integer_runtime_tests_unchecked
	safer_integer
)

add_executable(
	safer_integer_comparison_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_comparison_tests.c"
)
set_target_properties(
	safer_integer_comparison_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safer_integer_comparison_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safer_integer_comparison_tests
	terminal_text_color
	unit_testing
)

add_executable(
	safe_bitwise_operation_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safe_bitwise_operation_tests.c"
)
set_target_properties(
	safe_bitwise_operation_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safe_bitwise_operation_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safe_bitwise_operation_tests
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_runtime_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.cpp"
)
set_target_properties(
	safer_integer_type_runtime_tests PROPERTIES
	CXX_STANDARD 98
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS YES
)
target_include_directories(
	safer_integer_type_runtime_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
