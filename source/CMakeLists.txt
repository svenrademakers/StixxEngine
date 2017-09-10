cmake_minimum_required(VERSION 3.8)
project (opengl_game_engine)

find_package(assimp REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(SxCoreLib)

add_executable(TheGame MACOSX_BUNDLE main.cpp ShaderGL.cpp MeshGL.cpp)

target_include_directories(TheGame 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIR}>
	PRIVATE
		$<BUILD_INTERFACE:/shaders>)
		
find_library(COCOA Cocoa)
find_library(OPENGL OpenGl)
find_library(IOKIT IOKit)
find_library(COREVIDEO CoreVideo)

target_link_libraries(TheGame SxCoreLib glfw ${ASSIMP_LIBRARY} ${COCOA} ${OPENGL} ${COREVIDEO} ${IOKIT} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})

#add_subdirectory(examples)
