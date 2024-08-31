extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
	#include <FrameTime.h>
}
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_vulkan.h>
#include <ImGui/imgui_impl_sdl2.h>
#include <VulkanBuffer.h>
#include <Texture.h>
#include "Scene.h"

int main()
{
    time_init(60);
    GameEngine_CreateGraphicsWindow("Game", 1280, 720);
    Renderer_RendererSetUp();
    InterfaceRenderPass::StartUp();

    Scene scene;
    scene.StartUp();
    while (!global.Window.ExitWindow)
    {
        while (SDL_PollEvent(&global.Window.Event))
        {
            GameEngine_PollEventHandler(&global.Window.Event);
            ImGui_ImplSDL2_ProcessEvent(&global.Window.Event);
        }

        Uint32 windowFlags = SDL_GetWindowFlags(global.Window.SDLWindow);
        if (!(windowFlags & SDL_WINDOW_MINIMIZED))
        {
            time_update();
            scene.Update();
            scene.ImGuiUpdate();
            scene.Draw();
            time_update_late();
        }
    }
    vkDeviceWaitIdle(global.Renderer.Device);
    InterfaceRenderPass::Destroy();
    scene.Destroy();
    Renderer_DestroyRenderer();
    GameEngine_DestroyWindow();

    return 0;
}
