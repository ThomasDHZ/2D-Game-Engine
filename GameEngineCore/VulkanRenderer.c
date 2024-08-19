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

static bool Array_RendererExtensionPropertiesSearch(VkExtensionProperties* array, uint32_t arrayCount, const char* target)
{
    for (uint32_t x = 0; x < arrayCount; x++)
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

static VkExtensionProperties* GetDeviceExtensions(VkPhysicalDevice* physicalDevice, uint32_t* deviceExtensionCountPtr)
{
    uint32_t deviceExtensionCount = 0;
    vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &deviceExtensionCount, NULL);

    VkExtensionProperties* deviceExtensions = malloc(sizeof(VkExtensionProperties) * deviceExtensionCount);
    if (!deviceExtensions)
    {
        fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
        *deviceExtensionCountPtr = 0;
        return NULL;
    }

    vkEnumerateDeviceExtensionProperties(physicalDevice, NULL, &deviceExtensionCount, deviceExtensions);
    *deviceExtensionCountPtr = deviceExtensionCount;
    return deviceExtensions;
}

static VkSurfaceFormatKHR* GetSurfaceFormats(VkPhysicalDevice* physicalDevice)
{
    uint32_t surfaceFormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, global.Renderer.Surface, &surfaceFormatCount, NULL);
    if (surfaceFormatCount > 0)
    {
        VkSurfaceFormatKHR* surfaceFormats = malloc(sizeof(VkSurfaceFormatKHR) * surfaceFormatCount);
        if (!surfaceFormats)
        {
            fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
            return NULL;
        }

        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, global.Renderer.Surface, &surfaceFormatCount, surfaceFormats);
        return surfaceFormats;
    }
    return NULL;
}

static VkPresentModeKHR* GetPresentModes(VkPhysicalDevice* physicalDevice)
{
    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, global.Renderer.Surface, &presentModeCount, NULL);
    if (presentModeCount > 0)
    {
        VkPresentModeKHR* presentModes = malloc(sizeof(VkPresentModeKHR) * presentModeCount);
        if (!presentModes)
        {
            fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
            return NULL;
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, global.Renderer.Surface, &presentModeCount, presentModes);
        return presentModes;
    }
    return NULL;
}

static bool GetRayTracingSupport()
{   
    uint32_t deviceExtensionCount = INT32_MAX;
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
            uint32_t extensionCount;
            SDL_Vulkan_GetInstanceExtensions(global.Window.SDLWindow, &extensionCount, NULL);

            const char** extensions = malloc(sizeof(const char*) * (extensionCount + 3));
            SDL_Vulkan_GetInstanceExtensions(global.Window.SDLWindow, &extensionCount, extensions);
            if (!extensions) 
            {
                fprintf(stderr, "Failed to allocate memory for Vulkan.\n");
                free(deviceExtensions);
                return false;
            }
            extensions[extensionCount++] = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
            extensions[extensionCount++] = VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME;
            extensions[extensionCount++] = VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME;

            free(extensions);
            free(deviceExtensions);
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

void Renderer_RendererSetUp()
{
    global.Renderer.RebuildSwapChainFlag = false;

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
        Renderer_GetError(instanceResult);
        free(extensions);
        return; 
    }

#ifdef NDEBUG
#else
    VkResult debugMessangerResult = CreateDebugUtilsMessengerEXT(global.Renderer.Instance, &debugInfo, NULL, &global.Renderer.DebugMessenger);
    if (debugMessangerResult != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to create Vulkan Debug Messager: %s\n", SDL_GetError());
        Renderer_DestroyRenderer();
        free(extensions);
    }
#endif

    if (!SDL_Vulkan_CreateSurface(global.Window.SDLWindow, global.Renderer.Instance, &global.Renderer.Surface)) 
    {
        fprintf(stderr, "Failed to create Vulkan surface: %s\n", SDL_GetError());
        Renderer_DestroyRenderer();
        free(extensions);
        return;
    }

    uint32_t deviceCount = UINT32_MAX;
    vkEnumeratePhysicalDevices(global.Renderer.Instance, &deviceCount, NULL);
    if (deviceCount == 0)
    {
        fprintf(stderr, "Failed to find GPUs with Vulkan support: %s\n", SDL_GetError());
        Renderer_DestroyRenderer();
        free(extensions);
        return;
    }

    VkPhysicalDevice* physicalDeviceList = malloc(sizeof(VkPhysicalDevice) * deviceCount);
    VkResult physicalDeviceResult = vkEnumeratePhysicalDevices(global.Renderer.Instance, &deviceCount, physicalDeviceList);
    if (physicalDeviceResult != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to find to create physical device: %s\n", physicalDeviceResult);
        Renderer_DestroyRenderer();
        free(extensions);
        return;
    }

    VkPresentModeKHR* presentMode = NULL;
    for (int x = 0; x < deviceCount; x++)
    {
        vkGetPhysicalDeviceFeatures(physicalDeviceList[x], &global.Renderer.PhysicalDeviceFeatures);
        SwapChain_GetQueueFamilies(physicalDeviceList[x], &global.Renderer.SwapChain.GraphicsFamily, &global.Renderer.SwapChain.PresentFamily);
        VkSurfaceFormatKHR* surfaceFormat = GetSurfaceFormats(physicalDeviceList[x]);
        VkPresentModeKHR* presentMode = GetPresentModes(physicalDeviceList[x]);
        if (global.Renderer.SwapChain.GraphicsFamily != -1 &&
            global.Renderer.SwapChain.PresentFamily != -1 &&
            ARRAY_SIZE(surfaceFormat) > 0 &&
            ARRAY_SIZE(presentMode) != 0 &&
            global.Renderer.PhysicalDeviceFeatures.samplerAnisotropy)
        {
            global.Renderer.PhysicalDevice = physicalDeviceList[x];
            free(surfaceFormat);
            free(presentMode);
            break;
        }
        else
        {
            free(surfaceFormat);
            free(presentMode);
        }
    }
    if (global.Renderer.PhysicalDevice == VK_NULL_HANDLE)
    {
        Renderer_GetError(physicalDeviceResult);
        Renderer_DestroyRenderer();
        free(extensions);
        return;
    }

    VkPhysicalDeviceVulkan11Features physicalDeviceVulkan11Features;
    GetRendererFeatures(&physicalDeviceVulkan11Features);

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo[2];
    uint32_t queueCreateInfoCount = 0;
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

    VkDeviceCreateInfo deviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = queueCreateInfoCount,
        .pQueueCreateInfos = queueCreateInfo,
        .pEnabledFeatures = NULL,
        .enabledExtensionCount = ARRAY_SIZE(DeviceExtensionList),
        .ppEnabledExtensionNames = DeviceExtensionList
    };
