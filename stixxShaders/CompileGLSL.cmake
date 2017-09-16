set(VULKAN_ROOT "C:/VulkanSDK/1.0.57.0")

foreach(shader ${shaders})
	execute_process(COMMAND "${VULKAN_ROOT}/Bin/glslangValidator.exe -V ${shader}" RESULT_VARIABLE result)
	if(NOT result STREQUAL "")
		MESSAGE(FATAL_ERROR "could not compile ${shader}")
	endif()
endforeach()

