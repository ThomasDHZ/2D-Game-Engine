#pragma once
#include <vulkan/vulkan.h>

struct BufferInfo
{
    VkBuffer* Buffer;
    VkDeviceMemory* BufferMemory;
    VkDeviceSize* BufferSize;
    VkBufferUsageFlags* BufferUsage;
    VkMemoryPropertyFlags* BufferProperties;
    uint64_t* BufferDeviceAddress;
    VkAccelerationStructureKHR* BufferHandle;
    void** BufferData;
};

VkResult Buffer_CreateBuffer(struct BufferInfo* bufferInfo, void* BufferData, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties);
VkResult Buffer_CopyBuffer(struct BufferInfo* bufferInfo, VkBuffer* srcBuffer, VkBuffer* dstBuffer, VkDeviceSize* size);
VkResult Buffer_UpdateBufferSize(struct BufferInfo* bufferInfo, VkDeviceSize bufferSize);
void Buffer_UpdateBufferMemory(struct BufferInfo* bufferInfo, void* DataToCopy, VkDeviceSize BufferSize);
void Buffer_DestroyBuffer(struct BufferInfo* bufferInfo);
