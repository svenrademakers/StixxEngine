set(VULKAN_ROOT C:/VulkanSDK/1.0.57.0)

foreach(shader ${shaders})
	SET(cmd ${VULKAN_ROOT}/Bin/glslangValidator.exe -V ${shader})
	execute_process(COMMAND ${cmd} RESULT_VARIABLE result)
endforeach()

