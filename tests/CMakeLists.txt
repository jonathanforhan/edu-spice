macro(GenTest test_name)
	add_executable("${test_name}_test" "${test_name}/${test_name}.cpp")
	target_link_libraries("${test_name}_test" "${CMAKE_PROJECT_NAME}")
	add_test(NAME "${test_name}_test" COMMAND "${test_name}_test" "${CMAKE_CURRENT_SOURCE_DIR}/${test_name}/ckt.lua")

	add_custom_command(
		TARGET "${test_name}_test"
		POST_BUILD
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMAND ${CMAKE_CTEST_COMMAND} -R "^${test_name}$" "--output-on-failure"
	)
endmacro()

GenTest("ohms_law")