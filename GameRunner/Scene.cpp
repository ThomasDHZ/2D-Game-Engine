#include "Scene.h"
#include <Global.h>

void Scene::StartUp()
{
	frameRenderPass.BuildRenderPass();
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
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / global.time.frame_time, global.time.frame_rate);
	texture.ImGuiShowTexture(ImVec2(256, 128));
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
	CommandBufferSubmitList.emplace_back(InterfaceRenderPass::ImGuiCommandBuffers[global.Renderer.CommandIndex]);
	InterfaceRenderPass::Draw();
	Renderer_EndFrame(CommandBufferSubmitList.data(), CommandBufferSubmitList.size());
	//vkResetCommandBuffer()
}

void Scene::Destroy()
{
}
