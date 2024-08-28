#pragma once
#include <vulkan/vulkan.h>
#include "RenderPass.h"
#include "vertex.h"

class RenderPass2D : public RenderPass
{
private:
	VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;
	VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
	VkPipeline ShaderPipeline = VK_NULL_HANDLE;
	VkPipelineLayout ShaderPipelineLayout = VK_NULL_HANDLE;
	VkPipelineCache PipelineCache = VK_NULL_HANDLE;

public:
	RenderPass2D();
	virtual ~RenderPass2D();

	void BuildRenderPass(std::shared_ptr<Texture> renderedTexture);
	void BuildRenderPipeline(std::shared_ptr<Texture> renderedTexture);
	void UpdateRenderPass(std::shared_ptr<Texture> texture);
	VkCommandBuffer Draw();
	void Destroy() override;
};