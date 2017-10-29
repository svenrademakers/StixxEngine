#ifndef RENDERER_VULKAN_HPP
#define RENDERER_VULKAN_HPP

#include "vulkan/vulkan.h"
#include <WindowGlfw.hpp>
#include <Mesh.hpp>
#include "SwapchainVulkan.hpp"
#include "SurfaceVulkan.hpp"
#include "RenderPassVulkan.hpp"
#include "PipelineVulkan.hpp"
#include "InstanceVulkan.hpp"
#include "DeviceMemoryAllocatorVulkan.hpp"
#include "ModelVulkan.hpp"

namespace sx
{
    class  ShaderVertexVulkan;
    class ShaderFragmentVulkan;

    class RendererVulkan
    {
    public:
        RendererVulkan(PhysicalDeviceVulkan& pdevice, DeviceVulkan& device, SurfaceVulkan& surface, FileSystem& filesystem);
        RendererVulkan(const RendererVulkan&) = delete;
        RendererVulkan& operator = (const RendererVulkan&) = delete;
        virtual ~RendererVulkan();

        void RecordDrawingCommands(ModelVulkan& m);
        void Draw();

    private:
        std::vector<VkCommandBuffer> commandBuffers;

        SurfaceVulkan& surface;
        DeviceVulkan& device;
        SwapchainVulkan swapchain;
        RenderPassVulkan renderPass;
        PipelineVulkan pipeline;
    };
}

#endif /* RENDERERVULKAN_HPP */