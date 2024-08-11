#include "Window.h"
#include "Global.h"

static WindowState state = { 0 };

void GameEngineCreateGraphicsWindow(const char* WindowName, uint32_t width, uint32_t height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        printf("Could not loead SDL: %s\n", SDL_GetError());
    }

    global.Window.SDLWindow = SDL_CreateWindow(WindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_VULKAN);
    if (!global.Window.SDLWindow)
    {
        printf("Failed to load window: %s\n", SDL_GetError());
    }
}

void GameEnginePollEvents(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) )
    {
        switch (event.type)
        {
            case SDL_MOUSEMOTION: GameEngine_MouseMoveEvent(&event); break;
            case SDL_MOUSEBUTTONDOWN: GameEngine_MouseButtonPressedEvent(&event); break;
            case SDL_MOUSEBUTTONUP: GameEngine_MouseButtonPressedEvent(&event); break;
            default: break;
        }
    }
}

void GameEngineDestroyWindow(void)
{
    SDL_DestroyWindow(global.Window.SDLWindow);
    SDL_Quit();
}
