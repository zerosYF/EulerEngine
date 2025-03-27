#include "gkpch.h"
#include"GLLight.h"
#include"Math/EulerMath.h"
#include"Render/RawData/EulerMesh.h"
namespace EulerEngine {
	void EulerLight::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
		m_Shader->Bind();
		m_Shader->SetVec3("lightColor", color);

		m_Shader->SetMat4("projection", projection);
		m_Shader->SetMat4("view", view);
		m_Shader->SetMat4("model", model);
	}
}