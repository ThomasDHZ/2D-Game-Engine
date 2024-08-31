#pragma once
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdbool.h>
#pragma warning(push)
#pragma warning(disable : 26819) 
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#pragma warning(pop)
#include "CTypedef.h"

typedef struct windowState
{
    SDL_Window* SDLWindow;
    SDL_Event Event;
    uint32 Width;
    uint32 Height;
    bool FramebufferResized;
    bool ExitWindow;
} WindowState;

void GameEngine_CreateGraphicsWindow(const char* WindowName, uint32 width, uint32 height);
void GameEngine_PollEventHandler(SDL_Event* event);
void GameEngine_DestroyWindow(void);