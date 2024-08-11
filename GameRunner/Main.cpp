extern "C"
{
#include "Global.h"
}

int main()
{
	GameEngineCreateGraphicsWindow("Game", 1280, 720);
	while (global.Window.Event.type != SDL_QUIT)
	{
		GameEnginePollEvents();
		//int width = 0, height = 0;
		//glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		//while (width == 0 || height == 0) {
		//	glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		//	glfwWaitEvents();
		//}

		SDL_PollEvent(&global.Window.Event);
	}
	GameEngineDestroyWindow();
	return 0;
}

