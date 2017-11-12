#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include <mutex>
#include <atomic>
#include <optional>

#include "renderer\Renderer.hpp"
#include "InstanceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "SwapchainVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "PipelineVulkan.hpp"
#include "Window.hpp"

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

	struct VulkanStack
		: public WindowObserver
	{
	public:
		VulkanStack(Window& window);

		void Load(FileSystem& filesystem, const char * appName, std::vector<const char*> instanceExtensions);
		void Run(std::function<void()> temp);

		virtual void WindowCreated(WindowHandle& handle) override;
		virtual void Closing() override;

	public:
		std::optional<InstanceVulkan> instance;
		std::optional<PhysicalDeviceVulkan> pdevice;
		std::optional<DeviceVulkan> device;
		std::optional<SurfaceVulkan> surface;
		std::optional<PipelineVulkan> pipeline;
		std::optional<RendererVulkan> renderer;
		
		std::mutex surfaceMutex;
		std::condition_variable surfaceCondition;
		std::atomic<bool> running;
	};
}
#endif 
