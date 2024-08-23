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
    time_init(160);
    GameEngine_CreateGraphicsWindow("Game", 1280, 720);

    // Setup your Vulkan Renderer here
    Renderer_RendererSetUp();

    // Make sure the interface render pass is started after the graphics window is created
    InterfaceRenderPass::StartUp();

    Scene scene;
    scene.StartUp();

    Texture texture("../Texture/awesomeface.png", VkFormat::VK_FORMAT_R8G8B8A8_SRGB, TextureTypeEnum::kType_DiffuseTextureMap);

    while (!global.Window.ExitWindow)
    {
        time_update();

        // Event polling and handling
        while (SDL_PollEvent(&global.Window.Event))
        {
            GameEngine_PollEventHandler(&global.Window.Event);
            ImGui_ImplSDL2_ProcessEvent(&global.Window.Event);
        }

        scene.Update();
        scene.ImGuiUpdate();
        scene.Draw();
        time_update_late();
    }

    vkDeviceWaitIdle(global.Renderer.Device);
    InterfaceRenderPass::Destroy();
    Renderer_DestroyRenderer();
    GameEngine_DestroyWindow();

    return 0;
}
