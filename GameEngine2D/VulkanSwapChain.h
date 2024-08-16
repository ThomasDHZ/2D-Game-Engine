#pragma once
#include <vulkan/vulkan.h>
typedef struct swapChainState
{
	uint32_t GraphicsFamily;
	uint32_t PresentFamily;
	uint32_t SurfaceFormatCount;
	uint32_t PresentModeCount;
	uint32_t SwapChainImageCount;

	VkSurfaceFormatKHR SwapChainImageFormat;
	VkPresentModeKHR SwapChainPresentMode;
	VkSurfaceCapabilitiesKHR SwapChainCapabilities;

	//std::vector<VkExtensionProperties> SupportedExtensions;
	//std::vector<VkLayerProperties> VulkanLayers;
	//std::vector<VkSurfaceFormatKHR> CompatibleSwapChainFormatList;
	//std::vector<VkPresentModeKHR> CompatiblePresentModesList;

	//std::vector<VkImage> SwapChainImages;
	//std::vector<VkImageView> SwapChainImageViews;
	VkExtent2D SwapChainResolution;
}SwapChainState;

void Vulkan_SetUpSwapChain();