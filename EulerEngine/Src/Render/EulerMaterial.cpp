#include"gkpch.h"
#include"EulerMaterial.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	Ref<EulerMaterial> EulerMaterial::Create()
	{
		return CreateRef<EulerMaterial>();
	}

	EulerMaterial::EulerMaterial() {
		m_Color = glm::vec4(1.0f);
	}
	void EulerMaterial::SetShader(Ref<EulerShader> shader)
	{
		m_Shader = shader;
	}
	void EulerMaterial::SetTexture(Ref<Texture2D> texture) {
		m_Texture = texture;
	}

	void EulerMaterial::SetColor(glm::vec4 color)
	{
		m_Color = color;
	}

	void EulerMaterial::AddFloatParam(std::string& name, float param)
	{
		m_Paramters[name] = param;
	}

	Ref<EulerShader> EulerMaterial::GetShader() const
	{
		return m_Shader;
	}

	glm::vec4& EulerMaterial::GetColor()
	{
		return m_Color;
	}

	Ref<Texture2D>& EulerMaterial::GetTexture()
	{
		return m_Texture;
	}

	float EulerMaterial::GetFloatParam(const std::string & name) const
	{
		auto it = m_Paramters.find(name);
		return it != m_Paramters.end() ? it->second : 0;
	}

	void EulerMaterial::Apply(int texture_slot) const
	{
		m_Shader->Bind();
		m_Texture->Bind(texture_slot);
		for (const auto& [name, param]:m_Paramters) {
			m_Shader->SetFloat(name, param);
		}
		m_Shader->SetVec4("color", m_Color);
	}

	/*void Material::setSpotLightRender(EulerSpotLight* light) {
		m_Shader->SetVec3("spotLight.ambient", light_material.ambient*light->color);
		m_Shader->SetVec3("spotLight.diffuse", light_material.diffuse*light->color);
		m_Shader->SetVec3("spotLight.specular", light_material.specular*light->color);
		m_Shader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(light->outerCutOff)));
		m_Shader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(light->cutOff)));
		m_Shader->SetVec3("spotLight.direction", light->direction);
		m_Shader->SetVec3("spotLight.position", light->transform.position);
		m_Shader->SetFloat("spotLight.constant", light->constant);
		m_Shader->SetFloat("spotLight.linear", light->linear);
		m_Shader->SetFloat("spotLight.quatratic", light->quatratic);
	}
	void Material::setPointLightRender(EulerPointLight* light) {
		m_Shader->SetVec3("pointLight.position", light->transform.position);
		m_Shader->SetVec3("pointLight.ambient", light_material.ambient*light->color);
		m_Shader->SetVec3("pointLight.diffuse", light_material.diffuse*light->color);
		m_Shader->SetVec3("pointLight.specular", light_material.specular*light->color);
		m_Shader->SetFloat("pointLight.constant", light->constant);
		m_Shader->SetFloat("pointLight.linear", light->linear);
		m_Shader->SetFloat("pointLight.quatratic", light->quatratic);
	}
	void Material::setDirLightRender(EulerDirLight* light) {
		m_Shader->SetVec3("dirLight.ambient", light_material.ambient*light->color);
		m_Shader->SetVec3("dirLight.diffuse", light_material.diffuse*light->color);
		m_Shader->SetVec3("dirLight.specular", light_material.specular*light->color);
		m_Shader->SetVec3("dirLight.direction", light->direction);
	}*/
}