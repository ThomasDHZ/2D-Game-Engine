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
		std::vector<VkCommandBuffer> CommandBuffer;
		std::vector<VkFramebuffer> Framebuffer;
	public:
		RenderPass();
		~RenderPass();
		virtual void BuildRenderPass();
		virtual void Destroy();
};

