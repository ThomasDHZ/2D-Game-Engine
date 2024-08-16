#include "VulkanRenderer.h"
#include "VulkanError.h"
#include "Global.h"

static const char* DeviceExtensionList[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME,
										     VK_KHR_MAINTENANCE3_EXTENSION_NAME,
										     VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
										     VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
										     VK_KHR_SPIRV_1_4_EXTENSION_NAME,
										     VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
										     VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME};

static const char* ValidationLayers[] = { "VK_LAYER_KHRONOS_validation" };

static VkValidationFeatureEnableEXT enabledList[] = { VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT, 
													  VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT };

static VkValidationFeatureDisableEXT disabledList[] = { VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT,
														VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT,
														VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT,
														VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT };

static bool Array_LinearSearch(const char* array[], const char* target)
{
    int size = ARRAY_SIZE(array);
    for (int x = 0; x < size; x++)
    {
        if (array[x] == target)
        {
            return true;
        }
    }
    return false;
}

static void GetQueueFamilies(VkPhysicalDevice* physicalDevice, uint32_t* graphicsFamily, uint32_t* presentFamily)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);

    VkQueueFamilyProperties* queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);
    for (int x = 0; x <= queueFamilies; x++)
    {
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, x, global.Renderer.Surface, &presentSupport);

        if (queueFamilies->queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            *presentFamily = x;
            *graphicsFamily = x;
            break;
        }
    }

    free(queueFamilies);
}

static VkExtensionProperties* GetDeviceExtensions(VkPhysicalDevice* physicalDevice)
{
    uint32_t deviceExtensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &deviceExtensionCount, NULL);

    VkExtensionProperties* deviceExtensions = malloc(sizeof(VkExtensionProperties) * deviceExtensionCount);
    if (!deviceExtensions)
    {
        fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
        return;
    }

    vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &deviceExtensionCount, deviceExtensions);
    return deviceExtensions;
}

static VkSurfaceFormatKHR* GetSurfaceFormats(VkPhysicalDevice* physicalDevice)
{
    uint32_t surfaceFormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, global.Renderer.Surface, &surfaceFormatCount, NULL);
    if (surfaceFormatCount > 0)
    {
        VkSurfaceFormatKHR* surfaceFormat = malloc(sizeof(VkExtensionProperties) * surfaceFormatCount);
        if (!surfaceFormat)
        {
            fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
            return;
        }

        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, global.Renderer.Surface, &surfaceFormatCount, surfaceFormat);
        return surfaceFormat;
    }
}

static VkPresentModeKHR* GetPresentModes(VkPhysicalDevice* physicalDevice)
{
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, global.Renderer.Surface, &presentModeCount, NULL);
    if (presentModeCount > 0)
    {
        VkPresentModeKHR* presentMode = malloc(sizeof(VkPresentModeKHR) * presentModeCount);
        if (!presentMode)
        {
            fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
            return;
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, global.Renderer.Surface, &presentModeCount, presentMode);
        return presentMode;
    }
}

static bool GetRayTracingSupport()
{   
    VkExtensionProperties deviceExtenstion;
    GetDeviceExtensions(global.Renderer.PhysicalDevice, &deviceExtenstion);

    VkPhysicalDeviceAccelerationStructureFeaturesKHR physicalDeviceAccelerationStructureFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR
    };

    VkPhysicalDeviceRayTracingPipelineFeaturesKHR physicalDeviceRayTracingPipelineFeatures = 
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR,
        .pNext = &physicalDeviceAccelerationStructureFeatures
    };

    VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 = 
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .pNext = &physicalDeviceRayTracingPipelineFeatures
    };
    vkGetPhysicalDeviceFeatures2(global.Renderer.PhysicalDevice, &physicalDeviceFeatures2);

    if (physicalDeviceRayTracingPipelineFeatures.rayTracingPipeline == VK_TRUE &&
        physicalDeviceAccelerationStructureFeatures.accelerationStructure == VK_TRUE)
    {
        if (Array_LinearSearch(&deviceExtenstion, VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME) &&
            Array_LinearSearch(&deviceExtenstion, VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME))
        {
            uint32_t extensionCount;
            SDL_Vulkan_GetInstanceExtensions(global.Window.SDLWindow, &extensionCount, NULL);

            const char** extensions = malloc(sizeof(const char*) * (extensionCount + 3));
            SDL_Vulkan_GetInstanceExtensions(global.Window.SDLWindow, &extensionCount, extensions);
            if (!extensions) 
            {
                fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
                return false;
            }
            extensions[extensionCount++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
            extensions[extensionCount++] = VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME;
            extensions[extensionCount++] = VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME;
            free(extensions);

            return true;
        }
        else
        {
            fprintf(stderr, "GPU/Mother Board isn't ray tracing compatible.\n");
            return false;
        }
    }
    else
    {
        fprintf(stderr, "GPU/Mother Board isn't ray tracing compatible.\n");
        return false;
    }
}

