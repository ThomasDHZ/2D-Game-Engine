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
#include <Mesh2D.h>
#include "RenderPass2D.h"
class Scene
{
	private:
		Timer timer;
		std::shared_ptr<Texture> texture;
		Mesh2D mesh;
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

