#pragma once
extern "C"
{
	#include <Global.h>
	#include <CTexture.h>
	#include <CBuffer.h>
}
#include <memory>
#include "Typedef.h"
#include "VulkanDynamicBuffer.h"
#include "Vertex.h"
#include "Material.h"
#include "Timer.h"
#include "SceneDataBuffer.h"

struct MeshProperitiesStruct
{
	uint32 MeshIndex = 0;
	uint32 MaterialIndex = 0;
	mat4   MeshTransform = mat4(1.0f);
};

typedef VulkanDynamicBuffer<Vertex2D> VertexBuffer;
typedef VulkanDynamicBuffer<uint32> IndexBuffer;
typedef VulkanDynamicBuffer<MeshProperitiesStruct> MeshPropertiesBuffer;

class Mesh
{
	private:
		const VkBufferUsageFlags MeshBufferUsageSettings = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | 
														   VK_BUFFER_USAGE_INDEX_BUFFER_BIT | 
														   VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
														   VK_BUFFER_USAGE_TRANSFER_DST_BIT;

		const VkMemoryPropertyFlags MeshBufferPropertySettings = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
												                 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;


	protected:
public:
		uint64 MeshBufferIndex;
		uint32 VertexCount;
		uint32 IndexCount;

		MeshProperitiesStruct MeshProperties;
		mat4 MeshTransform;
		vec3 MeshPosition;
		vec3 MeshRotation;
		vec3 MeshScale;

		VertexBuffer MeshVertexBuffer;
		IndexBuffer MeshIndexBuffer;
		MeshPropertiesBuffer PropertiesBuffer;

		template<class T>
		void MeshStartUp(List<T>& vertexList, List<uint32>& indexList)
		{
			VertexCount = vertexList.size();
			IndexCount = indexList.size();

			MeshVertexBuffer = VertexBuffer(vertexList.data(), sizeof(T) * VertexCount, MeshBufferUsageSettings, MeshBufferPropertySettings);
			MeshIndexBuffer = IndexBuffer(indexList.data(), sizeof(uint32) * IndexCount, MeshBufferUsageSettings, MeshBufferPropertySettings);
			PropertiesBuffer = MeshPropertiesBuffer(static_cast<void*>(&MeshProperties), sizeof(MeshProperitiesStruct), MeshBufferUsageSettings, MeshBufferPropertySettings);
		}

		Mesh();
		virtual ~Mesh();
		virtual void Update(Timer& timer);
		virtual void BufferUpdate(VkCommandBuffer& commandBuffer);
		virtual void Draw(VkCommandBuffer& commandBuffer, VkPipeline& pipeline, VkPipelineLayout& shaderPipelineLayout, VkDescriptorSet& descriptorSet, SceneDataBuffer& sceneProperties);
		virtual void Destroy();

		MeshPropertiesBuffer* GetMeshPropertiesBuffer() { return &PropertiesBuffer; }
};

