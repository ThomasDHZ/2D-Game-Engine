#pragma once
#include <Windows.h> #include <objbase.h> #include <oaidl.h> #include <dxcapi.h>
#include "FrameTime.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "GameController.h"
#include "VulkanRenderer.h"

typedef struct global {
    SDLWindowState     Window;
    MouseState          Mouse;
    KeyboardState       Keyboard;
    GameControllerState Controller;
    RendererState       Renderer;
    Time_State      time;
} Global;

DLL_EXPORT Global global;