#pragma once
#include "Window.h"
#include "FrameTime.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"
#include "GameController.h"
#include "VulkanRenderer.h"

typedef struct global {
    WindowState         Window;
    MouseState          Mouse;
    KeyboardState       Keyboard;
    GameControllerState Controller;
    RendererState       Renderer;
    Time_State      time;
} Global;

DLL_EXPORT Global global;