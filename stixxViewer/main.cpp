#include <iostream>
#include <chrono>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "WindowGlfw.hpp"
#include "platform/FileSystemImpl.hpp"
#include "VulkanStack.hpp"
#include "AssetImporterAssimp.hpp"
#include "ModelVulkan.hpp"
#include "InputGlfw.hpp"
#include "interactors/InputInteractor.hpp"
#include "MemoryLoaderVulkan.hpp"

class RotateModelInteractor
	: public sx::HotLoopObserver
{
public:
	RotateModelInteractor(sx::Renderer& renderer, sx::Model& model)
		: sx::HotLoopObserver(renderer)
		, model(model)
	{}

	void Update(std::chrono::duration<float>& elapsedMs)
	{
		float time = (std::chrono::duration_cast<std::chrono::milliseconds>(elapsedMs).count() / 1000.0f);

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
	static sx::FileSystemImpl fileSystem;
	constexpr const char * appName = "StixxViewer";
	static sx::WindowGlfw window(appName, 1280, 800);
	static sx::InputGlfw input(window); 
	static sx::VulkanStack vulkan(window);
	window.Run();

	sx::Mesh mesh = {};
	static AssetImporterAssimp meshLoader;
	meshLoader.Load(R"(D:\Monkey.obj)");
	meshLoader.Next(mesh);

	vulkan.Load(fileSystem, appName, sx::WindowGlfw::InstanceExtensions());
	
	sx::MemoryLoaderVulkan writer(*vulkan.device, *vulkan.pdevice, vulkan.device->CommandPool(), vulkan.device->Queue());
	sx::ModelVulkan model(*vulkan.device, *vulkan.pdevice, *vulkan.pipeline, mesh, writer);
	
	model.LoadDescriptors(vulkan.pipeline->DescriptorSet());
	vulkan.renderer->RecordDrawingCommands(model);
	
	RotateModelInteractor rotate(*vulkan.renderer, model);
	vulkan.Run();

    return 0;
}