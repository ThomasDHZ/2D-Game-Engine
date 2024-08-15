#pragma once
#include <windows.h>
#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include <vulkan/vulkan_core.h>

#include "Macro.h"
#include "GraphicsDevice.h"
#include "Window.h"

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
	 //std::vector<VkFence> InFlightFences;
	 //std::vector<VkSemaphore> AcquireImageSemaphores;
	 //std::vector<VkSemaphore> PresentImageSemaphores;
	 //std::vector<const char*> ValidationLayers;

	 //VulkanSwapChain SwapChain;
}RendererState;

//void Vulkan_GetExtenstions();
void Vulkan_RendererSetUp();
void Vulkan_DestroyRenderer();

void Vulkan_DestroyCommandPool();
void Vulkan_DestroyDevice();
void Vulkan_DestroySurface();
void Vulkan_DestroyInstance();