if (NOT DEFINED PROGRAM_C_STANDARD)
	message("PROGRAM_C_STANDARD is not defined for dynamic_array.")
	set(PROGRAM_C_STANDARD "90")
	message("PROGRAM_C_STANDARD is defined as ${PROGRAM_C_STANDARD}.")
endif()

set_source_files_properties(
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test_code.c" PROPERTIES
	LANGUAGE C
)

add_executable(
	ABI_compatibility_test_between_c_app_and_c_lib
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test_code.c"
)
set_target_properties(
	ABI_compatibility_test_between_c_app_and_c_lib PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	ABI_compatibility_test_between_c_app_and_c_lib PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../../includes"
)
target_link_libraries(
	ABI_compatibility_test_between_c_app_and_c_lib
	ABI_compatibility_test
)
