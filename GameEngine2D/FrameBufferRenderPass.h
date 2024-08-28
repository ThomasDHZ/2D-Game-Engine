#pragma once
#include <vulkan/vulkan.h>
#include "RenderPass.h"
#include "RendereredColorTexture2D.h"
#include "vertex.h"

class FrameBufferRenderPass : public RenderPass
{
private:
	VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;
	VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
	VkPipeline ShaderPipeline = VK_NULL_HANDLE;
	VkPipelineLayout ShaderPipelineLayout = VK_NULL_HANDLE;
	VkPipelineCache PipelineCache = VK_NULL_HANDLE;

public:
	FrameBufferRenderPass();
	virtual ~FrameBufferRenderPass();

	void BuildRenderPass(std::shared_ptr<Texture> renderedTexture);
	void BuildRenderPipeline(std::shared_ptr<Texture> renderedTexture);
	VkCommandBuffer Draw();
	void Destroy() override;
};