file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(StixxImplVulkan
	${sources}
	${headers}
	${shaders}
) 

set(VULKAN_ROOT "C:/VulkanSDK/1.0.57.0")
set(VULKAN_INCL ${VULKAN_ROOT}/Include)
set(VULKAN_LIBS ${VULKAN_ROOT}/Lib/vulkan-1.Lib)

target_include_directories(StixxImplVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${VULKAN_INCL}>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(StixxImplVulkan StixxCore ${VULKAN_LIBS})

install(DIRECTORY include DESTINATION include/stixx)

install(TARGETS StixxImplVulkan
		EXPORT 	StixxImplVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxImplVulkan-targets FILE StixxImplVulkan-config.cmake DESTINATION lib/cmake/StixxImplVulkan)
