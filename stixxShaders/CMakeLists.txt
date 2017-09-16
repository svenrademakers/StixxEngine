file(GLOB_RECURSE shaders *.vert *.frag *.glsl)
MESSAGE(STATUS "${CMAKE_COMMAND} -Dshaders=\"${shaders}\" -P ${CMAKE_CURRENT_SOURCE_DIR}/CompileGLSL.cmake")
add_custom_target(StixxShaders 
	COMMAND ${CMAKE_COMMAND} "-Dshaders=\"${shaders}\" -P ${CMAKE_CURRENT_SOURCE_DIR}/CompileGLSL.cmake" SOURCES ${shaders} CompileGLSL.cmake)

