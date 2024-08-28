#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include <InterfaceRenderPass.h>
#include "RenderPass2D.h"
#include <Texture.h>
#include <FrameBufferRenderPass.h>
#include <RenderedColorTexture.h>
#include "RenderPass2D.h"

class Scene
{
	private:
		std::shared_ptr<Texture> texture;
		FrameBufferRenderPass frameRenderPass;
		RenderPass2D		  renderPass2D;
	public:
		void StartUp();
		void Update();
		void ImGuiUpdate();
		void BuildRenderPasses();
		void UpdateRenderPasses();
		void Draw();
		void Destroy();
};

