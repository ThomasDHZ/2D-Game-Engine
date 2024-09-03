#pragma once
#include <vulkan/vulkan.h>
#include <RenderedColorTexture.h>
#include <Mesh2D.h>
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

	void BuildRenderPass(std::shared_ptr<Mesh2D> mesh);
	void BuildRenderPipeline(std::shared_ptr<Mesh2D> mesh);
	void UpdateRenderPass(std::shared_ptr<Mesh2D> mesh);
	VkCommandBuffer Draw(std::shared_ptr<Mesh2D> mesh);
	void Destroy() override;

	std::shared_ptr<RenderedColorTexture> GetRenderedTexture() { return RenderedTexture; }
};