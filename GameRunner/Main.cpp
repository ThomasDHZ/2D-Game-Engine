extern "C"
{
#include "Global.h"
}

int main()
{
	GameEngineCreateGraphicsWindow(1280, 720, "Game");
	while (!glfwWindowShouldClose(global.Window.GLFWindow))
	{
		glfwPollEvents();

		int width = 0, height = 0;
		glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(global.Window.GLFWindow, &width, &height);
			glfwWaitEvents();
		}
	}
	GameEngineDestroyWindow();
}

