#include "VulkanDebugger.h"
#include "Global.h"

static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != NULL)
	{
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

static void DestroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator)
{
	PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(global.Renderer.Instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != NULL)
	{
		func(global.Renderer.Instance, global.Renderer.DebugMessenger, pAllocator);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

 VKAPI_ATTR VkBool32 VKAPI_CALL Vulkan_DebugCallBack(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* CallBackData, void* UserData)
{
	fprintf(stderr, "Validation Layer: %s\n", CallBackData->pMessage);
	return VK_FALSE;
}

void Vulkan_SetUpDebugger(VkDebugUtilsMessengerCreateInfoEXT* DebugInfo)
{
	DebugInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	DebugInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	DebugInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	DebugInfo->pfnUserCallback = Vulkan_DebugCallBack;

	VkResult result = CreateDebugUtilsMessengerEXT(global.Renderer.Instance, &DebugInfo, NULL, &global.Renderer.DebugMessenger);
	if (result != VK_SUCCESS)
	{
		//Vulkan_GetError(result);
		SDL_DestroyWindow(&global.Window);
		SDL_Quit();
		return 1;
	}
}

void Vulkan_DestroyDebugger()
{
	DestroyDebugUtilsMessengerEXT(global.Renderer.Instance, NULL);
}
