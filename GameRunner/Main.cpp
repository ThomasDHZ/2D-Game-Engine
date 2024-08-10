extern "C"
{
	#include "Global.h"
	#include "../GameEngine2D/Window.h"
}
#include "window.h"

int main()
{
	CreateGraphicsWindow(1280, 720, "Game");
	while (!glfwWindowShouldClose(global.window.GLFWindow))
	{
		glfwPollEvents();

		int width = 0, height = 0;
		glfwGetFramebufferSize(global.window.GLFWindow, &width, &height);
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(global.window.GLFWindow, &width, &height);
			glfwWaitEvents();
		}
	}
	//DestroyWindow();
}