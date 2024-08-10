#ifndef Window_H
#define Window_H
#pragma once

#include <GLFW/glfw3.h>
#include <memory>
#include <iostream>

class Window
{
private:
	static Window* window;
	static GLFWwindow* GLFWindow;
	static uint32_t Width;
	static uint32_t Height;
	static bool FramebufferResized;

public:

	static void CreateGraphicsWindow(uint32_t width, uint32_t height, const char* WindowName)
	{
		FramebufferResized = false;
		Width = width;
		Height = height;

		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		GLFWindow = glfwCreateWindow(width, height, WindowName, nullptr, nullptr);
		glfwSetWindowUserPointer(GLFWindow, nullptr);
		glfwSetFramebufferSizeCallback(GLFWindow, frameBufferResizeCallBack);
	}

	static void frameBufferResizeCallBack(GLFWwindow* window, int width, int height)
	{
		auto app = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
		app->FramebufferResized = true;

		glfwGetFramebufferSize(window, &width, &height);
		while (width == 0 || height == 0)
		{
			glfwGetFramebufferSize(window, &width, &height);
			glfwWaitEvents();
		}
	}

	static void Update()
	{

	}

	static void Destroy()
	{
		glfwDestroyWindow(GLFWindow);
		glfwTerminate();
	}

	static GLFWwindow* GetWindowPtr() { return GLFWindow; }
	static unsigned int GetWindowWidth() { return Width; }
	static unsigned int GetWindowHeight() { return Height; }
	static bool GetFrameBufferResizedFlag() { return FramebufferResized; }
};
#endif