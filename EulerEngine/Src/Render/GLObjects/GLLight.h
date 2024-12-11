#pragma once
#include"../../Math/EulerMath.h"
#include"../OpenGL/GLTransform.h"
#include"../OpenGL/GLMesh.h"
#include"../OpenGL/GLShader.h"
#define CUBE_VERTEX_CNT 36
#define CUBE_DATA_SIZE 8
namespace EulerEngine {
	enum Light_Type {
		POINT_LIGHT,
		DIR_LIGHT,
		SPOT_LIGHT,
	};
	extern float vertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE];
	//class EulerLight {
	//public:
	//	glm::vec3 color{1.0f,1.0f,1.0f};
	//	Mesh mesh;
	//	Shader shader;
	//	EulerTransform transform;
	//	EulerLight() {bindMesh();}
	//	void virtual setTransform(glm::vec3 pos, glm::vec3 scl, glm::vec3 rot) {transform.update(pos, scl, rot);}
	//	void setShader(Shader shader) {this->shader = shader;}
	//	void setColor(glm::vec3 color) {this->color = color;}
	//	void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	//	void Release() {
	//	}
	//private:
	//	void bindMesh();
	//};
	//class EulerPointLight:public EulerLight{
	//public:
	//	//Ë¥¼õÏµÊý
	//	float constant{1.0f};
	//	float linear{0.09f};
	//	float quatratic{0.032f};
	//public:
	//	EulerPointLight() = default;
	//};
	//class EulerDirLight:public EulerLight {
	//public:
	//	glm::vec3 direction;
	//	EulerDirLight() {
	//		direction = glm::vec3(1.0f,0.0f,0.0f);
	//	}
	//	void setDirection(glm::vec3 dir) {direction = dir;}
	//};
	//class EulerSpotLight:public EulerPointLight {
	//public:
	//	glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
	//	float cutOff{12.5f};
	//	float outerCutOff{15.0f};
	//	EulerSpotLight() = default;
	//	void setDirection(glm::vec3 dir) {direction = dir;}
	//	void setCutOff(float innerCf,float outerCf) {
	//		cutOff = innerCf;
	//		outerCutOff = outerCf;
	//	}
	//};
}