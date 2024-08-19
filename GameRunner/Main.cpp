extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_vulkan.h>
#include <ImGui/imgui_impl_sdl3.h>
#include "Scene.h"

int main()
{
	GameEngine_CreateGraphicsWindow("Game", 1280, 720);
	//ShaderCompiler::SetUpCompiler();
	Renderer_RendererSetUp();

	Scene scene;
	//RenderPass2D renderPass2D;
	//renderPass2D.BuildRenderPass();

	while (global.Window.Event.type != SDL_QUIT)
	{
		GameEngine_PollEvents();

		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
		scene.ImGuiUpdate();
		ImGui::Render();

		if (global.Keyboard.KeyPressed[INPUTKEY_Z] == KS_Held)
		{
			int a = 234;
		}
		//int width = 0, height = 0;
		//glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		//while (width == 0 || height == 0) {
		//	glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		//	glfwWaitEvents();
		//}
		/*renderPass2D.Draw();*/
		scene.Update();
		scene.Draw();
	}

	//SDL_GameControllerClose();
	Renderer_DestroyRenderer();
	GameEngine_DestroyWindow();
	return 0;
}

