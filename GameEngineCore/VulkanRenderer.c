#include "VulkanRenderer.h"
#include "Global.h"
#include "VulkanSwapChain.h"
#include "vulkanwindow.h"
#include "SDLWindow.h"

static const char* DeviceExtensionList[] = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    VK_KHR_MAINTENANCE3_EXTENSION_NAME,
    VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
    VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME,
    VK_KHR_SPIRV_1_4_EXTENSION_NAME,
    VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME,
    VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME,
    VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME,
    VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME,
    VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME,
    VK_EXT_ROBUSTNESS_2_EXTENSION_NAME
};

static const char* ValidationLayers[] = { "VK_LAYER_KHRONOS_validation" };

static VkValidationFeatureEnableEXT enabledList[] = { VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
                                                      VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT };

static VkValidationFeatureDisableEXT disabledList[] = { VK_VALIDATION_FEATURE_DISABLE_THREAD_SAFETY_EXT,
                                                        VK_VALIDATION_FEATURE_DISABLE_API_PARAMETERS_EXT,
                                                        VK_VALIDATION_FEATURE_DISABLE_OBJECT_LIFETIMES_EXT,
                                                        VK_VALIDATION_FEATURE_DISABLE_CORE_CHECKS_EXT };

//PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR;
//PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR;
//PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR;
//PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR;
//PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR;
//PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR;
//PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR;
//PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR;
//PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR;
//PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR;

static bool Array_RendererExtensionPropertiesSearch(VkExtensionProperties* array, uint32 arrayCount, const char* target)
{
    for (uint32 x = 0; x < arrayCount; x++)
    {
        if (strcmp(array[x].extensionName, target) == 0)
        {
            return true;
        }
    }
    return false;
}

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

static void DestroyDebugUtilsMessengerEXT(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != NULL)
    {
        func(instance, global.Renderer.DebugMessenger, pAllocator);
    }
    else
    {
        fprintf(stderr, "Failed to load vkDestroyDebugUtilsMessengerEXT function\n");
    }
}

VKAPI_ATTR VkBool32 VKAPI_CALL Vulkan_DebugCallBack(VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, VkDebugUtilsMessageTypeFlagsEXT MessageType, const VkDebugUtilsMessengerCallbackDataEXT* CallBackData, void* UserData)
{
    fprintf(stderr, "Validation Layer: %s\n", CallBackData->pMessage);
    return VK_FALSE;
}

static VkExtensionProperties* GetDeviceExtensions(VkPhysicalDevice physicalDevice, uint32* deviceExtensionCountPtr)
{
    uint32 deviceExtensionCount = 0;
    VULKAN_RESULT(vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &deviceExtensionCount, NULL));

    VkExtensionProperties* deviceExtensions = malloc(sizeof(VkExtensionProperties) * deviceExtensionCount);
    if (!deviceExtensions)
    {
        fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
        *deviceExtensionCountPtr = 0;
        return NULL;
    }

    VULKAN_RESULT(vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &deviceExtensionCount, deviceExtensions));
    *deviceExtensionCountPtr = deviceExtensionCount;
    return deviceExtensions;
}

static void GetSurfaceFormats(VkPhysicalDevice physicalDevice, VkSurfaceFormatKHR* surfaceFormat, uint32* surfaceFormatCount)
{
    VULKAN_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, global.Renderer.Surface, surfaceFormatCount, NULL));
    if (surfaceFormatCount > 0)
    {
        VkSurfaceFormatKHR* surfaceFormats = malloc(sizeof(VkSurfaceFormatKHR) * *surfaceFormatCount);
        if (!surfaceFormats)
        {
            fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
        }

        VULKAN_RESULT(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, global.Renderer.Surface, surfaceFormatCount, surfaceFormats));
    }
}

static void GetPresentModes(VkPhysicalDevice physicalDevice, VkPresentModeKHR* presentMode, int32* presentModeCount)
{
    VULKAN_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, global.Renderer.Surface, presentModeCount, NULL));
    if (presentModeCount > 0)
    {
        VkPresentModeKHR* presentModes = malloc(sizeof(VkPresentModeKHR) * *presentModeCount);
        if (!presentModes)
        {
            fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
        }

        VULKAN_RESULT(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, global.Renderer.Surface, presentModeCount, presentModes));
    }
}

