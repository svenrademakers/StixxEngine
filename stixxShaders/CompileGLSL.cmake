set(VULKAN_ROOT "C:/VulkanSDK/1.0.57.0")

foreach(shader ${shaders})
	execute_process(COMMAND "${VULKAN_ROOT}/Bin/glslangValidator.exe -V ${shader}" OUTPUT_VARIABLE  wat)
	message(STATUS "${wat}")
endforeach()