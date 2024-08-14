//#pragma once
//#include <vulkan/vulkan.h>
//#include "Window.h"
////
////typedef struct graphicsDeviceState
////{
////}GraphicsDeviceState;
//
//void Vulkan_GetRequiredExtensions(const char** extensions)
//{
//    uint32_t extensionCount = 0;
//    if (!SDL_Vulkan_GetInstanceExtensions(NULL, &extensionCount, NULL)) {
//        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
//    }
//    extensionCount++;
//
//    const char** tempExtensionNames = malloc(sizeof(const char*) * extensionCount);
//    extensions = malloc(sizeof(const char*) * extensionCount);
//    if (!SDL_Vulkan_GetInstanceExtensions(NULL, &extensionCount, tempExtensionNames)) 
//    {
//        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
//        free(tempExtensionNames);
//        free(extensions);
//    }
//    for (uint32_t i = 0; i < extensionCount - 1; i++)
//    {
//        extensions[i] = tempExtensionNames[i];
//    }
//    extensions[extensionCount - 1] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
//
//    free(tempExtensionNames);
//}