cmake_minimum_required(VERSION 2.8)

set(adapterpy_src 	dllmain.cpp
					adapterpyimpl.cpp)
					
if (${UNIX_OS})
	include_directories(
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}//extensions/include
		${by3rd_library_include}
		/usr/local/include
		/opt/local/include
		/usr/include
		/usr/include/python3.4m
		)
elseif (${WIN_OS})

else()

endif()


set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_library(adapterpy SHARED ${adapterpy_src})
set_target_properties(adapterpy PROPERTIES OUTPUT_NAME "adapterpy")
set_target_properties(adapterpy PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -std=c++11 -fpermissive -fPIC -frtti -fexceptions")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(adapterpy PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(adapterpy PROPERTIES COMPILE_FLAGS "-O3")
endif()


link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries(adapterpy dl crypt m libpython3.4m.so)

install(TARGETS adapterpy 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
