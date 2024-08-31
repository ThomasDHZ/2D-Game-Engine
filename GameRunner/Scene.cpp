#include "Scene.h"
#include <Global.h>
void Scene::StartUp()
{
	texture = std::make_shared<Texture>(Texture("../Textures/awesomeface.png", VK_FORMAT_R8G8B8A8_SRGB, TextureTypeEnum::kType_DiffuseTextureMap));
	BuildRenderPasses();
}

void Scene::Update()
{
	if (global.Renderer.RebuildRendererFlag)
	{
		UpdateRenderPasses();
	}
}

void Scene::ImGuiUpdate()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Button Window");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / global.time.frame_time, global.time.frame_rate);
	texture.get()->ImGuiShowTexture(ImVec2(256, 128));
	ImGui::End();
	ImGui::Render();
}

void Scene::BuildRenderPasses()
{
	frameRenderPass.BuildRenderPass(texture);
}

void Scene::UpdateRenderPasses()
{
	Renderer_RebuildSwapChain();
	frameRenderPass.UpdateRenderPass(texture);
	InterfaceRenderPass::RebuildSwapChain();
	global.Renderer.RebuildRendererFlag = false;
}

void Scene::Draw()
{
	std::vector<VkCommandBuffer> CommandBufferSubmitList;

	VULKAN_RESULT(Renderer_StartFrame());
	CommandBufferSubmitList.emplace_back(frameRenderPass.Draw());
	CommandBufferSubmitList.emplace_back(InterfaceRenderPass::Draw());
	VULKAN_RESULT(Renderer_EndFrame(CommandBufferSubmitList.data(), static_cast<uint32_t>(CommandBufferSubmitList.size())));
}

void Scene::Destroy()
{
	texture->Destroy();
	frameRenderPass.Destroy();
}
