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
		std::vector<VkCommandBuffer> CommandBufferList;
		std::vector<VkFramebuffer> FrameBufferList;
	public:
		RenderPass();
		virtual ~RenderPass();
		virtual VkCommandBuffer Draw() = 0;
		virtual void Destroy();
};

