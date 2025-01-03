#include "Scene.h"
#include <Global.h>
#include <Texture.h>
#include <SceneDataBuffer.h>

void Scene::StartUp()
{
	std::vector<uint32> SpriteIndexList = {
	   0, 1, 3,
	   1, 2, 3
	};

	Timer timer;
	timer.Time = 0.0f;

	texture = std::make_shared<Texture>(Texture("../Textures/awesomeface.png", VK_FORMAT_R8G8B8A8_SRGB, TextureTypeEnum::kType_DiffuseTextureMap));
	mesh = std::make_shared<Mesh2D>(Mesh2D(SpriteVertexList, SpriteIndexList));
	orthographicCamera = std::make_shared<OrthographicCamera>(OrthographicCamera(vec2((float)global.Renderer.SwapChain.SwapChainResolution.width, (float)global.Renderer.SwapChain.SwapChainResolution.height), vec3(0.0f, 0.0f, 5.0f)));

	BuildRenderPasses();
}

void Scene::Update()
{
	if (global.Renderer.RebuildRendererFlag)
	{
		UpdateRenderPasses();
	}
	VkCommandBuffer commandBuffer = Renderer_BeginSingleUseCommandBuffer();
	mesh->BufferUpdate(commandBuffer);
	Renderer_EndSingleUseCommandBuffer(commandBuffer);

	orthographicCamera->Update(sceneProperties);
	if (global.Keyboard.KeyPressed[INPUTKEY_W] == KS_Pressed)
	{
		orthographicCamera->Position.y -= .01f;
	}
	if (global.Keyboard.KeyPressed[INPUTKEY_A] == KS_Pressed)
	{
		orthographicCamera->Position.x += .01f;
	}
	if (global.Keyboard.KeyPressed[INPUTKEY_S] == KS_Pressed)
	{
		orthographicCamera->Position.y += .01f;
	}
	if (global.Keyboard.KeyPressed[INPUTKEY_D] == KS_Pressed)
	{
		orthographicCamera->Position.x -= .01f;
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
	renderPass2D.BuildRenderPass(mesh);
	frameRenderPass.BuildRenderPass(renderPass2D.GetRenderedTexture());
}

void Scene::UpdateRenderPasses()
{
	Renderer_RebuildSwapChain();
	renderPass2D.UpdateRenderPass(mesh);
	frameRenderPass.UpdateRenderPass(renderPass2D.GetRenderedTexture());
	InterfaceRenderPass::RebuildSwapChain();
	global.Renderer.RebuildRendererFlag = false;
}

void Scene::Draw()
{
	std::vector<VkCommandBuffer> CommandBufferSubmitList;

	VULKAN_RESULT(Renderer_StartFrame());

	CommandBufferSubmitList.emplace_back(renderPass2D.Draw(mesh, sceneProperties));
	CommandBufferSubmitList.emplace_back(frameRenderPass.Draw());
	CommandBufferSubmitList.emplace_back(InterfaceRenderPass::Draw());

	VULKAN_RESULT(Renderer_EndFrame(CommandBufferSubmitList.data(), static_cast<uint32_t>(CommandBufferSubmitList.size())));
}

void Scene::Destroy()
{
	mesh->Destroy();
	texture->Destroy();
	frameRenderPass.Destroy();
}
