#ifndef SURFACE_VULKAN_HPP
#define SURFACE_VULKAN_HPP

#include "vulkan/vulkan.h"
#include <string>
#include "renderer/Surface.hpp"

namespace sx
{
    class InstanceVulkan;

	class SurfaceVulkan
		: public Surface
	{
	public:
		SurfaceVulkan(const InstanceVulkan& instance);
        SurfaceVulkan(const SurfaceVulkan&) = delete;
        const SurfaceVulkan& operator = (const SurfaceVulkan&) = delete;
		virtual ~SurfaceVulkan();

        operator const VkSurfaceKHR&() const;

        // Surface
        bool CreateSurface(Window& window) override;
        uint32_t MaxImageCount() override;
        bool isSupported(const PresentMode type) override;
        SurfaceFormat Format() override;
        Extent CurrentExtent() override;
        Transform CurrentTransform() override;

	private:
        VkSurfaceKHR surface;
        const InstanceVulkan& instance;
        Surface::Transform currentTransform;
        Surface::Extent extent;
        uint32_t imageCountMax;
	};
}

#endif /* SURFACE_VULKAN_HPP */
