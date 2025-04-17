#pragma once
#include"gkpch.h"
#include"Math/EulerMath.h"
#include"Render/EulerShader.h"
#include"Render/VertexArray.h"
#include"EulerMaterial.h"
#include"Render/Renderer/RenderCmd.h"
#include<glad/glad.h>
#include"Jolt/Jolt.h"
namespace EulerEngine {
	enum class MeshType {
		None = 0,
		Cube,
		Plane,
		Sphere,
		Model,
	};

	struct NormalVertex {
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec3 Normal;
		int GameObjectID = 0;
	};
	struct SpriteVertex {
		glm::vec3 Position;
		glm::vec2 TexCoord;
		glm::vec4 Color;
		int GameObjectID = 0;
	};
	struct LineVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		int GameObjectID = 0;
	};
	class EulerMesh {
	public:
		EulerMesh() = default;
		EulerMesh(std::vector<float> vertices, std::vector<unsigned int> indices);
		inline void SetVertices(std::vector<float> vertices) { m_Vertices = vertices; }
		inline void SetIndices(std::vector<unsigned int> indices) { m_Indices = indices; }
		inline std::vector<float>& GetVertices() { return m_Vertices; }
		inline std::vector<unsigned int>& GetIndices() { return m_Indices; }

		static MeshType StringToMeshType(std::string type);
		static std::string MeshTypeToString(MeshType type);
	private:
		std::vector<float> m_Vertices;
		std::vector<unsigned int> m_Indices;
	};
}
