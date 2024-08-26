#include "RenderPass.h"
#include <Global.h>

RenderPass::RenderPass()
{
	RenderPassResolution = glm::ivec2((int)global.Renderer.SwapChain.SwapChainResolution.width, (int)global.Renderer.SwapChain.SwapChainResolution.height);
	SampleCount = VK_SAMPLE_COUNT_1_BIT;

	CommandBufferList.resize(global.Renderer.SwapChain.SwapChainImageCount);
	FrameBufferList.resize(global.Renderer.SwapChain.SwapChainImageCount);

	Renderer_CreateCommandBuffers(CommandBufferList.data());
}

RenderPass::~RenderPass()
{
}

void RenderPass::BuildRenderPass()
{
}

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
