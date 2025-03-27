#include "gkpch.h"
#include "EulerMesh.h"
#include<glm/gtx/quaternion.hpp>
namespace EulerEngine {
	EulerMesh::EulerMesh(MeshType type, std::vector<float> vertices, std::vector<unsigned int> indices):
		m_Type(type), m_Vertices(vertices), m_Indices(indices)
	{
	}
}