static bool GetRayTracingSupport()
{
    uint32 deviceExtensionCount = INT32_MAX;
    VkExtensionProperties* deviceExtensions = GetDeviceExtensions(global.Renderer.PhysicalDevice, &deviceExtensionCount);
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
        if (Array_RendererExtensionPropertiesSearch(deviceExtensions, deviceExtensionCount, VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME) &&
            Array_RendererExtensionPropertiesSearch(deviceExtensions, deviceExtensionCount, VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME))
        {
            uint32 pExtensionCount = 0;
            VkExtensionProperties* extensions = NULL;
            Window_SDL_GetInstanceExtensions(&pExtensionCount, &extensions);
            return true;
        }
        else
        {
            fprintf(stderr, "GPU/Mother Board isn't ray tracing compatible.\n");
            free(deviceExtensions);
            return false;
        }
    }
    else
    {
        fprintf(stderr, "GPU/Mother Board isn't ray tracing compatible.\n");
        free(deviceExtensions);
        return false;
    }
}

static void GetRendererFeatures(VkPhysicalDeviceVulkan11Features* physicalDeviceVulkan11Features)
{
    VkPhysicalDeviceBufferDeviceAddressFeatures bufferDeviceAddressFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES,
        .bufferDeviceAddress = VK_TRUE,
    };

    VkPhysicalDeviceDescriptorIndexingFeatures physicalDeviceDescriptorIndexingFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES,
        .runtimeDescriptorArray = VK_TRUE,
        .shaderSampledImageArrayNonUniformIndexing = VK_TRUE,
        .descriptorBindingVariableDescriptorCount = VK_TRUE,
    };

    VkPhysicalDeviceRobustness2FeaturesEXT PhysicalDeviceRobustness2Features =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT,
        .nullDescriptor = VK_TRUE,
        .pNext = &physicalDeviceDescriptorIndexingFeatures,
    };

    if (GetRayTracingSupport())
    {
        VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR,
            .accelerationStructure = VK_TRUE,
        };

        VkPhysicalDeviceRayTracingPipelineFeaturesKHR rayTracingPipelineFeatures =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR,
            .rayTracingPipeline = VK_TRUE,
            .pNext = &accelerationStructureFeatures,
        };

        bufferDeviceAddressFeatures.pNext = &rayTracingPipelineFeatures;
    }
    PhysicalDeviceRobustness2Features.pNext = &bufferDeviceAddressFeatures;

    VkPhysicalDeviceFeatures deviceFeatures =
    {
        .samplerAnisotropy = VK_TRUE,
        .fillModeNonSolid = VK_TRUE,
    };

    VkPhysicalDeviceFeatures2 deviceFeatures2 =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .features = deviceFeatures,
        .pNext = &PhysicalDeviceRobustness2Features,
    };

        physicalDeviceVulkan11Features->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
        physicalDeviceVulkan11Features->multiview = VK_TRUE;
        physicalDeviceVulkan11Features->pNext = &deviceFeatures2;

}

bool Iswindoww() 
{
    if (!global.Window.window)
    {
        return false;
    }

    SDL_SysWMinfo info;
    SDL_VERSION(&info.version);
    SDL_GetWindowWMInfo(global.Window.window, &info);
    HWND hwnd = info.info.win.window;
    return IsWindow(hwnd) == TRUE;
}

VkInstance Renderer_CreateVulkanInstance(VkInstanceCreateInfo instanceInfo)
{
    VkInstance Instance = VK_NULL_HANDLE;
    vkCreateInstance(&instanceInfo, NULL, &Instance);
    return Instance;
}

void Renderer_Windows_Renderer(uint32* pExtensionCount, VkExtensionProperties** extensionProperties)
{
    vkEnumerateInstanceExtensionProperties(NULL, &pExtensionCount, NULL);
    VkExtensionProperties* instanceExtensions = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties) * (*pExtensionCount));
    vkEnumerateInstanceExtensionProperties(NULL, &pExtensionCount, instanceExtensions);
    (*pExtensionCount)++;
    *extensionProperties = (VkExtensionProperties*)extensionProperties;
}

VkResult Renderer_RendererSetUp()
{
    global.Renderer.RebuildRendererFlag = false;
    uint32 pExtensionCount = 0;
    VkExtensionProperties* extensions = NULL;


    if (Iswindoww())
    {
        Window_SDL_GetInstanceExtensions(&pExtensionCount, &extensions);
        printf("This is an SDL window.\n");
    }
    else 
    {
        Renderer_Windows_Renderer(&pExtensionCount, &extensions);
        printf("This is NOT an SDL window.\n");
    }

    VkDebugUtilsMessengerCreateInfoEXT debugInfo =
    {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = Vulkan_DebugCallBack
    };

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
        .enabledExtensionCount = pExtensionCount,
        .ppEnabledExtensionNames = extensions
    };