static void GetVulkanFeatures(VkPhysicalDeviceVulkan11Features* physicalDeviceVulkan11Features)
{
    VkPhysicalDeviceBufferDeviceAddressFeatures physicalDeviceBufferDeviceAddressFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES,
        .bufferDeviceAddress = VK_TRUE
    };

    if (GetRayTracingSupport())
    {
        VkPhysicalDeviceRayTracingPipelineFeaturesKHR physicalDeviceRayTracingPipelineFeatures =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR,
            .rayTracingPipeline = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR
        };

        VkPhysicalDeviceRayTracingPipelinePropertiesKHR physicalDeviceRayTracingPipelineProperties =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_PROPERTIES_KHR,
            .pNext = &physicalDeviceRayTracingPipelineFeatures
        };

        VkPhysicalDeviceAccelerationStructureFeaturesKHR rayTracingDeviceProperties =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2,
            .pNext = &physicalDeviceRayTracingPipelineProperties
        };

        VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR,
            .accelerationStructure = VK_TRUE,
            .pNext = &rayTracingDeviceProperties
        };
        physicalDeviceBufferDeviceAddressFeatures.pNext = &accelerationStructureFeatures;
    }

    VkPhysicalDeviceDescriptorIndexingFeatures PhysicalDeviceDescriptorIndexingFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES,
        .runtimeDescriptorArray = VK_TRUE,
        .shaderSampledImageArrayNonUniformIndexing = VK_TRUE,
        .runtimeDescriptorArray = VK_TRUE,
        .descriptorBindingVariableDescriptorCount = VK_TRUE,
        .pNext = &physicalDeviceBufferDeviceAddressFeatures,
    };

    VkPhysicalDeviceRobustness2FeaturesEXT  physicalDeviceRobustness2Features =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT,
        .nullDescriptor = VK_TRUE,
        .pNext = &PhysicalDeviceDescriptorIndexingFeatures
    };

    VkPhysicalDeviceVulkan13Features physicalDeviceVulkan13Features =
    {
        .shaderDemoteToHelperInvocation = VK_TRUE,
        .pNext = &physicalDeviceRobustness2Features
    };

    VkPhysicalDeviceFeatures physicalDeviceFeatures =
    {
        .samplerAnisotropy = VK_TRUE,
        .fillModeNonSolid = VK_TRUE,
        .wideLines = VK_TRUE,
        .fragmentStoresAndAtomics = VK_TRUE,
        .vertexPipelineStoresAndAtomics = VK_TRUE,
        .sampleRateShading = VK_TRUE
    };

    VkPhysicalDeviceFeatures2 physicalDeviceFeatures2 =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .features = physicalDeviceFeatures,
        .pNext = &physicalDeviceVulkan13Features
    };

    physicalDeviceVulkan11Features->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    physicalDeviceVulkan11Features->multiview = VK_TRUE;
    physicalDeviceVulkan11Features->pNext = &physicalDeviceFeatures2;
}

void Vulkan_RendererSetUp()
{
    uint32_t extensionCount;
    SDL_Vulkan_GetInstanceExtensions(global.Window.SDLWindow, &extensionCount, NULL);
    const char** extensions = malloc(sizeof(const char*) * (extensionCount + 1));
    if (!extensions)
    {
        fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
        return;
    }

    SDL_Vulkan_GetInstanceExtensions(global.Window.SDLWindow, &extensionCount, extensions);
    extensions[extensionCount++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;

    VkDebugUtilsMessengerCreateInfoEXT debugInfo = { 0 };

    VkApplicationInfo applicationInfo =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "Vulkan Application",
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "No Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_3
    };

    VkInstanceCreateInfo vulkanCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
        .enabledExtensionCount = extensionCount,
        .ppEnabledExtensionNames = extensions
    };
#ifdef NDEBUG
    vulkanCreateInfo.enabledLayerCount = 0;
#else
    vulkanCreateInfo.enabledLayerCount = ARRAY_SIZE(ValidationLayers);
    vulkanCreateInfo.ppEnabledLayerNames = ValidationLayers;
    vulkanCreateInfo.pNext = &debugInfo;
