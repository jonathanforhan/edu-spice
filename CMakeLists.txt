cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
project(edu-spice-lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
enable_testing()

if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	cmake_policy(SET CMP0079 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_library("${CMAKE_PROJECT_NAME}" STATIC
"src/SpiceEngine.cpp"
"src/SpiceComponent.cpp"
)
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "src")

add_subdirectory("deps")
add_subdirectory("tests")

add_executable("edu-spice" "src/main.cpp" "src/SpiceComponent.cpp")
target_link_libraries("edu-spice" PUBLIC "${CMAKE_PROJECT_NAME}")
