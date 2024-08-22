#include "Buffer.h"
#include "Global.h"

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
		//throw std::runtime_error("Failed to create buffer.");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(global.Renderer.Device, bufferInfo->Buffer, &memRequirements);

	VkMemoryAllocateFlagsInfoKHR ExtendedAllocFlagsInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO_KHR,
		.flags = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT_KHR
	};

	VkMemoryAllocateInfo allocInfo = 
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = memRequirements.size,
		.memoryTypeIndex = Renderer_GetMemoryType(memRequirements.memoryTypeBits, bufferInfo->BufferProperties),
		.pNext = &ExtendedAllocFlagsInfo,
	};

	if (vkAllocateMemory(global.Renderer.Device, &allocInfo, NULL, &bufferInfo->BufferMemory) != VK_SUCCESS)
	{
		//throw std::runtime_error("Failed to allocate buffer memory.");
	}

	if (BufferData != NULL)
	{
		vkMapMemory(global.Renderer.Device, bufferInfo->BufferMemory, 0, bufferInfo->BufferSize, 0, &bufferInfo->BufferData);
		memcpy(bufferInfo->BufferData, BufferData, (size_t)bufferInfo->BufferSize);
		vkUnmapMemory(global.Renderer.Device, bufferInfo->BufferMemory);
	}

	vkBindBufferMemory(global.Renderer.Device, bufferInfo->Buffer, bufferInfo->BufferMemory, 0);
	return vkMapMemory(global.Renderer.Device, bufferInfo->BufferMemory, 0, bufferInfo->BufferSize, 0, &bufferInfo->BufferData);
}

VkResult Buffer_CopyBuffer(struct BufferInfo* bufferInfo, VkBuffer* srcBuffer, VkBuffer* dstBuffer, VkDeviceSize* size)
{
	return VK_RESULT_MAX_ENUM;
}

VkResult Buffer_UpdateBufferSize(struct BufferInfo* bufferInfo, VkDeviceSize* bufferSize)
{
	return VK_RESULT_MAX_ENUM;
}


void Buffer_UpdateBufferMemory(struct BufferInfo* bufferInfo, void* DataToCopy, VkDeviceSize BufferSize)
{
}

void Buffer_DestroyBuffer(struct BufferInfo* bufferInfo)
{

}