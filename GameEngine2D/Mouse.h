#pragma once
#include <GLFW/glfw3.h>
#include <stdbool.h>

static const uint32_t MOUSEBUTTONS = 3;

typedef struct mouseState
{
	double ScrollX;
	double ScrollY;
	double XPos;
	double YPos;
	double LastX;
	double LastY;

	float ZoomAmt;

	bool MouseButtonPressed[3];
	bool IsDragging;
}MouseState;

void GameEngineMousePosCallback(GLFWwindow* window, double xpos, double ypos);
void GameEngineMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void GameEngineMouseScrollCallback(GLFWwindow* window, double Xoffset, double Yoffset);