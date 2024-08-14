#pragma once
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
} Global;

extern Global global;