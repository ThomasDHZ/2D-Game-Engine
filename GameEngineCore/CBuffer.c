#include "CBuffer.h"
#include "Global.h"

static VkResult Buffer_AllocateMemory(struct BufferInfo* bufferInfo, VkMemoryPropertyFlags properties)
{
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(global.Renderer.Device, *bufferInfo->Buffer, &memRequirements);

    VkMemoryAllocateFlagsInfoKHR ExtendedAllocFlagsInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR,
        .flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR
    };
    VkMemoryAllocateInfo allocInfo =
    {
        .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .allocationSize = memRequirements.size,
        .memoryTypeIndex = Renderer_GetMemoryType(memRequirements.memoryTypeBits, properties),
        .pNext = &ExtendedAllocFlagsInfo,
    };
    if (vkAllocateMemory(global.Renderer.Device, &allocInfo, NULL, bufferInfo->BufferMemory) != VK_SUCCESS)
    {
        return VK_ERROR_OUT_OF_DEVICE_MEMORY;
    }
}

VkResult Buffer_CreateBuffer(struct BufferInfo* bufferInfo, void* BufferData, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties) 
{
    *bufferInfo->BufferSize = bufferSize;           
    *bufferInfo->BufferUsage = bufferUsage;
    *bufferInfo->BufferProperties = properties;
    *bufferInfo->Buffer = BufferData; 

    VkBufferCreateInfo buffer = 
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = bufferSize,
        .usage = bufferUsage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VkResult result = vkCreateBuffer(global.Renderer.Device, &buffer, NULL, bufferInfo->Buffer);
    if (result != VK_SUCCESS) 
    {
        return result;
    }

    result = Buffer_AllocateMemory(bufferInfo, properties);
    if (result != VK_SUCCESS)
    {
        return VK_ERROR_OUT_OF_DEVICE_MEMORY;
    }

    if (BufferData != NULL) 
    {
        vkMapMemory(global.Renderer.Device, *bufferInfo->BufferMemory, 0, *bufferInfo->BufferSize, 0, bufferInfo->BufferData);
        memcpy(*bufferInfo->BufferData, BufferData, (size_t)*bufferInfo->BufferSize);
        vkUnmapMemory(global.Renderer.Device, *bufferInfo->BufferMemory);
    }

    vkBindBufferMemory(global.Renderer.Device, *bufferInfo->Buffer, *bufferInfo->BufferMemory, 0);
    return vkMapMemory(global.Renderer.Device, *bufferInfo->BufferMemory, 0, *bufferInfo->BufferSize, 0, bufferInfo->BufferData);
}

VkResult Buffer_CopyBuffer(struct BufferInfo* bufferInfo, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    VkBufferCopy copyRegion = 
    {
        .size = size
    };
    VkCommandBuffer commandBuffer = Renderer_BeginSingleUseCommandBuffer();
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
    return Renderer_EndSingleUseCommandBuffer(&commandBuffer);
}

VkResult Buffer_UpdateBufferSize(struct BufferInfo* bufferInfo, VkDeviceSize bufferSize)
{
    *bufferInfo->BufferSize = bufferSize;
    Buffer_DestroyBuffer(bufferInfo);

    VkBufferCreateInfo buffer = 
    {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = *bufferInfo->BufferSize,
        .usage = *bufferInfo->BufferUsage,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE
    };
    VkResult result = vkCreateBuffer(global.Renderer.Device, &buffer, NULL, bufferInfo->Buffer);
    if (result != VK_SUCCESS)
    {
        return result;
    }

    result = Buffer_AllocateMemory(bufferInfo, *bufferInfo->BufferProperties);
    if (result != VK_SUCCESS)
    {
        return VK_ERROR_OUT_OF_DEVICE_MEMORY;
    }

    vkBindBufferMemory(global.Renderer.Device, bufferInfo->Buffer, bufferInfo->BufferMemory, 0);
    return vkMapMemory(global.Renderer.Device, bufferInfo->BufferMemory, 0, bufferInfo->BufferSize, 0, &bufferInfo->BufferData);
}

void Buffer_UpdateBufferMemory(void* dataBuffer, void* DataToCopy, VkDeviceSize BufferSize)
{
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