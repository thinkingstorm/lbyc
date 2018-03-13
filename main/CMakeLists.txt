cmake_minimum_required(VERSION 2.8)

set(main_src main.cpp)

if (${UNIX_OS})
	include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/extensions/include
		${by3rd_library_include}
		/usr/local/include
		/opt/local/include
		/usr/include
		)
elseif (${WIN_OS})

else()

endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(main ${main_src})

set_target_properties(main PROPERTIES OUTPUT_NAME "main")

set_target_properties(main PROPERTIES COMPILE_FLAGS "-std=c++11 -Wall -Werror -fexceptions")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(main PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(main PROPERTIES COMPILE_FLAGS "-O3")
endif()



link_directories (/usr/local/lib)
target_link_libraries(main dl)
install(TARGETS main DESTINATION bin)


