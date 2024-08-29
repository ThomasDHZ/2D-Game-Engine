#include "Mesh.h"

Mesh::Mesh()
{
	std::vector<Vertex2D> vertex2D;
	std::vector<uint32> IndiceData;

	MeshTransform = mat4(1.0f);
	MeshPosition = vec3(0.0f);
	MeshRotation = vec3(0.0f);
	MeshScale = vec3(1.0f);

	VertexBuffer->CreateBuffer(vertex2D, MeshBufferUsageSettings, MeshBufferPropertySettings);
	IndexBuffer->CreateBuffer(IndiceData, MeshBufferUsageSettings, MeshBufferPropertySettings);
	TransformBuffer->CreateBuffer(MeshTransform, MeshBufferUsageSettings, MeshBufferPropertySettings);
	MeshPropertiesBuffer->CreateBuffer(MeshProperties, MeshBufferUsageSettings, MeshBufferPropertySettings);
}

Mesh::~Mesh()
{
}

void Mesh::Update()
{
}
