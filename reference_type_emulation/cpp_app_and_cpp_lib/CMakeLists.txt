set_source_files_properties(
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test_code.c" PROPERTIES
	LANGUAGE CXX
)

add_executable(
	ABI_compatibility_test_between_cpp_app_and_cpp_lib
	"${CMAKE_CURRENT_SOURCE_DIR}/../ABI_compatibility_test_code.c"
)
set_target_properties(
	ABI_compatibility_test_between_cpp_app_and_cpp_lib PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_include_directories(
	ABI_compatibility_test_between_cpp_app_and_cpp_lib PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/.."
	"${CMAKE_CURRENT_SOURCE_DIR}/../../includes"
)
target_link_libraries(
	ABI_compatibility_test_between_cpp_app_and_cpp_lib
	ABI_compatibility_test_cpp
)
