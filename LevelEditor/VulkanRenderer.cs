using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace LevelEditor
{

     public class VulkanRenderer
    
    {


        public  class VkApiVersion
        {
            public const uint Version10 = 0x00000001;
            public const uint Version11 = 0x00000A00;
            public const uint Version12 = 0x00000C00;
            public const uint Version13 = 0x00000D00;
        }

        public unsafe VkResult OpenWindow()
        {
            UInt32 extentionCount = 0;
            IntPtr ptr = GameEngineAPI.Renderer_Windows_Renderer(ref extentionCount);
            if (ptr == IntPtr.Zero)
            {
                Console.WriteLine("Failed to get extensions.");
            }

            var ar = new VkResult();
            //VkInstance instance;

            //string[] ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

            //uint layerCount = 0;
            //VulkanAPI.vkEnumerateInstanceLayerProperties(ref layerCount, null); // Get number of layers
            //VkLayerProperties[] availableLayers = new VkLayerProperties[layerCount];
            //VulkanAPI.vkEnumerateInstanceLayerProperties(ref layerCount, availableLayers); // Get layer properties
            //List<VkLayerProperties> availableLayerList = availableLayers.ToList();


            //VkDebugUtilsMessengerEXT debugMessenger;
            //VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
            //debugCreateInfo.sType = VkStructureType.VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            //debugCreateInfo.messageSeverity = (ulong)(VkDebugUtilsMessageSeverityFlagBitsEXT.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            //                                          VkDebugUtilsMessageSeverityFlagBitsEXT.VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            //                                          VkDebugUtilsMessageSeverityFlagBitsEXT.VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT);
            //debugCreateInfo.messageType = VkDebugUtilsMessageTypeFlagsEXT.VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            //                              VkDebugUtilsMessageTypeFlagsEXT.VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            //                              VkDebugUtilsMessageTypeFlagsEXT.VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT);
            //debugCreateInfo.pfnUserCallback = DebugCallback;

            //// Create the debug messenger
            //if (VulkanAPI.vkCreateDebugUtilsMessengerEXT(ref instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS)
            //{
            //    throw std::runtime_error("Failed to set up debug messenger!");
            //}

            //// Check if "VK_LAYER_KHRONOS_validation" is available
            //bool layersSupported = availableLayers.Any(layer => layer.layerName == "VK_LAYER_KHRONOS_validation");
            //if (!layersSupported)
            //{
            //    throw new Exception("Validation layer VK_LAYER_KHRONOS_validation not found!");
            //}

            //VkApplicationInfo applicationInfo = new VkApplicationInfo
            //{
            //    sType = VkStructureType.VK_STRUCTURE_TYPE_APPLICATION_INFO,
            //    pNext = IntPtr.Zero,
            //    pApplicationName = "MyApp",
            //    applicationVersion = 1,
            //    pEngineName = "No Engine",
            //    engineVersion = 1,
            //    apiVersion = VkApiVersion.Version13
            //};
            //IntPtr appInfoPtr = Marshal.AllocHGlobal(Marshal.SizeOf(applicationInfo));
            //Marshal.StructureToPtr(applicationInfo, appInfoPtr, false);

            //VkInstanceCreateInfo createInfo = new VkInstanceCreateInfo
            //{
            //    sType = VkStructureType.VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            //    pNext = IntPtr.Zero,
            //    pApplicationInfo = appInfoPtr,
            //    enabledLayerCount = 0,
            //    pEnabledLayerNames = IntPtr.Zero,
            //    enabledExtensionCount = ((uint)ValidationLayers.Length),
            //    pEnabledExtensionNames = IntPtr.Zero
            //};

            //VkResult result = VulkanAPI.vkCreateInstance(ref createInfo, IntPtr.Zero, out instance);
            //if (result != VkResult.VK_SUCCESS)
            //{
            //    Marshal.FreeHGlobal(appInfoPtr);
            //    throw new Exception("Failed to create Vulkan instance!");
            //}

            //Marshal.FreeHGlobal(appInfoPtr);

            //Console.WriteLine("Vulkan instance created successfully!");
            return VkResult.VK_SUCCESS;
        }
    }
}
