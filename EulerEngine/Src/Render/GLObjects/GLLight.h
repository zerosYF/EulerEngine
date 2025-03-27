#pragma once
#include"Math/EulerMath.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/EulerShader.h"
#include"Render/RawData/EulerVertices.h"
namespace EulerEngine {
	enum Light_Type {
		POINT_LIGHT,
		DIR_LIGHT,
		SPOT_LIGHT,
	};
	extern float vertices[CUBE_VERTICE_CNT*CUBE_DATA_SIZE];
	class EulerLight {
	public:
		glm::vec3 color{1.0f,1.0f,1.0f};
		Ref<EulerMesh> m_Mesh;
		Ref<EulerShader> m_Shader;
		EulerLight(Ref<EulerShader> shader, Ref<EulerMesh> mesh) :m_Shader(shader), m_Mesh(mesh) {
		}
		void setColor(glm::vec3 color) {this->color = color;}
		void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
		void Release() {
		}
	private:
		void bindMesh();
	};
	class EulerPointLight:public EulerLight{
	public:
		float constant{1.0f};
		float linear{0.09f};
		float quatratic{0.032f};
	public:
		EulerPointLight() = default;
	};
	class EulerDirLight:public EulerLight {
	public:
		glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
		EulerDirLight() = default;
		void setDirection(glm::vec3 dir) {direction = dir;}
	};
	class EulerSpotLight:public EulerPointLight {
	public:
		glm::vec3 direction{ 0.0f, 0.0f, -1.0f };
		float cutOff{12.5f};
		float outerCutOff{15.0f};
		EulerSpotLight() = default;
		void setDirection(glm::vec3 dir) {direction = dir;}
		void setCutOff(float innerCf,float outerCf) {
			cutOff = innerCf;
			outerCutOff = outerCf;
		}
	};
}