#ifdef NDEBUG
    deviceCreateInfo.enabledLayerCount = 0;
#else
    deviceCreateInfo.enabledLayerCount = ARRAY_SIZE(ValidationLayers);
    deviceCreateInfo.ppEnabledLayerNames = ValidationLayers;
#endif

    VkResult deviceResult = vkCreateDevice(global.Renderer.PhysicalDevice, &deviceCreateInfo, NULL, &global.Renderer.Device);
    if (deviceResult != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to find to create device: %s\n", deviceResult);
        Renderer_DestroyRenderer();
        free(extensions);
        return;
    }

    Vulkan_SetUpSwapChain();

    VkCommandPoolCreateInfo CommandPoolCreateInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
        .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
        .queueFamilyIndex = global.Renderer.SwapChain.GraphicsFamily
    };

    VkResult commandPoolResult = vkCreateCommandPool(global.Renderer.Device, &CommandPoolCreateInfo, NULL, &global.Renderer.CommandPool);
    if (commandPoolResult != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to find to create graphics command pool: %s\n", commandPoolResult);
        Renderer_GetError(deviceResult);
        Renderer_DestroyRenderer();
        free(extensions);
        return;
    }

    global.Renderer.InFlightFences = malloc(sizeof(VkFence)* MAX_FRAMES_IN_FLIGHT);
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
    
    for (size_t x = 0; x < MAX_FRAMES_IN_FLIGHT; x++)
    {
        if (vkCreateSemaphore(global.Renderer.Device, &semaphoreCreateInfo, NULL, &global.Renderer.AcquireImageSemaphores[x]) != VK_SUCCESS ||
            vkCreateSemaphore(global.Renderer.Device, &semaphoreCreateInfo, NULL, &global.Renderer.PresentImageSemaphores[x]) != VK_SUCCESS ||
            vkCreateFence(global.Renderer.Device, &fenceInfo, NULL, &global.Renderer.InFlightFences[x]) != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to create synchronization objects for a frame.\n");
            Renderer_DestroyRenderer();
            free(extensions);
            return;
        }
    }

    vkGetDeviceQueue(global.Renderer.Device, global.Renderer.SwapChain.GraphicsFamily, 0, &global.Renderer.SwapChain.GraphicsQueue);
    vkGetDeviceQueue(global.Renderer.Device, global.Renderer.SwapChain.PresentFamily, 0, &global.Renderer.SwapChain.PresentQueue);
    free(extensions);
}

