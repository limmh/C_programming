if (NOT DEFINED COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang|IntelLLVM|XLClang|IBMClang")
		set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS YES)
	else()
		set(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS NO)
	endif()
endif()

if (NOT DEFINED LIBRARY_C_STANDARD)
	set(LIBRARY_C_STANDARD "c89")
endif()

if (NOT DEFINED PROGRAM_C_STANDARD)
	set(PROGRAM_C_STANDARD "c99")
endif()

# Programs
add_executable(
	binary_viewer
	"${CMAKE_CURRENT_SOURCE_DIR}/binary_viewer.c"
)
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		binary_viewer PRIVATE
		-std=${PROGRAM_C_STANDARD}
	)
endif()
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
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		byte_writer PRIVATE
		-std=${PROGRAM_C_STANDARD}
	)
endif()
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
if(COMPILER_SUPPORTS_GNU_COMPILER_FLAGS)
	target_compile_options(
		evaluate_expression PRIVATE
		-std=${PROGRAM_C_STANDARD}
	)
endif()
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
