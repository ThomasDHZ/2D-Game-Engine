#include "VulkanRenderer.h"
#include "VulkanError.h"
#include "Global.h"

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

    uint32_t extensionCount;
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, NULL)) 
    {
        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    const char** extensions = malloc(sizeof(const char*) * extensionCount++);
    if (!extensions) 
    {
        fprintf(stderr, "Failed to allocate memory for Vulkan extensions.\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions)) 
    {
        fprintf(stderr, "Failed to get Vulkan instance extensions: %s\n", SDL_GetError());
        free(extensions);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    extensions[extensionCount] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
    extensionCount++;

    for (unsigned int i = 0; i < extensionCount; i++) 
    {
        printf("%u: %s\n", i, extensions[i]);
    }

    VkApplicationInfo applicationInfo = { .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                          .pApplicationName = "Vulkan Application",
                                          .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
                                          .pEngineName = "No Engine",
                                          .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                          .apiVersion = VK_API_VERSION_1_3 };

    VkInstanceCreateInfo vulkanCreateInfo = {  .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                                               .pApplicationInfo = &applicationInfo,
                                               .enabledExtensionCount = extensionCount,
                                               .ppEnabledExtensionNames = extensions };
#ifdef NDEBUG
    vulkanCreateInfo.enabledLayerCount = 0;
#else
    vulkanCreateInfo.enabledLayerCount = ARRAY_SIZE(ValidationLayers);
    vulkanCreateInfo.ppEnabledLayerNames = ValidationLayers;
#endif

    VkDebugUtilsMessengerCreateInfoEXT DebugInfo = { 0 };
    Vulkan_SetUpDebugger(&DebugInfo);

    VkValidationFeaturesEXT ValidationFeatures = 
    {  
        .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
        .disabledValidationFeatureCount = ARRAY_SIZE(enabledList),
        .enabledValidationFeatureCount = ARRAY_SIZE(disabledList),
        .pEnabledValidationFeatures = enabledList,
        .pDisabledValidationFeatures = disabledList,
        .pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&DebugInfo
    };

    VkResult result = vkCreateInstance(&vulkanCreateInfo, NULL, &global.Renderer.Instance);
    if (result != VK_SUCCESS) 
    {
        Vulkan_GetError(result);
        free(extensions);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    VkSurfaceKHR surface;
    if (!SDL_Vulkan_CreateSurface(window, global.Renderer.Instance, &surface))
    {
        fprintf(stderr, "Failed to create Vulkan surface: %s\n", SDL_GetError());
        vkDestroyInstance(global.Renderer.Instance, NULL);
        free(extensions);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    free(extensions);
}

void Vulkan_DestroyRenderer()
{
    //SwapChain.Destroy(global.Renderer.Device);

    vkDestroyCommandPool(global.Renderer.Device, global.Renderer.CommandPool, NULL);
    global.Renderer.CommandPool = VK_NULL_HANDLE;

    for (size_t x = 0; x < MAX_FRAMES_IN_FLIGHT; x++)
    {
        //vkDestroySemaphore(global.Renderer.Device, AcquireImageSemaphores[x], NULL);
        //vkDestroySemaphore(global.Renderer.Device, PresentImageSemaphores[x], NULL);
        //vkDestroyFence(global.Renderer.Device, InFlightFences[x], NULL);

        //AcquireImageSemaphores[x] = VK_NULL_HANDLE;
        //PresentImageSemaphores[x] = VK_NULL_HANDLE;
        //InFlightFences[x] = VK_NULL_HANDLE;
    }

    vkDestroyDevice(global.Renderer.Device, NULL);
    global.Renderer.Device = VK_NULL_HANDLE;

    Vulkan_DestroyDebugger();

    vkDestroySurfaceKHR(global.Renderer.Instance, global.Renderer.Surface, NULL);
    vkDestroyInstance(global.Renderer.Instance, NULL);
}
