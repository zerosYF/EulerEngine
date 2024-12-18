#include "gkpch.h"
#include"GLLight.h"
namespace EulerEngine {
	/*void EulerLight::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
		shader.use();
		shader.setVec3("lightColor", color);

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		model = glm::translate(model, transform.position);
		model = glm::scale(model, transform.scale);
		shader.setMat4("model", model);
		mesh.Draw(shader);
	}
	void EulerLight::bindMesh() {
		std::vector<Vertex> vs;
		std::vector<unsigned int> is;
		for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
			Vertex v;
			v.Position = glm::vec3(vertices[i*CUBE_DATA_SIZE], vertices[i*CUBE_DATA_SIZE + 1], vertices[i*CUBE_DATA_SIZE + 2]);
			v.TexCoords = glm::vec2(vertices[i*CUBE_DATA_SIZE + 3], vertices[i*CUBE_DATA_SIZE + 4]);
			v.Normal = glm::vec3(vertices[i*CUBE_DATA_SIZE + 5], vertices[i*CUBE_DATA_SIZE + 6], vertices[i*CUBE_DATA_SIZE + 7]);
			vs.push_back(v);
		}
		mesh.setupVertex(vs, is);
	}*/
}