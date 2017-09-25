#find_package(assimp REQUIRED)

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(Stixx
	${sources}
	${headers}
)

target_include_directories(Stixx
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>)

target_compile_features(Stixx PUBLIC cxx_override cxx_inheriting_constructors)
target_link_libraries(Stixx glfw libassimp.so)

install(DIRECTORY include interfaces DESTINATION include)

install(TARGETS Stixx
		EXPORT 	Stixx-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT Stixx-targets FILE Stixx-config.cmake DESTINATION lib/cmake/Stixx)

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
