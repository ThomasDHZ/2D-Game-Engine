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

typedef VulkanBuffer<List<Vertex2D>> VertexBuffer;
typedef VulkanBuffer<List<uint32>> IndexBuffer;
typedef VulkanBuffer<MeshProperitiesStruct> MeshPropertiesBuffer;

class Mesh
{
	private:
		const VkBufferUsageFlags MeshBufferUsageSettings = 
														   VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
														   VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
														   VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;

		const VkMemoryPropertyFlags MeshBufferPropertySettings = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
												                 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;


	protected:
		uint64 MeshBufferIndex;
		uint32 VertexCount;
		uint32 IndexCount;

		MeshProperitiesStruct MeshProperties;
		mat4 MeshTransform;
		vec3 MeshPosition;
		vec3 MeshRotation;
		vec3 MeshScale;

		std::shared_ptr<VertexBuffer> MeshVertexBuffer;
		std::shared_ptr<IndexBuffer> MeshIndexBuffer;
		std::shared_ptr<MeshPropertiesBuffer> PropertiesBuffer;

		template<class T>
		void MeshStartUp(List<T>& vertexList, List<uint32>& indexList)
		{
			MeshVertexBuffer = std::make_shared<VertexBuffer>(vertexList, MeshBufferUsageSettings, MeshBufferPropertySettings);
			MeshIndexBuffer = std::make_shared<IndexBuffer>(indexList, MeshBufferUsageSettings, MeshBufferPropertySettings);
			PropertiesBuffer = std::make_shared<MeshPropertiesBuffer>(MeshProperties, MeshBufferUsageSettings, MeshBufferPropertySettings);
		}

	public:
		Mesh();
		virtual ~Mesh();
		virtual void Update(Timer& timer);
		virtual void Draw(VkCommandBuffer& commandBuffer, VkPipelineLayout& shaderPipelineLayout, VkDescriptorSet& descriptorSet);
		virtual void Destroy();

		MeshPropertiesBuffer* GetMeshPropertiesBuffer() { return PropertiesBuffer.get(); }
};

