#pragma once
#include "VulkanRenderer.h"
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_vulkan.h>
#include <ImGui/imgui_impl_sdl3.h>
#include <Global.h>
#include <vector>

class InterfaceRenderPass
{
private:
    static VkRenderPass RenderPass;
    static VkDescriptorPool ImGuiDescriptorPool;
    static VkCommandPool ImGuiCommandPool;
    static std::vector<VkFramebuffer> SwapChainFramebuffers;
   

    static void CreateRenderPass()
    {
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = VK_FORMAT_B8G8R8A8_UNORM;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        renderPassInfo.attachmentCount = 1;
        renderPassInfo.pAttachments = &colorAttachment;
        renderPassInfo.subpassCount = 1;
        renderPassInfo.pSubpasses = &subpass;
        renderPassInfo.dependencyCount = 1;
        renderPassInfo.pDependencies = &dependency;

        VkResult result = vkCreateRenderPass(global.Renderer.Device, &renderPassInfo, nullptr, &RenderPass);
        if (result != VK_SUCCESS) {
           // throw std::runtime_error("failed to create render pass!");
        }
    }

    static void CreateRendererFramebuffers()
    {
        SwapChainFramebuffers.resize(global.Renderer.SwapChain.SwapChainImageCount);
        for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++) 
        {
            std::vector<VkImageView> attachments = 
            {
                global.Renderer.SwapChain.SwapChainImageViews[x]
            };

            VkFramebufferCreateInfo frameBufferInfo =
            {
                .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
                .renderPass = RenderPass,
                .attachmentCount = static_cast<uint32_t>(attachments.size()),
                .pAttachments = attachments.data(),
                .width = global.Renderer.SwapChain.SwapChainResolution.width,
                .height = global.Renderer.SwapChain.SwapChainResolution.height,
                .layers = 1
            };

            VkResult result = vkCreateFramebuffer(global.Renderer.Device, &frameBufferInfo, nullptr, &SwapChainFramebuffers[x]);
            if (result != VK_SUCCESS) 
            {
                //throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    static void check_vk_result(VkResult err)
    {
        if (err == 0) return;
        printf("VkResult %d\n", err);
        if (err < 0)
            abort();
    }

public:
    static std::vector<VkCommandBuffer> ImGuiCommandBuffers;

    static void StartUp()
    {
        CreateRenderPass();
        CreateRendererFramebuffers();

        VkCommandPoolCreateInfo poolInfo
        {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex = global.Renderer.SwapChain.GraphicsFamily
        };

        VkResult commandPoolResult = vkCreateCommandPool(global.Renderer.Device, &poolInfo, nullptr, &ImGuiCommandPool);
        if (commandPoolResult != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to create graphics command pool: %s\n", commandPoolResult);
            Renderer_DestroyRenderer();
            GameEngine_DestroyWindow();
        }

        VkDescriptorPoolSize poolSizes[] =
        {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };

        VkDescriptorPoolCreateInfo pool_info = 
        {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
            .flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
            .maxSets = 1000 * IM_ARRAYSIZE(poolSizes),
            .poolSizeCount = (uint32_t)IM_ARRAYSIZE(poolSizes),
            .pPoolSizes = poolSizes
        };
        VkResult createDescriptorPoolResult = vkCreateDescriptorPool(global.Renderer.Device, &pool_info, nullptr, &ImGuiDescriptorPool);
        if (createDescriptorPoolResult != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to create descriptor pool: %s\n", createDescriptorPoolResult);
            Renderer_DestroyRenderer();
            GameEngine_DestroyWindow();
        }

        ImGuiCommandBuffers.resize(global.Renderer.SwapChain.SwapChainImageCount);
        for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
        {
            VkCommandBufferAllocateInfo commandBufferAllocateInfo
            {
                .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
                .commandPool = ImGuiCommandPool,
                .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
                .commandBufferCount = 1
            };

            VkResult allocateCommandBuffersResult = vkAllocateCommandBuffers(global.Renderer.Device, &commandBufferAllocateInfo, &ImGuiCommandBuffers[x]);
            if (allocateCommandBuffersResult != VK_SUCCESS)
            {
                fprintf(stderr, "Failed to allocate command buffers: %s\n", allocateCommandBuffersResult);
                Renderer_DestroyRenderer();
                GameEngine_DestroyWindow();
            }
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        ImGui_ImplSDL3_InitForVulkan(global.Window.SDLWindow);

        ImGui_ImplVulkan_InitInfo init_info =
        {
            .Instance = global.Renderer.Instance,
            .PhysicalDevice = global.Renderer.PhysicalDevice,
            .Device = global.Renderer.Device,
            .QueueFamily = global.Renderer.SwapChain.GraphicsFamily,
            .Queue = global.Renderer.SwapChain.GraphicsQueue,
            .DescriptorPool = ImGuiDescriptorPool,
            .MinImageCount = global.Renderer.SwapChain.SwapChainImageCount,
            .ImageCount = global.Renderer.SwapChain.SwapChainImageCount,
            .PipelineCache = VK_NULL_HANDLE,
            .Allocator = nullptr,
            .CheckVkResultFn = check_vk_result
        };
        ImGui_ImplVulkan_Init(&init_info);
        ImGui_ImplVulkan_CreateFontsTexture();
    }

    static void Draw()
    {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

        VkResult beginCommandBufferResult = vkBeginCommandBuffer(ImGuiCommandBuffers[global.Renderer.CommandIndex], &beginInfo);
        if (beginCommandBufferResult != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to start command buffers: %s\n", beginCommandBufferResult);
            Renderer_DestroyRenderer();
            GameEngine_DestroyWindow();
        }

        std::vector<VkClearValue> clearValues
        {
            VkClearValue {.color = { {0.0f, 0.0f, 0.0f, 1.0f} } },
            VkClearValue {.depthStencil = { 1.0f, 0 } }
        };

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = RenderPass;
        renderPassInfo.framebuffer = SwapChainFramebuffers[global.Renderer.ImageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = global.Renderer.SwapChain.SwapChainResolution;
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(ImGuiCommandBuffers[global.Renderer.CommandIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), ImGuiCommandBuffers[global.Renderer.CommandIndex]);
        vkCmdEndRenderPass(ImGuiCommandBuffers[global.Renderer.CommandIndex]);

        VkResult endCommandBufferResult = vkEndCommandBuffer(ImGuiCommandBuffers[global.Renderer.CommandIndex]);
        if (endCommandBufferResult != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to end command buffers: %s\n", endCommandBufferResult);
            Renderer_DestroyRenderer();
            GameEngine_DestroyWindow();
        }
    }

    static void RebuildSwapChain()
    {
        Renderer_DestroyRenderPass(&RenderPass);
        Renderer_DestroyFrameBuffers(SwapChainFramebuffers.data());
        CreateRenderPass();
        CreateRendererFramebuffers();
    }

    static void Destroy()
    {
        Renderer_DestroyRenderPass(&RenderPass);
        Renderer_DestroyFrameBuffers(SwapChainFramebuffers.data());
        Renderer_DestroyDescriptorPool(&ImGuiDescriptorPool);
        Renderer_DestroyCommandBuffers(&ImGuiDescriptorPool, ImGuiCommandBuffers.data());
        Renderer_DestroyCommnadPool(&ImGuiCommandPool);
        ImGui_ImplVulkan_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
};
