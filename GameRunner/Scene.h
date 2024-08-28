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
#include <RendereredColorTexture2D.h>

class Scene
{
	private:
		std::shared_ptr<Texture> texture;
		FrameBufferRenderPass frameRenderPass;
	public:
		void StartUp();
		void Update();
		void ImGuiUpdate();
		void BuildRenderers();
		void Draw();
		void Destroy();
};

