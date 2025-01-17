#include "gkpch.h"
#include"GLLight.h"
#include"Math/EulerMath.h"
#include"../EulerMesh.h"
namespace EulerEngine {
	void EulerLight::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
		m_Shader.Bind();
		m_Shader.setVec3("lightColor", color);

		m_Shader.setMat4("projection", projection);
		m_Shader.setMat4("view", view);
		model = glm::translate(model, transform.position);
		model = glm::scale(model, transform.scale);
		m_Shader.setMat4("model", model);
		m_Mesh.Draw();
	}
	void EulerLight::bindMesh() {
		std::vector<Mesh::Vertex> vs;
		std::vector<unsigned int> is;
		for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
			Mesh::Vertex v;
			v.Position = glm::vec3(vertices[i*CUBE_DATA_SIZE], vertices[i*CUBE_DATA_SIZE + 1], vertices[i*CUBE_DATA_SIZE + 2]);
			v.TexCoords = glm::vec2(vertices[i*CUBE_DATA_SIZE + 3], vertices[i*CUBE_DATA_SIZE + 4]);
			v.Normal = glm::vec3(vertices[i*CUBE_DATA_SIZE + 5], vertices[i*CUBE_DATA_SIZE + 6], vertices[i*CUBE_DATA_SIZE + 7]);
			vs.push_back(v);
		}
		m_Mesh.setupVertex(vs, is);
	}
}