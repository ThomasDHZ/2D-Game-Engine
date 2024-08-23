#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include <array>
#include <vector>
#include "RendereredColorTexture2D.h"

class RenderPass
{
	private:
	protected:
		glm::ivec2 RenderPassResolution;
		VkSampleCountFlagBits SampleCount;

		VkRenderPass RenderPassPtr;
		VkRenderPassBeginInfo RenderPassInfo;
		std::vector<VkCommandBuffer> CommandBufferList;
		std::vector<VkFramebuffer> FrameBufferList;
	public:
		RenderPass();
		~RenderPass();
		virtual void BuildRenderPass();
		virtual VkCommandBuffer Draw();
		virtual void Destroy();
};

