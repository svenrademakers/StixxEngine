file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)
set(CMAKE_CXX_STANDARD 14)
add_library(StixxImplVulkan STATIC
	${sources}
	${headers}
	${shaders}
)

find_package (Vulkan REQUIRED)

target_include_directories(StixxImplVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

target_link_libraries(StixxImplVulkan StixxCore ${Vulkan_LIBRARIES})
target_compile_features(StixxImplVulkan PUBLIC cxx_override cxx_inheriting_constructors)
install(DIRECTORY include DESTINATION include/stixx)

install(TARGETS StixxImplVulkan
		EXPORT 	StixxImplVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxImplVulkan-targets FILE StixxImplVulkan-config.cmake DESTINATION lib/cmake/StixxImplVulkan)
