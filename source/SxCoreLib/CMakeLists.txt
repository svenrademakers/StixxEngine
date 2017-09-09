
find_package(Boost 1.65 REQUIRED)

add_library(SxCoreLib
	src/Dummy.cpp)
	
target_compile_features(SxCoreLib PUBLIC cxx_override cxx_inheriting_constructors)
target_link_libraries(SxCoreLib glm)

target_include_directories(SxCoreLib 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
 		$<INSTALL_INTERFACE:include/sxcorelib>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<BUILD_INTERFACE: ${Boost_INCLUDE_DIR}>)
		
install(DIRECTORY include DESTINATION include/sxcorelib)

install(TARGETS SxCoreLib 
		EXPORT 	SxCoreLib-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT SxCoreLib-targets FILE SxCoreLib-config.cmake DESTINATION lib/cmake/SxCoreLib)

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