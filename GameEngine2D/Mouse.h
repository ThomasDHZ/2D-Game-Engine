#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>

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
	int X;
	int Y;
	int WheelOffset;
	MouseButtonEventState MouseButtonState[3];
}MouseState;

void GameEngine_MouseMoveEvent(const SDL_Event* event);
void GameEngine_MouseButtonPressedEvent(const SDL_Event* event);
void GameEngine_MouseButtonUnPressedEvent(const SDL_Event* event);
void GameEngine_MouseWheelEvent(const SDL_Event* event);