cmake_minimum_required(VERSION 3.2.2)
project (stixx)

if(WIN32)
SET(gtest_force_shared_crt on CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.") 
endif()

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)

add_subdirectory(stixxCore)
add_subdirectory(stixxVulkan)
add_subdirectory(stixxShaders)
add_subdirectory(stixxViewer)

