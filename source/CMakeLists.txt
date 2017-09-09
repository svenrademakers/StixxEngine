cmake_minimum_required(VERSION 3.8)
project (opengl_game_engine)

add_subdirectory(external/glfw)
find_package(GLEW REQUIRED)

add_subdirectory(SxCoreLib)

add_executable(TheGame MACOSX_BUNDLE main.cpp ShaderGl.cpp GameContainerMac.cpp)

target_include_directories(TheGame 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>)
		
find_library(COCOA Cocoa)
find_library(OPENGL OpenGl)
find_library(IOKIT IOKit)
find_library(COREVIDEO CoreVideo)

target_link_libraries(TheGame SxCoreLib glfw ${COCOA} ${OPENGL} ${COREVIDEO} ${IOKIT} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})

add_subdirectory(examples)