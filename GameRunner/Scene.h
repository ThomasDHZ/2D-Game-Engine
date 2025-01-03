#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include <InterfaceRenderPass.h>
#include "RenderPass2D.h"
#include <Texture.h>
#include <OrthographicCamera.h>
#include <FrameBufferRenderPass.h>
#include <RenderedColorTexture.h>
#include <Mesh2D.h>
#include "RenderPass2D.h"

class Scene
{
	private:
		std::vector<Vertex2D> SpriteVertexList;

		Timer timer;
		SceneDataBuffer sceneProperties;
		std::shared_ptr<Texture> texture;
		std::shared_ptr<Mesh2D> mesh;
		std::shared_ptr<OrthographicCamera> orthographicCamera;
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

