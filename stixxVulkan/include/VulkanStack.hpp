#ifndef VULKAN_STACK_HPP
#define VULKAN_STACK_HPP

#include <mutex>
#include <atomic>
#include <optional>

#include "InstanceVulkan.hpp"
#include "DeviceVulkan.hpp"
#include "PhysicalDeviceVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "PipelineVulkan.hpp"
#include "interfaces/Window.hpp"
#include "RendererVulkan.hpp"

namespace sx
{
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