#ifdef NDEBUG
    vulkanCreateInfo.enabledLayerCount = 0;
#else
    vulkanCreateInfo.enabledLayerCount = ARRAY_SIZE(ValidationLayers);
    vulkanCreateInfo.ppEnabledLayerNames = ValidationLayers;
    vulkanCreateInfo.pNext = &debugInfo;
#endif

    VULKAN_RESULT(vkCreateInstance(&vulkanCreateInfo, NULL, &global.Renderer.Instance));

#ifdef NDEBUG
#else
    VULKAN_RESULT(CreateDebugUtilsMessengerEXT(global.Renderer.Instance, &debugInfo, NULL, &global.Renderer.DebugMessenger));
#endif

    Window_SDL_CreateSurface(&global.Renderer.Instance, &global.Renderer.Surface);

    uint32 deviceCount = UINT32_MAX;
    VULKAN_RESULT(vkEnumeratePhysicalDevices(global.Renderer.Instance, &deviceCount, NULL));

    VkPhysicalDevice* physicalDeviceList = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    VULKAN_RESULT(vkEnumeratePhysicalDevices(global.Renderer.Instance, &deviceCount, physicalDeviceList));

    VkPresentModeKHR* presentMode = NULL;
    for (uint32 x = 0; x < deviceCount; x++)
    {
        vkGetPhysicalDeviceFeatures(physicalDeviceList[x], &global.Renderer.PhysicalDeviceFeatures);
        SwapChain_GetQueueFamilies(physicalDeviceList[x], &global.Renderer.SwapChain.GraphicsFamily, &global.Renderer.SwapChain.PresentFamily);
      
        VkSurfaceFormatKHR surfaceFormat;
        VkPresentModeKHR presentMode;
        uint32 surfaceFormatCount = 0;
        uint32 presentModeCount = 0;
        GetSurfaceFormats(physicalDeviceList[x], &surfaceFormat, &surfaceFormatCount);
        GetPresentModes(physicalDeviceList[x], &presentMode, &presentModeCount);

        if (global.Renderer.SwapChain.GraphicsFamily != -1 &&
            global.Renderer.SwapChain.PresentFamily != -1 &&
            surfaceFormatCount > 0 &&
            presentModeCount != 0 &&
            global.Renderer.PhysicalDeviceFeatures.samplerAnisotropy)
        {
            global.Renderer.PhysicalDevice = physicalDeviceList[x];
            break;
        }
        else
        {
            Renderer_DestroyRenderer();
            SDL_Quit();
        }
    }

    //VkPhysicalDeviceProperties deviceProperties;
    //vkGetPhysicalDeviceProperties(physicalDeviceList[0], &deviceProperties);

    //VkPhysicalDeviceVulkan11Features physicalDeviceVulkan11Features;
    //GetRendererFeatures(&physicalDeviceVulkan11Features);

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo[2];
    uint32 queueCreateInfoCount = 0;
    if (global.Renderer.SwapChain.GraphicsFamily != UINT32_MAX)
    {
        queueCreateInfo[queueCreateInfoCount++] = (VkDeviceQueueCreateInfo){
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = global.Renderer.SwapChain.GraphicsFamily,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority
        };
    }

    if (global.Renderer.SwapChain.PresentFamily != UINT32_MAX &&
        global.Renderer.SwapChain.PresentFamily != global.Renderer.SwapChain.GraphicsFamily)
    {
        queueCreateInfo[queueCreateInfoCount++] = (VkDeviceQueueCreateInfo)
        {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = global.Renderer.SwapChain.PresentFamily,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority
        };
    }

    VkPhysicalDeviceBufferDeviceAddressFeatures bufferDeviceAddressFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES,
        .bufferDeviceAddress = VK_TRUE,
    };

    VkPhysicalDeviceDescriptorIndexingFeatures physicalDeviceDescriptorIndexingFeatures =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_INDEXING_FEATURES,
        .runtimeDescriptorArray = VK_TRUE,
        .shaderSampledImageArrayNonUniformIndexing = VK_TRUE,
        .descriptorBindingVariableDescriptorCount = VK_TRUE,
    };

    VkPhysicalDeviceRobustness2FeaturesEXT PhysicalDeviceRobustness2Features =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ROBUSTNESS_2_FEATURES_EXT,
        .nullDescriptor = VK_TRUE,
        .pNext = &physicalDeviceDescriptorIndexingFeatures,
    };

    if (GetRayTracingSupport())
    {
        VkPhysicalDeviceAccelerationStructureFeaturesKHR accelerationStructureFeatures =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR,
            .accelerationStructure = VK_TRUE,
        };

        VkPhysicalDeviceRayTracingPipelineFeaturesKHR rayTracingPipelineFeatures =
        {
            .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR,
            .rayTracingPipeline = VK_TRUE,
            .pNext = &accelerationStructureFeatures,
        };

        bufferDeviceAddressFeatures.pNext = &rayTracingPipelineFeatures;
    }
    PhysicalDeviceRobustness2Features.pNext = &bufferDeviceAddressFeatures;

    VkPhysicalDeviceFeatures deviceFeatures =
    {
        .samplerAnisotropy = VK_TRUE,
        .fillModeNonSolid = VK_TRUE,
    };

    VkPhysicalDeviceFeatures2 deviceFeatures2 =
    {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
        .features = deviceFeatures,
        .pNext = &PhysicalDeviceRobustness2Features,
    };

    VkPhysicalDeviceVulkan11Features physicalDeviceVulkan11Features = { 0 };
    physicalDeviceVulkan11Features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES;
    physicalDeviceVulkan11Features.multiview = VK_TRUE;
    physicalDeviceVulkan11Features.pNext = &deviceFeatures2;

    VkDeviceCreateInfo deviceCreateInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = queueCreateInfoCount,
        .pQueueCreateInfos = queueCreateInfo,
        .pEnabledFeatures = NULL,
        .enabledExtensionCount = ARRAY_SIZE(DeviceExtensionList),
        .ppEnabledExtensionNames = DeviceExtensionList,
        .pNext = &physicalDeviceVulkan11Features
    };

