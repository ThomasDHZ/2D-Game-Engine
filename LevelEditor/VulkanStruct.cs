using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using LevelEditor;

namespace LevelEditor
{

    [StructLayout(LayoutKind.Sequential)]
    public struct VkInstance { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDevice { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDevice { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkQueue { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSemaphore { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCommandBuffer { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkFence { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDeviceMemory { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkEvent { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkQueryPool { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBufferView { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageView { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkShaderModule { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineCache { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineLayout { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipeline { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkRenderPass { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorSetLayout { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSampler { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorSet { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorPool { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkFramebuffer { private IntPtr handle; }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCommandPool { private IntPtr handle; }

    // Vulkan Structs
    [StructLayout(LayoutKind.Sequential)]
    public struct VkExtent2D
    {
        public uint Width;
        public uint Height;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkExtent3D
    {
        public uint Width;
        public uint Height;
        public uint Depth;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkOffset2D
    {
        public int X;
        public int Y;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkOffset3D
    {
        public int X;
        public int Y;
        public int Z;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkRect2D
    {
        public VkOffset2D Offset;
        public VkExtent2D Extent;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBaseInStructure
    {
        public VkStructureType SType;
        public IntPtr PNext; // Pointer for extension structures
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBaseOutStructure
    {
        public VkStructureType SType;
        public IntPtr PNext; // Pointer for extension structures
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBufferMemoryBarrier
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkAccessFlags SrcAccessMask;
        public VkAccessFlags DstAccessMask;
        public uint SrcQueueFamilyIndex;
        public uint DstQueueFamilyIndex;
        public VkBuffer Buffer;
        public VkDeviceSize Offset;
        public VkDeviceSize Size;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDispatchIndirectCommand
    {
        public uint X;
        public uint Y;
        public uint Z;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDrawIndexedIndirectCommand
    {
        public uint IndexCount;
        public uint InstanceCount;
        public uint FirstIndex;
        public int VertexOffset;
        public uint FirstInstance;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDrawIndirectCommand
    {
        public uint VertexCount;
        public uint InstanceCount;
        public uint FirstVertex;
        public uint FirstInstance;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageSubresourceRange
    {
        public VkImageAspectFlags AspectMask;
        public uint BaseMipLevel;
        public uint LevelCount;
        public uint BaseArrayLayer;
        public uint LayerCount;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageMemoryBarrier
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkAccessFlags SrcAccessMask;
        public VkAccessFlags DstAccessMask;
        public VkImageLayout OldLayout;
        public VkImageLayout NewLayout;
        public uint SrcQueueFamilyIndex;
        public uint DstQueueFamilyIndex;
        public VkImage Image;
        public VkImageSubresourceRange SubresourceRange;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMemoryBarrier
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkAccessFlags SrcAccessMask;
        public VkAccessFlags DstAccessMask;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineCacheHeaderVersionOne
    {
        public uint HeaderSize;
        public VkPipelineCacheHeaderVersion HeaderVersion;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = VulkanConsts.VK_UUID_SIZE)]
        public byte[] PipelineCacheUUID;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkAllocationCallbacks
    {
        public IntPtr PUserData;
        public IntPtr PfnAllocation;
        public IntPtr PfnReallocation;
        public IntPtr PfnFree;
        public IntPtr PfnInternalAllocation;
        public IntPtr PfnInternalFree;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkApplicationInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        [MarshalAs(UnmanagedType.LPUTF8Str)]
        public string PApplicationName;
        public uint ApplicationVersion;
        [MarshalAs(UnmanagedType.LPUTF8Str)]
        public string PEngineName;
        public uint EngineVersion;
        public uint ApiVersion;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkFormatProperties
    {
        public VkFormatFeatureFlags LinearTilingFeatures;
        public VkFormatFeatureFlags OptimalTilingFeatures;
        public VkFormatFeatureFlags BufferFeatures;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageFormatProperties
    {
        public VkExtent3D MaxExtent;
        public uint MaxMipLevels;
        public uint MaxArrayLayers;
        public VkSampleCountFlags SampleCounts;
        public VkDeviceSize MaxResourceSize;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkInstanceCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkInstanceCreateFlags Flags;
        public IntPtr pApplicationInfo; // Pointer to VkApplicationInfo
        public uint EnabledLayerCount;
        public IntPtr pEnabledLayerNames; // Pointer to array of layer names
        public uint EnabledExtensionCount;
        public IntPtr pEnabledExtensionNames; // Pointer to array of extension names
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMemoryHeap
    {
        public VkDeviceSize Size;
        public VkMemoryHeapFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMemoryType
    {
        public VkMemoryPropertyFlags PropertyFlags;
        public uint HeapIndex;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceFeatures
    {
        public VkBool32 RobustBufferAccess;
        public VkBool32 FullDrawIndexUint32;
        public VkBool32 ImageCubeArray;
        public VkBool32 IndependentBlend;
        public VkBool32 GeometryShader;
        public VkBool32 TessellationShader;
        public VkBool32 SampleRateShading;
        public VkBool32 DualSrcBlend;
        public VkBool32 LogicOp;
        public VkBool32 MultiDrawIndirect;
        public VkBool32 DrawIndirectFirstInstance;
        public VkBool32 DepthClamp;
        public VkBool32 DepthBiasClamp;
        public VkBool32 FillModeNonSolid;
        public VkBool32 DepthBounds;
        public VkBool32 WideLines;
        public VkBool32 LargePoints;
        public VkBool32 AlphaToOne;
        public VkBool32 MultiViewport;
        public VkBool32 SamplerAnisotropy;
        public VkBool32 TextureCompressionETC2;
        public VkBool32 TextureCompressionASTC_LDR;
        public VkBool32 TextureCompressionBC;
        public VkBool32 OcclusionQueryPrecise;
        public VkBool32 PipelineStatisticsQuery;
        public VkBool32 VertexPipelineStoresAndAtomics;
        public VkBool32 FragmentStoresAndAtomics;
        public VkBool32 ShaderTessellationAndGeometryPointSize;
        public VkBool32 ShaderImageGatherExtended;
        public VkBool32 ShaderStorageImageExtendedFormats;
        public VkBool32 ShaderStorageImageMultisample;
        public VkBool32 ShaderStorageImageReadWithoutFormat;
        public VkBool32 ShaderStorageImageWriteWithoutFormat;
        public VkBool32 ShaderUniformBufferArrayDynamicIndexing;
        public VkBool32 ShaderSampledImageArrayDynamicIndexing;
        public VkBool32 ShaderStorageBufferArrayDynamicIndexing;
        public VkBool32 ShaderStorageImageArrayDynamicIndexing;
        public VkBool32 ShaderClipDistance;
        public VkBool32 ShaderCullDistance;
        public VkBool32 ShaderFloat64;
        public VkBool32 ShaderInt64;
        public VkBool32 ShaderInt16;
        public VkBool32 ShaderResourceResidency;
        public VkBool32 ShaderResourceMinLod;
        public VkBool32 SparseBinding;
        public VkBool32 SparseResidencyBuffer;
        public VkBool32 SparseResidencyImage2D;
        public VkBool32 SparseResidencyImage3D;
        public VkBool32 SparseResidency2Samples;
        public VkBool32 SparseResidency4Samples;
        public VkBool32 SparseResidency8Samples;
        public VkBool32 SparseResidency16Samples;
        public VkBool32 SparseResidencyAliased;
        public VkBool32 VariableMultisampleRate;
        public VkBool32 InheritedQueries;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceLimits
    {
        public uint MaxImageDimension1D;
        public uint MaxImageDimension2D;
        public uint MaxImageDimension3D;
        public uint MaxImageDimensionCube;
        public uint MaxImageArrayLayers;
        public uint MaxTexelBufferElements;
        public uint MaxUniformBufferRange;
        public uint MaxStorageBufferRange;
        public uint MaxPushConstantsSize;
        public uint MaxMemoryAllocationCount;
        public uint MaxSamplerAllocationCount;
        public VkDeviceSize BufferImageGranularity;
        public VkDeviceSize SparseAddressSpaceSize;
        public uint MaxBoundDescriptorSets;
        public uint MaxPerStageDescriptorSamplers;
        public uint MaxPerStageDescriptorUniformBuffers;
        public uint MaxPerStageDescriptorStorageBuffers;
        public uint MaxPerStageDescriptorSampledImages;
        public uint MaxPerStageDescriptorStorageImages;
        public uint MaxPerStageDescriptorInputAttachments;
        public uint MaxPerStageResources;
        public uint MaxDescriptorSetSamplers;
        public uint MaxDescriptorSetUniformBuffers;
        public uint MaxDescriptorSetUniformBuffersDynamic;
        public uint MaxDescriptorSetStorageBuffers;
        public uint MaxDescriptorSetStorageBuffersDynamic;
        public uint MaxDescriptorSetSampledImages;
        public uint MaxDescriptorSetStorageImages;
        public uint MaxDescriptorSetInputAttachments;
        public uint MaxVertexInputAttributes;
        public uint MaxVertexInputBindings;
        public uint MaxVertexInputAttributeOffset;
        public uint MaxVertexInputBindingStride;
        public uint MaxVertexOutputComponents;
        public uint MaxTessellationGenerationLevel;
        public uint MaxTessellationPatchSize;
        public uint MaxTessellationControlPerVertexInputComponents;
        public uint MaxTessellationControlPerVertexOutputComponents;
        public uint MaxTessellationControlPerPatchOutputComponents;
        public uint MaxTessellationControlTotalOutputComponents;
        public uint MaxTessellationEvaluationInputComponents;
        public uint MaxTessellationEvaluationOutputComponents;
        public uint MaxGeometryShaderInvocations;
        public uint MaxGeometryInputComponents;
        public uint MaxGeometryOutputComponents;
        public uint MaxGeometryOutputVertices;
        public uint MaxGeometryTotalOutputComponents;
        public uint MaxFragmentInputComponents;
        public uint MaxFragmentOutputAttachments;
        public uint MaxFragmentDualSrcAttachments;
        public uint MaxFragmentCombinedOutputResources;
        public uint MaxComputeSharedMemorySize;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public uint[] MaxComputeWorkGroupCount;
        public uint MaxComputeWorkGroupInvocations;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
        public uint[] MaxComputeWorkGroupSize;
        public uint SubPixelPrecisionBits;
        public uint SubTexelPrecisionBits;
        public uint MipmapPrecisionBits;
        public uint MaxDrawIndexedIndexValue;
        public uint MaxDrawIndirectCount;
        public float MaxSamplerLodBias;
        public float MaxSamplerAnisotropy;
        public uint MaxViewports;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public uint[] MaxViewportDimensions;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public float[] ViewportBoundsRange;
        public uint ViewportSubPixelBits;
        public IntPtr MinMemoryMapAlignment;
        public VkDeviceSize MinTexelBufferOffsetAlignment;
        public VkDeviceSize MinUniformBufferOffsetAlignment;
        public VkDeviceSize MinStorageBufferOffsetAlignment;
        public int MinTexelOffset;
        public uint MaxTexelOffset;
        public int MinTexelGatherOffset;
        public uint MaxTexelGatherOffset;
        public float MinInterpolationOffset;
        public float MaxInterpolationOffset;
        public uint SubPixelInterpolationOffsetBits;
        public uint MaxFramebufferWidth;
        public uint MaxFramebufferHeight;
        public uint MaxFramebufferLayers;
        public VkSampleCountFlags FramebufferColorSampleCounts;
        public VkSampleCountFlags FramebufferDepthSampleCounts;
        public VkSampleCountFlags FramebufferStencilSampleCounts;
        public VkSampleCountFlags FramebufferNoAttachmentsSampleCounts;
        public uint MaxColorAttachments;
        public VkSampleCountFlags SampledImageColorSampleCounts;
        public VkSampleCountFlags SampledImageIntegerSampleCounts;
        public VkSampleCountFlags SampledImageDepthSampleCounts;
        public VkSampleCountFlags SampledImageStencilSampleCounts;
        public VkSampleCountFlags StorageImageSampleCounts;
        public uint MaxSampleMaskWords;
        public VkBool32 TimestampComputeAndGraphics;
        public float TimestampPeriod;
        public uint MaxClipDistances;
        public uint MaxCullDistances;
        public uint MaxCombinedClipAndCullDistances;
        public uint DiscreteQueuePriorities;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public float[] PointSizeRange;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public float[] LineWidthRange;
        public float PointSizeGranularity;
        public float LineWidthGranularity;
        public VkBool32 StrictLines;
        public VkBool32 StandardSampleLocations;
        public VkDeviceSize OptimalBufferCopyOffsetAlignment;
        public VkDeviceSize OptimalBufferCopyRowPitchAlignment;
        public VkDeviceSize NonCoherentAtomSize;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceMemoryProperties
    {
        public uint MemoryTypeCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = VulkanConsts.VK_MAX_MEMORY_TYPES)]
        public VkMemoryType[] MemoryTypes;
        public uint MemoryHeapCount;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = VulkanConsts.VK_MAX_MEMORY_HEAPS)]
        public VkMemoryHeap[] MemoryHeaps;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceSparseProperties
    {
        public VkBool32 ResidencyStandard2DBlockShape;
        public VkBool32 ResidencyStandard2DMultisampleBlockShape;
        public VkBool32 ResidencyStandard3DBlockShape;
        public VkBool32 ResidencyAlignedMipSize;
        public VkBool32 ResidencyNonResidentStrict;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceProperties
    {
        public uint ApiVersion;
        public uint DriverVersion;
        public uint VendorID;
        public uint DeviceID;
        public VkPhysicalDeviceType DeviceType;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VulkanConsts.VK_MAX_PHYSICAL_DEVICE_NAME_SIZE)]
        public string DeviceName;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = VulkanConsts.VK_UUID_SIZE)]
        public byte[] PipelineCacheUUID;
        public VkPhysicalDeviceLimits Limits;
        public VkPhysicalDeviceSparseProperties SparseProperties;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkQueueFamilyProperties
    {
        public VkQueueFlags QueueFlags;
        public uint QueueCount;
        public uint TimestampValidBits;
        public VkExtent3D MinImageTransferGranularity;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDeviceQueueCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDeviceQueueCreateFlags Flags;
        public uint QueueFamilyIndex;
        public uint QueueCount;
        public IntPtr PQueuePriorities; // Pointer to float array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDeviceCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDeviceCreateFlags Flags;
        public uint QueueCreateInfoCount;
        public IntPtr PQueueCreateInfos; // Pointer to VkDeviceQueueCreateInfo array
        public uint EnabledLayerCount;
        public IntPtr pEnabledLayerNames; // Pointer to array of layer names
        public uint EnabledExtensionCount;
        public IntPtr pEnabledExtensionNames; // Pointer to array of extension names
        public IntPtr PEnabledFeatures; // Pointer to VkPhysicalDeviceFeatures
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkExtensionProperties
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VulkanConsts.VK_MAX_EXTENSION_NAME_SIZE)]
        public string ExtensionName;
        public uint SpecVersion;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkLayerProperties
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VulkanConsts.VK_MAX_EXTENSION_NAME_SIZE)]
        public string LayerName;
        public uint SpecVersion;
        public uint ImplementationVersion;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = VulkanConsts.VK_MAX_DESCRIPTION_SIZE)]
        public string Description;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSubmitInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public uint WaitSemaphoreCount;
        public IntPtr PWaitSemaphores; // Pointer to array of VkSemaphore
        public IntPtr PWaitDstStageMask; // Pointer to array of VkPipelineStageFlags
        public uint CommandBufferCount;
        public IntPtr PCommandBuffers; // Pointer to array of VkCommandBuffer
        public uint SignalSemaphoreCount;
        public IntPtr PSignalSemaphores; // Pointer to array of VkSemaphore
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMappedMemoryRange
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDeviceMemory Memory;
        public VkDeviceSize Offset;
        public VkDeviceSize Size;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMemoryAllocateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDeviceSize AllocationSize;
        public uint MemoryTypeIndex;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMemoryRequirements
    {
        public VkDeviceSize Size;
        public VkDeviceSize Alignment;
        public uint MemoryTypeBits;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseMemoryBind
    {
        public VkDeviceSize ResourceOffset;
        public VkDeviceSize Size;
        public VkDeviceMemory Memory;
        public VkDeviceSize MemoryOffset;
        public VkSparseMemoryBindFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseBufferMemoryBindInfo
    {
        public VkBuffer Buffer;
        public uint BindCount;
        public IntPtr PBinds; // Pointer to array of VkSparseMemoryBind
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseImageOpaqueMemoryBindInfo
    {
        public VkImage Image;
        public uint BindCount;
        public IntPtr PBinds; // Pointer to array of VkSparseMemoryBind
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageSubresource
    {
        public VkImageAspectFlags AspectMask;
        public uint MipLevel;
        public uint ArrayLayer;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseImageMemoryBind
    {
        public VkImageSubresource Subresource;
        public VkOffset3D Offset;
        public VkExtent3D Extent;
        public VkDeviceMemory Memory;
        public VkDeviceSize MemoryOffset;
        public VkSparseMemoryBindFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseImageMemoryBindInfo
    {
        public VkImage Image;
        public uint BindCount;
        public IntPtr PBinds; // Pointer to array of VkSparseImageMemoryBind
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBindSparseInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public uint WaitSemaphoreCount;
        public IntPtr PWaitSemaphores; // Pointer to VkSemaphore array
        public uint BufferBindCount;
        public IntPtr PBufferBinds; // Pointer to VkSparseBufferMemoryBindInfo array
        public uint ImageOpaqueBindCount;
        public IntPtr PImageOpaqueBinds; // Pointer to VkSparseImageOpaqueMemoryBindInfo array
        public uint ImageBindCount;
        public IntPtr PImageBinds; // Pointer to VkSparseImageMemoryBindInfo array
        public uint SignalSemaphoreCount;
        public IntPtr PSignalSemaphores; // Pointer to VkSemaphore array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseImageFormatProperties
    {
        public VkImageAspectFlags AspectMask;
        public VkExtent3D ImageGranularity;
        public VkSparseImageFormatFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSparseImageMemoryRequirements
    {
        public VkSparseImageFormatProperties FormatProperties;
        public uint ImageMipTailFirstLod;
        public VkDeviceSize ImageMipTailSize;
        public VkDeviceSize ImageMipTailOffset;
        public VkDeviceSize ImageMipTailStride;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkFenceCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkFenceCreateFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSemaphoreCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkSemaphoreCreateFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkEventCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkEventCreateFlags Flags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkQueryPoolCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkQueryPoolCreateFlags Flags;
        public VkQueryType QueryType;
        public uint QueryCount;
        public VkQueryPipelineStatisticFlags PipelineStatistics;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBufferCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkBufferCreateFlags Flags;
        public VkDeviceSize Size;
        public VkBufferUsageFlags Usage;
        public VkSharingMode SharingMode;
        public uint QueueFamilyIndexCount;
        public IntPtr PQueueFamilyIndices; // Pointer to array of uint
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBufferViewCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkBufferViewCreateFlags Flags;
        public VkBuffer Buffer;
        public VkFormat Format;
        public VkDeviceSize Offset;
        public VkDeviceSize Range;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkImageCreateFlags Flags;
        public VkImageType ImageType;
        public VkFormat Format;
        public VkExtent3D Extent;
        public uint MipLevels;
        public uint ArrayLayers;
        public VkSampleCountFlagBits Samples;
        public VkImageTiling Tiling;
        public VkImageUsageFlags Usage;
        public VkSharingMode SharingMode;
        public uint QueueFamilyIndexCount;
        public IntPtr PQueueFamilyIndices; // Pointer to array of uint
        public VkImageLayout InitialLayout;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSubresourceLayout
    {
        public VkDeviceSize Offset;
        public VkDeviceSize Size;
        public VkDeviceSize RowPitch;
        public VkDeviceSize ArrayPitch;
        public VkDeviceSize DepthPitch;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkComponentMapping
    {
        public VkComponentSwizzle R;
        public VkComponentSwizzle G;
        public VkComponentSwizzle B;
        public VkComponentSwizzle A;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageViewCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkImageViewCreateFlags Flags;
        public VkImage Image;
        public VkImageViewType ViewType;
        public VkFormat Format;
        public VkComponentMapping Components;
        public VkImageSubresourceRange SubresourceRange;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkShaderModuleCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkShaderModuleCreateFlags Flags;
        public nuint CodeSize; // size_t in C
        public IntPtr PCode; // Pointer to uint array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineCacheCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineCacheCreateFlags Flags;
        public nuint InitialDataSize; // size_t in C
        public IntPtr PInitialData; // Pointer to void
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSpecializationMapEntry
    {
        public uint ConstantID;
        public uint Offset;
        public nuint Size; // size_t in C
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSpecializationInfo
    {
        public uint MapEntryCount;
        public IntPtr PMapEntries; // Pointer to VkSpecializationMapEntry array
        public nuint DataSize; // size_t in C
        public IntPtr PData; // Pointer to void
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineShaderStageCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineShaderStageCreateFlags Flags;
        public VkShaderStageFlagBits Stage;
        public VkShaderModule Module;
        [MarshalAs(UnmanagedType.LPUTF8Str)]
        public string PName;
        public IntPtr PSpecializationInfo; // Pointer to VkSpecializationInfo
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkComputePipelineCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineCreateFlags Flags;
        public VkPipelineShaderStageCreateInfo Stage;
        public VkPipelineLayout Layout;
        public VkPipeline BasePipelineHandle;
        public int BasePipelineIndex;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkVertexInputBindingDescription
    {
        public uint Binding;
        public uint Stride;
        public VkVertexInputRate InputRate;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkVertexInputAttributeDescription
    {
        public uint Location;
        public uint Binding;
        public VkFormat Format;
        public uint Offset;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineVertexInputStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineVertexInputStateCreateFlags Flags;
        public uint VertexBindingDescriptionCount;
        public IntPtr PVertexBindingDescriptions; // Pointer to array of VkVertexInputBindingDescription
        public uint VertexAttributeDescriptionCount;
        public IntPtr PVertexAttributeDescriptions; // Pointer to array of VkVertexInputAttributeDescription
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineInputAssemblyStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineInputAssemblyStateCreateFlags Flags;
        public VkPrimitiveTopology Topology;
        public VkBool32 PrimitiveRestartEnable;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineTessellationStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineTessellationStateCreateFlags Flags;
        public uint PatchControlPoints;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkViewport
    {
        public float X;
        public float Y;
        public float Width;
        public float Height;
        public float MinDepth;
        public float MaxDepth;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineViewportStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineViewportStateCreateFlags Flags;
        public uint ViewportCount;
        public IntPtr PViewports; // Pointer to VkViewport array
        public uint ScissorCount;
        public IntPtr PScissors; // Pointer to VkRect2D array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineRasterizationStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineRasterizationStateCreateFlags Flags;
        public VkBool32 DepthClampEnable;
        public VkBool32 RasterizerDiscardEnable;
        public VkPolygonMode PolygonMode;
        public VkCullModeFlags CullMode;
        public VkFrontFace FrontFace;
        public VkBool32 DepthBiasEnable;
        public float DepthBiasConstantFactor;
        public float DepthBiasClamp;
        public float DepthBiasSlopeFactor;
        public float LineWidth;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineMultisampleStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineMultisampleStateCreateFlags Flags;
        public VkSampleCountFlagBits RasterizationSamples;
        public VkBool32 SampleShadingEnable;
        public float MinSampleShading;
        public IntPtr PSampleMask; // Pointer to VkSampleMask array
        public VkBool32 AlphaToCoverageEnable;
        public VkBool32 AlphaToOneEnable;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkStencilOpState
    {
        public VkStencilOp FailOp;
        public VkStencilOp PassOp;
        public VkStencilOp DepthFailOp;
        public VkCompareOp CompareOp;
        public uint CompareMask;
        public uint WriteMask;
        public uint Reference;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineDepthStencilStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineDepthStencilStateCreateFlags Flags;
        public VkBool32 DepthTestEnable;
        public VkBool32 DepthWriteEnable;
        public VkCompareOp DepthCompareOp;
        public VkBool32 DepthBoundsTestEnable;
        public VkBool32 StencilTestEnable;
        public VkStencilOpState Front;
        public VkStencilOpState Back;
        public float MinDepthBounds;
        public float MaxDepthBounds;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineColorBlendAttachmentState
    {
        public VkBool32 BlendEnable;
        public VkBlendFactor SrcColorBlendFactor;
        public VkBlendFactor DstColorBlendFactor;
        public VkBlendOp ColorBlendOp;
        public VkBlendFactor SrcAlphaBlendFactor;
        public VkBlendFactor DstAlphaBlendFactor;
        public VkBlendOp AlphaBlendOp;
        public VkColorComponentFlags ColorWriteMask;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineColorBlendStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineColorBlendStateCreateFlags Flags;
        public VkBool32 LogicOpEnable;
        public VkLogicOp LogicOp;
        public uint AttachmentCount;
        public IntPtr PAttachments; // Pointer to VkPipelineColorBlendAttachmentState array
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public float[] BlendConstants;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineDynamicStateCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineDynamicStateCreateFlags Flags;
        public uint DynamicStateCount;
        public IntPtr PDynamicStates; // Pointer to VkDynamicState array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkGraphicsPipelineCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineCreateFlags Flags;
        public uint StageCount;
        public IntPtr PStages; // Pointer to VkPipelineShaderStageCreateInfo array
        public IntPtr PVertexInputState; // Pointer to VkPipelineVertexInputStateCreateInfo
        public IntPtr PInputAssemblyState; // Pointer to VkPipelineInputAssemblyStateCreateInfo
        public IntPtr PTessellationState; // Pointer to VkPipelineTessellationStateCreateInfo
        public IntPtr PViewportState; // Pointer to VkPipelineViewportStateCreateInfo
        public IntPtr PRasterizationState; // Pointer to VkPipelineRasterizationStateCreateInfo
        public IntPtr PMultisampleState; // Pointer to VkPipelineMultisampleStateCreateInfo
        public IntPtr PDepthStencilState; // Pointer to VkPipelineDepthStencilStateCreateInfo
        public IntPtr PColorBlendState; // Pointer to VkPipelineColorBlendStateCreateInfo
        public IntPtr PDynamicState; // Pointer to VkPipelineDynamicStateCreateInfo
        public VkPipeline Layout;
        public VkRenderPass RenderPass;
        public uint Subpass;
        public VkPipeline BasePipelineHandle;
        public int BasePipelineIndex;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPushConstantRange
    {
        public VkShaderStageFlags StageFlags;
        public uint Offset;
        public uint Size;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPipelineLayoutCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkPipelineLayoutCreateFlags Flags;
        public uint SetLayoutCount;
        public IntPtr PSetLayouts; // Pointer to VkDescriptorSetLayout array
        public uint PushConstantRangeCount;
        public IntPtr pPushConstantRanges; // Pointer to VkPushConstantRange array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSamplerCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkSamplerCreateFlags Flags;
        public VkFilter MagFilter;
        public VkFilter MinFilter;
        public VkSamplerMipmapMode MipmapMode;
        public VkSamplerAddressMode AddressModeU;
        public VkSamplerAddressMode AddressModeV;
        public VkSamplerAddressMode AddressModeW;
        public float MipLodBias;
        public VkBool32 AnisotropyEnable;
        public float MaxAnisotropy;
        public VkBool32 CompareEnable;
        public VkCompareOp CompareOp;
        public float MinLod;
        public float MaxLod;
        public VkBorderColor BorderColor;
        public VkBool32 UnnormalizedCoordinates;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCopyDescriptorSet
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDescriptorSet SrcSet;
        public uint SrcBinding;
        public uint SrcArrayElement;
        public VkDescriptorSet DstSet;
        public uint DstBinding;
        public uint DstArrayElement;
        public uint DescriptorCount;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorBufferInfo
    {
        public VkBuffer Buffer;
        public VkDeviceSize Offset;
        public VkDeviceSize Range;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorImageInfo
    {
        public VkSampler Sampler;
        public VkImageView ImageView;
        public VkImageLayout ImageLayout;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorPoolSize
    {
        public VkDescriptorType Type;
        public uint DescriptorCount;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorPoolCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDescriptorPoolCreateFlags Flags;
        public uint MaxSets;
        public uint PoolSizeCount;
        public IntPtr pPoolSizes; // Pointer to VkDescriptorPoolSize array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorSetAllocateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDescriptorPool DescriptorPool;
        public uint DescriptorSetCount;
        public IntPtr PSetLayouts; // Pointer to VkDescriptorSetLayout array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorSetLayoutBinding
    {
        public uint Binding;
        public VkDescriptorType DescriptorType;
        public uint DescriptorCount;
        public VkShaderStageFlags StageFlags;
        public IntPtr PImmutableSamplers; // Pointer to VkSampler array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorSetLayoutCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDescriptorSetLayoutCreateFlags Flags;
        public uint BindingCount;
        public IntPtr PBindings; // Pointer to VkDescriptorSetLayoutBinding array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkWriteDescriptorSet
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkDescriptorSet DstSet;
        public uint DstBinding;
        public uint DstArrayElement;
        public uint DescriptorCount;
        public VkDescriptorType DescriptorType;
        public IntPtr PImageInfo; // Pointer to VkDescriptorImageInfo array
        public IntPtr PBufferInfo; // Pointer to VkDescriptorBufferInfo array
        public IntPtr PTexelBufferView; // Pointer to VkBufferView array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkAttachmentDescription
    {
        public VkAttachmentDescriptionFlags Flags;
        public VkFormat Format;
        public VkSampleCountFlagBits Samples;
        public VkAttachmentLoadOp LoadOp;
        public VkAttachmentStoreOp StoreOp;
        public VkAttachmentLoadOp StencilLoadOp;
        public VkAttachmentStoreOp StencilStoreOp;
        public VkImageLayout InitialLayout;
        public VkImageLayout FinalLayout;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkAttachmentReference
    {
        public uint Attachment;
        public VkImageLayout Layout;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkFramebufferCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkFramebufferCreateFlags Flags;
        public VkRenderPass RenderPass;
        public uint AttachmentCount;
        public IntPtr PAttachments; // Pointer to array of VkImageView
        public uint Width;
        public uint Height;
        public uint Layers;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSubpassDescription
    {
        public VkSubpassDescriptionFlags Flags;
        public VkPipelineBindPoint PipelineBindPoint;
        public uint InputAttachmentCount;
        public IntPtr PInputAttachments; // Pointer to VkAttachmentReference array
        public uint ColorAttachmentCount;
        public IntPtr PColorAttachments; // Pointer to VkAttachmentReference array
        public IntPtr PResolveAttachments; // Pointer to VkAttachmentReference array
        public IntPtr PDepthStencilAttachment; // Pointer to VkAttachmentReference
        public uint PreserveAttachmentCount;
        public IntPtr pPreserveAttachments; // Pointer to array of uint
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSubpassDependency
    {
        public uint SrcSubpass;
        public uint DstSubpass;
        public VkPipelineStageFlags SrcStageMask;
        public VkPipelineStageFlags DstStageMask;
        public VkAccessFlags SrcAccessMask;
        public VkAccessFlags DstAccessMask;
        public VkDependencyFlags DependencyFlags;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkRenderPassCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkRenderPassCreateFlags Flags;
        public uint AttachmentCount;
        public IntPtr PAttachments; // Pointer to VkAttachmentDescription array
        public uint SubpassCount;
        public IntPtr PSubpasses; // Pointer to VkSubpassDescription array
        public uint DependencyCount;
        public IntPtr PDependencies; // Pointer to VkSubpassDependency array
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCommandPoolCreateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkCommandPoolCreateFlags Flags;
        public uint QueueFamilyIndex;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCommandBufferAllocateInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkCommandPool CommandPool;
        public VkCommandBufferLevel Level;
        public uint CommandBufferCount;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCommandBufferInheritanceInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkRenderPass RenderPass;
        public uint Subpass;
        public VkFramebuffer Framebuffer;
        public VkBool32 OcclusionQueryEnable;
        public VkQueryControlFlags QueryFlags;
        public VkQueryPipelineStatisticFlags PipelineStatistics;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkCommandBufferBeginInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkCommandBufferUsageFlags Flags;
        public IntPtr PInheritanceInfo; // Pointer to VkCommandBufferInheritanceInfo
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBufferCopy
    {
        public VkDeviceSize SrcOffset;
        public VkDeviceSize DstOffset;
        public VkDeviceSize Size;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageSubresourceLayers
    {
        public VkImageAspectFlags AspectMask;
        public uint MipLevel;
        public uint BaseArrayLayer;
        public uint LayerCount;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkBufferImageCopy
    {
        public VkDeviceSize BufferOffset;
        public uint BufferRowLength;
        public uint BufferImageHeight;
        public VkImageSubresourceLayers ImageSubresource;
        public VkOffset3D ImageOffset;
        public VkExtent3D ImageExtent;
    }

    [StructLayout(LayoutKind.Explicit)]
    public struct VkClearColorValue
    {
        [FieldOffset(0)] // Define the starting offset for this field
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public float[] Float32;

        [FieldOffset(0)] // Same offset, creating a union-like effect
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public int[] Int32;

        [FieldOffset(0)] // Same offset for uint as well
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public uint[] UInt32;

        public VkClearColorValue(float[] values)
        {
            // Initialize Float32 array
            Float32 = new float[4];
            Array.Copy(values, Float32, Math.Min(values.Length, 4));
            Int32 = null; // Clear other references
            UInt32 = null; // Clear other references
        }

        public VkClearColorValue(int[] values)
        {
            // Initialize Int32 array
            Int32 = new int[4];
            Array.Copy(values, Int32, Math.Min(values.Length, 4));
            Float32 = null; // Clear other references
            UInt32 = null; // Clear other references
        }

        public VkClearColorValue(uint[] values)
        {
            // Initialize UInt32 array
            UInt32 = new uint[4];
            Array.Copy(values, UInt32, Math.Min(values.Length, 4));
            Float32 = null; // Clear other references
            Int32 = null; // Clear other references
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkClearDepthStencilValue
    {
        public float Depth;
        public uint Stencil;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkClearValue
    {
        public VkClearColorValue Color;
        public VkClearDepthStencilValue DepthStencil;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkClearAttachment
    {
        public VkImageAspectFlags AspectMask;
        public uint ColorAttachment;
        public VkClearValue ClearValue;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkClearRect
    {
        public VkRect2D Rect;
        public uint BaseArrayLayer;
        public uint LayerCount;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageBlit
    {
        public VkImageSubresourceLayers SrcSubresource;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public VkOffset3D[] SrcOffsets; // Size is 2
        public VkImageSubresourceLayers DstSubresource;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2)]
        public VkOffset3D[] DstOffsets; // Size is 2
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageCopy
    {
        public VkImageSubresourceLayers SrcSubresource;
        public VkOffset3D SrcOffset;
        public VkImageSubresourceLayers DstSubresource;
        public VkOffset3D DstOffset;
        public VkExtent3D Extent;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageResolve
    {
        public VkImageSubresourceLayers SrcSubresource;
        public VkOffset3D SrcOffset;
        public VkImageSubresourceLayers DstSubresource;
        public VkOffset3D DstOffset;
        public VkExtent3D Extent;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkRenderPassBeginInfo
    {
        public VkStructureType SType;
        public IntPtr PNext;
        public VkRenderPass RenderPass;
        public VkFramebuffer Framebuffer;
        public VkRect2D RenderArea;
        public uint ClearValueCount;
        public IntPtr PClearValues; // Pointer to VkClearValue array
    }

    public struct VkPhysicalDeviceShaderDrawParametersFeatures
    {
        public VkStructureType sType; // Enum representing the structure type
        public IntPtr pNext; // Pointer to the next structure
        public Bool32 shaderDrawParameters; // Similar to above
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Bool32
    {
        public uint value; // 0 for false, 1 for true
        public static implicit operator Bool32(bool b) => new Bool32 { value = b ? 1u : 0u };
        public static implicit operator bool(Bool32 b) => b.value != 0;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSamplerReductionModeCreateInfo
    {
        VkStructureType sType;
        IntPtr pNext;
        VkSamplerReductionMode reductionMode;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceSamplerFilterMinmaxProperties
    {
        VkStructureType sType;
        IntPtr pNext;
        VkBool32 filterMinmaxSingleComponentFormats;
        VkBool32 filterMinmaxImageComponentMapping;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkTransformMatrixKHR
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)] 
        public float[,] matrix;

        public VkTransformMatrixKHR()
        {
            matrix = new float[3, 4];
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkMemoryRequirements2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkMemoryRequirements memoryRequirements;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageMemoryRequirementsInfo2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkImage image;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceProperties2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkPhysicalDeviceProperties properties;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkFormatProperties2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkFormatProperties formatProperties;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkImageFormatProperties2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkImageFormatProperties imageFormatProperties;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceMemoryProperties2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkPhysicalDeviceMemoryProperties memoryProperties;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkSamplerYcbcrConversionCreateInfo
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkFormat format;
        public VkSamplerYcbcrModelConversion ycbcrModel;
        public VkSamplerYcbcrRange ycbcrRange;
        public VkComponentMapping components;
        public VkChromaLocation xChromaOffset;
        public VkChromaLocation yChromaOffset;
        public VkFilter chromaFilter;
        public VkBool32 forceExplicitReconstruction;
    }

    public struct VkSamplerYcbcrConversion { }
    public struct VkDescriptorUpdateTemplate { }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkExternalBufferProperties
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkExternalMemoryProperties externalMemoryProperties;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkExternalFenceProperties
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkExternalFenceHandleTypeFlags exportFromImportedHandleTypes;
        public VkExternalFenceHandleTypeFlags compatibleHandleTypes;
        public VkExternalFenceFeatureFlags externalFenceFeatures;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkExternalSemaphoreProperties
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkExternalSemaphoreHandleTypeFlags exportFromImportedHandleTypes;
        public VkExternalSemaphoreHandleTypeFlags compatibleHandleTypes;
        public VkExternalSemaphoreFeatureFlags externalSemaphoreFeatures;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkDescriptorSetLayoutSupport
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkBool32 supported;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkExternalMemoryProperties
    {
        public VkExternalMemoryFeatureFlags externalMemoryFeatures;
        public VkExternalMemoryHandleTypeFlags exportFromImportedHandleTypes;
        public VkExternalMemoryHandleTypeFlags compatibleHandleTypes;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct VkPhysicalDeviceFeatures2
    {
        public VkStructureType sType;
        public IntPtr pNext;
        public VkPhysicalDeviceFeatures features;
    }
}
