if (WIN32)
	set(ASSIMP_INCLUDE_DIRS C:/Program\ Files/Assimp/include)
	set(ASSIMP_LIBRARIES C:/Program\ Files/assimp/lib/x64/assimp.lib)
	set(GLEWPATH ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.1.0)
	set(GLEW_INCLUDE_DIRS ${GLEWPATH}/include)
	set(GLEW_LIBRARIES	 ${GLEWPATH}/lib/Release/x64/glew32.lib)
else()
	find_package(assimp REQUIRED)
endif()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)

add_subdirectory(external/glm)

add_library(StixxCore
	include/Observer.hpp
	include/Renderer.hpp
	include/MeshLoaderAssimp.hpp
	include/Window.hpp
	include/WindowGlfw.hpp
	src/Observer.cpp
	src/ShaderLoader.cpp
	src/MeshLoaderAssimp.cpp
	src/WindowGlfw.cpp
)

target_include_directories(StixxCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>)

target_compile_features(StixxCore PUBLIC cxx_override cxx_inheriting_constructors)
target_link_libraries(StixxCore glm glfw ${ASSIMP_LIBRARIES} ${GLEW_LIBRARIES})

install(DIRECTORY include interfaces DESTINATION include/stixx)

install(TARGETS StixxCore
		EXPORT 	StixxCore-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxCore-targets FILE StixxCore-config.cmake DESTINATION lib/cmake/StixxCore)

#find_package(GTest REQUIRED)

#add_executable(micro_tests
#	test/test.cpp
#	test/TestAntHost.cpp
#	test/TestHbAlgo.cpp
#	test/TestMapController.cpp
#	test/TestSensorSniffer.cpp)

#target_compile_features(micro_tests PUBLIC cxx_default_function_template_args)

#target_link_libraries(micro_tests  dualant GTest /usr/local/lib/libgmock.a pthread )
#install(TARGETS micro_tests DESTINATION bin)
