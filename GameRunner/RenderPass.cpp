#include "RenderPass.h"

RenderPass::RenderPass()
{
	CommandBufferList.resize(global.Renderer.SwapChain.SwapChainImageCount);
	FrameBufferList.resize(global.Renderer.SwapChain.SwapChainImageCount);
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
