#include "Scene.h"

void Scene::StartUp()
{
	StartUp();
	BuildRenderers();
}

void Scene::Update()
{
}

void Scene::ImGuiUpdate()
{
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)");
}

void Scene::BuildRenderers()
{
}

void Scene::Draw()
{
	std::vector<VkCommandBuffer> CommandBufferSubmitList;

	Renderer_StartFrame();
	CommandBufferSubmitList.emplace_back(InterfaceRenderPass::ImGuiCommandBuffers[global.Renderer.CommandIndex]);
	Renderer_EndFrame(CommandBufferSubmitList.data());
}

void Scene::Destroy()
{
}