#ifdef NDEBUG
    deviceCreateInfo.enabledLayerCount = 0;
#else
    deviceCreateInfo.enabledLayerCount = ARRAY_SIZE(ValidationLayers);
    deviceCreateInfo.ppEnabledLayerNames = ValidationLayers;
#endif

    VULKAN_RESULT(vkCreateDevice(global.Renderer.PhysicalDevice, &deviceCreateInfo, NULL, &global.Renderer.Device));
    Vulkan_SetUpSwapChain();

    VkCommandPoolCreateInfo CommandPoolCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = global.Renderer.SwapChain.GraphicsFamily
    };

    VULKAN_RESULT(vkCreateCommandPool(global.Renderer.Device, &CommandPoolCreateInfo, NULL, &global.Renderer.CommandPool));

    global.Renderer.InFlightFences = malloc(sizeof(VkFence) * MAX_FRAMES_IN_FLIGHT);
    VkSemaphoreTypeCreateInfo semaphoreTypeCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO,
        .semaphoreType = VK_SEMAPHORE_TYPE_BINARY,
        .initialValue = 0,
        .pNext = NULL
    };

    global.Renderer.AcquireImageSemaphores = malloc(sizeof(VkSemaphore) * MAX_FRAMES_IN_FLIGHT);
    VkSemaphoreCreateInfo semaphoreCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
        .pNext = &semaphoreTypeCreateInfo
    };

    global.Renderer.PresentImageSemaphores = malloc(sizeof(VkSemaphore) * MAX_FRAMES_IN_FLIGHT);
    VkFenceCreateInfo fenceInfo =
    {
        .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
        .flags = VK_FENCE_CREATE_SIGNALED_BIT
    };

    if (global.Renderer.InFlightFences &&
        global.Renderer.AcquireImageSemaphores &&
        global.Renderer.PresentImageSemaphores)
    {
        for (size_t x = 0; x < MAX_FRAMES_IN_FLIGHT; x++)
        {
            VULKAN_RESULT(vkCreateSemaphore(global.Renderer.Device, &semaphoreCreateInfo, NULL, &global.Renderer.AcquireImageSemaphores[x]));
            VULKAN_RESULT(vkCreateSemaphore(global.Renderer.Device, &semaphoreCreateInfo, NULL, &global.Renderer.PresentImageSemaphores[x]));
            VULKAN_RESULT(vkCreateFence(global.Renderer.Device, &fenceInfo, NULL, &global.Renderer.InFlightFences[x]));
        }
    }
    else
    {
        Renderer_DestroyRenderer();
        SDL_Quit();
    }

    vkGetDeviceQueue(global.Renderer.Device, global.Renderer.SwapChain.GraphicsFamily, 0, &global.Renderer.SwapChain.GraphicsQueue);
    vkGetDeviceQueue(global.Renderer.Device, global.Renderer.SwapChain.PresentFamily, 0, &global.Renderer.SwapChain.PresentQueue);
    free(extensions);

    //PFN_vkGetBufferDeviceAddressKHR vkGetBufferDeviceAddressKHR = (PFN_vkGetBufferDeviceAddressKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkGetBufferDeviceAddressKHR"));
    //PFN_vkCreateAccelerationStructureKHR vkCreateAccelerationStructureKHR = (PFN_vkCreateAccelerationStructureKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkCreateAccelerationStructureKHR"));
    //PFN_vkDestroyAccelerationStructureKHR vkDestroyAccelerationStructureKHR = (PFN_vkDestroyAccelerationStructureKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkDestroyAccelerationStructureKHR"));
    //PFN_vkGetAccelerationStructureBuildSizesKHR vkGetAccelerationStructureBuildSizesKHR = (PFN_vkGetAccelerationStructureBuildSizesKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkGetAccelerationStructureBuildSizesKHR"));
    //PFN_vkGetAccelerationStructureDeviceAddressKHR vkGetAccelerationStructureDeviceAddressKHR = (PFN_vkGetAccelerationStructureDeviceAddressKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkGetAccelerationStructureDeviceAddressKHR"));
    //PFN_vkCmdBuildAccelerationStructuresKHR vkCmdBuildAccelerationStructuresKHR = (PFN_vkCmdBuildAccelerationStructuresKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkCmdBuildAccelerationStructuresKHR"));
    //PFN_vkBuildAccelerationStructuresKHR vkBuildAccelerationStructuresKHR = (PFN_vkBuildAccelerationStructuresKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkBuildAccelerationStructuresKHR"));
    //PFN_vkCmdTraceRaysKHR vkCmdTraceRaysKHR = (PFN_vkCmdTraceRaysKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkCmdTraceRaysKHR"));
    //PFN_vkGetRayTracingShaderGroupHandlesKHR vkGetRayTracingShaderGroupHandlesKHR = (PFN_vkGetRayTracingShaderGroupHandlesKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkGetRayTracingShaderGroupHandlesKHR"));
    //PFN_vkCreateRayTracingPipelinesKHR vkCreateRayTracingPipelinesKHR = (PFN_vkCreateRayTracingPipelinesKHR)(vkGetDeviceProcAddr(global.Renderer.Device, "vkCreateRayTracingPipelinesKHR"));

    return VK_SUCCESS;
}

