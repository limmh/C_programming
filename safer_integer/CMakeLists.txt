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
	safer_integer_type_runtime_tests_c89
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_runtime_tests_c89 PROPERTIES
	C_STANDARD 90
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safer_integer_type_runtime_tests_c89 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

add_executable(
	safer_integer_type_runtime_tests_c99
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_runtime_tests_c99 PROPERTIES
	C_STANDARD 99
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_runtime_tests_c99 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

add_executable(
	safer_integer_type_runtime_tests_c11
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_runtime_tests_c11 PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_runtime_tests_c11 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

add_executable(
	safer_integer_type_runtime_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_runtime_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_runtime_tests PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_compile_options(
	safer_integer_type_runtime_tests PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_include_directories(
	safer_integer_type_runtime_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

add_executable(
	safer_integer_type_tests_c89
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_c89 PROPERTIES
	C_STANDARD 90
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS YES
)
target_include_directories(
	safer_integer_type_tests_c89 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safer_integer_type_tests_c89
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_c99
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_c99 PROPERTIES
	C_STANDARD 99
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_c99 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safer_integer_type_tests_c99
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_c11
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_c11 PROPERTIES
	C_STANDARD 11
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_c11 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	safer_integer_type_tests_c11
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
)
target_compile_options(
	safer_integer_type_tests PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_cpp98
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_cpp98 PROPERTIES
	CXX_STANDARD 98
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS YES
)
target_include_directories(
	safer_integer_type_tests_cpp98 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_cpp98 PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
)
target_compile_options(
	safer_integer_type_tests_cpp98 PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_cpp98
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_cpp11
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_cpp11 PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_cpp11 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_cpp11 PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
)
target_compile_options(
	safer_integer_type_tests_cpp11 PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_cpp11
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_cpp14
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_cpp14 PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_cpp14 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_cpp14 PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
)
target_compile_options(
	safer_integer_type_tests_cpp14 PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_cpp14
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_cpp17
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_cpp17 PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_cpp17 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_cpp17 PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
)
target_compile_options(
	safer_integer_type_tests_cpp17 PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_cpp17
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_no_source_info
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_no_source_info PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_no_source_info PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_no_source_info PRIVATE
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
)
target_compile_options(
	safer_integer_type_tests_no_source_info PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_no_source_info
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_no_exception
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_no_exception PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_no_exception PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_no_exception PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
)
target_compile_options(
	safer_integer_type_tests_no_exception PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_no_exception
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_use_saturated_results
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_use_saturated_results PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_use_saturated_results PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_use_saturated_results PRIVATE
	-DSAFER_INTEGER_TYPE_INCLUDE_SOURCE_FILE_INFO
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_FOR_UNINITIALIZED_VARIABLES
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_THROW_CPLUSPLUS_EXCEPTIONS_ON_OPERATION_ERRORS
	-DSAFER_INTEGER_TYPE_APPLY_SATURATED_RESULTS
)
target_compile_options(
	safer_integer_type_tests_use_saturated_results PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_use_saturated_results
	terminal_text_color
	unit_testing
)

# No exception, no error reporting
add_executable(
	safer_integer_type_tests_use_saturated_results_2
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_use_saturated_results_2 PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_use_saturated_results_2 PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_use_saturated_results_2 PRIVATE
	-DSAFER_INTEGER_TYPE_APPLY_SATURATED_RESULTS
	-DSAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_CONVERSION_ERRORS
	-DSAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_OPERATION_ERRORS
	-DSAFER_INTEGER_TYPE_DISABLE_REPORTING_FOR_UNINITIALIZED_VARIABLES
)
target_compile_options(
	safer_integer_type_tests_use_saturated_results_2 PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_use_saturated_results_2
	terminal_text_color
	unit_testing
)

add_executable(
	safer_integer_type_tests_no_runtime_checks
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type_tests.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/safer_integer_type.h"
)
set_target_properties(
	safer_integer_type_tests_no_runtime_checks PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	safer_integer_type_tests_no_runtime_checks PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_compile_options(
	safer_integer_type_tests_no_runtime_checks PRIVATE
	-DSAFER_INTEGER_TYPE_USE_BUILTIN_INTEGER_TYPES
)
target_compile_options(
	safer_integer_type_tests_no_runtime_checks PRIVATE
	$<$<CXX_COMPILER_ID:MSVC>:/permissive- /Zc:__cplusplus>
)
target_link_libraries(
	safer_integer_type_tests_no_runtime_checks
	terminal_text_color
	unit_testing
)
