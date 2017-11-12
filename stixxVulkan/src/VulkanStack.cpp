#include "VulkanStack.hpp"

namespace sx
{
	VulkanStack::VulkanStack(Window& window)
		: WindowObserver(window)
	{
		surfaceMutex.lock();
	}

	void VulkanStack::Load(FileSystem& filesystem, const char * appName, std::vector<const char*> instanceExtensions)
	{
		instance.emplace("Stixx-Engine", appName, instanceExtensions);
		pdevice.emplace(*instance);
		device.emplace(*pdevice);
		pipeline.emplace(*device);

		std::unique_lock<std::mutex> lk(surfaceMutex, std::adopt_lock);
		surfaceCondition.wait(lk, [this] {return surface.has_value(); });

		renderer.emplace(*pdevice, *device, *surface, *pipeline, filesystem);
	}

	void VulkanStack::Run(std::function<void()> temp)
	{
		running = true;

		while (running)
		{
			temp();
			renderer->Draw();
		}
	}

	void VulkanStack::WindowCreated(WindowHandle& handle)
	{
		{
			std::lock_guard<std::mutex> lk(surfaceMutex);
			surface.emplace(*instance, *pdevice, handle);
		}

		if (!pdevice->PresentSupport(*surface))
			throw std::runtime_error("could not setup surface");

		surfaceCondition.notify_all();
	}

	void VulkanStack::Closing()
	{
		running = false;
	}
}