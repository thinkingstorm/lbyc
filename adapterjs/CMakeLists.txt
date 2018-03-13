cmake_minimum_required(VERSION 2.8)

set(adapterjs_src 	dllmain.cpp
					adapterjavascriptimpl.cpp)
					
	
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/extensions/include)
include_directories(${by3rd_library_include})
include_directories(/usr/local/include/)


link_directories(${PROJECT_SOURCE_DIR}/3rd/node-v8.9.3/out/Release/obj.target)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_library(adapterjs SHARED ${adapterjs_src})
set_target_properties(adapterjs PROPERTIES OUTPUT_NAME "adapterjs")
set_target_properties(adapterjs PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -std=c++11 -fpermissive -fPIC -frtti -fexceptions")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(adapterjs PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(adapterjs PROPERTIES COMPILE_FLAGS "-O3")
endif()

target_link_libraries(adapterjs dl pthread)

install(TARGETS adapterjs 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