VkResult Renderer_CreateCommandBuffers(VkCommandBuffer* commandBufferList)
{
    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        VkCommandBufferAllocateInfo commandBufferAllocateInfo =
        {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .commandPool = global.Renderer.CommandPool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount = 1
        };

        VULKAN_RESULT(vkAllocateCommandBuffers(global.Renderer.Device, &commandBufferAllocateInfo, &commandBufferList[x]));
    }
    return VK_SUCCESS;
}

VkResult Renderer_CreateFrameBuffer(VkFramebuffer* pFrameBuffer, VkFramebufferCreateInfo* frameBufferCreateInfo)
{
    return vkCreateFramebuffer(global.Renderer.Device, *&frameBufferCreateInfo, NULL, pFrameBuffer);
}

VkResult Renderer_CreateRenderPass(Renderer_RenderPassCreateInfoStruct* renderPassCreateInfo)
{
    VkRenderPassCreateInfo renderPassInfo =
    {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = renderPassCreateInfo->AttachmentCount,
        .pAttachments = renderPassCreateInfo->pAttachmentList,
        .subpassCount = renderPassCreateInfo->SubpassCount,
        .pSubpasses = renderPassCreateInfo->pSubpassDescriptionList,
        .dependencyCount = renderPassCreateInfo->DependencyCount,
        .pDependencies = renderPassCreateInfo->pSubpassDependencyList
    };
   return vkCreateRenderPass(global.Renderer.Device, &renderPassInfo, NULL, renderPassCreateInfo->pRenderPass);
}

VkResult Renderer_CreateDescriptorPool(VkDescriptorPool* descriptorPool, VkDescriptorPoolCreateInfo* descriptorPoolCreateInfo)
{
    return vkCreateDescriptorPool(global.Renderer.Device, descriptorPoolCreateInfo, NULL, descriptorPool);
}

VkResult Renderer_CreateDescriptorSetLayout(VkDescriptorSetLayout* descriptorSetLayout, VkDescriptorSetLayoutCreateInfo* descriptorSetLayoutCreateInfo)
{
    return vkCreateDescriptorSetLayout(global.Renderer.Device, descriptorSetLayoutCreateInfo, NULL, descriptorSetLayout);
}

