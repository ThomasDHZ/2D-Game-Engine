#pragma once
#include <vulkan/vulkan.h>

void Renderer_GetError(VkResult result)
{
    const char* errorMessage;
    switch (result)
    {
        case VK_NOT_READY: errorMessage = "VK_NOT_READY"; break;
        case VK_TIMEOUT: errorMessage = "VK_TIMEOUT"; break;
        case VK_EVENT_SET: errorMessage = "VK_EVENT_SET"; break;
        case VK_EVENT_RESET: errorMessage = "VK_EVENT_RESET"; break;
        case VK_INCOMPLETE: errorMessage = "VK_INCOMPLETE"; break;
        case VK_ERROR_OUT_OF_HOST_MEMORY: errorMessage = "VK_ERROR_OUT_OF_HOST_MEMORY"; break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: errorMessage = "VK_ERROR_OUT_OF_DEVICE_MEMORY"; break;
        case VK_ERROR_INITIALIZATION_FAILED: errorMessage = "VK_ERROR_INITIALIZATION_FAILED"; break;
        case VK_ERROR_DEVICE_LOST: errorMessage = "VK_ERROR_DEVICE_LOST"; break;
        case VK_ERROR_MEMORY_MAP_FAILED: errorMessage = "VK_ERROR_MEMORY_MAP_FAILED"; break;
        case VK_ERROR_LAYER_NOT_PRESENT: errorMessage = "VK_ERROR_LAYER_NOT_PRESENT"; break;
        case VK_ERROR_EXTENSION_NOT_PRESENT: errorMessage = "VK_ERROR_EXTENSION_NOT_PRESENT"; break;
        case VK_ERROR_FEATURE_NOT_PRESENT: errorMessage = "VK_ERROR_FEATURE_NOT_PRESENT"; break;
        case VK_ERROR_INCOMPATIBLE_DRIVER: errorMessage = "VK_ERROR_INCOMPATIBLE_DRIVER"; break;
        case VK_ERROR_TOO_MANY_OBJECTS: errorMessage = "VK_ERROR_TOO_MANY_OBJECTS"; break;
        case VK_ERROR_FORMAT_NOT_SUPPORTED: errorMessage = "VK_ERROR_FORMAT_NOT_SUPPORTED"; break;
        case VK_ERROR_FRAGMENTED_POOL: errorMessage = "VK_ERROR_FRAGMENTED_POOL"; break;
        case VK_ERROR_UNKNOWN: errorMessage = "VK_ERROR_UNKNOWN"; break;
        case VK_ERROR_OUT_OF_POOL_MEMORY: errorMessage = "VK_ERROR_OUT_OF_POOL_MEMORY"; break;
        case VK_ERROR_INVALID_EXTERNAL_HANDLE: errorMessage = "VK_ERROR_INVALID_EXTERNAL_HANDLE"; break;
        case VK_ERROR_FRAGMENTATION: errorMessage = "VK_ERROR_FRAGMENTATION"; break;
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: errorMessage = "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"; break;
        case VK_PIPELINE_COMPILE_REQUIRED: errorMessage = "VK_PIPELINE_COMPILE_REQUIRED"; break;
        case VK_ERROR_SURFACE_LOST_KHR: errorMessage = "VK_ERROR_SURFACE_LOST_KHR"; break;
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: errorMessage = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"; break;
        case VK_SUBOPTIMAL_KHR: errorMessage = "VK_SUBOPTIMAL_KHR"; break;
        case VK_ERROR_OUT_OF_DATE_KHR: errorMessage = "VK_ERROR_OUT_OF_DATE_KHR"; break;
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: errorMessage = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"; break;
        case VK_ERROR_VALIDATION_FAILED_EXT: errorMessage = "VK_ERROR_VALIDATION_FAILED_EXT"; break;
        case VK_ERROR_INVALID_SHADER_NV: errorMessage = "VK_ERROR_INVALID_SHADER_NV"; break;
        case VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR: errorMessage = "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR"; break;
        case VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR: errorMessage = "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR"; break;
        case VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR: errorMessage = "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR"; break;
        case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR: errorMessage = "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR"; break;
        case VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR: errorMessage = "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR"; break;
        case VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR: errorMessage = "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR"; break;
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: errorMessage = "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT"; break;
        case VK_ERROR_NOT_PERMITTED_KHR: errorMessage = "VK_ERROR_NOT_PERMITTED_KHR"; break;
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: errorMessage = "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT"; break;
        case VK_THREAD_IDLE_KHR: errorMessage = "VK_THREAD_IDLE_KHR"; break;
        case VK_THREAD_DONE_KHR: errorMessage = "VK_THREAD_DONE_KHR"; break;
        case VK_OPERATION_DEFERRED_KHR: errorMessage = "VK_OPERATION_DEFERRED_KHR"; break;
        case VK_OPERATION_NOT_DEFERRED_KHR: errorMessage = "VK_OPERATION_NOT_DEFERRED_KHR"; break;
        case VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR: errorMessage = "VK_ERROR_INVALID_VIDEO_STD_PARAMETERS_KHR"; break;
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: errorMessage = "VK_ERROR_COMPRESSION_EXHAUSTED_EXT"; break;
        case VK_INCOMPATIBLE_SHADER_BINARY_EXT: errorMessage = "VK_INCOMPATIBLE_SHADER_BINARY_EXT"; break;
        default: errorMessage = "Unknown Error"; break;
    };

    printf("Renderer function failed with error: %s\n", errorMessage);
}