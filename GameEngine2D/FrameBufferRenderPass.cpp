#include "FrameBufferRenderPass.h"
#include <Global.h>

FrameBufferRenderPass::FrameBufferRenderPass() : RenderPass()
{
}

FrameBufferRenderPass::~FrameBufferRenderPass()
{
}

void FrameBufferRenderPass::BuildRenderPass()
{
    if (RenderPassPtr == VK_NULL_HANDLE)
    {
        ColorTexture = std::make_shared<RendereredColorTexture2D>(RendereredColorTexture2D(RenderPassResolution, VK_FORMAT_R8G8B8A8_UNORM));
        BloomTexture = std::make_shared<RendereredColorTexture2D>(RendereredColorTexture2D(RenderPassResolution, VK_FORMAT_R8G8B8A8_UNORM));
    }
    else
    {

    }

    std::vector<VkImageView> TextureAttachmentList;
    TextureAttachmentList.emplace_back(ColorTexture->View);
    TextureAttachmentList.emplace_back(BloomTexture->View);

    std::vector<VkAttachmentDescription> attachmentDescriptionList
    {
        VkAttachmentDescription
            {
                .format = ColorTexture->GetTextureByteFormat(),
                .samples = ColorTexture->GetSampleCount(),
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            },
        VkAttachmentDescription
            {
                .format = BloomTexture->GetTextureByteFormat(),
                .samples = BloomTexture->GetSampleCount(),
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
            }
    };

    std::vector<VkAttachmentReference> colorRefsList
    {
        VkAttachmentReference
        {
            .attachment = 0,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        },
        VkAttachmentReference
        {
            .attachment = 1,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        }
    };

    std::vector<VkAttachmentReference> multiSampleReferenceList{};
    std::vector<VkAttachmentReference> depthReference{};

    std::vector<VkSubpassDescription> subpassDescriptionList
    {
        VkSubpassDescription
        {
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = static_cast<uint32_t>(colorRefsList.size()),
            .pColorAttachments = colorRefsList.data(),
            .pResolveAttachments = multiSampleReferenceList.data(),
            .pDepthStencilAttachment = depthReference.data()
        }
    };

    std::vector<VkSubpassDependency> subpassDependencyList
    {
        VkSubpassDependency
        {
            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .dstSubpass = 0,
            .srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask = VK_ACCESS_SHADER_READ_BIT,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
        },
        VkSubpassDependency
        {
            .srcSubpass = 0,
            .dstSubpass = VK_SUBPASS_EXTERNAL,
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            .dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
            .dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
        }
    };

    Renderer_RenderPassCreateInfoStruct renderPassCreateInfo
    {
      .pRenderPass = &RenderPassPtr,
      .pAttachmentList = attachmentDescriptionList.data(),
      .pSubpassDescriptionList = subpassDescriptionList.data(),
      .pSubpassDependencyList = subpassDependencyList.data(),
      .AttachmentCount = static_cast<uint32_t>(attachmentDescriptionList.size()),
      .SubpassCount = static_cast<uint32_t>(subpassDescriptionList.size()),
      .DependencyCount = static_cast<uint32_t>(subpassDependencyList.size()),
      .Width = static_cast<uint32_t>(RenderPassResolution.x),
      .Height = static_cast<uint32_t>(RenderPassResolution.y)
    };
    Renderer_CreateRenderPass(&renderPassCreateInfo);

    Renderer_CommandFrameBufferInfoStruct commandFrameBufferInfo
    {
        .pFrameBuffer = FrameBufferList.data(),
        .FrameBufferCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = RenderPassPtr,
            .attachmentCount = static_cast<uint32_t>(TextureAttachmentList.size()),
            .pAttachments = TextureAttachmentList.data(),
            .width = static_cast<uint32_t>(RenderPassResolution.x),
            .height = static_cast<uint32_t>(RenderPassResolution.y),
            .layers = 1
        }
    };

    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        std::vector<VkImageView> AttachmentList;
        AttachmentList.emplace_back(ColorTexture->View);
        AttachmentList.emplace_back(BloomTexture->View);

        VkFramebufferCreateInfo framebufferInfo
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = RenderPassPtr,
            .attachmentCount = static_cast<uint32_t>(AttachmentList.size()),
            .pAttachments = AttachmentList.data(),
            .width = static_cast<uint32_t>(RenderPassResolution.x),
            .height = static_cast<uint32_t>(RenderPassResolution.y),
            .layers = 1
        };

        if (vkCreateFramebuffer(global.Renderer.Device, &framebufferInfo, nullptr, &FrameBufferList[x]) != VK_SUCCESS) {
            //throw std::runtime_error("failed to create framebuffer!");
        }
    }
    Renderer_CreateFrameBuffer(&commandFrameBufferInfo);
}

void FrameBufferRenderPass::Draw()
{
    Renderer_StartFrame();

    std::vector<VkClearValue> clearValues
    {
        VkClearValue{.color = { {0.0f, 0.0f, 0.0f, 1.0f} } },
        VkClearValue{.color = { {0.0f, 0.0f, 0.0f, 1.0f} } },
    };

    VkViewport viewport
    {
        .x = 0.0f,
        .y = 0.0f,
        .width = (float)global.Renderer.SwapChain.SwapChainResolution.width,
        .height = (float)global.Renderer.SwapChain.SwapChainResolution.height,
        .minDepth = 0.0f,
        .maxDepth = 1.0f
    };

    VkRect2D rect2D
    {
        rect2D.offset = { 0, 0 },
        rect2D.extent =
        {
            (uint32_t)global.Renderer.SwapChain.SwapChainResolution.width,
            (uint32_t)global.Renderer.SwapChain.SwapChainResolution.height
        }
    };

    VkRenderPassBeginInfo renderPassInfo
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
        .renderPass = RenderPassPtr,
        .framebuffer = FrameBufferList[global.Renderer.ImageIndex],
        .renderArea
        {
            .offset = {0, 0},
            .extent = { (uint32_t)global.Renderer.SwapChain.SwapChainResolution.width, (uint32_t)global.Renderer.SwapChain.SwapChainResolution.height }
        },
        .clearValueCount = static_cast<uint32_t>(clearValues.size()),
        .pClearValues = clearValues.data()
    };

    VkCommandBufferBeginInfo CommandBufferBeginInfo
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT
    };

    Renderer_BeginCommandBufferStruct beginCommandBuffer
    {
        .pCommandBuffer = &CommandBufferList[global.Renderer.CommandIndex],
        .pCommandBufferBegin = &CommandBufferBeginInfo,
    };

    Renderer_BeginCommandBuffer(&beginCommandBuffer);
    vkCmdBeginRenderPass(CommandBufferList[global.Renderer.CommandIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdSetViewport(CommandBufferList[global.Renderer.CommandIndex], 0, 1, &viewport);
    vkCmdSetScissor(CommandBufferList[global.Renderer.CommandIndex], 0, 1, &rect2D);
    vkCmdEndRenderPass(CommandBufferList[global.Renderer.CommandIndex]);
    Renderer_EndCommandBuffer(&CommandBufferList[global.Renderer.CommandIndex]);

    Renderer_SubmitDraw(CommandBufferList.data());
}

void FrameBufferRenderPass::Destroy()
{
}
