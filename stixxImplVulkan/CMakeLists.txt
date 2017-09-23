file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(StixxImplVulkan STATIC
	${sources}
	${headers}
	${shaders}
)

find_package (Vulkan REQUIRED HINTS /home/sven/stixx/external/glfw/CMake/modules)

target_include_directories(StixxImplVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(StixxImplVulkan StixxCore ${Vulkan_LIBRARIES} vulkan)
target_compile_features(StixxImplVulkan PUBLIC cxx_override cxx_inheriting_constructors)
install(DIRECTORY include DESTINATION include/stixx)

install(TARGETS StixxImplVulkan
		EXPORT 	StixxImplVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxImplVulkan-targets FILE StixxImplVulkan-config.cmake DESTINATION lib/cmake/StixxImplVulkan)

#find_package(gtest REQUIRED)
#find_package(GTest REQUIRED)


add_executable(micro_tests_vulkan
	test/test.cpp)
#	test/TestAntHost.cpp
#	test/TestHbAlgo.cpp
#	test/TestMapController.cpp
#	test/TestSensorSniffer.cpp)

#target_compile_features(micro_tests PUBLIC cxx_default_function_template_args)

target_link_libraries(micro_tests_vulkan gtest gmock)
install(TARGETS micro_tests_vulkan DESTINATION bin)