VkResult Renderer_CreatePipelineLayout(VkPipelineLayout* pipelineLayout, VkPipelineLayoutCreateInfo* pipelineLayoutCreateInfo)
{
    return vkCreatePipelineLayout(global.Renderer.Device, pipelineLayoutCreateInfo, NULL, pipelineLayout);
}

VkResult Renderer_AllocateDescriptorSets(VkDescriptorSet* descriptorSet, VkDescriptorSetAllocateInfo* descriptorSetAllocateInfo)
{
    return vkAllocateDescriptorSets(global.Renderer.Device, descriptorSetAllocateInfo, descriptorSet);
}

VkResult Renderer_AllocateCommandBuffers(VkCommandBuffer* commandBuffer, VkCommandBufferAllocateInfo* ImGuiCommandBuffers)
{
    return vkAllocateCommandBuffers(global.Renderer.Device, ImGuiCommandBuffers, commandBuffer);
}

VkResult Renderer_CreateGraphicsPipelines(VkPipeline* graphicPipeline, VkGraphicsPipelineCreateInfo* createGraphicPipelines, uint32 createGraphicPipelinesCount)
{
    return vkCreateGraphicsPipelines(global.Renderer.Device, VK_NULL_HANDLE, createGraphicPipelinesCount, createGraphicPipelines, NULL, graphicPipeline);
}

VkResult Renderer_CreateCommandPool(VkCommandPool* commandPool, VkCommandPoolCreateInfo* commandPoolInfo)
{
    return vkCreateCommandPool(global.Renderer.Device, commandPoolInfo, NULL, commandPool);
}

void Renderer_UpdateDescriptorSet(VkWriteDescriptorSet* writeDescriptorSet, uint32 count)
{
    vkUpdateDescriptorSets(global.Renderer.Device, count, writeDescriptorSet, 0, NULL);
}

VkResult Renderer_RebuildSwapChain()
{
    global.Renderer.RebuildRendererFlag = true;

    VULKAN_RESULT(vkDeviceWaitIdle(global.Renderer.Device));
    Vulkan_DestroyImageView();
    vkDestroySwapchainKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, NULL);
    return Vulkan_RebuildSwapChain();
}

VkResult Renderer_StartFrame()
{
    global.Renderer.CommandIndex = (global.Renderer.CommandIndex + 1) % MAX_FRAMES_IN_FLIGHT;

    vkWaitForFences(global.Renderer.Device, 1, &global.Renderer.InFlightFences[global.Renderer.CommandIndex], VK_TRUE, UINT64_MAX);
    vkResetFences(global.Renderer.Device, 1, &global.Renderer.InFlightFences[global.Renderer.CommandIndex]);

    VkSemaphore imageAvailableSemaphore = global.Renderer.AcquireImageSemaphores[global.Renderer.CommandIndex];
    VkSemaphore renderFinishedSemaphore = global.Renderer.PresentImageSemaphores[global.Renderer.CommandIndex];

    VkResult result = vkAcquireNextImageKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &global.Renderer.ImageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) 
    {
        global.Renderer.RebuildRendererFlag = true;
        return result;
    }

    return result;
}

VkResult Renderer_EndFrame(VkCommandBuffer* pCommandBufferSubmitList, uint32 commandBufferCount)
{
    VkPipelineStageFlags waitStages[] =
    {
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
    };

    VkSubmitInfo submitInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &global.Renderer.AcquireImageSemaphores[global.Renderer.CommandIndex], 
        .pWaitDstStageMask = waitStages, 
        .commandBufferCount = commandBufferCount,
        .pCommandBuffers = pCommandBufferSubmitList,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex] 
    };
    VULKAN_RESULT(vkQueueSubmit(global.Renderer.SwapChain.GraphicsQueue, 1, &submitInfo, global.Renderer.InFlightFences[global.Renderer.CommandIndex]));

    VkPresentInfoKHR presentInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex],
        .swapchainCount = 1,
        .pSwapchains = &global.Renderer.SwapChain.Swapchain,
        .pImageIndices = &global.Renderer.ImageIndex,
    };
    VkResult result = vkQueuePresentKHR(global.Renderer.SwapChain.PresentQueue, &presentInfo);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
    {
        global.Renderer.RebuildRendererFlag = true;
    }

    return result;
}

VkResult Renderer_BeginCommandBuffer(VkCommandBuffer* pCommandBuffer, VkCommandBufferBeginInfo* commandBufferBeginInfo)
{
    return vkBeginCommandBuffer(*pCommandBuffer, commandBufferBeginInfo);
}

