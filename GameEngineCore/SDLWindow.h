#pragma once
#define SDL_MAIN_HANDLED
#pragma warning(push)
#pragma warning(disable : 26819) 
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <SDL2/SDL_syswm.h>
#pragma warning(pop)

#include <stdio.h>
#include <stdbool.h>
#include "CTypedef.h"
#include "Macro.h"

typedef struct sdlWindowState
{
    SDL_Window* window;
    SDL_Event Event;
    uint32 Width;
    uint32 Height;
    bool FramebufferResized;
    bool ExitWindow;
} SDLWindowState;


DLL_EXPORT void GameEngine_SDL_CreateGraphicsWindow(const char* WindowName, uint32 width, uint32 height);
DLL_EXPORT void GameEngine_SDL_PollEventHandler(SDL_Event* event);
DLL_EXPORT void GameEngine_SDL_DestroyWindow(void);