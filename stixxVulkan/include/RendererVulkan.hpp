#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include <vector>
#include "interfaces/renderer/Renderer.hpp"
#include "SwapchainVulkan.hpp"
#include "RenderPassVulkan.hpp"

namespace sx
{
	class FileSystem;
	class Window;
	class ModelVulkan;
	class PipelineVulkan;
	class ShaderVertexVulkan;
	class ShaderFragmentVulkan;

	class Buffer
		: public ObjectWrapper<VkBuffer>
	{
	public:
		Buffer() = default;
		Buffer(const VkBuffer&&);
	};

    class RendererVulkan
		: public Renderer
    {
    public:
        RendererVulkan(PhysicalDeviceVulkan& pdevice, DeviceVulkan& device, SurfaceVulkan& surface, PipelineVulkan& pipeline, ShaderVertexVulkan& vertexShader, ShaderFragmentVulkan& fragmentShader);
        RendererVulkan(const RendererVulkan&) = delete;
        RendererVulkan& operator = (const RendererVulkan&) = delete;
        virtual ~RendererVulkan();

        virtual void Draw() override;

		
		void RecordDrawingCommands(ModelVulkan& m);

    private:
        std::vector<VkCommandBuffer> commandBuffers;

		PipelineVulkan& pipeline;
        SurfaceVulkan& surface;
        DeviceVulkan& device;
        SwapchainVulkan swapchain;
        RenderPassVulkan renderPass;
    };

}

#endif 
