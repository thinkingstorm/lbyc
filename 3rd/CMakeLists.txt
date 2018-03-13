cmake_minimum_required(VERSION 2.8.0)
project(3rd)

#The below line was built error on Android Studio
#string(TOUPPER ${CMAKE_SYSTEM_NAME} OS_NAME)
if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(CMAKE_MACOSX_RPATH build)
endif()


if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(CMAKE_BUILD_TYPE Release)
else()
	set(CMAKE_BUILD_TYPE debug)
endif()


set(3rd_library_output 	"${PROJECT_SOURCE_DIR}/lib" 				CACHE INTERNAL "3rd Library" )
set(3rd_library_execute "${PROJECT_SOURCE_DIR}/3rdexecute/debug" 	CACHE INTERNAL "3rd execute" )
set(3rd_library_include "${PROJECT_SOURCE_DIR}/include" 			CACHE INTERNAL "3rd include" )
set(3rd 				"${PROJECT_SOURCE_DIR}" 					CACHE INTERNAL "3rd" )

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}) 
set(CMAKE_INSTALL_LIBDIR ${PROJECT_SOURCE_DIR}) 


message(STATUS "3rd_library_output: ${3rd_library_output}")
message(STATUS "3rd_library_include: ${3rd_library_include}")
message(STATUS "3rd_library_execute: ${3rd_library_execute}")
message(STATUS "3rd: ${PROJECT_SOURCE_DIR}")



#add_subdirectory(lib_acl)




add_subdirectory(libyang)
add_subdirectory(libssh-0.7.5)
add_subdirectory(libnetconf2)

#if (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Android")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	#add_subdirectory(lib_fiber/c fiber)
	#add_subdirectory(lib_fiber/cpp fiber_cpp)
endif()
