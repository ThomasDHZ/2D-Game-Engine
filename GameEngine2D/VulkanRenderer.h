#pragma once
#include <vulkan/vulkan.h>

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

void Vulkan_SetUp();