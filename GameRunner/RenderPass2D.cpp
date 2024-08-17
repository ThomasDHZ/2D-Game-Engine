#include "RenderPass2D.h"

RenderPass2D::RenderPass2D() : RenderPass()
{
}

RenderPass2D::~RenderPass2D()
{
}

void RenderPass2D::BuildRenderPass()
{
    VkAttachmentDescription colorAttachment
    {
        .format = VK_FORMAT_B8G8R8A8_UNORM,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    };

    VkAttachmentReference colorAttachmentRef
    {
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };


    VkSubpassDescription subpass
    {
        .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
        .colorAttachmentCount = 1,
        .pColorAttachments = &colorAttachmentRef
    };

    VkSubpassDependency dependency
    {
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
    };

    std::vector<VkAttachmentDescription> attachmentList;
    attachmentList.emplace_back(colorAttachment);

    VkRenderPassCreateInfo renderPassInfo
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = static_cast<uint32_t>(attachmentList.size()),
        .pAttachments = attachmentList.data(),
        .subpassCount = 1,
        .pSubpasses = &subpass,
        .dependencyCount = 1,
        .pDependencies = &dependency
    };

    Renderer_RenderPassCreateInfo renderPassCreateInfo
    {
        .pRenderPass = &RenderPassPtr,
        .pRenderPassCreateInfo = &renderPassInfo,
    };

    Renderer_CreateRenderPass(&renderPassCreateInfo);

    Renderer_CommandFrameBufferInfo commandFrameBufferInfo
    {
        .RenderPass = RenderPassPtr,
        .pAttachmentList = attachmentList.data(),
        .Width = global.Renderer.SwapChain.SwapChainResolution.width,
        .Height = global.Renderer.SwapChain.SwapChainResolution.height,
    };

    Renderer_CreateFrameBuffer(&commandFrameBufferInfo);
}

void RenderPass2D::Destroy()
{
}
