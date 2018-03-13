cmake_minimum_required(VERSION 2.8)

set(adapterlua_src 	dllmain.cpp
					adapterluaimpl.cpp)
					
if (${UNIX_OS})
	include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}//extensions/include
		${by3rd_library_include}
		/usr/local/include
		/opt/local/include
		/usr/include
		)
elseif (${WIN_OS})

else()

endif()


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_library(adapterlua SHARED ${adapterlua_src})
set_target_properties(adapterlua PROPERTIES OUTPUT_NAME "adapterlua")
set_target_properties(adapterlua PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -std=c++11 -fpermissive -fPIC -frtti -fexceptions")


if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(adapterlua PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(adapterlua PROPERTIES COMPILE_FLAGS "-O3")
endif()



target_link_libraries(adapterlua dl crypt m lua5.1)

install(TARGETS adapterlua 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
