#include <iostream>
#include <chrono>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "WindowGlfw.hpp"
#include "FileSystem.hpp"
#include "RendererVulkan.hpp"
#include "MeshLoaderAssimp.hpp"
#include "ModelVulkan.hpp"

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
		ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
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
	sx::Mesh mesh;
    //static MeshLoaderAssimp meshLoader(R"(D:\cube.obj)");
    //meshLoader.Next(mesh);

    sx::Vertex vertex = {};
    vertex.Normal = {-0.5f,-0.5f,0.0};
    mesh.vertices.push_back(vertex);
    vertex.Normal = {0.5,-0.5,0.0};
    mesh.vertices.push_back(vertex);
    vertex.Normal = {0.5,0.5,0.0};
    mesh.vertices.push_back(vertex);
    vertex.Normal = {-0.5f, 0.5f, 0.0};
    mesh.vertices.push_back(vertex);
    mesh.indices = {0,1,2,2,3,0};

    static sx::FileSystemStd fileSystem;
    static sx::WindowGlfw window("StixxViewer", 800, 600);
	static sx::VulkanRendererFacade renderer(window, fileSystem);
	sx::ModelVulkan model(renderer.device, renderer.pdevice, renderer.pipeline, mesh);
	renderer.Load();

	//short-cut; Todo: make intrusive-list
	renderer.renderer.RecordDrawingCommands(model);

	static RotateModelInteractor rotate(model);

    while (!window.ShouldClose()) {
        window.Poll();

		rotate.UpdateRotation();
        renderer.Draw();
    }

    return 0;
}