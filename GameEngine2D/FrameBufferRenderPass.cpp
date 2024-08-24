#include "FrameBufferRenderPass.h"
#include <Global.h>
#include "ShaderCompiler.h"
#include <stdexcept>

FrameBufferRenderPass::FrameBufferRenderPass() : RenderPass()
{
}

FrameBufferRenderPass::~FrameBufferRenderPass()
{
}

void FrameBufferRenderPass::BuildRenderPass(std::shared_ptr<Texture> texture)
{
    RenderedTexture = texture;

    std::vector<VkAttachmentDescription> attachmentDescriptionList
    {
        VkAttachmentDescription
        {
            .format = VK_FORMAT_R8G8B8A8_UNORM,
            .samples = VK_SAMPLE_COUNT_1_BIT,
            .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
            .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
            .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
            .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
            .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
            // Keep this layout as the expected final layout after rendering
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
        },
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

    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        std::vector<VkImageView> TextureAttachmentList;
        TextureAttachmentList.emplace_back(global.Renderer.SwapChain.SwapChainImageViews[x]);

        VkFramebufferCreateInfo framebufferInfo
        {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = RenderPassPtr,
            .attachmentCount = static_cast<uint32_t>(TextureAttachmentList.size()),
            .pAttachments = TextureAttachmentList.data(),
            .width = static_cast<uint32_t>(RenderPassResolution.x),
            .height = static_cast<uint32_t>(RenderPassResolution.y),
            .layers = 1
        };

        if (vkCreateFramebuffer(global.Renderer.Device, &framebufferInfo, nullptr, &FrameBufferList[x]) != VK_SUCCESS)
        {
            //throw std::runtime_error("failed to create framebuffer!");
        }
    }
    BuildRenderPipeline();
}

void FrameBufferRenderPass::BuildRenderPipeline()
{
    std::vector<VkPipelineShaderStageCreateInfo> PipelineShaderStageList
    {
        ShaderCompiler::CreateShader("C:/Users/DHZ/Documents/GitHub/2D-Game-Engine/Shaders/FrameBufferShaderVert.spv", VK_SHADER_STAGE_VERTEX_BIT),
        ShaderCompiler::CreateShader("C:/Users/DHZ/Documents/GitHub/2D-Game-Engine/Shaders/FrameBufferShaderFrag.spv", VK_SHADER_STAGE_FRAGMENT_BIT)
    };

    std::vector<VkDescriptorImageInfo> ColorDescriptorImage
    {
        VkDescriptorImageInfo
        {
            .sampler = RenderedTexture->Sampler,
            .imageView = RenderedTexture->View,
            .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
        }
    };

    std::vector<VkDescriptorPoolSize> DescriptorPoolBinding =
    {
        VkDescriptorPoolSize
        {
            .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount = 1
        }
    };

    VkDescriptorPoolCreateInfo poolInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = global.Renderer.SwapChain.SwapChainImageCount,
        .poolSizeCount = static_cast<uint32_t>(DescriptorPoolBinding.size()),
        .pPoolSizes = DescriptorPoolBinding.data(),
    };

    if (vkCreateDescriptorPool(global.Renderer.Device, &poolInfo, nullptr, &DescriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create descriptor pool.");
    }

    std::vector<VkDescriptorSetLayoutBinding> LayoutBindingList =
    {
        { 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr },
        { 1, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, nullptr }, // Add this line for binding 1
    };

    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = LayoutBindingList.data();

    if (vkCreateDescriptorSetLayout(global.Renderer.Device, &layoutInfo, nullptr, &DescriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create descriptor set layout.");
    }

    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = DescriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &DescriptorSetLayout;

    if (vkAllocateDescriptorSets(global.Renderer.Device, &allocInfo, &DescriptorSet) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate descriptor sets.");
    }

    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        std::vector<VkWriteDescriptorSet> descriptorSets
        {
            VkWriteDescriptorSet
            {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .dstSet = DescriptorSet,
                .dstBinding = 0,
                .dstArrayElement = 0,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .pImageInfo = ColorDescriptorImage.data(),
            }
        };
        vkUpdateDescriptorSets(global.Renderer.Device, static_cast<uint32_t>(descriptorSets.size()), descriptorSets.data(), 0, nullptr);
    }

  /*  std::vector<VkVertexInputBindingDescription> bindingDescriptions
    {
        Vertex2D::getBindingDescriptions()
    };
    std::vector<VkVertexInputAttributeDescription> attributeDescriptions
    {
        Vertex2D::getAttributeDescriptions()
    };

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();*/

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)RenderPassResolution.x;
    viewport.height = (float)RenderPassResolution.y;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D rect2D{};
    rect2D.offset = { 0, 0 };
    rect2D.extent = { (uint32_t)RenderPassResolution.x, (uint32_t)RenderPassResolution.y };

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &rect2D;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;

    std::vector<VkPipelineColorBlendAttachmentState> blendAttachmentList
    {
        VkPipelineColorBlendAttachmentState
        {
            .blendEnable = VK_TRUE,
            .srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
            .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
            .colorBlendOp = VK_BLEND_OP_ADD,
            .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
            .dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
            .alphaBlendOp = VK_BLEND_OP_ADD,
            .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |
                VK_COLOR_COMPONENT_G_BIT |
                VK_COLOR_COMPONENT_B_BIT |
                VK_COLOR_COMPONENT_A_BIT
        }
    };

    VkPipelineDepthStencilStateCreateInfo blendDepthAttachment
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = VK_TRUE,
        .depthWriteEnable = VK_TRUE,
        .depthCompareOp = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .stencilTestEnable = VK_FALSE
    };

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.lineWidth = 1.0f;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.cullMode = VK_CULL_MODE_NONE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_TRUE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.attachmentCount = static_cast<uint32_t>(blendAttachmentList.size());
    colorBlending.pAttachments = blendAttachmentList.data();

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &DescriptorSetLayout;

    //pipelineLayoutInfo.pushConstantRangeCount = 1;

    //VkPushConstantRange pushConstantRange{};
    //pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    //pushConstantRange.offset = 0;
    //pushConstantRange.size = buildPipelineInfo.RenderPassDescription.ConstBufferSize;
    //pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if (vkCreatePipelineLayout(global.Renderer.Device, &pipelineLayoutInfo, nullptr, &ShaderPipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout.");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = static_cast<uint32_t>(PipelineShaderStageList.size());
    pipelineInfo.pStages = PipelineShaderStageList.data();
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = &blendDepthAttachment;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.layout = ShaderPipelineLayout;
    pipelineInfo.renderPass = RenderPassPtr;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    VkResult result = vkCreateGraphicsPipelines(global.Renderer.Device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &ShaderPipeline);
    if (result != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline.");
    }
}

