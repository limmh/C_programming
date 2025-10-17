if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD is not defined for dynamic_array.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

# library 1
add_library(
	dynamic_array STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.h"
)
target_compile_options(
	dynamic_array PRIVATE
	-DNDEBUG
)
set_target_properties(
	dynamic_array PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	dynamic_array PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

# library 2
add_library(
	dynamic_array_debug STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.h"
)
target_compile_options(
	dynamic_array_debug PRIVATE
	-DDYNAMIC_ARRAY_NO_RUNTIME_CHECKS
)
set_target_properties(
	dynamic_array_debug PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	dynamic_array_debug PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

# library 3
add_library(
	dynamic_array_unsafe STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array.h"
)
target_compile_options(
	dynamic_array_unsafe PRIVATE
	-DNDEBUG
	-DDYNAMIC_ARRAY_NO_RUNTIME_CHECKS
)
set_target_properties(
	dynamic_array_unsafe PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	dynamic_array_unsafe PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

# library 4
add_library(
	static_pool STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/static_pool.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/static_pool.h"
)
set_target_properties(
	static_pool PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	static_pool PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)

# Tests
# test program 1
add_executable(
	dynamic_array_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array_tests.c"
)
set_target_properties(
	dynamic_array_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_compile_options(
	dynamic_array_tests PRIVATE
	-DNDEBUG
)
target_include_directories(
	dynamic_array_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	dynamic_array_tests
	dynamic_array
	static_pool
	terminal_text_color
	unit_testing
)

# test program 2
add_executable(
	dynamic_array_tests_no_realloc
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array_tests.c"
)
set_target_properties(
	dynamic_array_tests_no_realloc PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_compile_options(
	dynamic_array_tests_no_realloc PRIVATE
	-DNDEBUG
	-DDYNAMIC_ARRAY_TESTS_DO_NOT_USE_REALLOCATION_FUNCTION
)
target_include_directories(
	dynamic_array_tests_no_realloc PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	dynamic_array_tests_no_realloc
	dynamic_array
	static_pool
	terminal_text_color
	unit_testing
)

# test program 3
add_executable(
	dynamic_array_tests_debug
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array_tests.c"
)
set_target_properties(
	dynamic_array_tests_debug PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_compile_options(
	dynamic_array_tests_debug PRIVATE
	-DDYNAMIC_ARRAY_EXCEPTION_TESTS_DISABLED
)
target_include_directories(
	dynamic_array_tests_debug PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	dynamic_array_tests_debug
	dynamic_array_debug
	static_pool
	terminal_text_color
	unit_testing
)

# test program 4
add_executable(
	dynamic_array_tests_no_realloc_debug
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array_tests.c"
)
set_target_properties(
	dynamic_array_tests_no_realloc_debug PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_compile_options(
	dynamic_array_tests_no_realloc_debug PRIVATE
	-DDYNAMIC_ARRAY_EXCEPTION_TESTS_DISABLED
	-DDYNAMIC_ARRAY_TESTS_DO_NOT_USE_REALLOCATION_FUNCTION
)
target_include_directories(
	dynamic_array_tests_no_realloc_debug PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	dynamic_array_tests_no_realloc_debug
	dynamic_array_debug
	static_pool
	terminal_text_color
	unit_testing
)

# test program 5
add_executable(
	dynamic_array_tests_unsafe
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array_tests.c"
)
set_target_properties(
	dynamic_array_tests_unsafe PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_compile_options(
	dynamic_array_tests_unsafe PRIVATE
	-DDYNAMIC_ARRAY_EXCEPTION_TESTS_DISABLED
)
target_include_directories(
	dynamic_array_tests_unsafe PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	dynamic_array_tests_unsafe
	dynamic_array_unsafe
	static_pool
	terminal_text_color
	unit_testing
)

# test program 6
add_executable(
	dynamic_array_tests_no_realloc_unsafe
	"${CMAKE_CURRENT_SOURCE_DIR}/dynamic_array_tests.c"
)
set_target_properties(
	dynamic_array_tests_no_realloc_unsafe PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_compile_options(
	dynamic_array_tests_no_realloc_unsafe PRIVATE
	-DDYNAMIC_ARRAY_EXCEPTION_TESTS_DISABLED
	-DDYNAMIC_ARRAY_TESTS_DO_NOT_USE_REALLOCATION_FUNCTION
)
target_include_directories(
	dynamic_array_tests_no_realloc_unsafe PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	dynamic_array_tests_no_realloc_unsafe
	dynamic_array_unsafe
	static_pool
	terminal_text_color
	unit_testing
)

# test program 7
add_executable(
	static_pool_tests
	"${CMAKE_CURRENT_SOURCE_DIR}/static_pool_tests.c"
)
set_target_properties(
	static_pool_tests PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	static_pool_tests PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../unit_testing"
)
target_link_libraries(
	static_pool_tests
	static_pool
	terminal_text_color
	unit_testing
)
