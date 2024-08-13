#pragma once
#include <windows.h>
#include <sdl/include/SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <vulkan/vulkan_core.h>

#include "Window.h"

typedef struct rendererState
{
	 VkInstance Instance;
	 VkDevice Device;
	 VkPhysicalDevice PhysicalDevice;
	 VkSurfaceKHR Surface;
	 VkCommandPool CommandPool;
	 uint32_t ImageIndex;
	 uint32_t CMDIndex;

	 //std::vector<VkFence> InFlightFences;
	 //std::vector<VkSemaphore> AcquireImageSemaphores;
	 //std::vector<VkSemaphore> PresentImageSemaphores;
	 //std::vector<const char*> ValidationLayers;

	 //VulkanDebugger VulkanDebug;
	 //VulkanSwapChain SwapChain;
}RendererState;

void Vulkan_GetError();
void Vulkan_RendererSetUp();