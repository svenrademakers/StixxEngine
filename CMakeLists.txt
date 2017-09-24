cmake_minimum_required(VERSION 3.5.1)
project (stixx)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/googletest)

add_subdirectory(stixxCore)
add_subdirectory(stixxImplVulkan)
add_subdirectory(stixxShaders)
add_subdirectory(examples)
