#pragma once
#include "Mouse.h"
#include "Keyboard.h"
#include "Window.h"
#include "GameController.h"

typedef struct global {
    WindowState Window;
    MouseState Mouse;
    KeyboardState Keyboard;
    //ControllerState Controller;
} Global;

extern Global global;
