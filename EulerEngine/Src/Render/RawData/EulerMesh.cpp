#include "gkpch.h"
#include "EulerMesh.h"
#include<glm/gtx/quaternion.hpp>
namespace EulerEngine {
	EulerMesh::EulerMesh(std::vector<float> vertices, std::vector<unsigned int> indices):
		m_Vertices(vertices), m_Indices(indices)
	{
	}
	std::string EulerMesh::MeshTypeToString(MeshType type) {
		switch (type) {
		case MeshType::None:
			return "None";
		case MeshType::Cube:
			return "Cube";
		case MeshType::Sphere:
			return "Sphere";
		case MeshType::Plane:
			return "Plane";
		case MeshType::Model:
			return "Model";
		default:
			return "Unknown";
		}
	}
	MeshType EulerMesh::StringToMeshType(std::string type) {
		if (type == "None") {
			return MeshType::None;
		}
		else if (type == "Cube") {
			return MeshType::Cube;
		}
		else if (type == "Sphere") {
			return MeshType::Sphere;
		}
		else if (type == "Plane") {
			return MeshType::Plane;
		}
		else if (type == "Model") {
			return MeshType::Model;
		}
		else {
			return MeshType::None;
		}
	}
}