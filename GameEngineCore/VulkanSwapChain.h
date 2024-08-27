#pragma once
#include <vulkan/vulkan.h>
#include <SDL.h>

typedef struct swapChainState
{
	uint32_t SwapChainImageCount;
	uint32_t GraphicsFamily;
	uint32_t PresentFamily;
	VkQueue GraphicsQueue;
	VkQueue PresentQueue;
	VkImage* SwapChainImages;
	VkImageView* SwapChainImageViews;
	VkExtent2D SwapChainResolution;
	VkSwapchainKHR Swapchain;
}SwapChainState;

VkResult Vulkan_SetUpSwapChain();
VkResult Vulkan_RebuildSwapChain();
void Vulkan_DestroyImageView();
void Vulkan_DestroySwapChain();
