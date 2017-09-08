cmake_minimum_required(VERSION 3.8)
project (opengl_game_engine)

#glfw rommel
add_subdirectory(external/glfw)

add_executable(TheGame main.cpp)
target_include_directories(TheGame 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>)
		
find_library(COCOA Cocoa)
find_library(OPENGL OpenGl)
find_library(IOKIT IOKit)
find_library(COREVIDEO CoreVideo)

target_link_libraries(TheGame glfw3 ${COCOA} ${OPENGL} ${COREVIDEO} ${IOKIT} ${GLFW_STATIC_LIBRARIES})
