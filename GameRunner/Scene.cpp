#include "Scene.h"
#include <Global.h>
void Scene::StartUp()
{
	texture = std::make_shared<Texture>(Texture("../Textures/awesomeface.png", VK_FORMAT_R8G8B8A8_SRGB, TextureTypeEnum::kType_DiffuseTextureMap));
	frameRenderPass.BuildRenderPass(texture);
	BuildRenderers();
}

void Scene::Update()
{
}

void Scene::ImGuiUpdate()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Button Window");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / global.time.frame_time, global.time.frame_rate);
	texture.get()->ImGuiShowTexture(ImVec2(256, 128));
	ImGui::End();
	ImGui::Render();
}

void Scene::BuildRenderers()
{
}

void Scene::Draw()
{
	std::vector<VkCommandBuffer> CommandBufferSubmitList;

	Renderer_StartFrame();
	CommandBufferSubmitList.emplace_back(frameRenderPass.Draw());
    InterfaceRenderPass::Draw();
	CommandBufferSubmitList.emplace_back(InterfaceRenderPass::ImGuiCommandBuffers[global.Renderer.CommandIndex]);

	//Renderer_EndFrame(CommandBufferSubmitList.data(), CommandBufferSubmitList.size());
	//vkResetCommandBuffer()
    VkPipelineStageFlags waitStages[] =
    {
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT // Stage before signaling the semaphore
    };

    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    SubmitInfo.waitSemaphoreCount = 1;
    SubmitInfo.pWaitSemaphores = &global.Renderer.AcquireImageSemaphores[global.Renderer.CommandIndex];
    SubmitInfo.pWaitDstStageMask = waitStages;
    SubmitInfo.commandBufferCount = CommandBufferSubmitList.size();
    SubmitInfo.pCommandBuffers = CommandBufferSubmitList.data();
    SubmitInfo.signalSemaphoreCount = 1;
    SubmitInfo.pSignalSemaphores = &global.Renderer.AcquireImageSemaphores[global.Renderer.ImageIndex];
    VkResult QueueSubmit = vkQueueSubmit(global.Renderer.SwapChain.GraphicsQueue, 1, &SubmitInfo, global.Renderer.InFlightFences[global.Renderer.CommandIndex]);
    if (QueueSubmit != VK_SUCCESS)
    {
       // fprintf(stderr, "Failed to submit draw command buffer: %s\n", Renderer_GetError(QueueSubmit));
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
        return;
    }

    // Present info
    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = &global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex];
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &global.Renderer.SwapChain.Swapchain;
    presentInfo.pImageIndices = &global.Renderer.ImageIndex;

    // Present the frame
    VkResult presentResult = vkQueuePresentKHR(global.Renderer.SwapChain.PresentQueue, &presentInfo);
    if (presentResult == VK_ERROR_OUT_OF_DATE_KHR || presentResult == VK_SUBOPTIMAL_KHR)
    {
       // Renderer_RebuildSwapChain();
    }
    else if (presentResult != VK_SUCCESS)
    {
        //fprintf(stderr, "Failed to present swap chain image: %s\n", Renderer_GetError(presentResult));
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

void Scene::Destroy()
{
}
