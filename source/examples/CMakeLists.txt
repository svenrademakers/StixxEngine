cmake_minimum_required(VERSION 3.8)

add_subdirectory(../external/glfw)
find_package(GLEW REQUIRED)

add_executable(orangeBox_example MACOSX_BUNDLE main.cpp)

target_include_directories(orangeBox_example 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>)
		
find_library(COCOA Cocoa)
find_library(OPENGL OpenGl)
find_library(IOKIT IOKit)
find_library(COREVIDEO CoreVideo)

target_link_libraries(orangeBox_example glfw ${COCOA} ${OPENGL} ${COREVIDEO} ${IOKIT} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
