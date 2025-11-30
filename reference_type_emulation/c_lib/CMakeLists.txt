if (NOT DEFINED LIBRARY_C_STANDARD)
	message("LIBRARY_C_STANDARD is not defined for dynamic_array.")
	set(LIBRARY_C_STANDARD "90")
	message("LIBRARY_C_STANDARD is defined as ${LIBRARY_C_STANDARD}.")
endif()

set_source_files_properties(
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test.c" PROPERTIES
	LANGUAGE C
)

add_library(
	ABI_compatibility_test STATIC
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test.h"
)
set_target_properties(
	ABI_compatibility_test PROPERTIES
	C_STANDARD ${LIBRARY_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	ABI_compatibility_test PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../../includes"
)
