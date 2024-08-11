extern "C"
{
#include "Global.h"
}

int main()
{
	GameEngine_CreateGraphicsWindow("Game", 1280, 720);
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
	GameEngine_DestroyWindow();
	return 0;
}

