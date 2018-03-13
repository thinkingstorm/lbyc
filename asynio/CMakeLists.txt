cmake_minimum_required(VERSION 2.8)

set(asynio_src 	dllmain.cpp 
				filereadimpl.cpp
				filewriteimpl.cpp
				asynioimpl.cpp
				tcpsocketimpl.cpp
				sys_file.cpp)
			
	
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

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(asynio SHARED ${asynio_src})

set_target_properties(asynio PROPERTIES OUTPUT_NAME "asynio")

set_target_properties(asynio PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -fPIC -std=c++11 -frtti -Wall -Werror -fexceptions")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(asynio PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(asynio PROPERTIES COMPILE_FLAGS "-O3")
endif()


target_link_libraries(asynio dl)

install(TARGETS asynio 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
