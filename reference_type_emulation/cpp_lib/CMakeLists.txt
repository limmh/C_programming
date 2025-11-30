set_source_files_properties(
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test.c" PROPERTIES
	LANGUAGE CXX
)

add_library(
	ABI_compatibility_test_cpp STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test.h"
)
set_target_properties(
	ABI_compatibility_test_cpp PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	ABI_compatibility_test_cpp PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../../includes"
)
