
if (WIN32)
	add_subdirectory(external/assimp)
	set(GLEWPATH ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.1.0)
	set(GLEW_INCLUDE_DIRS ${GLEWPATH}/include)
	set(GLEW_LIBRARIES	 ${GLEWPATH}/lib/Release/x64/glew32.lib)
else()
	find_package(GLEW REQUIRED)
	find_package(assimp REQUIRED)
endif()

add_subdirectory(external/glfw)
add_subdirectory(external/glm)

add_library(stixxCore
	src/ShaderLoader.cpp
	src/MeshLoaderAssimp.cpp)

target_include_directories(stixxCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>)

target_compile_features(stixxCore PUBLIC cxx_override cxx_inheriting_constructors)
target_link_libraries(stixxCore glm ${ASSIMP_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})


install(DIRECTORY include interfaces DESTINATION include/stixx)

install(TARGETS stixxCore
		EXPORT 	stixxCore-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT stixxCore-targets FILE stixxCore-config.cmake DESTINATION lib/cmake/stixxCore)

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
