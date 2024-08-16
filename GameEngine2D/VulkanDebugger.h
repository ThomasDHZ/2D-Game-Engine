#pragma once
#include <vulkan/vulkan.h>

void Vulkan_SetUpDebugger(VkDebugUtilsMessengerCreateInfoEXT* DebugInfo);
void Vulkan_DestroyDebugger();
VKAPI_ATTR VkBool32 VKAPI_CALL Vulkan_DebugCallBack(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* CallBackData, void* UserData);

