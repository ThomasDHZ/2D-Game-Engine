#include "VulkanSwapChain.h"
#include "Global.h"

VkSurfaceFormatKHR SwapChain_FindSwapSurfaceFormat(VkSurfaceFormatKHR* availableFormats)
{
	for (int x = 0; x < ARRAY_SIZE(availableFormats); x++)
	{
		if (availableFormats[x].format == VK_FORMAT_B8G8R8A8_UNORM &&
			availableFormats[x].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormats[x];
		}
	}
	fprintf(stderr, "Couldn't find a usable swap surface format.\n");
	return;
}

VkPresentModeKHR SwapChain_FindSwapPresentMode(VkPresentModeKHR* availablePresentModes)
{
	for (int x = 0; x < ARRAY_SIZE(availablePresentModes); x++)
	{
		if (availablePresentModes[x] == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentModes[x];
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

void Vulkan_SetUpSwapChain()
{
	VkSurfaceFormatKHR* compatibleSwapChainFormatList = NULL;
	VkSurfaceFormatKHR* compatiblePresentModesList = NULL;

	uint32_t surfaceFormatCount = UINT32_MAX;
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(global.Renderer.PhysicalDevice, global.Renderer.Surface, &surfaceCapabilities);
	vkGetPhysicalDeviceSurfaceFormatsKHR(global.Renderer.PhysicalDevice, global.Renderer.Surface, &surfaceFormatCount, NULL);
	if (surfaceFormatCount != 0)
	{
		compatibleSwapChainFormatList = malloc(sizeof(VkSurfaceFormatKHR) * surfaceFormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(global.Renderer.PhysicalDevice, global.Renderer.Surface, &surfaceFormatCount, compatibleSwapChainFormatList);
	}

	uint32_t presentModeCount = UINT32_MAX;
	vkGetPhysicalDeviceSurfacePresentModesKHR(global.Renderer.PhysicalDevice, global.Renderer.Surface, &presentModeCount, NULL);
	if (presentModeCount != 0)
	{
		compatiblePresentModesList = malloc(sizeof(VkSurfaceFormatKHR) * presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(global.Renderer.PhysicalDevice, global.Renderer.Surface, &presentModeCount, compatiblePresentModesList);
	}

	FindQueueFamilies(global.Renderer.PhysicalDevice, global.Renderer.Surface);
	VkSurfaceFormatKHR SwapChainImageFormat = SwapChain_FindSwapSurfaceFormat(compatibleSwapChainFormatList);
	VkPresentModeKHR SwapChainPresentMode = SwapChain_FindSwapPresentMode(compatiblePresentModesList);

	int width = INT32_MAX;
	int height = INT32_MAX;
	SDL_Vulkan_GetDrawableSize(global.Window.SDLWindow, &width, &height);

	VkExtent2D extent = { (uint32_t)width, (uint32_t)height };
	global.Renderer.SwapChain.SwapChainResolution = extent;

	uint32_t SwapChainImageCount = surfaceCapabilities.minImageCount + 1;
	if (surfaceCapabilities.maxImageCount > 0 &&
		SwapChainImageCount > surfaceCapabilities.maxImageCount)
	{
		SwapChainImageCount = surfaceCapabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR SwapChainCreateInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = global.Renderer.Surface,
		.minImageCount = SwapChainImageCount,
		.imageFormat = SwapChainImageFormat.format,
		.imageColorSpace = SwapChainImageFormat.colorSpace,
		.imageExtent = extent,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
		.preTransform = surfaceCapabilities.currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = SwapChainPresentMode,
		.clipped = VK_TRUE
	};

	if (global.Renderer.SwapChain.GraphicsFamily != global.Renderer.SwapChain.PresentFamily)
	{
		uint32_t queueFamilyIndices[] = { global.Renderer.SwapChain.GraphicsFamily, global.Renderer.SwapChain.PresentFamily };

		SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		SwapChainCreateInfo.queueFamilyIndexCount = 2;
		SwapChainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		SwapChainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	VkResult result = vkCreateSwapchainKHR(global.Renderer.Device, &SwapChainCreateInfo, NULL, &global.Renderer.SwapChain.Swapchain);
	if (result != VK_SUCCESS)
	{
		fprintf(stderr, "failed to create swap chain! %s\n", result);
		free(compatibleSwapChainFormatList);
		free(compatiblePresentModesList);
		return;
	}

	vkGetSwapchainImagesKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, &SwapChainImageCount, NULL);
	global.Renderer.SwapChain.SwapChainImages = malloc(sizeof(VkImage) * SwapChainImageCount);
	vkGetSwapchainImagesKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, &SwapChainImageCount, &global.Renderer.SwapChain.SwapChainImages);

	global.Renderer.SwapChain.SwapChainImageViews = SwapChainImageCount;
	for (uint32_t x = 0; x < SwapChainImageCount; x++)
	{
		VkImageViewCreateInfo SwapChainViewInfo = 
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = global.Renderer.SwapChain.SwapChainImages[x],
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = SwapChainImageFormat.format,
			.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.subresourceRange.baseMipLevel = 0,
			.subresourceRange.levelCount = 1,
			.subresourceRange.baseArrayLayer = 0,
			.subresourceRange.layerCount = 1
		};

		VkResult result = vkCreateImageView(global.Renderer.Device, &SwapChainViewInfo, NULL, &global.Renderer.SwapChain.SwapChainImageViews[x]);
		if (result != VK_SUCCESS)
		{
			fprintf(stderr, "failed to create swap chain! %s\n", result);
			free(compatibleSwapChainFormatList);
			free(compatiblePresentModesList);
			return;
		}
	}

	free(compatibleSwapChainFormatList);
	free(compatiblePresentModesList);
}

void Vulkan_RebuildSwapChain()
{
	SetUpSwapChain(global.Window.SDLWindow, global.Renderer.Device, global.Renderer.PhysicalDevice, global.Renderer.Surface);
}

void Vulkan_DestroySwapChain()
{
	Vulkan_DestroyImageView();
	Vulkan_DestroySwapChain();
}

void Vulkan_DestroyImageView()
{
	for (int x = 0; x < ARRAY_SIZE(global.Renderer.SwapChain.SwapChainImageViews); x++)
	{
		if (global.Renderer.Surface != VK_NULL_HANDLE)
		{
			vkDestroyImageView(global.Renderer.Device, global.Renderer.SwapChain.SwapChainImageViews[x], NULL);
			global.Renderer.SwapChain.SwapChainImageViews[x] = VK_NULL_HANDLE;
		}
	}
}

void Vulkan_DestroySwapChain()
{
	vkDestroySwapchainKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, NULL);
	global.Renderer.SwapChain.Swapchain = VK_NULL_HANDLE;
}