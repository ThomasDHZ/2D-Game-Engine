#pragma once
#include "Mouse.h"
#include "Window.h"

typedef struct global {
    WindowState Window;
    MouseState Mouse;
} Global;

extern Global global;
