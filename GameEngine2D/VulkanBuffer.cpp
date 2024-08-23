#include "VulkanBuffer.h"

VulkanBuffer::VulkanBuffer()
{
}

VulkanBuffer::VulkanBuffer(void* BufferData, VkDeviceSize BufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
    CreateBuffer(BufferData, BufferSize, usage, properties);
}

VulkanBuffer::~VulkanBuffer()
{
    DestroyBuffer(SendCBufferInfo().get());
}

std::unique_ptr<BufferInfo> VulkanBuffer::SendCBufferInfo()
{
    std::unique_ptr<BufferInfo>  bufferInfo = std::make_unique<BufferInfo>();
    bufferInfo->Buffer = &Buffer;
    bufferInfo->BufferMemory = &BufferMemory;
    bufferInfo->BufferSize = &BufferSize;
    bufferInfo->BufferUsage = &BufferUsage;
    bufferInfo->BufferProperties = &BufferProperties;
    bufferInfo->BufferDeviceAddress = &BufferDeviceAddress;
    bufferInfo->BufferHandle = &BufferHandle;
    bufferInfo->BufferData = &BufferData;
    return bufferInfo;
}

VkResult VulkanBuffer::CreateBuffer(void* BufferData, VkDeviceSize BufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
    return Buffer_CreateBuffer(SendCBufferInfo().get(), BufferData, BufferSize, usage, properties);
}

VkResult VulkanBuffer::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
    return Buffer_CopyBuffer(SendCBufferInfo().get(), &srcBuffer, &dstBuffer, size);
}

void VulkanBuffer::UpdateBufferMemory(void* DataToCopy, VkDeviceSize BufferSize)
{
    Buffer_UpdateBufferMemory(SendCBufferInfo().get(), &DataToCopy, BufferSize);
}

VkResult VulkanBuffer::UpdateBufferSize(VkDeviceSize bufferSize)
{
    return Buffer_UpdateBufferSize(SendCBufferInfo().get(), bufferSize);
}

void VulkanBuffer::DestroyBuffer(BufferInfo* buffer)
{
    Buffer_DestroyBuffer(buffer);
}
