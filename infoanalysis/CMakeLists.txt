cmake_minimum_required(VERSION 2.8)

set(infoanalysis_src 	dllmain.cpp
						infoanalysisimpl.cpp
						cjson.cpp
						cjson_utils.cpp
						json.cpp
						crootimpl.cpp)

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

add_library(infoanalysis SHARED ${infoanalysis_src})

set_target_properties(infoanalysis PROPERTIES OUTPUT_NAME "infoanalysis")

set_target_properties(infoanalysis PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -fPIC -std=c++11 -frtti -Wall -Werror -fexceptions")


if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(infoanalysis PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(infoanalysis PROPERTIES COMPILE_FLAGS "-O3")
endif()


target_link_libraries(infoanalysis dl)

install(TARGETS infoanalysis 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
