#include "VulkanRenderer.h"
#include "VulkanError.h"
#include "Global.h"

 const char** ExtensionList[3] = {0 };

static const char* DeviceExtensionList[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME,
										     VK_KHR_MAINTENANCE3_EXTENSION_NAME,
										     VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
										     VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
										     VK_KHR_SPIRV_1_4_EXTENSION_NAME,
										     VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
										     VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME,
                                             NULL};

static const char* ValidationLayers[] = { "VK_LAYER_KHRONOS_validation" };

static VkValidationFeatureEnableEXT enabledList[] = { VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT, 
													  VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT };

static VkValidationFeatureDisableEXT disabledList[] = { VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT,
														VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT,
														VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT,
														VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT };

void Vulkan_RendererSetUp()
{
    SDL_Window* window = global.Window.SDLWindow;

    uint32_t* pCount = 0;
    const char** pNames = NULL;
    SDL_bool _InstanceExtensions = SDL_Vulkan_GetInstanceExtensions(window, pCount, pNames);

    uint32_t extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(NULL, &extensionCount, NULL))
    {
        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
        return 1;
    }

    const char** extensionNames = malloc(sizeof(const char*) * extensionCount);
    if (!SDL_Vulkan_GetInstanceExtensions(NULL, &extensionCount, extensionNames))
    {
        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
        free(extensionNames);
        return 1;
    }

    VkApplicationInfo appInfo = { 0 };
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Application";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo VulkanCreateInfo = { 0 };
    VulkanCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VulkanCreateInfo.pApplicationInfo = &appInfo;
    VulkanCreateInfo.enabledExtensionCount = pCount;
    VulkanCreateInfo.ppEnabledExtensionNames = pNames;
    VulkanCreateInfo.enabledLayerCount = 0;
    VulkanCreateInfo.pNext = NULL;

    {
        VkResult result = vkCreateInstance(&VulkanCreateInfo, NULL, &global.Renderer.Instance);
        if (result != VK_SUCCESS)
        {
            Vulkan_GetError(result);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
    }

    if (!SDL_Vulkan_CreateSurface(window, global.Renderer.Instance, global.Renderer.Surface)) 
    {
        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
}
