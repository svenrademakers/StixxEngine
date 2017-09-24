file(GLOB_RECURSE tests *.cpp)
add_executable(vulkan_microtests ${tests})

target_include_directories(vulkan_microtests
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_link_libraries(vulkan_microtests StixxImplVulkan gtest gmock)
install(TARGETS vulkan_microtests DESTINATION bin)
