#pragma once
extern "C"
{
	#include <Global.h>
	#include <VulkanRenderer.h>
	#include <CBuffer.h>
}
#include <iostream>
#include <memory>
#include <vector>
#include "Typedef.h"

template <class T>
class VulkanBuffer
{
	private:
		VkDeviceMemory BufferMemory = VK_NULL_HANDLE;
		VkDeviceSize BufferSize = 0;
		VkBufferUsageFlags BufferUsage;
		VkMemoryPropertyFlags BufferProperties;
		uint64 BufferDeviceAddress = 0;
		VkAccelerationStructureKHR BufferHandle = VK_NULL_HANDLE;
		void* BufferData;

		std::unique_ptr<BufferInfo> SendCBufferInfo()
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

		VkResult UpdateBufferSize(VkDeviceSize bufferSize)
		{
			BufferSize = bufferSize;
			return Buffer_UpdateBufferSize(SendCBufferInfo().get(), bufferSize);
		}

	public:
		VkBuffer Buffer = VK_NULL_HANDLE;

		VulkanBuffer()
		{
		}

		VulkanBuffer(T& bufferData, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
		{
			BufferData = static_cast<void*>(&bufferData);
			CreateBuffer(bufferData, usage, properties);
		}

		VulkanBuffer(List<T>& bufferData, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
		{
			BufferData = static_cast<void*>(&bufferData);
			CreateBuffer(bufferData, usage, properties);
		}

		VulkanBuffer(void* bufferData, uint32 bufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
		{
			BufferData = bufferData;
			CreateBuffer(bufferData, bufferSize, usage, properties);
		}

		virtual ~VulkanBuffer()
		{
		}

		VkResult CreateBuffer(T& bufferData, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
		{
			return Buffer_CreateBuffer(SendCBufferInfo().get(), &bufferData, sizeof(T), usage, properties);
		}

		VkResult CreateBuffer(List<T>& bufferData, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
		{
			return Buffer_CreateBuffer(SendCBufferInfo().get(), bufferData.data(), sizeof(T) * bufferData.size(), usage, properties);
		}

		VkResult CreateBuffer(void* bufferData, uint32 bufferSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
		{
			return Buffer_CreateBuffer(SendCBufferInfo().get(), bufferData, bufferSize, usage, properties);
		}

		void UpdateBufferData(T& bufferData)
		{
			if (BufferSize < sizeof(T))
			{
				RENDERER_ERROR("Buffer does not contain enough data for a single T object.");
			}
			Buffer_UpdateBufferMemory(SendCBufferInfo().get(), &bufferData, BufferSize);
		}

		void UpdateBufferData(List<T>& bufferData)
		{
			if (BufferSize != sizeof(T) * bufferData.size())
			{
				UpdateBufferSize(sizeof(T) * bufferData.size());
			}
			Buffer_UpdateBufferMemory(SendCBufferInfo().get(), &bufferData, BufferSize);
		}

		void UpdateBufferData(void* bufferData, uint32 bufferSize)
		{
			if (BufferSize != bufferSize)
			{
				UpdateBufferSize(bufferSize);
			}
			Buffer_UpdateBufferMemory(SendCBufferInfo().get(), &bufferData, BufferSize);
		}

		T ViewBufferData()
		{
			if (BufferSize < sizeof(T)) 
			{
				RENDERER_ERROR("Buffer does not contain enough data for a single T object.");
			}
			return *static_cast<T*>(BufferData);
		}

		List<T> ViewListBufferData()
		{
			const size_t elementCount = BufferSize / sizeof(T);
			List<T> dataArray(elementCount);
			std::memcpy(dataArray.data(), BufferData, BufferSize);
			return dataArray;
		}

		void DestroyBuffer()
		{
			Buffer_DestroyBuffer(SendCBufferInfo().get());
		}

		VkBuffer GetBuffer() { return Buffer; }
		VkBuffer* GetBufferPtr() { return &Buffer; }
		VkDeviceMemory GetBufferMemory() { return BufferMemory; }
		VkDeviceMemory* GetBufferMemoryPtr() { return &BufferMemory; }
		VkDeviceSize GetBufferSize() { return BufferSize; }
		uint64 GetBufferDeviceAddress() { return BufferDeviceAddress; }
		VkAccelerationStructureKHR GetBufferHandle() { return BufferHandle; }
		VkAccelerationStructureKHR* GetBufferHandlePtr() { return &BufferHandle; }
};

