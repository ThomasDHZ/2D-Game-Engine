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

void RenderPass::Draw()
{
}

void RenderPass::Destroy()
{

}
