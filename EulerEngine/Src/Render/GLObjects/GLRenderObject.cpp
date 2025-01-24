#include "gkpch.h"
#include"GLRenderObject.h"
namespace EulerEngine {
	/*void RenderObject::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos) {
		shader.use();

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		model = glm::translate(model, transform.position);
		model = glm::scale(model, transform.scale);
		model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
		shader.setMat4("model", model);
		shader.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));

		shader.setVec3("viewPos", viewPos);

		mesh.Draw(shader);
	}
	void RenderObject::setMaterial(int dCnt, EulerDirLight* dLight, int sCnt, EulerSpotLight* sLight, int pCnt, EulerPointLight* pLight) {
		shader.use();
		material.Draw(shader, dCnt, dLight, pCnt, pLight, sCnt, sLight);
	}
	void RenderObject::bindMesh(float* vertices) {
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