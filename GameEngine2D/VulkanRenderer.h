#pragma once
#include <windows.h>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include "Macro.h"
#include "VulkanRendererStruct.h"
#include "GraphicsDevice.h"
#include "VulkanSwapChain.h"
#include "Window.h"
#include "CArray.h"

static const int MAX_FRAMES_IN_FLIGHT = 3;

typedef struct rendererState
{
	 VkInstance Instance;
	 VkDevice Device;
	 VkPhysicalDevice PhysicalDevice;
	 VkSurfaceKHR Surface;
	 VkCommandPool CommandPool;
	 uint32_t ImageIndex;
	 uint32_t CMDIndex;
	 VkDebugUtilsMessengerEXT DebugMessenger;
	 SwapChainState SwapChain;
	 VkPhysicalDeviceFeatures PhysicalDeviceFeatures;

	 VkFence* InFlightFences;
	 VkSemaphore* AcquireImageSemaphores;
	 VkSemaphore* PresentImageSemaphores;
	 bool RebuildSwapChainFlag;
}RendererState;

void Renderer_RendererSetUp();
void Renderer_CreateCommandBuffers(VkImageView* commandBufferList);
void Renderer_CreateFrameBuffer(Renderer_CommandFrameBufferInfoStruct* createCommandBufferInfo);
void Renderer_CreateRenderPass(Renderer_RenderPassCreateInfoStruct* renderPassCreateInfo);
void Renderer_StartFrame();
void Renderer_EndFrame(VkCommandBuffer* commandBufferSubmitList);
void Renderer_BeginCommandBuffer(Renderer_BeginCommandBufferStruct* beginCommandBufferInfo);
void Renderer_EndCommandBuffer(VkCommandBuffer* commandBuffer);

void Renderer_DestroyRenderer();
void Renderer_DestroyFences();
void Renderer_DestroyCommandPool();
void Renderer_DestroyDevice();
void Renderer_DestroySurface();
void Renderer_DestroyDebugger();
void Renderer_DestroyInstance();