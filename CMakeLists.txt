cmake_minimum_required(VERSION 3.8.2)
project (stixxEngine)

SET(STIXX_ASSIMP ON CACHE BOOL "Enable build of assimp implementations")
SET(STIXX_GLFW ON CACHE BOOL "Enable build of glfw implementation")
add_subdirectory(stixx)

add_subdirectory(stixxVulkan)
add_subdirectory(stixxShaders)
add_subdirectory(stixxViewer)

