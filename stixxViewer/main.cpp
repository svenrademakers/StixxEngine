#include <iostream>
#include <chrono>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "WindowGlfw.hpp"
#include "FileSystem.hpp"
#include "RendererVulkan.hpp"
#include "MeshLoaderAssimp.hpp"
#include "ModelVulkan.hpp"
#include "UiHandlerGlfw.hpp"

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
	static sx::WindowGlfw window(appName, 800, 600);
	static sx::VulkanStack renderer(window);

	window.Run();

	sx::Mesh mesh = {};
	static MeshLoaderAssimp meshLoader(R"(D:\Monkey.obj)");
	meshLoader.Next(mesh);

	renderer.Load(fileSystem, appName, sx::WindowGlfw::InstanceExtensions());
	
	sx::ModelVulkan model(*renderer.device, *renderer.pdevice, *renderer.pipeline, mesh);
	model.LoadDescriptors(renderer.pipeline->DescriptorSet());
	renderer.renderer->RecordDrawingCommands(model);

	static RotateModelInteractor rotate(model);

    while (window.IsOpen()) {
		rotate.UpdateRotation();
        renderer.renderer->Draw();
    }

    return 0;
}