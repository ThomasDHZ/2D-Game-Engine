#pragma once
#include "Mesh.h"

class Mesh2D : public Mesh
{
private:
protected:
public:
	Mesh2D();
	Mesh2D(std::vector<Vertex2D>& vertexList, std::vector<uint32>& indexList);
	virtual ~Mesh2D();

	Mesh2D& operator=(Mesh2D&& other) noexcept {
		if (this != &other) {
			// Release any resources before moving
			VertexBuffer = std::move(other.VertexBuffer);
			IndexBuffer = std::move(other.IndexBuffer);
			MeshPropertiesBuffer = std::move(other.MeshPropertiesBuffer);

			// Copy other data...
			MeshBufferIndex = other.MeshBufferIndex;
		}
		return *this;
	}
};

