if(WIN32)
	if(DEFINED ENV{ASSIMP_ROOT})
		set(ASSIMP_INCLUDE_DIRS $ENV{ASSIMP_ROOT}/include)
		set(ASSIMP_LIB $ENV{ASSIMP_ROOT}/lib/x64/assimp-vc140-mt.lib)
	else()
		message(FATAL_ERROR "please define enviroment ASSIMP_ROOT..")
	endif()
elseif(UNIX)
	set(ASSIMP_LIB libassimp.so)
endif()

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(StixxCore STATIC
	${sources}
	${headers}
)
set_property(TARGET StixxCore PROPERTY CXX_STANDARD 14)

target_include_directories(StixxCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>)

		
target_link_libraries(StixxCore glfw glm ${ASSIMP_LIB})

install(DIRECTORY include interfaces DESTINATION include)

install(TARGETS StixxCore
		EXPORT 	StixxCore-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxCore-targets FILE StixxCore-config.cmake DESTINATION lib/cmake/StixxCore)

add_subdirectory(test)

