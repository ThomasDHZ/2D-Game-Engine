#pragma once
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>


typedef struct windowState
{
    SDL_Window* SDLWindow;
    SDL_Event Event;
    uint32_t Width;
    uint32_t Height;
    bool FramebufferResized;
} WindowState;

void GameEngine_CreateGraphicsWindow(const char* WindowName, uint32_t width, uint32_t height);
void GameEngine_PollEvents(void);
void GameEngine_DestroyWindow(void);