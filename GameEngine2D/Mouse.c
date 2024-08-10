#include "Mouse.h"
#include "Global.h"

void GameEngineMousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	global.Mouse.LastX = global.Mouse.XPos;
	global.Mouse.LastY = global.Mouse.YPos;
	global.Mouse.XPos = xpos;
	global.Mouse.YPos = ypos;
	global.Mouse.IsDragging = global.Mouse.MouseButtonPressed[0] || global.Mouse.MouseButtonPressed[1] || global.Mouse.MouseButtonPressed[2];
}

void GameEngineMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button < MOUSEBUTTONS)
		{
			global.Mouse.MouseButtonPressed[button] = true;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		if (button < MOUSEBUTTONS)
		{
			global.Mouse.MouseButtonPressed[button] = false;
			global.Mouse.IsDragging = false;
		}
	}
}

void GameEngineMouseScrollCallback(GLFWwindow* window, double Xoffset, double Yoffset)
{
	global.Mouse.ZoomAmt += Yoffset / 50.0f;
	global.Mouse.ScrollX = Xoffset;
	global.Mouse.ScrollY = global.Mouse.ZoomAmt;
}