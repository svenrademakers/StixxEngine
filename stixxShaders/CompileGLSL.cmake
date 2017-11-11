foreach(shader ${shaders})
	SET(cmd $ENV{VULKAN_SDK}/bin/glslangValidator.exe -V ${shader})
	execute_process(COMMAND ${cmd})
endforeach()