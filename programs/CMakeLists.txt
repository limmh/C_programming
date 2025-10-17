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
	binary_viewer
	"${CMAKE_CURRENT_SOURCE_DIR}/binary_viewer.c"
)
set_target_properties(
	binary_viewer PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	binary_viewer PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../dynamic_array"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
)
target_link_libraries(
	binary_viewer
	dynamic_array
)

add_executable(
	byte_writer
	"${CMAKE_CURRENT_SOURCE_DIR}/byte_writer.c")
set_target_properties(
	byte_writer PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	byte_writer PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../dynamic_array"
)
target_link_libraries(
	byte_writer
	dynamic_array
)

add_executable(
	evaluate_expression
	"${CMAKE_CURRENT_SOURCE_DIR}/evaluate_expression.c"
)
set_target_properties(
	evaluate_expression PROPERTIES
	C_STANDARD ${PROGRAM_C_STANDARD}
	C_STANDARD_REQUIRED YES
	C_EXTENSIONS NO
)
target_include_directories(
	evaluate_expression PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../dynamic_array"
	"${CMAKE_CURRENT_SOURCE_DIR}/../includes"
	"${CMAKE_CURRENT_SOURCE_DIR}/../simple_tokenizer"
)
target_link_libraries(
	evaluate_expression
	dynamic_array
	simple_tokenizer
)