void Renderer_CreateCommandBuffers(VkCommandBuffer* commandBufferList)
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

        VkResult result = vkAllocateCommandBuffers(global.Renderer.Device, &commandBufferAllocateInfo, &commandBufferList[x]);
        if (result != VK_SUCCESS) 
        {
            fprintf(stderr, "Failed to create command buffers: %s\n", result);
            Renderer_DestroyRenderer();
            GameEngine_DestroyWindow();
        }
    }
}

void Renderer_CreateFrameBuffer(Renderer_CommandFrameBufferInfoStruct* createCommandBufferInfo)
{
    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        VkResult result = vkCreateFramebuffer(global.Renderer.Device, &createCommandBufferInfo->FrameBufferCreateInfo, NULL, &createCommandBufferInfo->pFrameBuffer[x]);
        if (result != VK_SUCCESS)
        {
            fprintf(stderr, "Failed to create frame buffers: %s\n", result);
            Renderer_DestroyRenderer();
            GameEngine_DestroyWindow();
        }
    }
}

void Renderer_CreateRenderPass(Renderer_RenderPassCreateInfoStruct* renderPassCreateInfo)
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

    VkResult result = vkCreateRenderPass(global.Renderer.Device, &renderPassInfo, NULL, renderPassCreateInfo->pRenderPass);
    if (result)
    {
        fprintf(stderr, "Failed to create render pass:%s\n", result);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

void Renderer_RebuildSwapChain()
{
    vkDeviceWaitIdle(global.Renderer.Device);

    global.Renderer.RebuildSwapChainFlag = true;
    Vulkan_DestroyImageView();

    vkDestroySwapchainKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, NULL);
    Vulkan_RebuildSwapChain();
}

