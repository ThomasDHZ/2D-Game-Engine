#include "RenderPass.h"
#include <Global.h>

RenderPass::RenderPass()
{
	RenderPassResolution = glm::ivec2((int)global.Renderer.SwapChain.SwapChainResolution.width, (int)global.Renderer.SwapChain.SwapChainResolution.height);
	SampleCount = VK_SAMPLE_COUNT_1_BIT;

	CommandBufferList.resize(global.Renderer.SwapChain.SwapChainImageCount);
	FrameBufferList.resize(global.Renderer.SwapChain.SwapChainImageCount);

	VULKAN_RESULT(Renderer_CreateCommandBuffers(CommandBufferList.data()));
}

RenderPass::~RenderPass()
{
}

VkWriteDescriptorSet RenderPass::CreateTextureDescriptorSet(std::shared_ptr<Texture> texture, uint32 bindingSlot)
{
    return CreateTextureDescriptorSet(texture, bindingSlot, 1);
}

VkWriteDescriptorSet RenderPass::CreateTextureDescriptorSet(std::shared_ptr<Texture> texture, uint32 bindingSlot, uint32 descriptorCount)
{
    return CreateTextureDescriptorSet(texture, bindingSlot, descriptorCount, 0);
}

VkWriteDescriptorSet RenderPass::CreateTextureDescriptorSet(std::shared_ptr<Texture> texture, uint32 bindingSlot, uint32 descriptorCount, uint32 arrayElement)
{
    VkWriteDescriptorSet textureBuffer
    {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = DescriptorSet,
        .dstBinding = 1,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = texture->GetTextureBuffer()
    };
    return textureBuffer;
}

VkWriteDescriptorSet RenderPass::CreateStorageDescriptorSet(std::shared_ptr<Mesh> mesh, uint32 bindingSlot)
{
   return CreateStorageDescriptorSet(mesh, bindingSlot, 0);
}

VkWriteDescriptorSet RenderPass::CreateStorageDescriptorSet(std::shared_ptr<Mesh> mesh, uint32 bindingSlot, uint32 arrayElement)
{
    VkWriteDescriptorSet buffer
    {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = DescriptorSet,
        .dstBinding = 0,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .pBufferInfo = mesh->PropertiesBuffer.GetDescriptorbuffer(),
    };
    return buffer;
}

//VkWriteDescriptorSet RenderPass::CreateUnimformDescriptorSet()
//{
//    return VK_NULL_HANDLE;
//}

VkCommandBuffer RenderPass::Draw()
{
	return VK_NULL_HANDLE;
}

void RenderPass::Destroy()
{
	Renderer_DestroyRenderPass(&RenderPassPtr);
	Renderer_DestroyCommandBuffers(&global.Renderer.CommandPool, CommandBufferList.data());
	Renderer_DestroyFrameBuffers(FrameBufferList.data());
}