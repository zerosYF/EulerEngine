#pragma once
#include"../../Math/EulerMath.h"
#include"../OpenGL/GLTransform.h"
#include"../OpenGL/GLMesh.h"
#include"../OpenGL/GLShader.h"
#include"GLCube.h"
#define CUBE_VERTEX_CNT 36
#define CUBE_DATA_SIZE 8
namespace EulerEngine {
	extern float vertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE];
	class EulerLight {
	public:
		glm::vec3 color;
		Mesh mesh;
		Shader shader;
		EulerTransform transform;
		EulerLight() {
			color = glm::vec3(1.0f);
			bindMesh();
		}
		void setTransform(glm::vec3 pos, glm::vec3 scl, glm::vec3 rot) {
			transform.update(pos, scl, rot);
		}
		void setShader(Shader shader) {
			this->shader = shader;
		}
		void setColor(glm::vec3 color) {
			this->color = color;
		}
		void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
			shader.use();
			shader.setVec3("lightColor", color);

			shader.setMat4("projection", projection);
			shader.setMat4("view", view);
			model = glm::translate(model, transform.position);
			model = glm::scale(model, transform.scale);
			shader.setMat4("model", model);
			mesh.Draw(shader);
		}
		void Release() {
		}
	private:
		void bindMesh() {
			vector<Vertex> vs;
			vector<unsigned int> is;
			for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
				Vertex v;
				v.Position = glm::vec3(vertices[i*CUBE_DATA_SIZE], vertices[i*CUBE_DATA_SIZE + 1], vertices[i*CUBE_DATA_SIZE + 2]);
				v.TexCoords = glm::vec2(vertices[i*CUBE_DATA_SIZE + 3], vertices[i*CUBE_DATA_SIZE + 4]);
				v.Normal = glm::vec3(vertices[i*CUBE_DATA_SIZE + 5], vertices[i*CUBE_DATA_SIZE + 6], vertices[i*CUBE_DATA_SIZE + 7]);
				vs.push_back(v);
			}
			mesh.setupVertex(vs, is);
		}
	};
	class EulerPointLight:public EulerLight{
	public:
		//˥��ϵ��
		float constant;
		float linear;
		float quartric;
	public:
		EulerPointLight() {

		}
	};
	class EulerParallelLight:public EulerLight {
	public:
		glm::vec3 direction;
		EulerParallelLight() {
		}
	};
}