cmake_minimum_required(VERSION 2.8)

set(mempool_src 	dllmain.cpp
					mempoolimpl.cpp
					palloc.cpp
					alloc.cpp)
	
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

add_library(mempool SHARED ${mempool_src})

set_target_properties(mempool PROPERTIES OUTPUT_NAME "mempool")

set_target_properties(mempool PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -std=c++11 -fpermissive -fPIC -frtti -fexceptions")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(mempool PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(mempool PROPERTIES COMPILE_FLAGS "-O3")
endif()

target_link_libraries(mempool dl crypt)

install(TARGETS mempool 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
