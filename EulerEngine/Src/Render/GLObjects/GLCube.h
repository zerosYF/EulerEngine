#pragma once
#include<glad/glad.h>
#include"../OpenGL/GLTexture.h"
#include"GLLight.h"
#include"../OpenGL/GLTransform.h"
#include"../OpenGL/GLMesh.h"
#include"../OpenGL/GLShader.h"
#include<iostream>
#define CUBE_VERTEX_CNT 36
#define CUBE_DATA_SIZE 8
using namespace std;
namespace EulerEngine {
	extern float vertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};
	enum TextureType {
		DIFFUSE,
		SPECULAR,
	};
	struct LightMaterial {
		float ambient;
		float diffuse;
		float specular;
		float reflectStrength;
	};
	class Cube {
	private:
		EulerTransform transform;
		vector<Texture2D> textures;
		vector<TextureType> textures_type;
		Mesh mesh;
		Shader shader;
		LightMaterial light_material;

	public:
		Cube() {
			light_material.reflectStrength = 32;
			light_material.ambient = 0.1f;
			light_material.diffuse = 0.5f;
			light_material.specular = 1.0f;
			bindMesh();
		}
		void Render(glm::mat4 model,glm::mat4 view,glm::mat4 projection,glm::vec3 viewPos,
			EulerPointLight pLight,EulerDirLight dLight,EulerSpotLight sLight) {
			shader.use();
			bindTexture(shader);

			shader.setMat4("projection",projection);
			shader.setMat4("view",view);
			model = glm::translate(model,transform.position);
			model = glm::scale(model,transform.scale);
			model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0, 0.0, 0.0));
			model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0, 1.0, 0.0));
			model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0, 0.0, 1.0));
			shader.setMat4("model", model);
			shader.setMat3("normalMatrix",glm::transpose(glm::inverse(model)));

			shader.setVec3("viewPos",viewPos);
			setSpotLightRender(shader,sLight);
			setPointLightRender(shader,pLight);
			setDirLightRender(shader,dLight);

			mesh.Draw(shader);
		}
		void setTransform(glm::vec3 pos,glm::vec3 scl,glm::vec3 rot) {
			transform.update(pos,scl,rot);
		}
		void setShader(Shader shader) {
			this->shader = shader;
		}
		void addTexture(Texture2D texture,TextureType type) {
			textures.push_back(texture);
			textures_type.push_back(type);
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
		void bindTexture(Shader shader) {
			unsigned int diffuseNr = 1;
			unsigned int specularNr = 1;
			for (int i = 0; i < textures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				string number;
				TextureType type = textures_type[i];
				if (type == DIFFUSE) {
					number = std::to_string(diffuseNr++);
					shader.setInt(("material.diffuseTex" + number).c_str(), i);
				}
				else if (type == SPECULAR) {
					number = std::to_string(specularNr++);
					shader.setInt(("material.specularTex" + number).c_str(), i);
				}
				glBindTexture(GL_TEXTURE_2D, textures[i].ID);
			}
			shader.setFloat("material.reflectStrength", light_material.reflectStrength);
			glActiveTexture(GL_TEXTURE0);
		}
		void setSpotLightRender(Shader shader,EulerSpotLight light) {
			shader.setVec3("spotLight.ambient", light_material.ambient*light.color);
			shader.setVec3("spotLight.diffuse", light_material.diffuse*light.color);
			shader.setVec3("spotLight.specular", light_material.specular*light.color);

			shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(light.outerCutOff)));
			shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(light.cutOff)));
			shader.setVec3("spotLight.direction",light.direction);
			shader.setVec3("spotLight.position",light.transform.position);

			shader.setFloat("spotLight.constant", light.constant);
			shader.setFloat("spotLight.linear", light.linear);
			shader.setFloat("spotLight.quatratic", light.quatratic);
		}
		void setPointLightRender(Shader shader,EulerPointLight light) {
			shader.setVec3("pointLight.position", light.transform.position);
			shader.setVec3("pointLight.ambient", light_material.ambient*light.color);
			shader.setVec3("pointLight.diffuse", light_material.diffuse*light.color);
			shader.setVec3("pointLight.specular", light_material.specular*light.color);

			shader.setFloat("pointLight.constant", light.constant);
			shader.setFloat("pointLight.linear", light.linear);
			shader.setFloat("pointLight.quatratic", light.quatratic);
		}
		void setDirLightRender(Shader shader,EulerDirLight light) {
			shader.setVec3("dirLight.ambient", light_material.ambient*light.color);
			shader.setVec3("dirLight.diffuse", light_material.diffuse*light.color);
			shader.setVec3("dirLight.specular", light_material.specular*light.color);
			shader.setVec3("dirLight.direction",light.direction);
		}
	};
}