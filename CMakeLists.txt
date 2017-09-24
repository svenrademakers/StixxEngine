cmake_minimum_required(VERSION 3.2.2)
project (stixx)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)

add_subdirectory(stixx)
add_subdirectory(stixxVulkan)
add_subdirectory(stixxShaders)
add_subdirectory(examples)
