#pragma once
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdbool.h>
#include <sdl/include/sdl.h>


typedef struct windowState
{
    SDL_Window* SDLWindow;
    SDL_Event Event;
    uint32_t Width;
    uint32_t Height;
    bool FramebufferResized;
} WindowState;

void GameEngineCreateGraphicsWindow(const char* WindowName, uint32_t width, uint32_t height);
void GameEnginePollEvents(void);
void GameEngineDestroyWindow(void);