#pragma once
extern "C"
{
	#include <Global.h>
	#include <CTexture.h>
	#include <CBuffer.h>
}
#include <memory>
#include "Typedef.h"
#include "VulkanBuffer.h"
#include <Vertex.h>
#include "Material.h"
#include "Timer.h"

struct MeshProperitiesStruct
{
	uint32 MeshIndex;
	uint32 MaterialIndex;
	mat4   MeshTransform;
};

class Mesh
{
	private:
		const VkBufferUsageFlags MeshBufferUsageSettings = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
														   VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
														   VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
														   VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;

		const VkMemoryPropertyFlags MeshBufferPropertySettings = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
												                 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT |
																 VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT;


	protected:
		uint64 MeshBufferIndex;
		uint32 VertexCount;
		uint32 IndexCount;

		MeshProperitiesStruct MeshProperties;
		mat4 MeshTransform;
		vec3 MeshPosition;
		vec3 MeshRotation;
		vec3 MeshScale;

		VulkanBuffer<std::vector<Vertex2D>> VertexBuffer;
		VulkanBuffer<std::vector<uint32>> IndexBuffer;
		VulkanBuffer<MeshProperitiesStruct> MeshPropertiesBuffer;

		template<class T>
		void MeshStartUp(std::vector<T>& vertexList, std::vector<uint32>& indexList)
		{
			VertexBuffer.CreateBuffer(vertexList, MeshBufferUsageSettings, MeshBufferPropertySettings);
			IndexBuffer.CreateBuffer(indexList, MeshBufferUsageSettings, MeshBufferPropertySettings);
			MeshPropertiesBuffer.CreateBuffer(MeshProperties, MeshBufferUsageSettings, MeshBufferPropertySettings);
		}

	public:
		Mesh();
		virtual ~Mesh();
		virtual void Update(Timer& timer);
		virtual void Draw(VkCommandBuffer& commandBuffer, VkPipelineLayout& shaderPipelineLayout, VkDescriptorSet& descriptorSet);
		virtual void Destroy();

		VulkanBuffer<MeshProperitiesStruct>& GetMeshPropertiesBuffer() { return MeshPropertiesBuffer; }
};

