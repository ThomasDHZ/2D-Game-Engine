#pragma once
#include <vulkan/vulkan.h>
#include <RenderedColorTexture.h>
#include "SceneProperties.h"
#include "RenderPass.h"
#include "vertex.h"

class RenderPass2D : public RenderPass
{
private:
	std::shared_ptr<RenderedColorTexture> RenderedTexture;

	VkDescriptorPool DescriptorPool = VK_NULL_HANDLE;
	VkDescriptorSetLayout DescriptorSetLayout = VK_NULL_HANDLE;
	VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
	VkPipeline ShaderPipeline = VK_NULL_HANDLE;
	VkPipelineLayout ShaderPipelineLayout = VK_NULL_HANDLE;
	VkPipelineCache PipelineCache = VK_NULL_HANDLE;

public:
	RenderPass2D();
	virtual ~RenderPass2D();

	void BuildRenderPass();
	void BuildRenderPipeline();
	void UpdateRenderPass();
	VkCommandBuffer Draw();
	void Destroy() override;
};