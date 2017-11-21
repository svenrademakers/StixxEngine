
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

target_link_libraries(StixxCore ${ASSIMP_LIB})
target_include_directories(StixxCore 
	PUBLIC 
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/assimp/include>)


