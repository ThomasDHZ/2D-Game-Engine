#include "Scene.h"

void Scene::StartUp()
{
	BuildRenderers();
}

void Scene::Update()
{
}

void Scene::ImGuiUpdate()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Button Window");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)");
	ImGui::End();
	ImGui::Render();
}

void Scene::BuildRenderers()
{
}

void Scene::Draw()
{
	std::vector<VkCommandBuffer> CommandBufferSubmitList;

	Renderer_StartFrame();
	InterfaceRenderPass::Draw();
	CommandBufferSubmitList.emplace_back(InterfaceRenderPass::ImGuiCommandBuffers[global.Renderer.CommandIndex]);
	Renderer_EndFrame(CommandBufferSubmitList.data(), CommandBufferSubmitList.size());
}

void Scene::Destroy()
{
}
