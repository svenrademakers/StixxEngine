cmake_minimum_required(VERSION 3.8.2)

set(STIXX_MAJOR_VERSION 0)
set(STIXX_MINOR_VERSION 1)
set(STIXX_PATCH_VERSION 0)
set(STIXX_VERSION ${STIXX_MAJOR_VERSION}.${STIXX_MINOR_VERSION}.${STIXX_PATCH_VERSION})
message(STATUS "StixxCore version ${STIXX_VERSION}")

option(STIXX_ASSIMP "Build Assimp implementation for AssetLoader interfaces" OFF)
option(STIXX_MICROTESTS "Build micro tests" ON)

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

if(STIXX_ASSIMP)
	list(APPEND sources ${CMAKE_CURRENT_SOURCE_DIR}/assimp/src/AssetImporterAssimp.cpp)
	list(APPEND headers ${CMAKE_CURRENT_SOURCE_DIR}/assimp/include/AssetImporterAssimp.hpp)
endif()

add_library(StixxCore
	${sources}
	${headers}
)

set_target_properties(StixxCore PROPERTIES
	OUTPUT_NAME StixxCore
	DEBUG_POSTFIX -d
	VERSION ${STIXX_VERSION}
	SOVERSION ${STIXX_MAJOR_VERSION}
	FOLDER stixxCore
)

set_property(TARGET StixxCore PROPERTY CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

target_include_directories(StixxCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)
		
	
target_link_libraries(StixxCore glfw glm)

install(DIRECTORY include interfaces DESTINATION include)

install(TARGETS StixxCore
		EXPORT 	StixxCore-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxCore-targets FILE StixxCore-config.cmake DESTINATION lib/cmake/StixxCore)

if(STIXX_ASSIMP)
	include(assimp/assimp.cmake)
endif()

if(STIXX_MICROTESTS)
	add_subdirectory(test)
endif()