#endif

    VkResult instanceResult = vkCreateInstance(&vulkanCreateInfo, NULL, &global.Renderer.Instance);
    if (instanceResult != VK_SUCCESS) 
    {
        Vulkan_GetError(instanceResult);
        free(extensions);
        return; 
    }

    Vulkan_SetUpDebugger(&debugInfo);

    if (!SDL_Vulkan_CreateSurface(global.Window.SDLWindow, global.Renderer.Instance, &global.Renderer.Surface)) 
    {
        fprintf(stderr, "Failed to create Vulkan surface: %s\n", SDL_GetError());
        Vulkan_DestroyRenderer();
        free(extensions);
        return;
    }

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(global.Renderer.Instance, &deviceCount, NULL);
    if (deviceCount == 0)
    {
        fprintf(stderr, "Failed to find GPUs with Vulkan support: %s\n", SDL_GetError());
        Vulkan_DestroyRenderer();
        free(extensions);
        return;
    }

    VkPhysicalDevice* physicalDeviceList = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    VkResult physicalDeviceResult = vkEnumeratePhysicalDevices(global.Renderer.Instance, &deviceCount, physicalDeviceList);
    if (physicalDeviceResult != VK_SUCCESS)
    {
        Vulkan_GetError(physicalDeviceResult);
        Vulkan_DestroyRenderer();
        free(extensions);
        return;
    }

    uint32_t graphicsFamily = UINT32_MAX;
    uint32_t presentFamily = UINT32_MAX;
    VkPresentModeKHR* presentMode = NULL;
    for (int x = 0; x < deviceCount; x++)
    {
        vkGetPhysicalDeviceFeatures(physicalDeviceList[x], &global.Renderer.PhysicalDeviceFeatures);
        GetQueueFamilies(physicalDeviceList[x], &graphicsFamily, &presentFamily);
        VkExtensionProperties* deviceExtensions = GetDeviceExtensions(physicalDeviceList[x]);
        VkSurfaceFormatKHR* surfaceFormat = GetSurfaceFormats(physicalDeviceList[x]);
        VkPresentModeKHR* presentMode = GetPresentModes(physicalDeviceList[x]);
        if (graphicsFamily != -1 &&
            presentFamily != -1 &&
            ARRAY_SIZE(surfaceFormat) > 0 &&
            ARRAY_SIZE(presentMode) != 0 &&
            global.Renderer.PhysicalDeviceFeatures.samplerAnisotropy)
        {
            global.Renderer.PhysicalDevice = physicalDeviceList[x];
            free(surfaceFormat);
            free(deviceExtensions);
            free(presentMode);
            break;
        }
        else
        {
            free(surfaceFormat);
            free(deviceExtensions);
            free(presentMode);
        }
    }
    if (global.Renderer.PhysicalDevice == VK_NULL_HANDLE)
    {
        Vulkan_GetError(physicalDeviceResult);
        Vulkan_DestroyRenderer();
        free(extensions);
        return;
    }

    float queuePriority = 1.0f;
    uint32_t uniqueQueueFamilies[] = { graphicsFamily, presentFamily };
    VkDeviceQueueCreateInfo deviceQueueCreateInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = uniqueQueueFamilies[0],
        .queueCount = 1,
        .pQueuePriorities = &queuePriority
    };

    VkPhysicalDeviceVulkan11Features physicalDeviceVulkan11Features;
    GetVulkanFeatures(&physicalDeviceVulkan11Features);

    VkDeviceCreateInfo deviceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &deviceQueueCreateInfo,
        .pEnabledFeatures = NULL,
        .enabledExtensionCount = ARRAY_SIZE(DeviceExtensionList),
        .ppEnabledExtensionNames = DeviceExtensionList,
        .pNext = &physicalDeviceVulkan11Features
    };
#ifdef NDEBUG
    deviceCreateInfo.enabledLayerCount = 0;
#else
    deviceCreateInfo.enabledLayerCount = ARRAY_SIZE(ValidationLayers);
    deviceCreateInfo.pEnabledFeatures = ValidationLayers;
#endif

    VkResult deviceResult = vkCreateDevice(global.Renderer.PhysicalDevice, &deviceCreateInfo, NULL, &global.Renderer.Device);
    {
        Vulkan_GetError(deviceResult);
        Vulkan_DestroyRenderer();
        free(extensions);
        return;
    }

    free(extensions);
}

void Vulkan_DestroyRenderer()
{
    //SwapChain.Destroy(global.Renderer.Device);

    Vulkan_DestroyCommandPool();
    for (size_t x = 0; x < MAX_FRAMES_IN_FLIGHT; x++)
    {
        //vkDestroySemaphore(global.Renderer.Device, AcquireImageSemaphores[x], NULL);
        //vkDestroySemaphore(global.Renderer.Device, PresentImageSemaphores[x], NULL);
        //vkDestroyFence(global.Renderer.Device, InFlightFences[x], NULL);

        //AcquireImageSemaphores[x] = VK_NULL_HANDLE;
        //PresentImageSemaphores[x] = VK_NULL_HANDLE;
        //InFlightFences[x] = VK_NULL_HANDLE;
    }
    Vulkan_DestroyDevice();
    Vulkan_DestroyDebugger();
    Vulkan_DestroySurface();
    Vulkan_DestroyInstance();
}

void Vulkan_DestroyCommandPool()
{
    if (global.Renderer.CommandPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(global.Renderer.Device, global.Renderer.CommandPool, NULL);
        global.Renderer.CommandPool = VK_NULL_HANDLE;
    }
}

void Vulkan_DestroyDevice()
{
    if (global.Renderer.Device != VK_NULL_HANDLE)
    {
        vkDestroyDevice(global.Renderer.Device, NULL);
        global.Renderer.Device = VK_NULL_HANDLE;
    }
}

void Vulkan_DestroySurface()
{
    if (global.Renderer.Surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(global.Renderer.Instance, global.Renderer.Surface, NULL);
        global.Renderer.Surface = VK_NULL_HANDLE;
    }
}

void Vulkan_DestroyInstance()
{
    if (global.Renderer.Instance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(global.Renderer.Instance, NULL);
        global.Renderer.Instance = VK_NULL_HANDLE;
    }
}