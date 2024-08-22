extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
	#include <FrameTime.h>
}
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_vulkan.h>
#include <ImGui/imgui_impl_sdl2.h>
#include <VulkanBuffer.h>
#include <Texture.h>
#include "Scene.h"

int main()
{
	time_init(160);
	GameEngine_CreateGraphicsWindow("Game", 1280, 720);
	//ShaderCompiler::SetUpCompiler();
	Renderer_RendererSetUp();
	InterfaceRenderPass::StartUp();
	
	Scene scene;
	scene.StartUp();

	Texture texture(54);
    while (!global.Window.ExitWindow)
    {
		time_update();
		while (SDL_PollEvent(&global.Window.Event))
		{
			GameEngine_PollEventHandler(&global.Window.Event);
			ImGui_ImplSDL2_ProcessEvent(&global.Window.Event);
		}
		scene.Update();
		scene.ImGuiUpdate();
		scene.Draw();
		time_update_late();
    }

	vkDeviceWaitIdle(global.Renderer.Device);
	//SDL_GameControllerClose();
	InterfaceRenderPass::Destroy();
	Renderer_DestroyRenderer();
	GameEngine_DestroyWindow();
	return 0;
}
