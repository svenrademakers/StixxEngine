file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE headers include/*.hpp)

add_library(StixxCore
	${sources}
	${headers}
)

target_include_directories(StixxCore
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/interfaces>
 		$<INSTALL_INTERFACE:stixx>
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		$<BUILD_INTERFACE:${ASSIMP_INCLUDE_DIRS}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(StixxCore PUBLIC cxx_override cxx_inheriting_constructors)
target_link_libraries(StixxCore glfw glm libassimp.so)

install(DIRECTORY include interfaces DESTINATION include)

install(TARGETS StixxCore
		EXPORT 	StixxCore-targets
    	ARCHIVE  DESTINATION lib
    	LIBRARY  DESTINATION lib
    	RUNTIME  DESTINATION bin)

install(EXPORT StixxCore-targets FILE StixxCore-config.cmake DESTINATION lib/cmake/StixxCore)

add_subdirectory(test)

