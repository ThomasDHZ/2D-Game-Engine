#include "CBuffer.h"
#include "Global.h"

static VkResult Buffer_AllocateMemory(struct BufferInfo* bufferInfo, VkMemoryPropertyFlags properties)
{
    if (bufferInfo->BufferData == NULL)
    {
        RENDERER_ERROR("Buffer Data is NULL");
        return VK_ERROR_MEMORY_MAP_FAILED;
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(global.Renderer.Device, *bufferInfo->Buffer, &memRequirements);

    VkMemoryAllocateFlagsInfoKHR ExtendedAllocFlagsInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR
    };
    VkMemoryAllocateInfo allocInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = Renderer_GetMemoryType(memRequirements.memoryTypeBits, properties),
        .pNext = &ExtendedAllocFlagsInfo,
    };

    return vkAllocateMemory(global.Renderer.Device, &allocInfo, NULL, bufferInfo->BufferMemory);
}

VkResult Buffer_CreateBuffer(struct BufferInfo* bufferInfo, void* bufferData, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties)
{
    if (bufferData == NULL ||
        bufferSize == 0)
    {
        RENDERER_ERROR("Buffer Data and Size can't be NULL");
        return VK_ERROR_MEMORY_MAP_FAILED;
    }

    *bufferInfo->BufferSize = bufferSize;
    *bufferInfo->BufferUsage = bufferUsage;
    *bufferInfo->BufferProperties = properties;
    *bufferInfo->Buffer = bufferData;

    VkBufferCreateInfo buffer =
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = bufferSize,
        .usage = bufferUsage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VULKAN_RESULT(vkCreateBuffer(global.Renderer.Device, &buffer, NULL, bufferInfo->Buffer));
    VULKAN_RESULT(Buffer_AllocateMemory(bufferInfo, properties));

    if (bufferData != NULL)
    {
        VULKAN_RESULT(vkMapMemory(global.Renderer.Device, *bufferInfo->BufferMemory, 0, *bufferInfo->BufferSize, 0, bufferInfo->BufferData));
        memcpy(*bufferInfo->BufferData, bufferData, (size_t)*bufferInfo->BufferSize);
        vkUnmapMemory(global.Renderer.Device, *bufferInfo->BufferMemory);
    }

    VULKAN_RESULT(vkBindBufferMemory(global.Renderer.Device, *bufferInfo->Buffer, *bufferInfo->BufferMemory, 0));
    return vkMapMemory(global.Renderer.Device, *bufferInfo->BufferMemory, 0, *bufferInfo->BufferSize, 0, bufferInfo->BufferData);
}

VkResult Buffer_CopyBuffer(struct BufferInfo* bufferInfo, VkBuffer* srcBuffer, VkBuffer* dstBuffer, VkDeviceSize size)
{
    if (srcBuffer == NULL)
    {
        RENDERER_ERROR("Source Buffer is NULL");
        return VK_ERROR_MEMORY_MAP_FAILED;
    }

    VkBufferCopy copyRegion =
    {
        .srcOffset = 0,
        .dstOffset = 0,
        .size = size
    };
    VkCommandBuffer commandBuffer = Renderer_BeginSingleUseCommandBuffer();
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    return Renderer_EndSingleUseCommandBuffer(&commandBuffer);
}

VkResult Buffer_UpdateBufferSize(struct BufferInfo* bufferInfo, VkDeviceSize bufferSize)
{
    if (bufferInfo->BufferSize < bufferSize)
    {
        RENDERER_ERROR("New buffer size can't be less than the old buffer size.");
        return VK_ERROR_MEMORY_MAP_FAILED;
    }

    bufferInfo->BufferSize = bufferSize;
    Buffer_DestroyBuffer(bufferInfo);

    VkBufferCreateInfo buffer =
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = bufferInfo->BufferSize,
        .usage = bufferInfo->BufferUsage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VULKAN_RESULT(vkCreateBuffer(global.Renderer.Device, &buffer, NULL, &bufferInfo->Buffer));
    VULKAN_RESULT(Buffer_AllocateMemory(bufferInfo, bufferInfo->BufferProperties));
    VULKAN_RESULT(vkBindBufferMemory(global.Renderer.Device, bufferInfo->Buffer, bufferInfo->BufferMemory, 0));
    return vkMapMemory(global.Renderer.Device, bufferInfo->BufferMemory, 0, bufferInfo->BufferSize, 0, &bufferInfo->BufferData);
}

void Buffer_UpdateBufferMemory(void* dataBuffer, void* DataToCopy, VkDeviceSize BufferSize)
{
    if (DataToCopy == NULL ||
        BufferSize == 0)
    {
        RENDERER_ERROR("Buffer Data and Size can't be NULL");
        return VK_ERROR_MEMORY_MAP_FAILED;
    }
    memcpy(dataBuffer, DataToCopy, (size_t)BufferSize);
}

void Buffer_DestroyBuffer(struct BufferInfo* bufferInfo)
{
    *bufferInfo->BufferSize = 0;
    *bufferInfo->BufferUsage = 0;
    *bufferInfo->BufferProperties = 0;
    *bufferInfo->BufferData = VK_NULL_HANDLE;
    Renderer_DestroyBuffer(bufferInfo->Buffer);
    Renderer_FreeMemory(bufferInfo->BufferMemory);
}