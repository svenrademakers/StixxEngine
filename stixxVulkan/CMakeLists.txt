file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(StixxVulkan STATIC
	${sources}
	${headers}
	${shaders}
)

set(Vulkan_INCLUDE_DIR $ENV{VULKAN_SDK}/include)
set(Vulkan_LIBRARIES $ENV{VULKAN_SDK}/lib/libvulkan.so)

target_include_directories(StixxVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(StixxVulkan ${Vulkan_LIBRARIES} Stixx)
target_compile_features(StixxVulkan PUBLIC cxx_override cxx_inheriting_constructors)

install(DIRECTORY include DESTINATION include/stixx)
install(TARGETS StixxVulkan
		EXPORT 	StixxVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)
install(EXPORT StixxVulkan-targets FILE StixxVulkan-config.cmake DESTINATION lib/cmake/StixxVulkan)

add_subdirectory(test)
