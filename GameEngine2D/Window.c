#include "Window.h"
#include "Global.h"

static WindowState state = { 0 };

void GameEngineCreateGraphicsWindow(uint32_t width, uint32_t height, const char* WindowName)
{
	global.Window.FramebufferResized = false;
	global.Window.Width = width;
	global.Window.Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	global.Window.GLFWindow = glfwCreateWindow(width, height, WindowName, NULL, NULL);
	GLFWwindow* a = global.Window.GLFWindow;
	glfwSetWindowUserPointer(global.Window.GLFWindow, NULL);
	glfwSetFramebufferSizeCallback(global.Window.GLFWindow, GameEngineFrameBufferResizeCallBack);
	glfwSetCursorPosCallback(global.Window.GLFWindow, GameEngineMousePosCallback);
	glfwSetMouseButtonCallback(global.Window.GLFWindow, GameEngineMouseButtonCallback);
	glfwSetScrollCallback(global.Window.GLFWindow, GameEngineMouseScrollCallback);
	//glfwSetKeyCallback(GLFWindow, Keyboard::KeyCallBack);
	//GameController::SetUpGamePad();
}

void GameEngineFrameBufferResizeCallBack(GLFWwindow* window, int width, int height)
{
	global.Window.FramebufferResized = true;

	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
}

void GameEngineDestroyWindow(void)
{
	glfwDestroyWindow(global.Window.GLFWindow);
	glfwTerminate();
}
