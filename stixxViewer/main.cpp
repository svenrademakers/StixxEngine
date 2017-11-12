#include <iostream>
#include <chrono>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "WindowGlfw.hpp"
#include "FileSystem.hpp"
#include "VulkanStack.hpp"
#include "MeshLoaderAssimp.hpp"
#include "ModelVulkan.hpp"
#include "InputGlfw.hpp"
#include "interactors/InputInteractor.hpp"

class RotateModelInteractor
{
public:
	RotateModelInteractor(sx::Model& model)
		: model(model)
	{}

	void UpdateRotation()
	{
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() / 1000.0f;

		sx::UniformBufferObject ubo = {};
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), 800 / (float)600, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		model.UpdateUbo(ubo);
	}

private:
	sx::Model& model;
};

int main(void)
{
	static sx::FileSystemStd fileSystem;
	constexpr const char * appName = "StixxViewer";
	static sx::WindowGlfw window(appName, 1280, 800);
	static sx::InputGlfw input(window); 
	static sx::VulkanStack vulkan(window);
	window.Run();

	static sx::InputInteractor inputInteractor(input, input, window);

	sx::Mesh mesh = {};
	static MeshLoaderAssimp meshLoader(R"(D:\Monkey.obj)");
	meshLoader.Next(mesh);

	vulkan.Load(fileSystem, appName, sx::WindowGlfw::InstanceExtensions());

	sx::ModelVulkan model(*vulkan.device, *vulkan.pdevice, *vulkan.pipeline, mesh);
	model.LoadDescriptors(vulkan.pipeline->DescriptorSet());
	vulkan.renderer->RecordDrawingCommands(model);
	
	RotateModelInteractor rotate(model);
	vulkan.Run([&rotate] {rotate.UpdateRotation(); });

    return 0;
}