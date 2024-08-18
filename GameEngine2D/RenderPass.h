#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include <array>
#include <vector>

class RenderPass
{
	private:
	protected:
		VkRenderPass RenderPassPtr = VK_NULL_HANDLE;
		VkRenderPassBeginInfo RenderPassInfo;
		std::vector<VkCommandBuffer> CommandBufferList;
		std::vector<VkFramebuffer> FrameBufferList;
	public:
		RenderPass();
		~RenderPass();
		virtual void BuildRenderPass();
		virtual void Draw();
		virtual void Destroy();
};

