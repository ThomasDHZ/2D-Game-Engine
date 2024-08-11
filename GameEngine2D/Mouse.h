#pragma once
#define SDL_MAIN_HANDLED
#include <stdbool.h>
#include <sdl/include/sdl.h>

typedef enum mouseButtons
{
	MB_Left = 1,
	MB_Middle = 2,
	MB_Right = 3
}MouseButtons;

typedef enum mouseButtonEventState
{
	MS_UNPRESSED,
	MS_PRESSED,
	MS_HELD
}MouseButtonEventState;

typedef struct mouseState
{
	uint32_t X;
	uint32_t Y;
	MouseButtonEventState MouseButtonState[3];

}MouseState;

static void GameEngine_MouseButtonState(uint32_t buttonstate, const MouseButtons button);
void GameEngine_MouseMoveEvent(const SDL_Event* event);
void GameEngine_MouseButtonPressedEvent(const SDL_Event* event);
//void GameEngineMousePosCallback(GLFWwindow* window, double xpos, double ypos);
//void GameEngineMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
//void GameEngineMouseScrollCallback(GLFWwindow* window, double Xoffset, double Yoffset);