VkResult Renderer_EndCommandBuffer(VkCommandBuffer* pCommandBuffer)
{
    return vkEndCommandBuffer(*pCommandBuffer);
}

VkResult Renderer_SubmitDraw(VkCommandBuffer* pCommandBufferSubmitList)
{
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    VkSubmitInfo SubmitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &global.Renderer.AcquireImageSemaphores[global.Renderer.CommandIndex],
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = 3,
        .pCommandBuffers = pCommandBufferSubmitList,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = &global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex],
    };
    VULKAN_RESULT(vkQueueSubmit(global.Renderer.SwapChain.GraphicsQueue, 1, &SubmitInfo, global.Renderer.InFlightFences[global.Renderer.CommandIndex]));

    VkPresentInfoKHR PresentInfoKHR =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex],
        .swapchainCount = 1,
        .pSwapchains = &global.Renderer.SwapChain.Swapchain,
        .pImageIndices = &global.Renderer.ImageIndex
    };
    VkResult result = vkQueuePresentKHR(global.Renderer.SwapChain.PresentQueue, &PresentInfoKHR);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        global.Renderer.RebuildRendererFlag = true;
        return result;
    }
    return result;
}

uint32 Renderer_GetMemoryType(uint32 typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(global.Renderer.PhysicalDevice, &memProperties);

    for (uint32 x = 0; x < memProperties.memoryTypeCount; x++)
    {
        if ((typeFilter & (1 << x)) &&
            (memProperties.memoryTypes[x].propertyFlags & properties) == properties)
        {
            return x;
        }
    }

    fprintf(stderr, "Couldn't find suitable memory type.\n");
    Renderer_DestroyRenderer();
    GameEngine_SDL_DestroyWindow();
    return -1;
}

VkCommandBuffer Renderer_BeginSingleUseCommandBuffer()
{
    VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
    VkCommandBufferAllocateInfo allocInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandPool = global.Renderer.CommandPool,
        .commandBufferCount = 1
    };
    VULKAN_RESULT(vkAllocateCommandBuffers(global.Renderer.Device, &allocInfo, &commandBuffer));

    VkCommandBufferBeginInfo beginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };
    VULKAN_RESULT(vkBeginCommandBuffer(commandBuffer, &beginInfo));
    return commandBuffer;
}

VkResult Renderer_EndSingleUseCommandBuffer(VkCommandBuffer commandBuffer)
{
    VULKAN_RESULT(vkEndCommandBuffer(commandBuffer));

    VkSubmitInfo submitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer
    };
    VULKAN_RESULT(vkQueueSubmit(global.Renderer.SwapChain.GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE));
    VULKAN_RESULT(vkQueueWaitIdle(global.Renderer.SwapChain.GraphicsQueue));
    vkFreeCommandBuffers(global.Renderer.Device, global.Renderer.CommandPool, 1, &commandBuffer);
    return VK_SUCCESS;
}

void Renderer_DestroyRenderer()
{
    Vulkan_DestroyImageView();
    Vulkan_DestroySwapChain();
    Renderer_DestroyCommandPool();
    Renderer_DestroyFences();
    Renderer_DestroyDevice();
    Renderer_DestroyDebugger();
    Renderer_DestroySurface();
    Renderer_DestroyInstance();
}

