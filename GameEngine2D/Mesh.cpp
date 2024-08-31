#include "Mesh.h"
#include "SceneDataBuffer.h"

Mesh::Mesh()
{
	MeshBufferIndex = 0;
	MeshTransform = mat4(1.0f);
	MeshPosition = vec3(0.0f);
	MeshRotation = vec3(0.0f);
	MeshScale = vec3(1.0f);

	VertexCount = 0;
	IndexCount = 0;
}

Mesh::~Mesh()
{
}

void Mesh::Update(Timer& timer)
{
	mat4 MeshMatrix = mat4(1.0f);
	MeshMatrix = glm::translate(MeshMatrix, MeshPosition);
	MeshMatrix = glm::rotate(MeshMatrix, glm::radians(MeshRotation.x), vec3(1.0f, 0.0f, 0.0f));
	MeshMatrix = glm::rotate(MeshMatrix, glm::radians(MeshRotation.y), vec3(0.0f, 1.0f, 0.0f));
	MeshMatrix = glm::rotate(MeshMatrix, glm::radians(MeshRotation.z), vec3(0.0f, 0.0f, 1.0f));
	MeshMatrix = glm::scale(MeshMatrix, MeshScale);

	MeshProperties.MeshIndex = 0;
	MeshProperties.MaterialIndex = 0;
	MeshProperties.MeshTransform = MeshTransform;
	MeshPropertiesBuffer.UpdateBufferData(MeshProperties);
}

void Mesh::Draw(VkCommandBuffer& commandBuffer, VkPipelineLayout& shaderPipelineLayout, VkDescriptorSet& descriptorSet)
{
	VkDeviceSize offsets[] = { 0 };
	vkCmdPushConstants(commandBuffer, shaderPipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(SceneProperties), &SceneProperties);
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &VertexBuffer.Buffer, offsets);
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, shaderPipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
	vkCmdBindIndexBuffer(commandBuffer, IndexBuffer.Buffer, 0, VK_INDEX_TYPE_UINT32);
	vkCmdDrawIndexed(commandBuffer, IndexCount, 1, 0, 0, 0);
}

void Mesh::Destroy()
{
	VertexBuffer.DestroyBuffer();
	IndexBuffer.DestroyBuffer();
	MeshPropertiesBuffer.DestroyBuffer();
}
