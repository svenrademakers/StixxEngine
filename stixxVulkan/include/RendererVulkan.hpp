#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include "renderer\Renderer.hpp"
#include "InstanceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "SwapchainVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "PipelineVulkan.hpp"

namespace sx
{
	class FileSystem;
	class Window;
	class ModelVulkan;

    class RendererVulkan
		: public Renderer
    {
    public:
        RendererVulkan(PhysicalDeviceVulkan& pdevice, DeviceVulkan& device, SurfaceVulkan& surface, PipelineVulkan& pipeline, FileSystem& filesystem);
        RendererVulkan(const RendererVulkan&) = delete;
        RendererVulkan& operator = (const RendererVulkan&) = delete;
        virtual ~RendererVulkan();

        virtual void Draw() override;
		virtual void Load() override;

		void RecordDrawingCommands(ModelVulkan& m);

    private:
        std::vector<VkCommandBuffer> commandBuffers;

		PipelineVulkan& pipeline;
        SurfaceVulkan& surface;
        DeviceVulkan& device;
        SwapchainVulkan swapchain;
        RenderPassVulkan renderPass;
		FileSystem& filesystem;
    };

	struct VulkanRendererFacade
		: public Renderer
	{
	public:
		VulkanRendererFacade(Window& window, FileSystem& filesystem);

		virtual void Draw() override;
		virtual void Load() override;

	public:
		InstanceVulkan instance;
		PhysicalDeviceVulkan pdevice;
		SurfaceVulkan surface;
		DeviceVulkan device;
		PipelineVulkan pipeline;
		RendererVulkan renderer;
	};
}
#endif 
