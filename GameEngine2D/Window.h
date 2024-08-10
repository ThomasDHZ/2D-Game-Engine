#pragma once
#include <GLFW/glfw3.h>
#include <stdbool.h>

typedef struct windowState 
{
	GLFWwindow* GLFWindow;
	uint32_t Width;
	uint32_t Height;
	bool FramebufferResized;
} WindowState;

void CreateGraphicsWindow(uint32_t width, uint32_t height, const char* WindowName);
void FrameBufferResizeCallBack(GLFWwindow* window, int width, int height);
//void DestroyWindow(void);