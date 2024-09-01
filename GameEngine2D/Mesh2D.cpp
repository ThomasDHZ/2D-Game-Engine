#include "Mesh2D.h"

Mesh2D::Mesh2D() : Mesh()
{
}

Mesh2D::Mesh2D(List<Vertex2D>& vertexList, List<uint32>& indexList) : Mesh()
{
	MeshStartUp<Vertex2D>(vertexList, indexList);
}

Mesh2D::~Mesh2D()
{
}
