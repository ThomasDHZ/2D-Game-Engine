#pragma once
#include <vulkan/vulkan.h>
#include <SDL.h>

typedef struct swapChainState
{
	uint32_t GraphicsFamily;
	uint32_t PresentFamily;
	VkImage* SwapChainImages;
	VkImageView* SwapChainImageViews;
	VkExtent2D SwapChainResolution;
	VkSwapchainKHR Swapchain;
}SwapChainState;

void Vulkan_SetUpSwapChain();
void Vulkan_RebuildSwapChain();
void Vulkan_DestroySwapChain();
void Vulkan_DestroyImageView();
void Vulkan_DestroySwapChain();
