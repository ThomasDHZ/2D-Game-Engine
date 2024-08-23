#pragma once
#include "RenderPass.h"
#include "RendereredColorTexture2D.h"
#include "vertex.h"

class FrameBufferRenderPass : public RenderPass
{
private:
	std::shared_ptr<RendereredColorTexture2D> RenderedTexture;
	std::shared_ptr<RendereredColorTexture2D> BloomTexture;

	VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;
	VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
	VkPipeline ShaderPipeline = VK_NULL_HANDLE;
	VkPipelineLayout ShaderPipelineLayout = VK_NULL_HANDLE;
	VkPipelineCache PipelineCache = VK_NULL_HANDLE;

public:
	FrameBufferRenderPass();
	virtual ~FrameBufferRenderPass();

	void BuildRenderPass(std::shared_ptr<RendereredColorTexture2D> renderedTexture);
	void BuildRenderPipeline();
	void Draw();
	void Destroy();
};