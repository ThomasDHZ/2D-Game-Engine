#include "Window.h"
#include "Global.h"

void CreateGraphicsWindow(uint32_t width, uint32_t height, const char* WindowName)
{
	global.window.FramebufferResized = false;
	global.window.Width = width;
	global.window.Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	global.window.GLFWindow = glfwCreateWindow(width, height, WindowName, NULL, NULL);
	GLFWwindow* a = global.window.GLFWindow;
	//glfwSetWindowUserPointer(GLFWindow, nullptr);
	glfwSetFramebufferSizeCallback(global.window.GLFWindow, FrameBufferResizeCallBack);
	//glfwSetCursorPosCallback(GLFWindow, Mouse::MousePosCallback);
	//glfwSetMouseButtonCallback(GLFWindow, Mouse::MouseButtonCallback);
	//glfwSetScrollCallback(GLFWindow, Mouse::MouseScrollCallback);
	//glfwSetKeyCallback(GLFWindow, Keyboard::KeyCallBack);
	//GameController::SetUpGamePad();
}

void FrameBufferResizeCallBack(GLFWwindow* window, int width, int height)
{
	//global.window.FramebufferResized = true;

	//glfwGetFramebufferSize(window, &width, &height);
	//while (width == 0 || height == 0)
	//{
	//	glfwGetFramebufferSize(window, &width, &height);
	//	glfwWaitEvents();
	//}
}

//void DestroyWindow()
//{
//	glfwDestroyWindow(global.window.GLFWindow);
//	glfwTerminate();
//}