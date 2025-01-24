#pragma once
//#include<glad/glad.h>
//#include"../OpenGL/GLTexture.h"
//#include"GLLight.h"
//#include"../OpenGL/GLTransform.h"
//#include"../OpenGL/GLMesh.h"
//#include"../OpenGL/GLShader.h"
//#include"../OpenGL/GLMaterial.h"
//#include"../OpenGL/GLMaterial.h"
//#include<iostream>
//namespace EulerEngine {
//	class Material;
//	class EulerDirLight;
//	class EulerSpotLight;
//	class EulerPointLight;
//	extern float vertices[];
//	extern float SquareVertices[];
//	class RenderObject {
//	private:
//		EulerTransform transform;
//		Mesh mesh;
//		Shader shader;
//		Material material;
//
//	public:
//		RenderObject(float* vertices) {
//			bindMesh(vertices);
//		}
//		/*void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 viewPos);
//		void setTransform(glm::vec3 pos,glm::vec3 scl,glm::vec3 rot) {transform.update(pos,scl,rot);}*/
//		void setShader(Shader shader) {this->shader = shader;}
//		void setMaterial(int dCnt, EulerDirLight* dLight, int sCnt, EulerSpotLight* sLight, int pCnt, EulerPointLight* pLight);
//		void addTexture(Texture2D texture,TextureType type) {material.addTexture(texture,type);}
//		void Release() {}
//	private:
//		void bindMesh(float* vertices);
//	};
//}