void Renderer_StartFrame()
{
    global.Renderer.CommandIndex = (global.Renderer.CommandIndex + 1) % MAX_FRAMES_IN_FLIGHT;

    vkWaitForFences(global.Renderer.Device, 1, &global.Renderer.InFlightFences[global.Renderer.CommandIndex], VK_TRUE, UINT64_MAX);
    vkResetFences(global.Renderer.Device, 1, &global.Renderer.InFlightFences[global.Renderer.CommandIndex]);

    VkResult result = vkAcquireNextImageKHR(global.Renderer.Device, global.Renderer.SwapChain.Swapchain, UINT64_MAX, global.Renderer.AcquireImageSemaphores[global.Renderer.CommandIndex], VK_NULL_HANDLE, &global.Renderer.ImageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        Renderer_RebuildSwapChain();
        return result;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        fprintf(stderr, "Failed to create synchronization objects for a frame.\n");
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

void Renderer_EndFrame(VkCommandBuffer* pCommandBufferSubmitList)
{
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

    VkSubmitInfo SubmitInfo =
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &global.Renderer.AcquireImageSemaphores[global.Renderer.CommandIndex],
        .pWaitDstStageMask = waitStages,
        .commandBufferCount = ARRAY_SIZE(pCommandBufferSubmitList),
        .pCommandBuffers = pCommandBufferSubmitList,
        .signalSemaphoreCount = 1,
        .pSignalSemaphores = global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex]
    };
    VkResult QueueSubmit = vkQueueSubmit(global.Renderer.SwapChain.GraphicsFamily, 1, &SubmitInfo, global.Renderer.InFlightFences[global.Renderer.CommandIndex]);
    if (QueueSubmit != VK_SUCCESS) 
    {
        fprintf(stderr, "Failed to submit draw command buffer.\n");
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }

    VkPresentInfoKHR PresentInfoKHR =
    {
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &global.Renderer.PresentImageSemaphores[global.Renderer.ImageIndex],
        .swapchainCount = 1,
        .pSwapchains = &global.Renderer.SwapChain.Swapchain,
        .pImageIndices = &global.Renderer.ImageIndex
    };
    VkResult result = vkQueuePresentKHR(global.Renderer.SwapChain.PresentFamily, &PresentInfoKHR);
    if (result == VK_ERROR_OUT_OF_DATE_KHR)
    {
        Renderer_RebuildSwapChain();
        return result;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
    {
        fprintf(stderr, "Failed to present swap chain image.\n");
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

void Renderer_BeginCommandBuffer(Renderer_BeginCommandBufferStruct* pBeginCommandBufferInfo)
{
    VkResult result = vkBeginCommandBuffer(*pBeginCommandBufferInfo->pCommandBuffer, pBeginCommandBufferInfo->pCommandBufferBegin);
    if (result != VK_SUCCESS) 
    {
        fprintf(stderr, "Failed to begin recording command buffer.%s\n", result);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

void Renderer_EndCommandBuffer(VkCommandBuffer* pCommandBuffer)
{
    VkResult result = vkEndCommandBuffer(*pCommandBuffer);
    if (result != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to record command buffer.%s\n", result);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

void Renderer_SubmitDraw(VkCommandBuffer* pCommandBufferSubmitList)
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

    VkResult QueueSubmit = vkQueueSubmit(global.Renderer.SwapChain.GraphicsQueue, 1, &SubmitInfo, global.Renderer.InFlightFences[global.Renderer.CommandIndex]);
    if (QueueSubmit != VK_SUCCESS)
    {
        fprintf(stderr, "Failed to submit draw command buffer: %s\n", QueueSubmit);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }

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
        // RebuildSwapChain();
        return result;
    }
    else if (result != VK_SUCCESS && 
             result != VK_SUBOPTIMAL_KHR)
    {
        fprintf(stderr, "Failed to present swap chain image: %s\n", QueueSubmit);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
}

VkCommandBuffer Renderer_BeginSingleTimeCommand()
{
    VkCommandBuffer commandBuffer = VK_NULL_HANDLE;
    VkCommandBufferAllocateInfo allocInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
        .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
        .commandPool = global.Renderer.CommandPool,
        .commandBufferCount = 1
    };

    VkResult allocatResult = vkAllocateCommandBuffers(global.Renderer.Device, &allocInfo, &commandBuffer);
    if(allocatResult)
    {
        fprintf(stderr, "Failed to allocate command buffer: %s\n", allocatResult);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }

    VkCommandBufferBeginInfo beginInfo =
    {
        .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
        .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
    };
    VkResult commandSubmitResult = vkBeginCommandBuffer(commandBuffer, &beginInfo);
    if (commandSubmitResult)
    {
        fprintf(stderr, "Failed to submit command buffer: %s\n", commandSubmitResult);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }
    return commandBuffer;
}

void Renderer_EndSingleTimeCommand(VkCommandBuffer* commandBuffer)
{
    VkResult endCommandResult = vkEndCommandBuffer(commandBuffer);
    if (endCommandResult)
    {
        fprintf(stderr, "Failed to end command buffer: %s\n", endCommandResult);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }

    VkSubmitInfo submitInfo = 
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .commandBufferCount = 1,
        .pCommandBuffers = &commandBuffer
    };
    VkResult queueSubmitResult = vkQueueSubmit(global.Renderer.SwapChain.GraphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
    if (queueSubmitResult)
    {
        fprintf(stderr, "Failed to submit queue: %s\n", queueSubmitResult);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }

    VkResult queueWaitResult = vkQueueWaitIdle(global.Renderer.SwapChain.GraphicsQueue);
    if (queueWaitResult)
    {
        fprintf(stderr, "Failed to get response: %s\n", queueWaitResult);
        Renderer_DestroyRenderer();
        GameEngine_DestroyWindow();
    }

    vkFreeCommandBuffers(global.Renderer.Device, global.Renderer.CommandPool, 1, commandBuffer);
}

void Renderer_DestroyRenderer()
{
    vkDeviceWaitIdle(global.Renderer.Device);
    Vulkan_DestroySwapChain();
    Vulkan_DestroyImageView();
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
    if (renderPass != VK_NULL_HANDLE)
    {
        vkDestroyRenderPass(global.Renderer.Device, renderPass, NULL);
        renderPass = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyFrameBuffers(VkFramebuffer* frameBufferList)
{
    for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
    {
        if (frameBufferList != VK_NULL_HANDLE)
        {
            vkDestroyFramebuffer(global.Renderer.Device, frameBufferList, NULL);
            frameBufferList = VK_NULL_HANDLE;
        }
    }
}

void Renderer_DestroyDescriptorPool(VkDescriptorPool* descriptorPool)
{
    if (descriptorPool != VK_NULL_HANDLE)
    {
        vkDestroyDescriptorPool(global.Renderer.Device, descriptorPool, NULL);
        descriptorPool = VK_NULL_HANDLE;
    }
}

void Renderer_DestroyCommandBuffers(VkDescriptorPool* descriptorPool, VkCommandBuffer* commandBufferList)
{
    if (commandBufferList[0] != VK_NULL_HANDLE)
    {
        vkFreeCommandBuffers(global.Renderer.Device, descriptorPool, 1, &commandBufferList[0]);
        for (size_t x = 0; x < global.Renderer.SwapChain.SwapChainImageCount; x++)
        {
            commandBufferList[x] = VK_NULL_HANDLE;
        }
    }
}

void Renderer_DestroyCommnadPool(VkCommandPool* commandPool)
{
    if (commandPool != VK_NULL_HANDLE)
    {
        vkDestroyCommandPool(global.Renderer.Device, commandPool, NULL);
        commandPool = VK_NULL_HANDLE;
    }
}
