#pragma once
#include "VulkanRenderer.h"

struct BufferInfo
{
    VkBuffer* Buffer;
    VkBuffer* StagingBuffer;
    VkDeviceMemory* BufferMemory;
    VkDeviceMemory* StagingBufferMemory;
    VkDeviceSize* BufferSize;
    VkBufferUsageFlags* BufferUsage;
    VkMemoryPropertyFlags* BufferProperties;
    uint64* BufferDeviceAddress;
    VkAccelerationStructureKHR* BufferHandle;
    void** BufferData;
    bool* IsMapped;
};

VkResult Buffer_CreateBuffer(struct BufferInfo* bufferInfo, void* BufferData, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties);
VkResult Buffer_CreateStagingBuffer(struct BufferInfo* bufferInfo, void* bufferData, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags properties);
VkResult Buffer_CopyBuffer(struct BufferInfo* bufferInfo, VkBuffer* srcBuffer, VkBuffer* dstBuffer, VkDeviceSize size);
VkResult Buffer_CopyStagingBuffer(struct BufferInfo* bufferInfo, VkCommandBuffer* commandBuffer, VkBuffer* srcBuffer, VkBuffer* dstBuffer, VkDeviceSize size);
VkResult Buffer_UpdateBufferSize(struct BufferInfo* bufferInfo, VkDeviceSize bufferSize);
VkResult Buffer_UnmapBufferMemory(struct BufferInfo* bufferInfo);
VkResult Buffer_UpdateBufferMemory(struct BufferInfo* bufferInfo, void* DataToCopy, VkDeviceSize BufferSize);
VkResult Buffer_UpdateStagingBufferMemory(struct BufferInfo* bufferInfo, void* DataToCopy, VkDeviceSize BufferSize);

void* Buffer_MapBufferMemory(struct BufferInfo* bufferInfo);
void* Buffer_CheckBufferContents(struct BufferInfo* bufferInfo);
void Buffer_DestroyBuffer(struct BufferInfo* bufferInfo);