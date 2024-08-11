#include "Window.h"
#include "Global.h"

static WindowState state = { 0 };

void GameEngine_CreateGraphicsWindow(const char* WindowName, uint32_t width, uint32_t height)
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

void GameEngine_PollEvents(void)
{
    while (SDL_PollEvent(&global.Window.Event) )
    {
        switch (global.Window.Event.type)
        {
            case SDL_MOUSEMOTION:     GameEngine_MouseMoveEvent(&global.Window.Event); break;
            case SDL_MOUSEBUTTONDOWN: GameEngine_MouseButtonPressedEvent(&global.Window.Event); break;
            case SDL_MOUSEBUTTONUP:   GameEngine_MouseButtonUnPressedEvent(&global.Window.Event); break;
            case SDL_MOUSEWHEEL:      GameEngine_MouseWheelEvent(&global.Window.Event); break;
            default: break;
        }
    }
}

void GameEngine_DestroyWindow(void)
{
    SDL_DestroyWindow(global.Window.SDLWindow);
    SDL_Quit();
}
