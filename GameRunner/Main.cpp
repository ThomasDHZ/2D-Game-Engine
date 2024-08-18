extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
}
#include "RenderPass2D.h"

int main()
{
	GameEngine_CreateGraphicsWindow("Game", 1280, 720);
	Renderer_RendererSetUp();

	RenderPass2D renderPass2D;
	renderPass2D.BuildRenderPass();

	while (global.Window.Event.type != SDL_QUIT)
	{
		GameEngine_PollEvents();
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
		renderPass2D.Draw();
	}

	//SDL_GameControllerClose();
	Renderer_DestroyRenderer();
	GameEngine_DestroyWindow();
	return 0;
}

