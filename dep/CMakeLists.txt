# edu-spice dependencies

# LUA
if (WIN32)
	set(LUA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lua-5.4.2/lua-5.4.2-win64/")
	target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${LUA_DIR}/include/")
	target_link_libraries("${CMAKE_PROJECT_NAME}" PUBLIC "${LUA_DIR}/lua54.lib")
	execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different "${LUA_DIR}/lua54.dll" "${CMAKE_BINARY_DIR}/lua54.dll")
else()
	message(FATAL_ERROR "Lua support for linux is not complete")
endif()
