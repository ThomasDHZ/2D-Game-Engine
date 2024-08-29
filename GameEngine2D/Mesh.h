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
	mat4   Projection;
	mat4   View;
	float  Timer;
};

class Mesh
{
	private:
		const VkBufferUsageFlags MeshBufferUsageSettings = VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
														   VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
														   VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
														   VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;

		const VkMemoryPropertyFlags MeshBufferPropertySettings = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
												                 VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

		uint64 MeshBufferIndex;
		std::unique_ptr<VulkanBuffer<std::vector<Vertex2D>>> VertexBuffer;
		std::unique_ptr<VulkanBuffer<std::vector<uint32>>> IndexBuffer;
		std::unique_ptr<VulkanBuffer<mat4>> TransformBuffer;
		std::unique_ptr<VulkanBuffer<MeshProperitiesStruct>> MeshPropertiesBuffer;

	protected:

		MeshProperitiesStruct MeshProperties;
		mat4 MeshTransform;
		vec3 MeshPosition;
		vec3 MeshRotation;
		vec3 MeshScale;

	public:

		Mesh();
		virtual ~Mesh();

		void Update();
};

