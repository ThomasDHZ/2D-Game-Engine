#include "Mouse.h"
#include "Global.h"

static MouseState state = { 0 };

void GameEngine_MouseMoveEvent(const SDL_Event* event)
{
	global.Mouse.X = event->motion.x;
	global.Mouse.Y = event->motion.y;
}

void GameEngine_MouseButtonPressedEvent(const SDL_Event* event)
{
    switch (global.Window.Event.button.button)
    {
		case SDL_BUTTON_LEFT:   global.Mouse.MouseButtonState[MB_Left-1] = MS_PRESSED; printf("Mouse Button Left: %i\n", global.Mouse.MouseButtonState[MB_Left - 1]); break;
		case SDL_BUTTON_MIDDLE: global.Mouse.MouseButtonState[MB_Middle-1] = MS_PRESSED; printf("Mouse Button Middle: %i\n", global.Mouse.MouseButtonState[MB_Middle - 1]); break;
		case SDL_BUTTON_RIGHT:  global.Mouse.MouseButtonState[MB_Right-1] = MS_PRESSED; printf("Mouse Button Right: %i\n", global.Mouse.MouseButtonState[MB_Right - 1]); break;
        default: break;
    }
}

void GameEngine_MouseButtonUnPressedEvent(const SDL_Event* event)
{
	switch (global.Window.Event.button.button)
	{
		case SDL_BUTTON_LEFT:   global.Mouse.MouseButtonState[MB_Left-1] = MS_UNPRESSED; printf("Mouse Button Left: %i\n", global.Mouse.MouseButtonState[MB_Left - 1]); break;
		case SDL_BUTTON_MIDDLE: global.Mouse.MouseButtonState[MB_Middle-1] = MS_UNPRESSED; printf("Mouse Button Middle: %i\n", global.Mouse.MouseButtonState[MB_Middle - 1]); break;
		case SDL_BUTTON_RIGHT:  global.Mouse.MouseButtonState[MB_Right-1] = MS_UNPRESSED; printf("Mouse Button Right: %i\n", global.Mouse.MouseButtonState[MB_Right - 1]); break;
		default: break;
	}
}

void GameEngine_MouseWheelEvent(const SDL_Event* event)
{
	global.Mouse.WheelOffset += event->wheel.y;
	printf("Mouse Wheel Offset: %i\n", global.Mouse.WheelOffset);
}
