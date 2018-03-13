cmake_minimum_required(VERSION 2.8)

set(sshchannel_src 	dllmain.cpp
					sshchannelimpl.cpp)
					
	
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


link_directories(/usr/lib/x86_64-linux-gnu)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_library(sshchannel SHARED ${sshchannel_src})

set_target_properties(sshchannel PROPERTIES OUTPUT_NAME "sshchannel")

set_target_properties(sshchannel PROPERTIES COMPILE_FLAGS "-fvisibility=hidden -std=c++11 -fpermissive -fPIC -frtti -fexceptions")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(sshchannel PROPERTIES COMPILE_FLAGS "-g3")
endif()

if(CMAKE_BUILD_TYPE STREQUAL Release)
	set_target_properties(sshchannel PROPERTIES COMPILE_FLAGS "-O3")
endif()


install(TARGETS sshchannel 
	LIBRARY DESTINATION bin
	ARCHIVE DESTINATION bin)
