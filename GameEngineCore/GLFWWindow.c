#include "GLFWWindow.h"
#include "Global.h"

GLFW_Window glfwWindow = { 0 };

void Window_GLFW_CreateGraphicsWindow(const char* WindowName, uint32 width, uint32 height)
{
	glfwWindow.FramebufferResized = false;
	glfwWindow.Width = width;
	glfwWindow.Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindow.GLFWindow = glfwCreateWindow(width, height, WindowName, NULL, NULL);
	glfwSetWindowUserPointer(glfwWindow.GLFWindow, NULL);
	glfwSetFramebufferSizeCallback(glfwWindow.GLFWindow, Window_GLFW_FrameBufferResizeCallBack);
	//glfwSetCursorPosCallback(glfwWindow.GLFWindow, Mouse::MousePosCallback);
	//glfwSetMouseButtonCallback(glfwWindow.GLFWindow, Mouse::MouseButtonCallback);
	//glfwSetScrollCallback(glfwWindow.GLFWindow, Mouse::MouseScrollCallback);
	//glfwSetKeyCallback(glfwWindow.GLFWindow, Keyboard::KeyCallBack);
}

void Window_GLFW_FrameBufferResizeCallBack(GLFWwindow* window, int width, int height)
{
	GLFW_Window* app = (GLFW_Window*)glfwGetWindowUserPointer(window);
	app->FramebufferResized = true;

	glfwGetFramebufferSize(window, &width, &height);
	while (width == 0 || height == 0)
	{
		glfwGetFramebufferSize(window, &width, &height);
		glfwWaitEvents();
	}
}

void Window_GLFW_GetInstanceExtensions(uint32_t* pExtensionCount, const char** extensionProperties) 
{
	const char** extensions = glfwGetRequiredInstanceExtensions(pExtensionCount);
	if (extensions) 
	{
		for (uint32_t x = 0; x < *pExtensionCount; x++) 
		{
			((const char**)extensionProperties)[x] = extensions[x];
		}
	}
	else 
	{
		*pExtensionCount = 0;
		extensionProperties = NULL;
	}
}

void Window_GLFW_CreateSurface(VkInstance* instance, VkSurfaceKHR* surface)
{
	glfwCreateWindowSurface(instance, glfwWindow.GLFWindow, NULL, surface);
}

void Window_GLFW_Destroy(GLFWwindow* window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}