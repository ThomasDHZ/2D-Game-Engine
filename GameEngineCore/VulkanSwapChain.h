#pragma once
#include <vulkan/vulkan.h>
#include <SDL.h>
#include "CTypedef.h"

typedef struct swapChainState
{
	uint32 SwapChainImageCount;
	uint32 GraphicsFamily;
	uint32 PresentFamily;
	VkQueue GraphicsQueue;
	VkQueue PresentQueue;
	VkImage* SwapChainImages;
	VkImageView* SwapChainImageViews;
	VkExtent2D SwapChainResolution;
	VkSwapchainKHR Swapchain;
}SwapChainState;

VkResult Vulkan_SetUpSwapChain();
VkResult Vulkan_RebuildSwapChain();
void SwapChain_GetQueueFamilies(VkPhysicalDevice physicalDevice, uint32* graphicsFamily, uint32* presentFamily);
void Vulkan_DestroyImageView();
void Vulkan_DestroySwapChain();
