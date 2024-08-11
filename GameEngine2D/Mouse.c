#include "Mouse.h"
#include "Global.h"

static MouseState state = { 0 };

//void GameEngineMousePosCallback(GLFWwindow* window, double xpos, double ypos)
//{
//	global.Mouse.LastX = global.Mouse.XPos;
//	global.Mouse.LastY = global.Mouse.YPos;
//	global.Mouse.XPos = xpos;
//	global.Mouse.YPos = ypos;
//	global.Mouse.IsDragging = global.Mouse.MouseButtonPressed[0] || global.Mouse.MouseButtonPressed[1] || global.Mouse.MouseButtonPressed[2];
//}
//
//void GameEngineMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (action == GLFW_PRESS)
//	{
//		if (button < MOUSEBUTTONS)
//		{
//			global.Mouse.MouseButtonPressed[button] = true;
//		}
//	}
//	else if (action == GLFW_RELEASE)
//	{
//		if (button < MOUSEBUTTONS)
//		{
//			global.Mouse.MouseButtonPressed[button] = false;
//			global.Mouse.IsDragging = false;
//		}
//	}
//}
//
//void GameEngineMouseScrollCallback(GLFWwindow* window, double Xoffset, double Yoffset)
//{
//	global.Mouse.ZoomAmt += Yoffset / 50.0f;
//	global.Mouse.ScrollX = Xoffset;
//	global.Mouse.ScrollY = global.Mouse.ZoomAmt;
//}

void GameEngine_MouseButtonState(uint32_t buttonstate, const MouseButtons button)
{
	if (buttonstate)
	{
		//if (global.Mouse.MouseButtonState[button] > 0)
		//{
		//	global.Mouse.MouseButtonState[button] = MS_HELD;
		//}
		//else
		//{
			global.Mouse.MouseButtonState[button] = MS_PRESSED;
		//}
	}
	else
	{
		global.Mouse.MouseButtonState[button] = MS_UNPRESSED;
	}

	printf("Mouse Button Left: %i\n", global.Mouse.MouseButtonState[MB_Left]);
	printf("Mouse Button Middle: %i\n", global.Mouse.MouseButtonState[MB_Middle]);
	printf("Mouse Button Right: %i\n", global.Mouse.MouseButtonState[MB_Right]);
}

void GameEngine_MouseMoveEvent(const SDL_Event* event)
{
	global.Mouse.X = event->motion.x;
	global.Mouse.Y = event->motion.y;
}

void GameEngine_MouseButtonPressedEvent(const SDL_Event* event)
{
	const uint32_t mouseState = SDL_GetMouseState(NULL,NULL);
    switch (event->button.button)
    {
		case SDL_BUTTON_LEFT: GameEngine_MouseButtonState(mouseState, MB_Left); break;
        case SDL_BUTTON_MIDDLE: GameEngine_MouseButtonState(mouseState, MB_Middle); break;
        case SDL_BUTTON_RIGHT: GameEngine_MouseButtonState(mouseState, MB_Right); break;
        default: break;
    }
}
