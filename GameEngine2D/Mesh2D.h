#pragma once
#include "Mesh.h"

class Mesh2D : public Mesh
{
private:
protected:
public:
	Mesh2D();
	Mesh2D(List<Vertex2D>& vertexList, List<uint32>& indexList);
	virtual ~Mesh2D();

	Mesh2D& operator=(Mesh2D&& other) noexcept {
		if (this != &other) 
		{
			MeshVertexBuffer = std::move(other.MeshVertexBuffer);
			MeshIndexBuffer = std::move(other.MeshIndexBuffer);
			PropertiesBuffer = std::move(other.PropertiesBuffer);

			MeshBufferIndex = other.MeshBufferIndex;
		}
		return *this;
	}
};

