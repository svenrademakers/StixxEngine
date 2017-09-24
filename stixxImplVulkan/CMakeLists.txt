file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(StixxImplVulkan STATIC
	${sources}
	${headers}
	${shaders}
)

set(Vulkan_INCLUDE_DIR $ENV{VULKAN_SDK}/include)
file(GLOB_RECURSE Vulkan_LIBRARIES $ENV{VULKAN_SDK}/lib/*)

target_include_directories(StixxImplVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(StixxImplVulkan ${Vulkan_LIBRARIES} StixxCore)
target_compile_features(StixxImplVulkan PUBLIC cxx_override cxx_inheriting_constructors)

install(DIRECTORY include DESTINATION include/stixx)
install(TARGETS StixxImplVulkan
		EXPORT 	StixxImplVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)
install(EXPORT StixxImplVulkan-targets FILE StixxImplVulkan-config.cmake DESTINATION lib/cmake/StixxImplVulkan)

add_subdirectory(test)
