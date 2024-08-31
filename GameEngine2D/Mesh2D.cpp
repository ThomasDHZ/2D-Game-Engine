#include "Mesh2D.h"

Mesh2D::Mesh2D() : Mesh()
{
}

Mesh2D::Mesh2D(std::vector<Vertex2D>& vertexList, std::vector<uint32>& indexList) : Mesh()
{
	MeshStartUp<Vertex2D>(vertexList, indexList);
}

Mesh2D::~Mesh2D()
{
}