VkCommandBuffer FrameBufferRenderPass::Draw()
{
    Renderer_StartFrame();

    std::vector<VkClearValue> clearValues
    {
        VkClearValue{.color = { {0.0f, 0.0f, 0.0f, 1.0f} } }
        //VkClearValue{.color = { {0.0f, 0.0f, 0.0f, 1.0f} } },
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
        .pCommandBuffer = &CommandBufferList[global.Renderer.ImageIndex],
        .pCommandBufferBegin = &CommandBufferBeginInfo,
    };


    VkResult result = vkBeginCommandBuffer(CommandBufferList[global.Renderer.CommandIndex], &CommandBufferBeginInfo);
    // Renderer_BeginCommandBuffer(&beginCommandBuffer);
    vkCmdBeginRenderPass(CommandBufferList[global.Renderer.CommandIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdSetViewport(CommandBufferList[global.Renderer.CommandIndex], 0, 1, &viewport);
    vkCmdSetScissor(CommandBufferList[global.Renderer.CommandIndex], 0, 1, &rect2D);
    vkCmdBindPipeline(CommandBufferList[global.Renderer.CommandIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, ShaderPipeline);
    vkCmdBindDescriptorSets(CommandBufferList[global.Renderer.CommandIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, ShaderPipelineLayout, 0, 1, &DescriptorSet, 0, nullptr);
    vkCmdDraw(CommandBufferList[global.Renderer.CommandIndex], 6, 1, 0, 0);
    vkCmdEndRenderPass(CommandBufferList[global.Renderer.CommandIndex]);
    Renderer_EndCommandBuffer(&CommandBufferList[global.Renderer.CommandIndex]);
    //Renderer_SubmitDraw(CommandBufferList.data());

    return CommandBufferList[global.Renderer.CommandIndex];
}

void FrameBufferRenderPass::Destroy()
{
}
