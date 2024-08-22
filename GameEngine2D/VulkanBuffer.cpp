#include "VulkanBuffer.h"

BufferInfo* VulkanBuffer::SendCBufferInfo()
{
	BufferInfo bufferInfo =
	{
		.Buffer = &Buffer,
		.BufferMemory = &BufferMemory,
		.BufferSize = &BufferSize,
		.BufferUsage = &BufferUsage,
		.BufferProperties = &BufferProperties,
		.BufferDeviceAddress = &BufferDeviceAddress,
		.BufferHandle = &BufferHandle,
		.BufferData = &BufferData
	};

	return &bufferInfo;
}

VulkanBuffer::VulkanBuffer()
{
}

VulkanBuffer::VulkanBuffer(void* BufferData, VkDeviceSize BufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
	Buffer_CreateBuffer(SendCBufferInfo(), BufferData, BufferSize, usage, properties);
}

VulkanBuffer::~VulkanBuffer()
{
}