void Renderer_DestroyCommandPool()
{
    if (global.Renderer.CommandPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(global.Renderer.Device, global.Renderer.CommandPool, NULL);
        global.Renderer.CommandPool = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyFences()
{
    for (size_t x = 0; x < MAX_FRAMES_IN_FLIGHT; x++)
    {
        if (global.Renderer.AcquireImageSemaphores[x] != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(global.Renderer.Device, global.Renderer.AcquireImageSemaphores[x], NULL);
            global.Renderer.AcquireImageSemaphores[x] = VK_NULL_HANDLE;
        }
        if (global.Renderer.PresentImageSemaphores[x] != VK_NULL_HANDLE)
        {
            vkDestroySemaphore(global.Renderer.Device, global.Renderer.PresentImageSemaphores[x], NULL);
            global.Renderer.PresentImageSemaphores[x] = VK_NULL_HANDLE;
        }
        if (global.Renderer.InFlightFences[x] != VK_NULL_HANDLE)
        {
            vkDestroyFence(global.Renderer.Device, global.Renderer.InFlightFences[x], NULL);
            global.Renderer.InFlightFences[x] = VK_NULL_HANDLE;
        }
    }
}

void Renderer_DestroyDevice()
{
    if (global.Renderer.Device != VK_NULL_HANDLE)
    {
        vkDestroyDevice(global.Renderer.Device, NULL);
        global.Renderer.Device = VK_NULL_HANDLE;
    }
}

void Renderer_DestroySurface()
{
    if (global.Renderer.Surface != VK_NULL_HANDLE)
    {
        vkDestroySurfaceKHR(global.Renderer.Instance, global.Renderer.Surface, NULL);
        global.Renderer.Surface = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyDebugger()
{
    DestroyDebugUtilsMessengerEXT(global.Renderer.Instance, NULL);
}

void Renderer_DestroyInstance()
{
    if (global.Renderer.Instance != VK_NULL_HANDLE)
    {
        vkDestroyInstance(global.Renderer.Instance, NULL);
        global.Renderer.Instance = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyRenderPass(VkRenderPass* renderPass)
{
    if (*renderPass != VK_NULL_HANDLE)
    {
        vkDestroyRenderPass(global.Renderer.Device, *renderPass, NULL);
        *renderPass = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyFrameBuffers(VkFramebuffer* frameBufferList)
{
    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        if (frameBufferList[x] != VK_NULL_HANDLE)
        {
            vkDestroyFramebuffer(global.Renderer.Device, frameBufferList[x], NULL);
            frameBufferList[x] = VK_NULL_HANDLE;
        }
    }
}

void Renderer_DestroyDescriptorPool(VkDescriptorPool* descriptorPool)
{
    if (*descriptorPool != VK_NULL_HANDLE)
    {
        vkDestroyDescriptorPool(global.Renderer.Device, *descriptorPool, NULL);
        *descriptorPool = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyDescriptorSetLayout(VkDescriptorSetLayout* descriptorSetLayout)
{
    if (*descriptorSetLayout != VK_NULL_HANDLE)
    {
        vkDestroyDescriptorSetLayout(global.Renderer.Device, *descriptorSetLayout, NULL);
        *descriptorSetLayout = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyCommandBuffers(VkCommandPool* commandPool, VkCommandBuffer* commandBufferList)
{
    if (*commandBufferList != VK_NULL_HANDLE)
    {
        vkFreeCommandBuffers(global.Renderer.Device, *commandPool, global.Renderer.SwapChain.SwapChainImageCount, &*commandBufferList);
        for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
        {
            commandBufferList[x] = VK_NULL_HANDLE;
        }
    }
}

void Renderer_DestroyCommnadPool(VkCommandPool* commandPool)
{
    if (*commandPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(global.Renderer.Device, *commandPool, NULL);
        *commandPool = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyBuffer(VkBuffer* buffer)
{
    if (*buffer != VK_NULL_HANDLE)
    {
        vkDestroyBuffer(global.Renderer.Device, *buffer, NULL);
        *buffer = VK_NULL_HANDLE;
    }
}

void Renderer_FreeMemory(VkDeviceMemory* memory)
{
    if (*memory != VK_NULL_HANDLE)
    {
        vkFreeMemory(global.Renderer.Device, *memory, NULL);
        *memory = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyImageView(VkImageView* imageView)
{
    if (*imageView != VK_NULL_HANDLE)
    {
        vkDestroyImageView(global.Renderer.Device, *imageView, NULL);
        *imageView = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyImage(VkImage* image)
{
    if (*image != VK_NULL_HANDLE)
    {
        vkDestroyImage(global.Renderer.Device, *image, NULL);
        *image = VK_NULL_HANDLE;
    }
}

void Renderer_DestroySampler(VkSampler* sampler)
{
    if (*sampler != VK_NULL_HANDLE)
    {
        vkDestroySampler(global.Renderer.Device, *sampler, NULL);
        *sampler = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyPipeline(VkPipeline* pipeline)
{
    if (*pipeline != VK_NULL_HANDLE)
    {
        vkDestroyPipeline(global.Renderer.Device, *pipeline, NULL);
        *pipeline = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyPipelineLayout(VkPipelineLayout* pipelineLayout)
{
    if (*pipelineLayout != VK_NULL_HANDLE)
    {
        vkDestroyPipelineLayout(global.Renderer.Device, *pipelineLayout, NULL);
        *pipelineLayout = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyPipelineCache(VkPipelineCache* pipelineCache)
{
    if (*pipelineCache != VK_NULL_HANDLE)
    {
        vkDestroyPipelineCache(global.Renderer.Device, *pipelineCache, NULL);
        *pipelineCache = VK_NULL_HANDLE;
    }
}

int SimpleTest()
{
    return 42;
}