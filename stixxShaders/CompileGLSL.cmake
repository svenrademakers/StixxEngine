foreach(shader ${shaders})
	SET(cmd ${VULKAN_SDK}/bin/glslangValidator -V ${shader})
	message(INFO ${cmd})
	execute_process(COMMAND ${cmd})
endforeach()

message(FATAL_ERROR "ja toch")