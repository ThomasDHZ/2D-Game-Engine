#include <vulkan/vulkan_core.h>
#include <GLFW/glfw3.h>
#include "CTypedef.h"
#include <stdio.h>
#include <stdbool.h>
#include "Macro.h"

typedef struct glfw_Window
{
	GLFWwindow* GLFWindow;
	uint32_t Width;
	uint32_t Height;
	bool FramebufferResized;
}GLFW_Window;
DLL_EXPORT GLFW_Window glfwWindow;

DLL_EXPORT void Window_GLFW_CreateGraphicsWindow(const char* WindowName, uint32 width, uint32 height);
DLL_EXPORT void Window_GLFW_FrameBufferResizeCallBack(GLFWwindow* window, int width, int height);
DLL_EXPORT void Window_GLFW_GetInstanceExtensions(uint32_t* pExtensionCount, const char** extensionProperties);
DLL_EXPORT void Window_GLFW_CreateSurface(VkInstance* instance, VkSurfaceKHR* surface);
DLL_EXPORT void Window_GLFW_Destroy(GLFWwindow* window);