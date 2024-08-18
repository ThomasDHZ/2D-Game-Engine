#include "RenderPass2D.h"

RenderPass2D::RenderPass2D() : RenderPass()
{

}

RenderPass2D::~RenderPass2D()
{
}

void RenderPass2D::BuildRenderPass()
{
    std::vector<VkImageView> textureAttachmentList;
    std::vector<VkAttachmentDescription> attachmentDescriptionList
    {
        VkAttachmentDescription
            {
                .format = VK_FORMAT_B8G8R8A8_UNORM,
                .samples = VK_SAMPLE_COUNT_1_BIT,
                .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
                .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
            }
    };

    std::vector<VkAttachmentReference> colorRefsList
    {
        VkAttachmentReference
        {
            .attachment = 0,
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
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .srcAccessMask = 0,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
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
      .Width = global.Renderer.SwapChain.SwapChainResolution.width,
      .Height = global.Renderer.SwapChain.SwapChainResolution.height,
    };
    Renderer_CreateRenderPass(&renderPassCreateInfo);

    Renderer_CommandFrameBufferInfoStruct commandFrameBufferInfo
    {
        .pFrameBuffer = FrameBufferList.data(),
        .FrameBufferCreateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = RenderPassPtr,
            .attachmentCount = static_cast<uint32_t>(textureAttachmentList.size()),
            .pAttachments = textureAttachmentList.data(),
            .width = global.Renderer.SwapChain.SwapChainResolution.width,
            .height = global.Renderer.SwapChain.SwapChainResolution.height,
            .layers = 1
        }
    };

    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        std::vector<VkImageView> AttachmentList;
        AttachmentList.emplace_back(global.Renderer.SwapChain.SwapChainImageViews[x]);

        VkFramebufferCreateInfo framebufferInfo
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = RenderPassPtr,
            .attachmentCount = static_cast<uint32_t>(AttachmentList.size()),
            .pAttachments = AttachmentList.data(),
            .width = global.Renderer.SwapChain.SwapChainResolution.width,
            .height = global.Renderer.SwapChain.SwapChainResolution.height,
            .layers = 1
        };

        if (vkCreateFramebuffer(global.Renderer.Device, &framebufferInfo, nullptr, &FrameBufferList[x]) != VK_SUCCESS) {
            //throw std::runtime_error("failed to create framebuffer!");
        }
    }
    //Renderer_CreateFrameBuffer(&commandFrameBufferInfo);
}

void RenderPass2D::Draw()
{
    Renderer_StartFrame();

    std::vector<VkClearValue> clearValues
    {
        VkClearValue{.color = { {0.0f, 0.0f, 1.0f, 1.0f} } },
        VkClearValue{.depthStencil = { 1.0f, 0 } }
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

void RenderPass2D::Destroy()
{
}
