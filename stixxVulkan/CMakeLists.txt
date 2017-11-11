file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp interfaces/*.hpp)

add_library(StixxVulkan STATIC
	${sources}
	${headers}
	${shaders}
)

if(DEFINED ENV{VULKAN_SDK})
	set(Vulkan_INCLUDE_DIR $ENV{VULKAN_SDK}/include)
else()
	message(FATAL_ERROR "VULKAN_SDK path not set in environment..")
endif()

target_include_directories(StixxVulkan
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

if (UNIX)
	set(Vulkan_LIBRARY $ENV{VULKAN_SDK}/lib)
	set(Vulkan_Lib ${Vulkan_LIBRARY}/libvulkan.so)
elseif (WIN32)
	set(Vulkan_LIBRARY $ENV{VULKAN_SDK}/Lib)
	set(Vulkan_Lib ${Vulkan_LIBRARY}/vulkan-1.lib)
endif()

target_link_libraries(StixxVulkan StixxCore ${Vulkan_Lib})
target_compile_features(StixxVulkan PUBLIC cxx_override cxx_inheriting_constructors)

set_property(TARGET StixxVulkan PROPERTY CXX_STANDARD 14)

install(DIRECTORY include DESTINATION include/stixx)
install(TARGETS StixxVulkan
		EXPORT 	StixxVulkan-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)
install(EXPORT StixxVulkan-targets FILE StixxVulkan-config.cmake DESTINATION lib/cmake/StixxVulkan)


