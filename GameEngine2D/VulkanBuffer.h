#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
	#include <Buffer.h>
}

class VulkanBuffer
{
	private:
		VkDeviceMemory BufferMemory = VK_NULL_HANDLE;
		VkDeviceSize BufferSize = 0;
		VkBufferUsageFlags BufferUsage;
		VkMemoryPropertyFlags BufferProperties;
		uint64_t BufferDeviceAddress = 0;
		VkAccelerationStructureKHR BufferHandle = VK_NULL_HANDLE;
		void* BufferData;

		BufferInfo* SendCBufferInfo();

	public:
		VkBuffer Buffer = VK_NULL_HANDLE;

		VulkanBuffer();
		VulkanBuffer(void* BufferData, VkDeviceSize BufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
		~VulkanBuffer();

		VkBuffer GetBuffer() { return Buffer; }
		VkBuffer* GetBufferPtr() { return &Buffer; }
		VkDeviceMemory GetBufferMemory() { return BufferMemory; }
		VkDeviceMemory* GetBufferMemoryPtr() { return &BufferMemory; }
		VkDeviceSize GetBufferSize() { return BufferSize; }
		uint64_t GetBufferDeviceAddress() { return BufferDeviceAddress; }
		VkAccelerationStructureKHR GetBufferHandle() { return BufferHandle; }
		VkAccelerationStructureKHR* GetBufferHandlePtr() { return &BufferHandle; }
		void* GetData() { return BufferData; }
		template<class T> T* DataView() { return ((T*)BufferData); }
};

