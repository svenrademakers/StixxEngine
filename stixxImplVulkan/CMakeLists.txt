add_library(StixxImplVulkan
	include/RendererVulkan.hpp
	src/RendererVulkan.cpp
)

set(VULKAN_INCL "C:/VulkanSDK/1.0.57.0/Include")
set(VULKAN_LIBS "C:/VulkanSDK/1.0.57.0/Lib/vulkan-1.Lib")

target_include_directories(StixxImplVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${VULKAN_INCL}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(StixxImplVulkan StixxCore ${VULKAN_LIBS})

install(DIRECTORY include DESTINATION include/stixx)

install(TARGETS StixxImplVulkan
		EXPORT 	StixxImplVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxImplVulkan-targets FILE StixxImplVulkan-config.cmake DESTINATION lib/cmake/StixxImplVulkan)
