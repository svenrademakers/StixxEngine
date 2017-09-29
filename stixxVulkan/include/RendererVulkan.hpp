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

namespace sx
{
    class  ShaderVertexVulkan;
    class ShaderFragmentVulkan;

    class RendererVulkan
    {
    public:
        RendererVulkan(DeviceVulkan& device, SurfaceVulkan& surface, const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment);
        RendererVulkan(const RendererVulkan&) = delete;
        RendererVulkan& operator = (const RendererVulkan&) = delete;
        virtual ~RendererVulkan();

        void LoadScene(const std::vector<sx::Vertex>& vertex, const std::vector<uint32_t>& indices);
        void LoadDrawingCommands();
        void Draw();

    private:
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        SurfaceVulkan& surface;
        DeviceVulkan& device;
        SwapchainVulkan swapchain;
        RenderPassVulkan renderPass;
        PipelineVulkan pipeline;
    };
}

#endif /* RENDERERVULKAN_HPP */