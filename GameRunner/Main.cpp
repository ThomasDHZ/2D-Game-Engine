extern "C"
{
#include <Global.h>
#include <VulkanRenderer.h>
}

int main()
{
	GameEngine_CreateGraphicsWindow("Game", 1280, 720);
	Vulkan_RendererSetUp();
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
	}

	//SDL_GameControllerClose();
	Vulkan_DestroyRenderer();
	GameEngine_DestroyWindow();
	return 0;
}

